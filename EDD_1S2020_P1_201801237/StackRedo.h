#pragma once
#include "LogChange.h"
/*
	CTRL + Y
*/
class StackRedo
{
public:
    StackRedo();
    LogChange* top = NULL;
    void Push(LogChange* p);
    bool IsEmpty();
    LogChange* Pop();
    void Show();
    void Clear();
    void GenerateGraph(string nombre);
    virtual ~StackRedo();
};

