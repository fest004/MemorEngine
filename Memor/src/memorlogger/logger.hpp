#include <spdlog/spdlog.h>
#define MEMOR_DEFAULT_LOGGER_NAME "MemorLogger"

#ifndef MEMOR_CONFIG_RELEASE

// Different levels of logging, from general info to critical erros

#define MemorTrace(...)                                                        \
  if (spdlog::get(MEMOR_DEFAULT_LOGGER_NAME) != nullptr) {                     \
    spdlog::get(MEMOR_DEFAULT_LOGGER_NAME)->trace(__VA_ARGS__);                \
  }
#define MemorDebug(...)                                                        \
  if (spdlog::get(MEMOR_DEFAULT_LOGGER_NAME) != nullptr) {                     \
    spdlog::get(MEMOR_DEFAULT_LOGGER_NAME)->debug(__VA_ARGS__);                \
  }
#define MemorInfo(...)                                                         \
  if (spdlog::get(MEMOR_DEFAULT_LOGGER_NAME) != nullptr) {                     \
    spdlog::get(MEMOR_DEFAULT_LOGGER_NAME)->info(__VA_ARGS__);                 \
  }
#define MemorWarn(...)                                                         \
  if (spdlog::get(MEMOR_DEFAULT_LOGGER_NAME) != nullptr) {                     \
    spdlog::get(MEMOR_DEFAULT_LOGGER_NAME)->warn(__VA_ARGS__);                 \
  }
#define MemorError(...)                                                        \
  if (spdlog::get(MEMOR_DEFAULT_LOGGER_NAME) != nullptr) {                     \
    spdlog::get(MEMOR_DEFAULT_LOGGER_NAME)->error(__VA_ARGS__);                \
  }
#define MemorCritical(...)                                                     \
  if (spdlog::get(MEMOR_DEFAULT_LOGGER_NAME) != nullptr) {                     \
    spdlog::get(MEMOR_DEFAULT_LOGGER_NAME)->critical(__VA_ARGS__);             \
  }
#else
// Disable logging for release builds
#define MemorTrace(...) (void)0
#define MemorDebug(...) (void)0
#define MemorInfo(...) (void)0
#define MemorWarn(...) (void)0
#define MemorError(...) (void)0
#define MemorCritical(...) (void)0
#endif
