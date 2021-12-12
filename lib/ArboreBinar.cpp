#include "ArboreBinar.h"

ArboreBinar::ArboreBinar()
{
    this->_radacina = nullptr;
    this->_nod_curent = nullptr;
    this->_directie = false;
}

ArboreBinar::~ArboreBinar()
{
    // TODO: Dezalocă toate nodurile și apoi și rădăcina
}

ArboreBinar::Nod
ArboreBinar::CreareNod(const string &p_informatie_nod)
{
    return new Celula{
            ._informatie = p_informatie_nod,
            ._stanga = nullptr,
            ._dreapta = nullptr
    };
}

ArboreBinar::Nod
ArboreBinar::CreareNod(const string &p_informatie_nod, const string &p_informatie_descendent, const bool &p_directie)
{
    return new Celula{
            ._informatie = p_informatie_nod,
            ._stanga = !p_directie ? this->CreareNod(p_informatie_descendent) : nullptr,
            ._dreapta = p_directie ? this->CreareNod(p_informatie_descendent) : nullptr
    };
}

ArboreBinar::Nod
ArboreBinar::CreareNod(const string &p_informatie_nod, const string &p_informatie_descendent_stang, const string &p_informatie_descendent_drept)
{
    return new Celula{
            ._informatie = p_informatie_nod,
            ._stanga = this->CreareNod(p_informatie_descendent_stang),
            ._dreapta = this->CreareNod(p_informatie_descendent_drept)
    };
}

ArboreBinar::Nod
ArboreBinar::GasireTataNodCurent(const Nod &p_nod)
{
    if (p_nod == nullptr)
    {
        return nullptr;
    }

    if (p_nod->_stanga == this->_nod_curent || p_nod->_dreapta == this->_nod_curent)
    {
        return p_nod;
    }

    if (p_nod->_stanga != nullptr)
    {
        return this->GasireTataNodCurent(p_nod->_stanga);
    }

    if (p_nod->_dreapta != nullptr)
    {
        return this->GasireTataNodCurent(p_nod->_dreapta);
    }

    return nullptr;
}

void
ArboreBinar::DeplasareInapoi()
{
    if (this->_radacina == this->_nod_curent)
    {
        return;
    }

    this->_nod_curent = this->GasireTataNodCurent(this->_radacina);
}

void
ArboreBinar::RouterSalvareNod(const string &p_informatie_nod,
                              const string *p_informatie_descendent_1, const string *p_informatie_descendent_2,
                              const bool *p_directie)
{
    const Nod &nod_nou =
            p_informatie_descendent_1 != nullptr && p_informatie_descendent_2 != nullptr ?
            this->CreareNod(p_informatie_nod, *p_informatie_descendent_1, *p_informatie_descendent_2) :
            p_directie != nullptr ?
            (p_informatie_descendent_1 != nullptr ?
             this->CreareNod(p_informatie_nod, *p_informatie_descendent_1, *p_directie) :
             p_informatie_descendent_2 != nullptr ?
             this->CreareNod(p_informatie_nod, *p_informatie_descendent_2, *p_directie) :
             this->CreareNod(p_informatie_nod)
            ) :
            this->CreareNod(p_informatie_nod);

    if (this->_radacina == nullptr)
    {
        if (p_informatie_nod.empty())
        {
            delete nod_nou;
            return;
        }
        this->_radacina = nod_nou;
        this->_nod_curent = this->_radacina;
        return;
    }

    if (!this->_directie)
    {
        if (!p_informatie_nod.empty())
        {
            if (this->_nod_curent->_stanga != nullptr)
            {
                this->_nod_curent->_stanga->_informatie = p_informatie_nod; // "3", "5", "7"
                delete nod_nou;
            } else
            {
                this->_nod_curent->_stanga = nod_nou;
            }
            this->_nod_curent = this->_nod_curent->_stanga;
        } else
        {
            this->_directie = true;
            delete nod_nou;
        }
    } else
    {
        if (!p_informatie_nod.empty())
        {
            if (this->_nod_curent->_dreapta != nullptr)
            {
                this->_nod_curent->_dreapta->_informatie = p_informatie_nod;
                delete nod_nou;
            } else
            {
                this->_nod_curent->_dreapta = nod_nou;
            }
            this->_nod_curent = this->_nod_curent->_dreapta;
        } else
        {
            this->DeplasareInapoi();
            delete nod_nou;
        }
        this->_directie = false;
    }
}


string
ArboreBinar::GetRadacina()
{
    if (this->_radacina == nullptr)
    {
        return "";
    }
    return this->_radacina->_informatie;
}

void
ArboreBinar::SalvareNod(const string &p_informatie_nod)
{
    this->RouterSalvareNod(p_informatie_nod, nullptr, nullptr, nullptr);
}

void
ArboreBinar::SalvareNod(const string &p_informatie_nod, const string &p_informatie_descendent, const bool &p_directie)
{
    if (p_informatie_descendent.empty())
    {
        this->SalvareNod(p_informatie_nod);
        return;
    }

    this->RouterSalvareNod(p_informatie_nod, &p_informatie_descendent, nullptr, &p_directie);
}

void
ArboreBinar::SalvareNod(const string &p_informatie_nod, const string &p_informatie_descendent_stang, const string &p_informatie_descendent_drept)
{
    const bool descendent_stang_fara_informatie = p_informatie_descendent_stang.empty();
    const bool descendent_drept_fara_informatie = p_informatie_descendent_drept.empty();

    if (descendent_stang_fara_informatie && descendent_drept_fara_informatie)
    {
        this->SalvareNod(p_informatie_nod);
    }

    if (descendent_stang_fara_informatie)
    {
        this->SalvareNod(p_informatie_nod, p_informatie_descendent_drept, true);
        return;
    }

    if (descendent_drept_fara_informatie)
    {
        this->SalvareNod(p_informatie_nod, p_informatie_descendent_stang, false);
        return;
    }

    this->RouterSalvareNod(p_informatie_nod, &p_informatie_descendent_stang, &p_informatie_descendent_stang, nullptr);
}
