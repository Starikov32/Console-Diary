#include "diary.h"
#include "page.h"
#include "record.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <cstring>

Diary::Diary(const std::string & listfile, const std::string & recordextension) : listFile(listfile), recordExtension(recordextension)
{
    std::ifstream file;
    file.open(listFile.c_str());
    if(!file.is_open())
    {
        std::cout << "\nYou created a new Diary!\n";
        std::cout << "Your list file: " << listFile << std::endl;
        std::cout << "Extensions of your page files: " << recordExtension << "\n\n";
    }
    file.close();
    std::ofstream listF;
    listF.open(listFile.c_str(), std::ios::app);
    std::cout << "\n---------- Diary ----------\n\n";
    listF.close();
}

bool Diary::addToList(const std::string & fileName)
{
    std::ofstream listF;
    listF.open(listFile.c_str(), std::ios::app);
    if(!listF.is_open())
    {
        std::cout << "ERROR: list file not found!\n\n";
        return false;
    }
    listF << fileName << std::endl;
    listF.close();
    return true;
}

void Diary::showList()
{
    std::cout << "\n---------- List -----------\n\n";
    std::vector<std::string> listF = getList();
    for(int i = 0; i < listF.size(); ++i)
    {
        std::cout << listF[i] << std::endl;
    }
    std::cout << "--------------------------\n";
}

bool Diary::deleteAll()
{
    std::vector<std::string> listF = getList();
    for(int i = 0; i < listF.size(); ++i)
    {
        std::remove((listF[i] + recordExtension).c_str());
    }
    std::ofstream file;
    file.open(listFile);
    file.close();
    return true;
}

void Diary::showAll()
{
    std::vector<std::string> listF = getList();
    for(int i = 0; i < listF.size(); ++i)
    {
        showPage(listF[i]);
    }
}

void Diary::showPage(std::string fileName)
{
    fileName += recordExtension;
    if(fileName.size() <= recordExtension.size())
        return;
    std::ifstream file;
    file.open(fileName.c_str());
    if(!file.is_open())
    {
        std::cout << "\nERROR: file " << fileName << " not found!\n\n";
        return;
    }
    file.close();
    Page page(fileName);
    page.show();
}

bool Diary::newRecord()
{
    Secondary secondary;
    std::string fileName;
    fileName += secondary.getToday();
    Record record;
    record.introduce();
    std::vector<std::string> files = getList();
    for(int i = 0; i < files.size(); ++i)
    {
        if(files[i] == fileName)
            break;
        else if(i == files.size()-1)
            addToList(fileName);
    }
    Page page(fileName + recordExtension);
    return page.addRecord(record);
}

bool Diary::deletePage(std::string fileName)
{
    std::string forDelete = fileName;
    forDelete += recordExtension;
    std::remove(forDelete.c_str());
    std::ofstream temp;
    temp.open("temp.f");
    std::ifstream read;
    read.open(listFile.c_str());
    if(!read.is_open())
    {
        std::cout << "\nERROR: failed to open list file!\n\n";
        return false;
    }
    while(!read.eof())
    {
        std::string str;
        read >> str;
        read.get();
        if(str != fileName)
            temp << str;
    }
    read.close();
    temp.close();
    std::remove(listFile.c_str());
    std::ofstream listF;
    std::ifstream temp1;
    temp1.open("temp.f");
    listF.open(listFile.c_str());
    if(!listF.is_open())
    {
        std::cout << "\nERROR: failed to open list file!\n\n";
        return false;
    }
    while(!temp1.eof())
    {
        std::string str;
        getline(temp1, str);
        listF << str;
    }
    temp1.close();
    listF.close();
    return true;
}

std::vector<std::string> Diary::getList()
{
    std::vector<std::string> files;
    files.reserve(10);
    std::ifstream listF;
    listF.open(listFile.c_str());
    if(!listF.is_open())
    {
        std::cout << "ERROR: list file not found!\n\n";
        return std::vector<std::string>(0);
    }
    std::string temp;
    while(!listF.eof())
    {
        getline(listF, temp);
        files.push_back(temp);
    }
    listF.close();
    files.shrink_to_fit();
    return files;
}
