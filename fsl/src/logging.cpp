#include <fsl/common.h>
#include <fsl/logging.h>
#include <fsl/std.h>

namespace Fractal {

    std::string get_time_formatted() {
        std::time_t unix_time;
        std::time(&unix_time);
        
        std::tm* time_info = std::localtime(&unix_time);

        char time_str[9];
        std::strftime(time_str, sizeof(time_str), "%H:%M:%S", time_info);

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

        const int MAX_MSG_LEN = 4096; 
        char msg_buf[MAX_MSG_LEN];

        // I eventually need to reduce allocations here as well
        std::snprintf(msg_buf, MAX_MSG_LEN, 
            "[%s] [%s] [%s] %s\n", 
            get_time_formatted().c_str(), 
            get_severity_str(severity).c_str(), 
            get_readable_location(location).c_str(), 
            message
        );

        printf("%s", msg_buf);

        if(severity == FRACTAL_LOG_ABORT) {
            fractal_abort();
        }
    }
    
    void write_log(const std::string& message, FractalLogSeverity severity, const char* location) {
        write_log(message.c_str(), severity, location);
    }


}