#ifndef DIARY_H
#define DIARY_H

#include "secondary.h"
#include <string>
#include <vector>

class Diary
{
    public:
        Diary(const std::string & listfile, const std::string & recordextension);
        void showList();
        bool deleteAll();
        void showAll();
        void showPage(std::string fileName);
        bool newRecord();
        bool deletePage(std::string fileName);
    private:
        std::string listFile;
        std::string recordExtension;

        bool addToList(const std::string & fileName);
        std::vector<std::string> getList();
};

#endif // DIARY_H
