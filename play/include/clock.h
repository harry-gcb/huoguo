#ifndef HUOGUO_PLAY_CLOCK_H_
#define HUOGUO_PLAY_CLOCK_H_

namespace huoguo {
namespace play {

class Clock {
public:
public:
    double pts;           /* clock base */
    double pts_drift;     /* clock base minus time at which we updated the clock */
    double last_updated;
    double speed;
    int serial;           /* clock is based on a packet with this serial */
    int paused;
    int *queue_serial;    /* pointer to the current packet queue serial, used for obsolete clock detection */
} Clock;

}
}

#endif