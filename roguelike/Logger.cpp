
#include "Logger.h"

#ifdef LOG_STATS
void Logger::logStats(){
    SerialUSB.print("CPU : ");
    SerialUSB.print(gb.getCpuLoad());
    SerialUSB.print(" / RAM : ");
    SerialUSB.println(gb.getFreeRam());
}
#endif

void Logger::trace(String message)
{
#ifdef LOG_LEVEL
#if LOG_LEVEL < 0
    #ifdef LOG_STATS
	    SerialUSB.print(message);
		SerialUSB.print(" | ");
        logStats();
	#else
		SerialUSB.println(message);
    #endif
#endif
#endif
}
void Logger::debug(String message)
{
#ifdef LOG_LEVEL
#if LOG_LEVEL < 1
    #ifdef LOG_STATS
	    SerialUSB.print(message);
		SerialUSB.print(" | ");
        logStats();
	#else
		SerialUSB.println(message);
    #endif
#endif
#endif
}
void Logger::info(String message)
{
#ifdef LOG_LEVEL
#if LOG_LEVEL < 2
    #ifdef LOG_STATS
	    SerialUSB.print(message);
		SerialUSB.print(" | ");
        logStats();
	#else
		SerialUSB.println(message);
    #endif
#endif
#endif
}
void Logger::warn(String message)
{
#ifdef LOG_LEVEL
#if LOG_LEVEL < 3
    #ifdef LOG_STATS
	    SerialUSB.print(message);
		SerialUSB.print(" | ");
        logStats();
	#else
		SerialUSB.println(message);
    #endif
#endif
#endif
}
void Logger::error(String message)
{
#ifdef LOG_LEVEL
#if LOG_LEVEL < 4
    #ifdef LOG_STATS
	    SerialUSB.print(message);
		SerialUSB.print(" | ");
        logStats();
	#else
		SerialUSB.println(message);
    #endif
#endif
#endif
}
void Logger::fatal(String message)
{
#ifdef LOG_LEVEL
#if LOG_LEVEL < 5
    #ifdef LOG_STATS
	    SerialUSB.print(message);
		SerialUSB.print(" | ");
        logStats();
	#else
		SerialUSB.println(message);
    #endif
#endif
#endif
}
void Logger::critical(String message)
{
#ifdef LOG_LEVEL
#if LOG_LEVEL < 5
    #ifdef LOG_STATS
	    SerialUSB.print(message);
		SerialUSB.print(" | ");
        logStats();
	#else
		SerialUSB.println(message);
    #endif
#endif
#endif
}
