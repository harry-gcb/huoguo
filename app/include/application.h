#ifndef HUOGOU_APP_APPLICATION_H_
#define HUOGOU_APP_APPLICATION_H_

#include <condition_variable>

namespace huoguo {
namespace app {

class Application {
public:
    Application(int argc, char *argv[]);
    int run();
private:  
    int init_option(int argc, char *argv[]);
    void init_config();
    void init_logs();
private:
    bool m_stop;
    std::condition_variable m_cv;
    std::mutex m_mutex;
    std::thread m_thread;
};

}
}

#endif // HUOGOU_APP_APPLICATION_H_