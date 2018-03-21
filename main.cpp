#include "page.h"
#include "record.h"
#include "diary.h"
#include "gui.h"
#include "secondary.h"
#include <iostream>

int main()
{
    std::string listFile;
    std::string extension;
    std::cout << "Enter list file of diary >> ";
    std::cin >> listFile;
    std::cin.sync();
    std::cout << "Enter extension of records >> ";
    std::cin >> extension;
    std::cin.sync();
    Diary diary(listFile, extension);
    GUI gui(diary);
    gui.exec();
    return 0;
}
