#include "page.h"
#include <fstream>
#include <iostream>
#include "record.h"
#include "diary.h"
#include <cstring>

Page::Page(const std::string & filename) : fileName(filename)
{
    std::ofstream file;
    file.open(fileName.c_str(), std::ios::app);
    if(!file.is_open())
    {
        std::cout << "\nERROR: failed to open file " << fileName << "!\n\n";
    }
    file.close();
}

void Page::show()
{
    std::ifstream file;
    file.open(fileName.c_str());
    if(!file.is_open())
    {
        std::cout << "\nERROR: File for this date not found!\n\n";
        return;
    }
    std::string temp;
    std::cout << "\n---------- " << fileName << " ----------\n";
    while(!file.eof())
    {
        getline(file, temp);
        std::cout << temp << std::endl;
    }
    std::cout << "--------------------------------\n";
}

bool Page::addRecord(const Record & record)
{
    std::ofstream file;
    file.open(fileName.c_str(), std::ios::app);
    if(!file.is_open())
    {
        std::cout << "\nERROR: opening the file " << fileName << "!\n\n";
        return false;
    }
    file << record;
    file.close();
    return true;
}
