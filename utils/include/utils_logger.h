#ifndef lHUOGUO_UTILS_LOGGER_H_
#define lHUOGUO_UTILS_LOGGER_H_

#include <string>
#include <chrono>
#include <cstring>
#include <atomic>
#include <vector>
#include <map>
#include <mutex>

namespace huoguo {
namespace utils {

#ifdef _WIN32

#define LOG_PRINT(level, ...)  LOGGER.log_message(LOG_LEVEL(level), __VA_ARGS__)
#define LOGGER                 huoguo::utils::Logger::logger
#define LOG_LEVEL(level)       huoguo::utils::Logger::LOG_##level, __FILE__, __LINE__, __FUNCTION__
#define LOG_BASE(level, ...)   LOG_PRINT(level, __VA_ARGS__)
#define LOG(level, fmt, ...)   LOG_BASE(level, fmt, __VA_ARGS__)

#define DebugL(fmt, ...) LOG(LEVEL_DEBUG, fmt, __VA_ARGS__)
#define TraceL(fmt, ...) LOG(LEVEL_TRACE, fmt, __VA_ARGS__)
#define InfoL(fmt,  ...) LOG(LEVEL_INFO,  fmt, __VA_ARGS__)
#define WarnL(fmt,  ...) LOG(LEVEL_WARN,  fmt, __VA_ARGS__)
#define ErrorL(fmt, ...) LOG(LEVEL_ERROR, fmt, __VA_ARGS__)
#define FatalL(fmt, ...) LOG(LEVEL_FATAL, fmt, __VA_ARGS__)
#else
#define LOG_PRINT(level, args...)  LOGGER.log_message(LOG_LEVEL(level), ##args)
#define LOGGER                     huoguo::utils::Logger::logger
#define LOG_LEVEL(level)           huoguo::utils::Logger::LOG_LEVEL_##level, strrchr(__FILE__, '/') + 1, __LINE__, __FUNCTION__
#define LOG_BASE(level, args...)  (huoguo::utils::Logger::LOG_LEVEL_##level>LOGGER.get_level()) ? (void)0 : LOG_PRINT(level, ##args)
#define LOG(level, fmt, args...)  (huoguo::utils::Logger::LOG_LEVEL_##level>LOGGER.get_level()) ? (void)0 : LOG_BASE(level, fmt, ##args)

#define DebugL(fmt, args...) LOG(DEBUG, fmt, ##args)
#define TraceL(fmt, args...) LOG(TRACE, fmt, ##args)
#define InfoL(fmt,  args...) LOG(INFO,  fmt, ##args)
#define WarnL(fmt,  args...) LOG(WARN,  fmt, ##args)
#define ErrorL(fmt, args...) LOG(ERROR, fmt, ##args)
#define FatalL(fmt, args...) LOG(FATAL, fmt, ##args)
#endif

#define TRACE_LEVEL huoguo::utils::Logger::LOG_LEVEL_TRACE

#define MIN_FILE_COUNT 0x01
#define DEF_FILE_COUNT 0x0F
#define MAX_FILE_COUNT 0xFF
#define MIN_FILE_SIZE  0x04000000
#define DEF_FILE_SIZE  0x10000000
#define MAX_FILE_SIZE  0x40000000

struct LogConfig {
    std::string logdir;
    std::string filename;
    std::string suffix;
    std::string level;
    // size_t file_count;
    size_t file_size;
    bool enable_color;
    bool enable_fileline;
    bool enable_function;
    LogConfig()
        // : file_count(DEF_FILE_COUNT),
        : level("INFO"),
          file_size(DEF_FILE_SIZE),
          enable_color(true),
          enable_fileline(false),
          enable_function(false) {}
};

class Logger {
public:
    enum LOG_LEVE {
        LOG_LEVEL_FATAL = 0,
        LOG_LEVEL_ERROR = 1,
        LOG_LEVEL_WARN  = 2,
        LOG_LEVEL_INFO  = 3,
        LOG_LEVEL_DEBUG = 4,
        LOG_LEVEL_TRACE = 5,
    };

public:
    void init(const LogConfig &config);
    // 0-FATAL, 1-ERROR, 2-WARN, 3-INFO, 4-DEBUG, 5-TRACE
    void set_level(LOG_LEVE level);
    void log_message(LOG_LEVE level, const char *filename, int line, const char *function, const char *format, ...);
public:
    static Logger logger;
    int get_level() const;
private:
    Logger();
    ~Logger();

    bool check_logdir(std::string &logdir);
    bool check_logfile(std::string &filename, time_t now = time(nullptr));
    bool reopen_logfile(const std::string &filename);
private:

    FILE *m_filep;
    int m_level;
    
    std::string m_logdir;
    std::string m_filename;
    std::string m_suffix;
    std::string m_current_filename;

    // size_t m_file_count;
    size_t m_file_size; 
    bool m_enable_color;

    std::atomic<bool> m_inited;
    bool m_has_logdir;
    bool m_has_logfile;

    size_t m_current_file_size;
    unsigned long m_current_file_index;
    time_t m_last_time;

    std::mutex m_mutex;
    bool m_enable_print_fileline;
    bool m_enable_print_function;
};

} // namespace utils
} // namespace huoguo

#endif // lHUOGUO_UTILS_LOGGER_H_