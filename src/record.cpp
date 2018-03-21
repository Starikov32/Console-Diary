#include "record.h"
#include <iostream>
#include <fstream>
#include <cstring>

Record::Record() : text("")
{
    Secondary secondary;
    time = secondary.getTime();
}

void Record::show()
{
    std::cout << std::endl << "----------" << std::endl;
    std::cout << *this;
    std::cout << "----------" << std::endl;
}

void Record::introduce()
{
    std::cout << "Enter the text entry >> ";
    getline(std::cin, text);
}

std::ostream & operator<<(std::ostream & os, const Record & record)
{
    os << record.time << std::endl;
    os << record.text << std::endl;
    return os;
}
