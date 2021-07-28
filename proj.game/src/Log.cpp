#include "Log.hpp"

#if __ANDROID__
#include <android/log.h>
#else
#include <stdio.h>
#endif

namespace GoumzAndStuff {
void Log::debug(const std::string& msg) {
#if __ANDROID__
  __android_log_print(ANDROID_LOG_DEBUG, "goumz-and-stuff", "[DEBUG] %s",
                      msg.c_str());
#else
#endif
}

void Log::error(const std::string& msg) {
#if __ANDROID__
  __android_log_print(ANDROID_LOG_ERROR, "goumz-and-stuff", "[ERROR] %s",
                      msg.c_str());
#else
#endif
}
}  // namespace GoumzAndStuff