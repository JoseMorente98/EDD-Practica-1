#pragma once
#include <string>
using namespace std;
class LogChange
{
public:
    /*
       PROPIEDADES
   */
    LogChange();
    LogChange(string search, string replace, bool state, string word, int x, int y);
    virtual ~LogChange();
    int positionX;
    int positionY;
    string search;
    string replace;
    bool state;
    string word;
    LogChange* next;

    /*
        GETTER'S
    */
public:
    string getSearch() const;
    string getReplace() const;
    bool getState() const;
    string getWord() const;
    int getPositionX() const;
    int getPositionY() const;
    LogChange* getNext() const;

    /*
        SETTER'S
    */
public:
    void setSearch(string a);
    void setReplace(string a);
    void setState(bool a);
    void setWord(string a);
    void setPositionX(int a);
    void setPositionY(int a);
    void setNext(LogChange* a);
};
