/**
 * @file log.h
 * @author anonymous (undefined)
 * @brief Enable logging system based on SEGGER RTT Technology
 * @version 0.1
 * @date 2025-04-18
 * 
 * @copyright Copyright (c) 2025
 * 
 */


#ifndef LOG_H
#define LOG_H

// #define LOG_EN

#ifdef LOG_EN
    #include <SEGGER_RTT.h>
#endif


#ifdef LOG_EN
    #define LOG(...) SEGGER_RTT_printf(0, __VA_ARGS__)
#else
    #define LOG(...) __NOP()
#endif


#endif