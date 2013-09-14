#ifndef Log_h
#define Log_h

#include <android/log.h>

static const char* tag = "Log";

class Log {
public:
    template <typename... Args>
    static void info(const char* fmt, const Args&... args) {
        __android_log_print(ANDROID_LOG_INFO, tag, fmt, args...);
    }
};

#endif /* Log_h */
