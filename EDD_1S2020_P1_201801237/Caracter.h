#pragma once
#include <iostream>

class Caracter
{
protected:
    char dato;
    Caracter* adelante;
    Caracter* atras;
public:
    Caracter(char t)
    {
        dato = t;
        adelante = atras = NULL;
    }

    char getDato() const { return dato; }

    Caracter* getSiguiente() const { return adelante; }

    Caracter* getAnterior() const { return atras; }

    void setSiguiente(Caracter* a) { adelante = a; }

    void setAnterior(Caracter* a) { atras = a; }
};