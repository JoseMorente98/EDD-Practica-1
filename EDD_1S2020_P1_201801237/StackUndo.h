#pragma once
#include "LogChange.h"
/*
	CTRL + Z
*/
class StackUndo
{
public:
    StackUndo();
    LogChange* top = NULL;
    void Push(LogChange* p);
    bool IsEmpty();
    LogChange* Pop();
    void Show();
    void Clear();
    virtual ~StackUndo();
};

