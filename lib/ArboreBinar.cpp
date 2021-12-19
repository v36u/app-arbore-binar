#include "ArboreBinar.h"

ArboreBinar::ArboreBinar()
{
    this->_radacina = nullptr;
    this->_nod_curent = nullptr;
}

ArboreBinar::~ArboreBinar()
{
    this->DezalocareArbore(this->_radacina);
}

ArboreBinar::Celula::Celula(string p_informatie) : Celula(p_informatie, nullptr, nullptr, E_Directie::Stanga)
{}

ArboreBinar::Celula::Celula(string p_informatie, Celula *p_descendent_stang, Celula *p_descendent_drept, E_Directie p_directie)
{
    this->_stanga = p_descendent_stang;
    this->_dreapta = p_descendent_drept;
    this->_informatie = p_informatie;
    this->_directie = p_directie;
}

ArboreBinar::Nod
ArboreBinar::CreareNod(string p_informatie_nod)
{
    return new Celula(p_informatie_nod);
}

ArboreBinar::Nod
ArboreBinar::CreareNod(string p_informatie_nod, string p_informatie_descendent, E_Directie p_directie)
{
    return
            new Celula(p_informatie_nod,
                       p_directie == E_Directie::Stanga ? this->CreareNod(p_informatie_descendent) : nullptr,
                       p_directie == E_Directie::Dreapta ? this->CreareNod(p_informatie_descendent) : nullptr,
                       this->_nod_curent != nullptr ? this->_nod_curent->_directie : E_Directie::Stanga
            );
}

ArboreBinar::Nod
ArboreBinar::CreareNod(string p_informatie_nod, string p_informatie_descendent_stang, string p_informatie_descendent_drept)
{
    return
            new Celula(p_informatie_nod,
                       this->CreareNod(p_informatie_descendent_stang),
                       this->CreareNod(p_informatie_descendent_drept),
                       this->_nod_curent != nullptr ? this->_nod_curent->_directie : E_Directie::Stanga
            );
}

ArboreBinar::Nod
ArboreBinar::RouterCreareNod(string p_informatie_nod, string *p_informatie_descendent_1, string *p_informatie_descendent_2, E_Directie *p_directie)
{
    if (p_informatie_descendent_1 != nullptr && p_informatie_descendent_2 != nullptr)
    {
        return this->CreareNod(p_informatie_nod, *p_informatie_descendent_1, *p_informatie_descendent_2);
    }

    if (p_directie == nullptr)
    {
        return this->CreareNod(p_informatie_nod);
    }

    if (p_informatie_descendent_1 != nullptr)
    {
        return this->CreareNod(p_informatie_nod, *p_informatie_descendent_1, *p_directie);
    }

    if (p_informatie_descendent_2 != nullptr)
    {
        return this->CreareNod(p_informatie_nod, *p_informatie_descendent_2, *p_directie);
    }

    return this->CreareNod(p_informatie_nod);
}

void
ArboreBinar::EditareNodCurentExistent(ArboreBinar::Nod p_nod)
{
    this->_nod_curent->_informatie = p_nod->_informatie;
    if (p_nod->_stanga != nullptr)
    {
        if (this->_nod_curent->_stanga == nullptr)
        {
            this->_nod_curent->_stanga = p_nod->_stanga;
        } else
        {
            this->_nod_curent->_stanga->_informatie = p_nod->_stanga->_informatie;
        }
    }
    if (p_nod->_dreapta != nullptr)
    {
        if (this->_nod_curent->_dreapta == nullptr)
        {
            this->_nod_curent->_dreapta = p_nod->_dreapta;
        } else
        {
            this->_nod_curent->_dreapta->_informatie = p_nod->_dreapta->_informatie;
        }
    }
}

bool
ArboreBinar::NoduriCuInformatiiEgale(ArboreBinar::Nod p_nod_1, ArboreBinar::Nod p_nod_2)
{
    if ((p_nod_1 == nullptr) != (p_nod_2 == nullptr))
    {
        return false;
    }

    if ((p_nod_1->_stanga == nullptr) != (p_nod_2->_stanga == nullptr))
    {
        return false;
    }

    if ((p_nod_1->_dreapta == nullptr) != (p_nod_2->_dreapta == nullptr))
    {
        return false;
    }

    if (p_nod_1 != nullptr) //=> p_nod_2 != nullptr
    {
        if (p_nod_1->_informatie != p_nod_2->_informatie)
        {
            return false;
        }

        if (p_nod_1->_stanga != nullptr) //=> p_nod_2->_stanga != nullptr
        {
            if (p_nod_1->_stanga->_informatie != p_nod_2->_stanga->_informatie)
            {
                return false;
            }
        }

        if (p_nod_1->_dreapta != nullptr) //=> p_nod_2->_dreapta != nullptr
        {
            if (p_nod_1->_dreapta->_informatie != p_nod_2->_dreapta->_informatie)
            {
                return false;
            }
        }
    }

    return true;
}

void
ArboreBinar::DeplasareNodCurentSus(Nod p_nod)
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
        this->DeplasareNodCurentSus(p_nod->_stanga);
    }
    if (p_nod->_dreapta != nullptr)
    {
        this->DeplasareNodCurentSus(p_nod->_dreapta);
    }
}

