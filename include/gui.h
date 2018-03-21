#ifndef GUI_H
#define GUI_H

#include "diary.h"

class GUI
{
    public:
        GUI(const Diary & diary_);
        void exec();
    private:
        Diary diary;

        void help();
};

#endif // GUI_H
