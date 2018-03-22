#include "diary.h"
#include "page.h"
#include "record.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <algorithm>
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
    auto files = getList();
    for(const auto& file : files)
    {
        std::cout << file << std::endl;
    }
    std::cout << "--------------------------\n";
}

bool Diary::deleteAll()
{
    auto files = getList();
    for(const auto & file : files)
    {
        std::remove((file + recordExtension).c_str());
    }
    std::ofstream file;
    file.open(listFile);
    file.close();
    return true;
}

void Diary::showAll()
{
    auto files = getList();
    for(const auto & file : files)
    {
        showPage(file);
    }
}

void Diary::showPage(std::string fileName)
{
    if(fileName.length() == 0) {
        return;
    }
    fileName += recordExtension;
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
    auto files = getList();
    if(std::find(files.begin(), files.end(), fileName) == files.end()) {
        addToList(fileName);
    }
    Page page(fileName + recordExtension);
    return page.addRecord(record);
}

bool Diary::deletePage(std::string fileName)
{
    std::string forDelete = fileName;
    forDelete += recordExtension;
    std::ifstream file_;
    file_.open(forDelete);
    if(!file_.is_open())
    {
        std::cout << "\nERROR: file " << forDelete << " not found!\n\n";
        return false;
    }
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
            temp << str << std::endl;
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
    std::remove("temp.f");
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
        return {};
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
