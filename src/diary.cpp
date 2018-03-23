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
    filesList = getList();
}

Diary::~Diary()
{
    std::ofstream fileList;
    fileList.open(listFile.c_str());
    for(const auto& file : filesList)
    {
        fileList << file << std::endl;
    }
    fileList.close();
}

bool Diary::addToList(const std::string & fileName)
{
    filesList.push_back(fileName);
    return true;
}

void Diary::showList()
{
    std::cout << "\n---------- List -----------\n\n";
    for(const auto& file : filesList)
    {
        std::cout << file << std::endl;
    }
    std::cout << "--------------------------\n";
}

bool Diary::deleteAll()
{
    for(const auto & file : filesList)
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
    for(const auto & file : filesList)
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
    if(std::find(filesList.begin(), filesList.end(), fileName) == filesList.end()) {
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
    filesList.erase(std::find(filesList.begin(), filesList.end(), fileName));
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
