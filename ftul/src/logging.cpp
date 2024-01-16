#include <ftul/logging.h>

#include <ftul/fractal_common.h>

#include <stdio.h>
#include <time.h>

#include <sstream>
#include <string>

namespace Fractal {

    std::string get_time_formatted() {
        time_t unix_time;
        time(&unix_time);
        
        tm* time_info = localtime(&unix_time);

        char time_str[9];
        strftime(time_str, sizeof(time_str), "%H:%M:%S", time_info);

        return std::string(time_str);
    }

    std::string get_severity_str(FractalLogSeverity severity) {
        switch(severity) {
            case FRACTAL_LOG_DEBUG:
                return "DEBUG";
            case FRACTAL_LOG_INFO:
                return "INFO ";
            case FRACTAL_LOG_WARN:
                return "WARN ";
            case FRACTAL_LOG_ERROR:
                return "ERROR";
            case FRACTAL_LOG_ABORT:
                return "ABORT";
            default:
                return "UNKWN";
        }
    }

    const int PREFERRED_LOC_SIZE = 8;
    std::string get_readable_location(const char* location) {
        std::string str;

        str.reserve(PREFERRED_LOC_SIZE);
        str += location;

        while(str.length() < PREFERRED_LOC_SIZE) {
            str += ' ';
        }

        return str;
    }

    void write_log(const char* message, FractalLogSeverity severity, const char* location) {
        if(severity == FRACTAL_LOG_DEBUG) {
            return;
        }

        std::stringstream str_builder;

        str_builder << "[" << get_time_formatted() << 
                     "] [" << get_severity_str(severity) << 
                     "] [" << get_readable_location(location) << "] " 
                           << message << '\n';

        printf("%s", str_builder.str().c_str());

        if(severity == FRACTAL_LOG_ABORT) {
            fractal_abort();
        }
    }
    
    void write_log(const std::string& message, FractalLogSeverity severity, const char* location) {
        write_log(message.c_str(), severity, location);
    }


}