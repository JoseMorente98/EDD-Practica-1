#include "Validacion.h"

bool Validacion::ValidarNumero(std::string cadena)
{
    for (size_t i = 0; i < cadena.size(); i++)
    {
        if (!std::isdigit(cadena[i]))
            return false;
    }

    return true;
}
