#include "ArboreBinar.h"

ArboreBinar::ArboreBinar()
{
    this->_radacina = nullptr;
    this->_nod_curent = nullptr;
    this->_directie = true;
}

ArboreBinar::~ArboreBinar()
{
    DezalocareArbore(this->_radacina);
}

ArboreBinar::Nod
ArboreBinar::CreareNod(string p_informatie_nod)
{
    if (p_informatie_nod.empty())
    {
        return nullptr;
    }
    return new Celula{
            ._informatie = p_informatie_nod,
            ._stanga = nullptr,
            ._dreapta = nullptr
    };
}

ArboreBinar::Nod
ArboreBinar::CreareNod(string p_informatie_nod, string p_informatie_descendent, bool p_directie)
{
    if (p_informatie_nod.empty())
    {
        return nullptr;
    }
    return new Celula{
            ._informatie = p_informatie_nod,
            ._stanga = !p_directie ? this->CreareNod(p_informatie_descendent) : nullptr,
            ._dreapta = p_directie ? this->CreareNod(p_informatie_descendent) : nullptr
    };
}

ArboreBinar::Nod
ArboreBinar::CreareNod(string p_informatie_nod, string p_informatie_descendent_stang, string p_informatie_descendent_drept)
{
    if (p_informatie_nod.empty())
    {
        return nullptr;
    }
    return new Celula{
            ._informatie = p_informatie_nod,
            ._stanga = this->CreareNod(p_informatie_descendent_stang),
            ._dreapta = this->CreareNod(p_informatie_descendent_drept)
    };
}

void
ArboreBinar::DeplasareInapoiNodCurent(Nod p_nod)
{
    if (p_nod == nullptr)
    {
        return;
    }

    if (p_nod->_stanga == this->_nod_curent || p_nod->_dreapta == this->_nod_curent)
    {
        this->_nod_curent = p_nod;
        return;
    }

    if (p_nod->_stanga != nullptr)
    {
        this->DeplasareInapoiNodCurent(p_nod->_stanga);
    }

    if (p_nod->_dreapta != nullptr)
    {
        this->DeplasareInapoiNodCurent(p_nod->_dreapta);
    }
}

ArboreBinar::Nod
ArboreBinar::GetNodNouRouter(string p_informatie_nod, string *p_informatie_descendent_1, string *p_informatie_descendent_2, bool *p_directie)
{
    if (p_informatie_descendent_1 != nullptr && p_informatie_descendent_2 != nullptr)
    {
        return this->CreareNod(p_informatie_nod, *p_informatie_descendent_1, *p_informatie_descendent_2);
    }
    if (!p_directie)
    {
        return this->CreareNod(p_informatie_nod);
    }
    if (p_informatie_descendent_1 != nullptr)
    {
        this->CreareNod(p_informatie_nod, *p_informatie_descendent_1, *p_directie);
    }
    if (p_informatie_descendent_2 != nullptr)
    {
        this->CreareNod(p_informatie_nod, *p_informatie_descendent_2, *p_directie);
    }
    return this->CreareNod(p_informatie_nod);
}

void
ArboreBinar::RouterSalvareNod(string p_informatie_nod, string *p_informatie_descendent_1, string *p_informatie_descendent_2, bool *p_directie)
{
    auto nod_nou = GetNodNouRouter(p_informatie_nod, p_informatie_descendent_1, p_informatie_descendent_2, p_directie);

    if (this->_radacina == nullptr)
    {
        if (nod_nou != nullptr)
        {
            this->_radacina = nod_nou;
            this->_nod_curent = this->_radacina;

            bool mutare_executata = this->MutaNodCurentDacaEstePosibil(true, false);
            if (!mutare_executata)
            {
                this->_directie = false;
            }
        }
    } else if (this->_directie)
    {
        if (nod_nou != nullptr)
        {
            if (this->_nod_curent->_stanga != nullptr)
            {
                this->_nod_curent->_stanga->_informatie = nod_nou->_informatie;
                if (this->_nod_curent->_stanga->_stanga != nullptr)
                {
                    if (nod_nou->_stanga != nullptr)
                    {
                        this->_nod_curent->_stanga->_stanga->_informatie = nod_nou->_stanga->_informatie;
                    }
                } else
                {
                    this->_nod_curent->_stanga->_stanga = nod_nou->_stanga;
                }
                if (this->_nod_curent->_stanga->_dreapta != nullptr)
                {
                    if (nod_nou->_dreapta != nullptr)
                    {
                        this->_nod_curent->_stanga->_dreapta->_informatie = nod_nou->_dreapta->_informatie;
                    }
                } else
                {
                    this->_nod_curent->_stanga->_dreapta = nod_nou->_dreapta;
                }
            } else
            {
                this->_nod_curent->_stanga = nod_nou;
            }
        }
        bool mutare_executata = this->MutaNodCurentDacaEstePosibil(true, nod_nou != nullptr);
        if (!mutare_executata)
        {
            this->_directie = false;
        }
    } else
    {
        if (nod_nou != nullptr)
        {
            if (this->_nod_curent->_dreapta != nullptr)
            {
                this->_nod_curent->_dreapta->_informatie = nod_nou->_informatie;
                if (this->_nod_curent->_dreapta->_stanga != nullptr)
                {
                    if (nod_nou->_stanga != nullptr)
                    {
                        this->_nod_curent->_dreapta->_stanga->_informatie = nod_nou->_stanga->_informatie;
                    }
                } else
                {
                    this->_nod_curent->_dreapta->_stanga = nod_nou->_stanga;
                }
                if (this->_nod_curent->_dreapta->_dreapta != nullptr)
                {
                    if (nod_nou->_dreapta != nullptr)
                    {
                        this->_nod_curent->_dreapta->_dreapta->_informatie = nod_nou->_dreapta->_informatie;
                    }
                } else
                {
                    this->_nod_curent->_dreapta->_dreapta = nod_nou->_dreapta;
                }
            } else
            {
                this->_nod_curent->_dreapta = nod_nou;
            }
        }
        bool mutare_executata = this->MutaNodCurentDacaEstePosibil(false, nod_nou != nullptr);
        if (mutare_executata)
        {
            this->_directie = true;
        } else
        {
            this->DeplasareInapoiNodCurent(this->_radacina);
        }
    }

    delete p_informatie_descendent_1;
    delete p_informatie_descendent_2;
    delete p_directie;
}

