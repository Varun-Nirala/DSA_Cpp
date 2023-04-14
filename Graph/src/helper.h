#ifndef __HELPER_H__
#define __HELPER_H__

#include <iostream>
#include <string>
#include <sstream>

#define SAFE_RELEASE(x) if(x)\
                        {\
                            x->release();\
                            x = nullptr;\
                        }
                        
#define SAFE_DELETE(x) if(x)\
                        {\
                            delete x;\
                            x = nullptr;\
                        }

enum E_DIRECTION
{
    UNI_DIRECTIONAL = 0,
    BI_DIRECTIONAL
};

static void LOG_INFO(std::string func, int line, std::string msg)
{
    std::cout << "INFO :: " << func << "::" << line << " -> " << msg << "." << std::endl;
}

static void LOG_DEBUG(std::string func, int line, std::string msg)
{
    std::cout << "DEBUG :: " << func << "::" << line << " -> " << msg << "." << std::endl;
}

static void LOG_ERROR(std::string func, int line, std::string msg, int error_code)
{
    std::cout << "ERROR :: " << func << "::" << line << ":: " << error_code << " -> "<< msg << "." << std::endl;
}

static std::string DirectionEnumtoString(E_DIRECTION eDir)
{
    std::string rc;
    switch(eDir)
    {
        case UNI_DIRECTIONAL:
            rc = "UNI_DIRECTIONAL";
            break;
        case BI_DIRECTIONAL:
            rc = "BI_DIRECTIONAL";
            break;
        default:
            LOG_ERROR(__func__, __LINE__, "Error :: Wrong Direction Of Edge!!!", 1);
            rc = "Error :: Wrong Direction Of Edge!!!";
    }
    return rc;
}

template<typename T>    // For int, char, float, double and long
T ReadInput()
{
    T rc;
    std::string str;
    std::getline(std::cin, str);
    std::stringstream ss(str);
    ss >> rc;
    return rc;
}
#endif