#ifndef GUI_H
#define GUI_H

#include "diary.h"

class GUI
{
    public:
        GUI(const Diary & diary);
        void exec();
    private:
        Diary diary;

        void help();
        void cls();
};

#endif // GUI_H
