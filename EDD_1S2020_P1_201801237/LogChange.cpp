#include "LogChange.h"

LogChange::LogChange()
{
}

LogChange::LogChange(string search, string replace, bool state, string word, int x, int y)
{
    this->search = search;
    this->replace = replace;
    this->state = state;
    this->positionX = x;
    this->positionY = y;
    this->next = NULL;
}

LogChange::~LogChange()
{
}

/*
    GETTER'S
 */
string LogChange::getSearch() const { return search; }
string LogChange::getReplace() const { return replace; }
bool LogChange::getState() const { return state; }
string LogChange::getWord() const { return word; }
int LogChange::getPositionX() const { return positionX; }
int LogChange::getPositionY() const { return positionY; }
LogChange* LogChange::getNext() const { return next; }

/*
    SETTER'S
*/
void LogChange::setSearch(string a) { search = a; }
void LogChange::setReplace(string a) { replace = a; }
void LogChange::setState(bool a) { state = a; }
void LogChange::setWord(string a) { word = a; }
void LogChange::setPositionX(int a) { positionX = a; }
void LogChange::setPositionY(int a) { positionY = a; }
void LogChange::setNext(LogChange* a) { next = a; }

