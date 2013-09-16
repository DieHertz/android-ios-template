#ifndef LogIos_h
#define LogIos_h

#include <cstdio>

class Log {
public:
    template <typename... Args>
    static void info(const char* fmt, const Args&... args) {
        std::printf(fmt, args...);
        std::printf("\n");
    }
};

#endif /* LogIos_h */
