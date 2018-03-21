#include "secondary.h"
#include <ctime>
#include <string>

std::string Secondary::intToString(int number)
{
    int temp = number, size = 1;
    std::string str = "";
    while(temp)
    {
        size++;
        str += char((temp % 10) + 48);
        temp /= 10;
    }
    for(int i = 0, j = size-2; i < j; i++, j--)
    {
        std::swap(str[j], str[i]);
    }
    return str;
}

std::string Secondary::getToday()
{
    time_t seconds = time(nullptr);
    std::string date = "";
    tm* timeinfo = localtime(&seconds);
    date += intToString(timeinfo->tm_mday);
    date += "_";
    date += intToString(timeinfo->tm_mon + 1);
    date += "_";
    date += intToString(timeinfo->tm_year + 1900);
    return date;
}


std::string Secondary::getTime()
{
    time_t seconds = time(nullptr);
    std::string time = "";
    tm* timeinfo = localtime(&seconds);
    time += intToString(timeinfo->tm_hour);
    time += ":";
    time += intToString(timeinfo->tm_min);
    time += ":";
    time += intToString(timeinfo->tm_sec);
    return time;
}
