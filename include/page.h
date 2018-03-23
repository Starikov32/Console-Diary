#ifndef PAGE_H
#define PAGE_H

#include "record.h"
#include "diary.h"
#include <string>
#include <vector>

class Page
{
    public:
        explicit Page(const std::string & fileName);
        void show();
        bool addRecord(const Record & record);
    private:
        std::string fileName;
};

#endif // PAGE_H
