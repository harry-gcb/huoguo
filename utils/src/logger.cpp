#include <ctime>
#include <cstdarg>
#include <filesystem>
#include <iostream>
#include "logger.h"
#include "process.h"
#include "strutils.h"

namespace huoguo {
namespace utils {

Logger Logger::logger;
static const char *const log_level_names[] = {"FATAL", "ERROR", "WARN", "INFO", "DEBUG", "TRACE"};
static const char *const log_level_begin[] = {"\033[31m", "\033[35m", "\033[33m", "\033[37m", "\033[32m", "\033[36m"};
static const char *const log_level_end[] = {"\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m", "\033[0m"};
// static const char *const log_level_begin[] = {"\033[41m", "\033[45m", "\033[43m", "\033[47m", "\033[42m", "\033[46m"};

#define LOG_MESSAGE_DATA_SIZE 4096
#define LOG_MESSAGE_TIME_SIZE 1024
#define LOG_FILENAME_LENGTH   1024 

Logger::Logger() 
    : m_filep(stdout),
      m_level(LOG_LEVEL_INFO),
    //   m_file_count(DEF_FILE_COUNT),
      m_file_size(DEF_FILE_SIZE),
      m_enable_color(true),
      m_inited(false),
      m_has_logdir(false),
      m_has_logfile(false),
      m_current_file_size(0),
      m_current_file_index(0) {
        // m_filep = fopen("test.log", "w+");
}

Logger::~Logger() {
    if (m_has_logfile) {
        fflush(m_filep);
        fclose(m_filep);
        m_filep = nullptr;
        m_has_logfile = false;
    }
}

void Logger::init(const LogConfig &config) {
    bool expired = false;
    if (m_inited.compare_exchange_strong(expired, true)) {
        m_logdir = config.logdir;
        m_filename = config.filename;
        m_suffix = config.suffix;
        // m_file_count = (config.file_count < MIN_FILE_COUNT || config.file_count > MAX_FILE_COUNT) ? 
        //             m_file_count : config.file_count;
        m_file_size = (config.file_size < MIN_FILE_COUNT || config.file_size > MAX_FILE_SIZE) ?
                    m_file_size : config.file_size;
        m_enable_color = config.enable_color;
        if (m_filename.empty()) return;
        m_has_logdir = check_logdir(m_logdir);
        m_has_logfile = check_logfile(m_filename);
    }
}

int Logger::get_level() const {
    return m_level;
}

void Logger::set_level(LOG_LEVE level) {
    m_level = level;
}

bool Logger::check_logdir(std::string &logdir) {
    std::error_code ec;
    if (logdir.empty()) {
        INFO("logdir is empty");
        return false;
    }
    if (!std::filesystem::exists(logdir) && !std::filesystem::create_directory(logdir)) {
        WARN("logdir[%s] not exists and can't create", logdir.c_str());
        return false;
    }
    if (!std::filesystem::is_directory(logdir)) {
        WARN("logdir[%s] is not a directory", logdir.c_str());
        return false;
    }
    std::filesystem::permissions(logdir, std::filesystem::perms::owner_write, std::filesystem::perm_options::add, ec);
    if (ec.value()) {
        ERROR("logdir[%s] can't be accessed", logdir.c_str());
        return false;
    }
    return true;
}

bool Logger::check_logfile(std::string &logfile, time_t now) {
    if (logfile.empty()) {
        INFO("logfile is empty");
        return false;
    }
    m_last_time = now;
    tm *tm = localtime(&now);
    char filename[LOG_FILENAME_LENGTH] = { 0 };
    if (m_has_logdir) {
        if (ends_with(m_logdir, "/")) {
            snprintf(filename, sizeof(filename), "%s%s", m_logdir.c_str(), logfile.c_str());
        } else {
            snprintf(filename, sizeof(filename), "%s/%s", m_logdir.c_str(), logfile.c_str());
        }
    } else {
        snprintf(filename, sizeof(filename), "%s", logfile.c_str());
    }
    snprintf(filename + strlen(filename), sizeof(filename) - strlen(filename), "_%04d-%02d-%02d_%d_%02lu", 
             tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday, getpid(), m_current_file_index++);

    if (!m_suffix.empty()) {
        snprintf(filename + strlen(filename), sizeof(filename) - strlen(filename), ".%s", m_suffix.c_str());
    }
    return reopen_logfile(std::string(filename));
}

bool Logger::reopen_logfile(const std::string &filename) {
    m_filep = freopen(filename.c_str(), "w+", m_filep);
    if (!m_filep) {
        return false;
    }
    if (!m_has_logfile) {
        fclose(stderr);
    }
    m_current_filename = filename;
    return true;
}

void Logger::log_message(LOG_LEVE level, const char *filename, int line, const char *function, const char *format, ...) {
    if (level > m_level) {
        return;
    }

    auto now = std::chrono::system_clock::now();
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()) % 1000000;
    auto time = std::chrono::system_clock::to_time_t(now);
    tm *tm = std::localtime(&time);
    char data[LOG_MESSAGE_DATA_SIZE] = { 0 };

    va_list args;
    va_start(args, format);
    vsnprintf(data, LOG_MESSAGE_DATA_SIZE, format, args);
    va_end(args);

    char buff[LOG_MESSAGE_DATA_SIZE + LOG_MESSAGE_TIME_SIZE] = { 0 };
    size_t size = 0;
    if (m_enable_color) {
        size = snprintf(buff, sizeof(buff),"%s%04d-%02d-%02d %02d:%02d:%02d.%-6ld %-5s %ld [%s:%d %s] %s%s\n",
        log_level_begin[level], tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
        tm->tm_hour, tm->tm_min, tm->tm_sec, us.count(),
        log_level_names[level], pthread_self(), filename, line, function, data, log_level_end[level]);

    } else {
        size = snprintf(buff, sizeof(buff),"%04d-%02d-%02d %02d:%02d:%02d.%-6ld %-5s %ld [%s:%d %s] %s\n",
        tm->tm_year+1900, tm->tm_mon+1, tm->tm_mday,
        tm->tm_hour, tm->tm_min, tm->tm_sec, us.count(),
        log_level_names[level], pthread_self(), filename, line, function, data);
    }
    if (tm->tm_hour == 0 && tm->tm_min ==0 && tm->tm_sec == 0 && m_has_logfile && m_last_time != time) {
        std::lock_guard<std::mutex> guard(m_mutex);
        if (m_last_time != time) {
            m_current_file_index = 0;
            check_logfile(m_filename, time);
            m_current_file_size = 0;
        }
    }
    m_current_file_size += fwrite(buff, size, 1, m_filep);
    if (m_current_file_size > m_file_size) {
        std::lock_guard<std::mutex> guard(m_mutex);
        if (m_current_file_size > m_file_size) {
            check_logfile(m_filename, time);
            m_current_file_index = 0;
        }
    }
}

} // namespace utils
} // namespace huoguo