bool
ArboreBinar::DeplasareNodCurent(E_Directie p_directie)
{
    if (p_directie == E_Directie::Stanga)
    {
        this->_nod_curent->_directie = E_Directie::Dreapta;
        if (this->_nod_curent->_stanga != nullptr)
        {
            this->_nod_curent = this->_nod_curent->_stanga;
            return true;
        }
        return false;
    }

    if (p_directie == E_Directie::Dreapta)
    {

        if (this->_nod_curent != this->_radacina)
        {
            this->_nod_curent->_directie = E_Directie::Sus;
        } else
        {
            this->_nod_curent->_directie = E_Directie::Stanga;
        }
        if (this->_nod_curent->_dreapta != nullptr)
        {
            this->_nod_curent = this->_nod_curent->_dreapta;
            return true;
        }
        return false;
    }

    if (p_directie == E_Directie::Sus)
    {
        this->_nod_curent->_directie = E_Directie::Stanga;
        this->DeplasareNodCurentSus(this->_radacina);
        return true;
    }

    return false;
}

void
ArboreBinar::SalvareNod(string p_informatie_nod, string *p_informatie_descendent_1, string *p_informatie_descendent_2, E_Directie *p_directie)
{
    auto nod_nou = this->RouterCreareNod(p_informatie_nod, p_informatie_descendent_1, p_informatie_descendent_2, p_directie);

    if (NoduriCuInformatiiEgale(this->_nod_curent, nod_nou))
    {
        if (!this->DeplasareNodCurent(this->_nod_curent->_directie))
        {
            if (!this->DeplasareNodCurent(this->_nod_curent->_directie))
            {
                this->DeplasareNodCurent(this->_nod_curent->_directie);
            }
        }
    } else
    {
        if (this->_radacina == nullptr)
        {
            this->_nod_curent = this->_radacina = nod_nou;
        }

        this->EditareNodCurentExistent(nod_nou);

        if (!this->DeplasareNodCurent(E_Directie::Stanga))
        {
            this->DeplasareNodCurent(E_Directie::Dreapta);
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

vector<string>
ArboreBinar::RSD(ArboreBinar::Nod p_nod)
{
    if (p_nod == nullptr)
    {
        return vector<string>();
    }

    vector<string> vector_stanga = this->RSD(p_nod->_stanga);
    vector<string> vector_dreapta = this->RSD(p_nod->_dreapta);

    vector<string> vector_rsd = vector({p_nod->_informatie});
    vector_rsd.insert(vector_rsd.end(), vector_stanga.begin(), vector_stanga.end());
    vector_rsd.insert(vector_rsd.end(), vector_dreapta.begin(), vector_dreapta.end());

    return vector_rsd;
}

vector<string>
ArboreBinar::SRD(ArboreBinar::Nod p_nod)
{
    if (p_nod == nullptr)
    {
        return vector<string>();
    }

    vector<string> vector_stanga = this->SRD(p_nod->_stanga);
    vector<string> vector_dreapta = this->SRD(p_nod->_dreapta);

    vector<string> vector_srd = vector(vector_stanga.begin(), vector_stanga.end());
    vector_srd.push_back(p_nod->_informatie);
    vector_srd.insert(vector_srd.end(), vector_dreapta.begin(), vector_dreapta.end());

    return vector_srd;
}

vector<string>
ArboreBinar::SDR(ArboreBinar::Nod p_nod)
{
    if (p_nod == nullptr)
    {
        return vector<string>();
    }

    vector<string> vector_stanga = this->SDR(p_nod->_stanga);
    vector<string> vector_dreapta = this->SDR(p_nod->_dreapta);

    vector<string> vector_sdr = vector(vector_stanga.begin(), vector_stanga.end());
    vector_sdr.insert(vector_sdr.end(), vector_dreapta.begin(), vector_dreapta.end());
    vector_sdr.push_back(p_nod->_informatie);

    return vector_sdr;
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
    auto descendent_stang_fara_informatie = p_informatie_descendent_stang.empty();
    auto descendent_drept_fara_informatie = p_informatie_descendent_drept.empty();

    if (descendent_stang_fara_informatie && descendent_drept_fara_informatie)
    {
        this->SalvareNod(p_informatie_nod, nullptr, nullptr, nullptr);
        return;
    }

    if (descendent_stang_fara_informatie)
    {
        this->SalvareNod(p_informatie_nod, nullptr, new string{p_informatie_descendent_drept}, new E_Directie{this->Dreapta});
        return;
    }

    if (descendent_drept_fara_informatie)
    {
        this->SalvareNod(p_informatie_nod, new string{p_informatie_descendent_stang}, nullptr, new E_Directie{this->Stanga});
        return;
    }

    this->SalvareNod(p_informatie_nod, new string{p_informatie_descendent_stang}, new string{p_informatie_descendent_drept}, nullptr);
}

vector<string>
ArboreBinar::ParcurgerePreordineDeLaRadacina()
{
    return this->RSD(this->_radacina);
}

vector<string>
ArboreBinar::ParcurgerePreordineDeLaNodulCurent()
{
    return this->RSD(this->_nod_curent);
}

vector<string>
ArboreBinar::ParcurgereInordineDeLaRadacina()
{
    return this->SRD(this->_radacina);
}

vector<string>
ArboreBinar::ParcurgereInordineDeLaNodulCurent()
{
    return this->SRD(this->_nod_curent);
}

vector<string>
ArboreBinar::ParcurgerePostordineDeLaRadacina()
{
    return this->SDR(this->_radacina);
}

vector<string>
ArboreBinar::ParcurgerePostordineDeLaNodulCurent()
{
    return this->SDR(this->_nod_curent);
}
