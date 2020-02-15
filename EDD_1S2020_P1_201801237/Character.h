#pragma once
class Character
{
    /*
        PROPIEDADES
    */
public:
    int positionX;
    int positionY;
    char character;
    Character* next;
    Character* previous;

public:
    Character();
    Character(char c, int x, int y);
    virtual ~Character();

    /*
        GETTER'S
    */
public:
    char getCharacter() const;
    int getPositionX() const;
    int getPositionY() const;
    Character* getNext() const;
    Character* getPrevious() const;

    /*
        SETTER'S
    */
public:
    void setCharacter(char a);
    void setPositionX(int a);
    void setPositionY(int a);
    void setNext(Character* a);
    void setPrevious(Character* a);
    
   

};

