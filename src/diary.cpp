#include "diary.h"
#include "page.h"
#include "record.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstring>

Diary::Diary(const std::string & listFile, const std::string & recordExtension) : listFile(listFile), recordExtension(recordExtension)
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
    std::ofstream fileList;
    fileList.open(listFile.c_str(), std::ios::app);
    std::cout << "\n---------- Diary ----------\n\n";
    fileList.close();
}

bool Diary::addToList(const std::string & fileName)
{
    std::ofstream fileList;
    fileList.open(listFile.c_str(), std::ios::app);
    if(!fileList.is_open())
    {
        std::cout << "ERROR: list file not found!\n\n";
        return false;
    }
    fileList << fileName << std::endl;
    fileList.close();
    return true;
}

void Diary::showList()
{
    std::cout << "\n---------- List -----------\n\n";
    auto fileList = getList();
    for(const auto& file : fileList)
    {
        std::cout << file << std::endl;
    }
    std::cout << "--------------------------\n";
}

bool Diary::deleteAll()
{
    auto fileList = getList();
    for(const auto & file : fileList)
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
    auto fileList = getList();
    for(const auto & file : fileList)
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
    std::string fileName;
    fileName += secondary::getToday();
    Record record;
    record.introduce();
    auto fileList = getList();
    if(std::find(fileList.begin(), fileList.end(), fileName) == fileList.end()) {
        addToList(fileName);
    }
    Page page(fileName + recordExtension);
    return page.addRecord(record);
}

bool Diary::deletePage(std::string fileName)
{
    std::string forDelete = fileName;
    forDelete += recordExtension;
    std::ifstream fileCheck;
    fileCheck.open(forDelete);
    if(!fileCheck.is_open())
    {
        std::cout << "\nERROR: file " << forDelete << " not found!\n\n";
        return false;
    }
    fileCheck.close();
    std::remove(forDelete.c_str());
    std::ofstream tempFile;
    tempFile.open("temp.f");
    std::ifstream fileList;
    fileList.open(listFile.c_str());
    if(!fileList.is_open())
    {
        std::cout << "\nERROR: failed to open list file!\n\n";
        return false;
    }
    while(!fileList.eof())
    {
        std::string str;
        fileList >> str;
        fileList.get();
        if(str != fileName)
            tempFile << str << std::endl;
    }
    fileList.close();
    tempFile.close();
    std::remove(listFile.c_str());
    std::ofstream fileList1;
    std::ifstream tempFile1;
    tempFile1.open("temp.f");
    fileList1.open(listFile.c_str());
    if(!fileList1.is_open())
    {
        std::cout << "\nERROR: failed to open list file!\n\n";
        return false;
    }
    while(!tempFile1.eof())
    {
        std::string str;
        getline(tempFile1, str);
        fileList1 << str << std::endl;
    }
    tempFile1.close();
    fileList1.close();
    std::remove("temp.f");
    return true;
}

std::vector<std::string> Diary::getList()
{
    std::vector<std::string> files;
    std::ifstream fileList;
    fileList.open(listFile.c_str());
    if(!fileList.is_open())
    {
        std::cout << "ERROR: list file not found!\n\n";
        return {};
    }
    std::string tempStr;
    while(!fileList.eof())
    {
        getline(fileList, tempStr);
        files.push_back(tempStr);
    }
    fileList.close();
    files.shrink_to_fit();
    return files;
}
