#ifndef __TIMER007_H__
#define __TIMER007_H__

#include <iostream>
#include <chrono>

#include "Common/logger.h"

namespace ns_Util
{
class Timer
{
public:
    inline void start() { m_start = std::chrono::high_resolution_clock::now(); }

    inline std::chrono::milliseconds getElapsedMS() const
    {
        const auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(end - m_start);
    }

    inline void print(const std::string &msg) const
    {
        Logger::LOG_MSG(msg, getElapsedMS().count(), " ms.");
    }
private:
    std::chrono::high_resolution_clock::time_point      m_start;
};
}

#endif //#ifndef __TIMER007_H__