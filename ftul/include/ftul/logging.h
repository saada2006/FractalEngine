#ifndef FTUL_LOGGING_H
#define FTUL_LOGGING_H

#ifndef FRACTAL_LOGGING_LOCATION
#define FRACTAL_LOGGING_LOCATION "Unknown"
#endif

#include <string>

namespace Fractal {

    enum FractalLogSeverity {
        FRACTAL_LOG_DEBUG, // for debug information
        FRACTAL_LOG_INFO, // for general info that should be printed to the screen
        FRACTAL_LOG_WARN, // for possibly concerning problems
        FRACTAL_LOG_ERROR, // for errors we can recover from
        FRACTAL_LOG_ABORT, // for errors we cannot recover from (this will abort program execution)
    };

    void write_log(const char* message, FractalLogSeverity severity = FRACTAL_LOG_INFO, const char* location = FRACTAL_LOGGING_LOCATION);
    void write_log(const std::string& message, FractalLogSeverity severity = FRACTAL_LOG_INFO, const char* location = FRACTAL_LOGGING_LOCATION);

}

#endif