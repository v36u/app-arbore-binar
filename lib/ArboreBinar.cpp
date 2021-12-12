#include "ArboreBinar.h"

ArboreBinar::ArboreBinar()
{
    this->_radacina = nullptr;
}

ArboreBinar::~ArboreBinar()
{
    // TODO: Dezalocă toate nodurile și apoi și rădăcina
}

string ArboreBinar::GetRadacina()
{
    if (this->_radacina == nullptr) {
        return "";
    }
    return this->_radacina->_informatie;
}
