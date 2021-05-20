#include <stdio.h>
#include <stdarg.h>
#include "logger.h"

namespace logger{
    void log(int mode, const char* file, int line, const char* time, const char* fmt, ...){
        const char txt_modes[3][8] = {"INFO", "WARNING", "ERROR"};
        const int color_modes[3] = {37, 33, 31};
        if (mode > 2) {
            ERR("Invalid log mode [mode = %d]", mode);
            return;
        }

        char buff[4096];
        va_list args;
        va_start(args, fmt);
        vsprintf(buff, fmt, args);
        va_end(args);

        printf("\033[%dm([%s - %s]: %s:%d) %s\n\033[39m", color_modes[mode], txt_modes[mode], time, file, line, buff);
    }
}