void
ArboreBinar::DezalocareArbore(Nod p_nod)
{
    if (p_nod == nullptr)
    {
        return;
    }

    if (p_nod->_stanga != nullptr)
    {
        this->DezalocareArbore(p_nod->_stanga);
    }

    if (p_nod->_dreapta != nullptr)
    {
        this->DezalocareArbore(p_nod->_dreapta);
    }

    delete p_nod;
}

bool
ArboreBinar::MutaNodCurentDacaEstePosibil(bool p_directie, bool p_abia_adaugat)
{
    if (p_directie && this->_nod_curent->_stanga != nullptr)
    {
        this->_nod_curent = this->_nod_curent->_stanga;
        if (p_abia_adaugat)
        {
            MutaNodCurentAbiaAdaugat();
        }
        return true;
    }
    if (!p_directie && this->_nod_curent->_dreapta != nullptr)
    {
        this->_nod_curent = this->_nod_curent->_dreapta;
        if (p_abia_adaugat)
        {
            MutaNodCurentAbiaAdaugat();
        }
        return true;
    }
    return false;
}

void ArboreBinar::MutaNodCurentAbiaAdaugat()
{
    if (this->_nod_curent->_stanga != nullptr)
    {
        this->_nod_curent = this->_nod_curent->_stanga;
    } else if (this->_nod_curent->_dreapta != nullptr)
    {
        this->_nod_curent = this->_nod_curent->_dreapta;
    }
}

ArboreBinar::NodDto
ArboreBinar::GetInformatiiNodCurent()
{
    auto informatie_nod = string();
    auto informatie_descendent_stang = string();
    auto informatie_descendent_drept = string();

    if (this->_nod_curent != nullptr)
    {
        informatie_nod = this->_nod_curent->_informatie;
        if (this->_nod_curent->_stanga != nullptr)
        {
            informatie_descendent_stang = this->_nod_curent->_stanga->_informatie;
        }
        if (this->_nod_curent->_dreapta != nullptr)
        {
            informatie_descendent_drept = this->_nod_curent->_dreapta->_informatie;
        }
    }

    return {
            ._informatie_nod = informatie_nod,
            ._informatie_descendent_stang = informatie_descendent_stang,
            ._informatie_descendent_drept = informatie_descendent_drept
    };
}

void
ArboreBinar::SalvareNod(string p_informatie_nod, string p_informatie_descendent_stang, string p_informatie_descendent_drept)
{
    const auto descendent_stang_fara_informatie = p_informatie_descendent_stang.empty();
    const auto descendent_drept_fara_informatie = p_informatie_descendent_drept.empty();

    if (descendent_stang_fara_informatie && descendent_drept_fara_informatie)
    {
        this->RouterSalvareNod(p_informatie_nod, nullptr, nullptr, nullptr);
        return;
    }

    if (descendent_stang_fara_informatie)
    {
        this->RouterSalvareNod(p_informatie_nod, nullptr, new string{p_informatie_descendent_stang}, new bool{true});
        return;
    }

    if (descendent_drept_fara_informatie)
    {
        this->RouterSalvareNod(p_informatie_nod, new string{p_informatie_descendent_stang}, nullptr, new bool{false});
        return;
    }

    this->RouterSalvareNod(p_informatie_nod, new string{p_informatie_descendent_stang}, new string{p_informatie_descendent_drept}, nullptr);
}
