#ifndef INCLUDE_LOG
#define INCLUDE_LOG
#ifndef TESTING
    #define TESTING 0
#endif
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#endif
