#ifndef __LOGGER007_H__
#define __LOGGER007_H__

#include <iostream>
#include <type_traits>

namespace ns_Util
{
class Logger
{
public:
#ifndef DEBUG
    template<typename T>
    static inline void LOG_INFO(const T &last)
    {
        if constexpr (std::is_same_v<T, std::wstring> || std::is_convertible_v<T, wchar_t const*>)
        {
            std::wcerr << last;
        }
        else
        {
            std::cerr << last;
        }
    }

    template<typename T>
    static inline void LOG_ERROR(const T& last)
    {
        if constexpr (std::is_same_v<T, std::wstring> || std::is_convertible_v<T, wchar_t const*>)
        {
            std::wcerr << last;
        }
        else
        {
            std::cerr << last;
        }
    }

    template<typename T, typename ... Args>
    static inline void LOG_INFO(const T &first, const Args& ... args)
    {
        if constexpr (std::is_same_v<T, std::wstring> || std::is_convertible_v<T, wchar_t const*>)
        {
            std::wcerr << first;
        }
        else
        {
            std::cerr << first;
        }
        LOG_INFO(args ...);
    }

    template<typename T, typename ... Args>
    static inline void LOG_ERROR(const T &first, const Args& ... args)
    {
        if constexpr (std::is_same_v<T, std::wstring> || std::is_convertible_v<T, wchar_t const*>)
        {
            std::wcerr << first;
        }
        else
        {
            std::cerr << first;
        }
        LOG_ERROR(args ...);
    }

    template<typename ... Args>
    static inline void LOG_INFO(const Args& ... args)
    {
        std::cerr << "INFO  : ";
        LOG_INFO(args ...);
    }

    template<typename ... Args>
    static inline void LOG_ERROR(const Args& ... args)
    {
        std::cerr << "ERROR : ";
        LOG_ERROR(args ...);
    }
#else
    template<typename T>
    static inline void LOG_INFO(const T &last) { ; }

    template<typename T>
    static inline void LOG_ERROR(const T &last) { ; }

    template<typename T, typename ... Args>
    static inline void LOG_INFO(const T &first, const Args& ... args) { ; }

    template<typename T, typename ... Args>
    static inline void LOG_ERROR(const T &first, const Args& ... args) { ; }
#endif

    template<typename T>
    static inline void LOG_MSG(const T &last)
    {
        if constexpr (std::is_same_v<T, std::wstring> || std::is_convertible_v<T, wchar_t const*>)
        {
            std::wcout << last;
        }
        else
        {
            std::cout << last;
        }
    }

    template<typename T, typename ... Args>
    static inline void LOG_MSG(const T &first, const Args& ... args)
    {
        if constexpr (std::is_same_v<T, std::wstring> || std::is_convertible_v<T, wchar_t const*>)
        {
            std::wcout << first;
        }
        else
        {
            std::cout << first;
        }
        LOG_MSG(args ...);
    }

    static inline void LOG_RESULT(const size_t totalTestCases, const size_t passCount, const std::string &msg)
    {
        if (totalTestCases == passCount)
        {
            LOG_MSG("Test :: ", msg, " PASS!\n");
        }
        else
        {
            LOG_MSG("Test :: ", msg, " FAIL! Fail count = ", totalTestCases - passCount, '\n');
        }
        LOG_MSG("        Total Test Cases  : ", totalTestCases, ", Passed Test Cases : ", passCount, '\n');
    }
};
}

#endif //#ifndef __LOGGER007_H__