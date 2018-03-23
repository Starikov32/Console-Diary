#include "secondary.h"
#include <ctime>
#include <string>
#include <cstdio>

namespace secondary
{
    std::string intToString(int value)
    {
        char a[100];
        sprintf(a, "%i", value);
        return a;
    }

    std::string getToday()
    {
        time_t seconds = time(nullptr);
        std::string date = "";
        tm* timeInfo = localtime(&seconds);
        date += intToString(timeInfo->tm_mday);
        date += "_";
        date += intToString(timeInfo->tm_mon + 1);
        date += "_";
        date += intToString(timeInfo->tm_year + 1900);
        return date;
    }

    std::string getTime()
    {
        time_t seconds = time(nullptr);
        std::string time = "";
        tm* timeInfo = localtime(&seconds);
        time += intToString(timeInfo->tm_hour);
        time += ":";
        time += intToString(timeInfo->tm_min);
        time += ":";
        time += intToString(timeInfo->tm_sec);
        return time;
    }
} // namespace secondary
