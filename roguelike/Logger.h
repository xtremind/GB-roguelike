#ifndef LOGGER
#define LOGGER

#include <Gamebuino-Meta.h>

/**
 * define LOG_LEVEL variable :
 *  - -1 : TRACE
 *  -  0 : DEBUG
 *  -  1 : INFO
 *  -  2 : WARN
 *  -  3 : ERROR
 *  -  4 : FATAL
 *  -  5 : CRITICAL
*/
class Logger
{
private:
    static void logStats();
public:
    static void trace(String message);
    static void debug(String message);
    static void info(String message);
    static void warn(String message);
    static void error(String message);
    static void fatal(String message);
    static void critical(String message);
};

#endif