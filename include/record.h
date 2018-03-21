#ifndef RECORD_H
#define RECORD_H

#include "secondary.h"
#include <iostream>
#include <string>

class Record
{
    public:
        Record();
        void show();
        void introduce();
        friend std::ostream & operator<<(std::ostream & os, const Record & record);
    private:
        std::string time;
        std::string text;
};

#endif // RECORD_H
