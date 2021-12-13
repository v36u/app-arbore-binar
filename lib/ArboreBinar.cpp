#include "ArboreBinar.h"

ArboreBinar::ArboreBinar()
{
    this->_radacina = nullptr;
    this->_nod_curent = nullptr;
    this->_directie = false;
    this->_deplasat = false;
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

// TODO: Simplifică, Optimizează, Sparge (S.O.S.)
void
ArboreBinar::RouterSalvareNod(string p_informatie_nod, string *p_informatie_descendent_1, string *p_informatie_descendent_2, bool *p_directie)
{
    auto nod_nou =
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
        if (nod_nou != nullptr)
        {
            this->_radacina = nod_nou;
            this->_nod_curent = this->_radacina;
        }
    } else if (!this->_directie)
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
        } else
        {
            this->_directie = true;
        }
        if (this->_nod_curent->_stanga != nullptr)
        {
            this->_nod_curent = this->_nod_curent->_stanga;
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
            this->_directie = false;
        } else
        {
            if (this->_nod_curent->_dreapta == nullptr)
            {
                this->DeplasareInapoiNodCurent(this->_radacina);
                this->_deplasat = true;
                this->_directie = true;
            } else
            {
                this->_directie = false;
            }
        }
        if (!this->_deplasat && this->_nod_curent->_dreapta != nullptr)
        {
            this->_nod_curent = this->_nod_curent->_dreapta;
        }
    }

    if (!this->_deplasat)
    {
        if (this->_nod_curent->_stanga != nullptr)
        {
            this->_nod_curent = this->_nod_curent->_stanga;
        } else if (this->_nod_curent->_dreapta != nullptr)
        {
            this->_nod_curent = this->_nod_curent->_dreapta;
        }
    } else
    {
        this->_deplasat = false;
    }

    delete p_informatie_descendent_1;
    delete p_informatie_descendent_2;
    delete p_directie;
}

void ArboreBinar::DezalocareArbore(Nod p_nod)
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
        this->RouterSalvareNod(p_informatie_nod, nullptr, new string{p_informatie_descendent_stang}, new bool{false});
        return;
    }

    if (descendent_drept_fara_informatie)
    {
        this->RouterSalvareNod(p_informatie_nod, new string{p_informatie_descendent_stang}, nullptr, new bool{true});
        return;
    }

    this->RouterSalvareNod(p_informatie_nod, new string{p_informatie_descendent_stang}, new string{p_informatie_descendent_drept}, nullptr);
}
