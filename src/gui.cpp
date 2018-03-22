#include "gui.h"
#include <iostream>
#include "diary.h"
#include <windows.h>

GUI::GUI(const Diary & diary_) : diary(diary_) {}

void GUI::cls()
{
    #ifdef _WIN32

    system("cls");

    #else
    system("clear");
    #endif // defined
}

void GUI::exec()
{
    while(true)
    {
        std::string command;
        std::cout << "Enter command >> ";
        std::cin >> command;
        std::cin.sync();
        if(command == "cls" || command == "clear") {
            cls();
        }
        else if(command == "help") {
            help();
        }
        else if(command == "new") {
            if(!diary.newRecord()) {
                std::cout << "\nERROR: failed to add a new record!\n\n";
            }
        }
        else if(command == "read")
        {
            Secondary secondary;
            std::string subCommand;
            std::cout << "Enter subCommand >> ";
            std::cin >> subCommand;
            std::cin.sync();
            if(subCommand == "all") {
                diary.showAll();
            }
            else if(subCommand == "today") {
                diary.showPage(secondary.getToday());
            }
            else {
                diary.showPage(subCommand);
            }
        }
        else if(command == "list") {
            diary.showList();
        }
        else if(command == "delete")
        {
            Secondary secondary;
            std::string subCommand;
            std::cout << "Enter subCommand >> ";
            std::cin >> subCommand;
            std::cin.sync();
            if(subCommand == "all") {
                if(!diary.deleteAll()) {
                    std::cout << "\nERROR: failed to delete all records in diary!\n\n";
                } else {
                    std::cout << "Delete successful!\n";
                }
            }
            else if(subCommand == "today") {
                if(!diary.deletePage(secondary.getToday())) {
                    std::cout << "\nERROR: failed to delete today records!\n\n";
                } else {
                    std::cout << "Delete successful!\n";
                }
            }
            else {
                if(!diary.deletePage(subCommand)) {
                    std::cout << "\nERROR: failed to delete " << subCommand << " records!\n\n";
                } else {
                    std::cout << "Delete successful!\n";
                }
            }
        }
        else if(command == "exit" || command == "quit") {
            break;
        }
        else {
            std::cout << "Command not found. Enter \"help\" for show all commands!\n";
        }
    }
    std::cout << "\n\n---------- Diary ----------\n\n";
}

void GUI::help() {
  std::cout <<
    "help -> show this message\n"
    "new -> create new record for this day\n"
    "read\n"
    "    all -> show all records in the diary\n"
    "    today -> show all records for today\n"
    "    date -> format(day_month_year); show all records for entered date\n"
    "delete\n"
    "    all -> delete all records in the diary\n"
    "    today -> delete all records for today\n"
    "    date -> format(day_month_year); delete all records for entered date\n"
    "list -> displays a list of dates in which records were made\n"
    "clear, cls -> clear the console\n"
    "quit, exit -> exit from Diary!\n";
}
