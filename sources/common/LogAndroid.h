#ifndef LogAndroid_h
#define LogAndroid_h

#include <android/log.h>

namespace {
    const char* tag = "Log";
}

class Log {
public:
    template <typename... Args>
    static void info(const char* fmt, const Args&... args) {
        __android_log_print(ANDROID_LOG_INFO, tag, fmt, args...);
    }
};

#endif /* LogAndroid_h */
