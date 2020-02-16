#pragma once
#include "LogChange.h"
/*
	CTRL + Y
*/
class StackRedo
{
    StackRedo();
    LogChange* top = NULL;
    void Push(LogChange* p);
    bool IsEmpty();
    LogChange* Pop();
    void Show();
    void Clear();
    virtual ~StackRedo();
};

