#include "Character.h"
#include <stdio.h>

Character::Character()
{
}
Character::Character(char c, int x, int y)
{
    character = c;
    positionX = x;
    positionY = y;
    next = previous = NULL;
}
Character::~Character()
{
}

/*
    GETTER'S
 */
char Character::getCharacter() const { return character; }
int Character::getPositionX() const { return positionX; }
int Character::getPositionY() const { return positionY; }
Character* Character::getNext() const { return next; }
Character* Character::getPrevious() const { return previous; }

/*
    SETTER'S
*/
void Character::setCharacter(char a) { character = a; }
void Character::setPositionX(int a) { positionX = a; }
void Character::setPositionY(int a) { positionY = a; }
void Character::setNext(Character* a) { next = a; }
void Character::setPrevious(Character* a) { previous = a; }

