#ifndef Log_h
#define Log_h

#ifdef __ANDROID__
#include "LogAndroid.h"
#else
#include "LogIos.h"
#endif

#endif /* Log_h */
