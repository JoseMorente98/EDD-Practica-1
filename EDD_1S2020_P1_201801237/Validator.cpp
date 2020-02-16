#include "Validator.h"

bool Validator::IsDigit(std::string cadena)
{
    for (size_t i = 0; i < cadena.size(); i++)
    {
        if (!std::isdigit(cadena[i]))
            return false;
    }

    return true;
}
