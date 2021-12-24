#include "ArboreBinar.h"

ArboreBinar::ArboreBinar()
{
    this->_radacina = nullptr;
    this->_nod_curent = nullptr;

    this->_id_curent = 0;

    this->_numar_noduri = 0;
    this->_numar_frunze = 0;
    this->_numar_niveluri = 0;
}

ArboreBinar::~ArboreBinar()
{
    this->DezalocareArbore(this->_radacina);
}

ArboreBinar::Celula::Celula(string p_informatie, unsigned int p_id, unsigned short p_nivel)
        : Celula(p_informatie, p_id, p_nivel, nullptr, nullptr, E_Directie::Stanga)
{}

ArboreBinar::Celula::Celula
        (string p_informatie,
         unsigned int p_id,
         unsigned short p_nivel,
         Celula *p_descendent_stang,
         Celula *p_descendent_drept,
         E_Directie p_directie)
{
    this->_id = p_id;
    this->_informatie = p_informatie;
    this->_nivel = p_nivel;
    this->_stanga = p_descendent_stang;
    this->_dreapta = p_descendent_drept;
    this->_directie = p_directie;
}

ArboreBinar::Nod
ArboreBinar::CreareNod(string p_informatie_nod, unsigned short p_nivel)
{
    return new Celula(p_informatie_nod, this->_id_curent++, p_nivel);
}

ArboreBinar::Nod
ArboreBinar::CreareNod
        (string p_informatie_nod,
         unsigned short p_nivel,
         string p_informatie_descendent,
         E_Directie p_directie)
{
    return
            new Celula(p_informatie_nod,

                       this->_id_curent++,

                       p_nivel,

                       p_directie == E_Directie::Stanga
                       ? this->CreareNod(p_informatie_descendent, p_nivel + 1)
                       : nullptr,

                       p_directie == E_Directie::Dreapta
                       ? this->CreareNod(p_informatie_descendent, p_nivel + 1)
                       : nullptr,

                       this->_nod_curent != nullptr
                       ? this->_nod_curent->_directie
                       : E_Directie::Stanga
            );
}

ArboreBinar::Nod
ArboreBinar::CreareNod
        (string p_informatie_nod,
         unsigned short p_nivel,
         string p_informatie_descendent_stang,
         string p_informatie_descendent_drept)
{
    return
            new Celula(p_informatie_nod,

                       this->_id_curent++,

                       p_nivel,

                       this->CreareNod(p_informatie_descendent_stang, p_nivel + 1),

                       this->CreareNod(p_informatie_descendent_drept, p_nivel + 1),

                       this->_nod_curent != nullptr
                       ? this->_nod_curent->_directie
                       : E_Directie::Stanga
            );
}

ArboreBinar::Nod
ArboreBinar::RouterCreareNod
        (string p_informatie_nod,
         unsigned short p_nivel,
         string *p_informatie_descendent_1,
         string *p_informatie_descendent_2,
         E_Directie *p_directie)
{
    if (p_informatie_descendent_1 != nullptr && p_informatie_descendent_2 != nullptr)
    {
        return this->CreareNod(p_informatie_nod, p_nivel, *p_informatie_descendent_1, *p_informatie_descendent_2);
    }

    if (p_directie == nullptr)
    {
        return this->CreareNod(p_informatie_nod, p_nivel);
    }

    if (p_informatie_descendent_1 != nullptr)
    {
        return this->CreareNod(p_informatie_nod, p_nivel, *p_informatie_descendent_1, *p_directie);
    }

    if (p_informatie_descendent_2 != nullptr)
    {
        return this->CreareNod(p_informatie_nod, p_nivel, *p_informatie_descendent_2, *p_directie);
    }

    return this->CreareNod(p_informatie_nod, p_nivel);
}

bool
ArboreBinar::EsteFrunza(ArboreBinar::Nod p_nod)
{
    return p_nod->_stanga == nullptr && p_nod->_dreapta == nullptr;
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

void ArboreBinar::DeplasareNodCurentUndeEstePosibil()
{
    while (!this->DeplasareNodCurent(this->_nod_curent->_directie) && this->_nod_curent->_directie != E_Directie::Stanga)
    { /* Maxim 3 iterații, deoarece DeplasareNodCurent(E_Directie::Sus) va fi mereu true. */}
}

void
ArboreBinar::EditareNodCurentExistent(ArboreBinar::Nod p_nod)
{
    if (p_nod->_informatie.empty())
    {
        if (this->_nod_curent == this->_radacina)
        {
            this->DezalocareArbore(this->_radacina);
            this->_nod_curent = this->_radacina = nullptr;
            return;
        }

        auto aux = this->_nod_curent;
        this->DeplasareNodCurent(E_Directie::Sus);
        auto directie_aux = E_Directie::Stanga;
        if (this->_nod_curent->_dreapta == aux)
        {
            directie_aux = E_Directie::Dreapta;
        }

        this->DezalocareArbore(aux);
        if (directie_aux == E_Directie::Stanga)
        {
            this->_nod_curent->_stanga = nullptr;
        } else if (directie_aux == E_Directie::Dreapta)
        {
            this->_nod_curent->_dreapta = nullptr;
        }
        return;
    }

    this->_nod_curent->_informatie = p_nod->_informatie;

    if (p_nod->_stanga != nullptr)
    {
        if (p_nod->_stanga->_informatie.empty())
        {
            this->DezalocareArbore(this->_nod_curent->_stanga);
            this->_nod_curent->_stanga = nullptr;
        } else if (this->_nod_curent->_stanga == nullptr)
        {
            this->_nod_curent->_stanga = p_nod->_stanga;
            this->_numar_noduri++;
            if (this->_nod_curent->_dreapta != nullptr)
            {
                this->_numar_frunze++;
            }
            if (this->_nod_curent->_stanga->_nivel > this->_numar_niveluri)
            {
                this->_numar_niveluri = this->_nod_curent->_stanga->_nivel;
            }
        } else
        {
            this->_nod_curent->_stanga->_informatie = p_nod->_stanga->_informatie;
        }
    }

    if (p_nod->_dreapta != nullptr)
    {
        if (p_nod->_dreapta->_informatie.empty())
        {
            this->DezalocareArbore(this->_nod_curent->_dreapta);
            this->_nod_curent->_dreapta = nullptr;
        } else if (this->_nod_curent->_dreapta == nullptr)
        {
            this->_nod_curent->_dreapta = p_nod->_dreapta;
            this->_numar_noduri++;
            if (this->_nod_curent->_stanga != nullptr)
            {
                this->_numar_frunze++;
            }
            if (this->_nod_curent->_dreapta->_nivel > this->_numar_niveluri)
            {
                this->_numar_niveluri = this->_nod_curent->_dreapta->_nivel;
            }
        } else
        {
            this->_nod_curent->_dreapta->_informatie = p_nod->_dreapta->_informatie;
        }
    }

    this->DeplasareNodCurentUndeEstePosibil();
}

bool
ArboreBinar::NoduriCuInformatiiEgale(ArboreBinar::Nod p_nod_1, ArboreBinar::Nod p_nod_2)
{
    if ((p_nod_1 == nullptr) != (p_nod_2 == nullptr))
    {
        return false;
    } else if (p_nod_1 == nullptr) //=> p_nod_2 != nullptr
    {
        return false; // un nullptr nu ar trebui să fie considerat egal cu alt nullptr
    }

    if (p_nod_1->_informatie != p_nod_2->_informatie)
    {
        return false;
    }

    if ((p_nod_1->_stanga == nullptr) != (p_nod_2->_stanga == nullptr))
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

    if ((p_nod_1->_dreapta == nullptr) != (p_nod_2->_dreapta == nullptr))
    {
        return false;
    }

    if (p_nod_1->_dreapta != nullptr) //=> p_nod_2->_dreapta != nullptr
    {
        if (p_nod_1->_dreapta->_informatie != p_nod_2->_dreapta->_informatie)
        {
            return false;
        }
    }

    return true;
}

void
ArboreBinar::InitializareCazRadacinaGoala(Nod p_nod)
{
    this->_nod_curent = this->_radacina = p_nod;
    this->_numar_noduri = 1;
    this->_numar_frunze = 1;
    this->_numar_niveluri = 1;

    if (this->_nod_curent->_stanga != nullptr || this->_nod_curent->_dreapta != nullptr)
    {
        this->_numar_noduri = 2;
        this->_numar_niveluri = 2;
        if (this->_nod_curent->_stanga != nullptr && this->_nod_curent->_dreapta != nullptr)
        {
            this->_numar_noduri = 3;
            this->_numar_frunze = 2;
        }
    }
}

void
ArboreBinar::SalvareNod
        (string p_informatie_nod,
         string *p_informatie_descendent_1,
         string *p_informatie_descendent_2,
         E_Directie *p_directie)
{
    auto nod_nou =
            this->RouterCreareNod
                    (p_informatie_nod,

                     this->_nod_curent != nullptr
                     ? this->_nod_curent->_nivel
                     : 1,

                     p_informatie_descendent_1,

                     p_informatie_descendent_2,

                     p_directie);

    if (this->NoduriCuInformatiiEgale(this->_nod_curent, nod_nou))
    {
        this->DeplasareNodCurentUndeEstePosibil();
        delete nod_nou;
    } else
    {
        if (this->_radacina == nullptr)
        {
            this->InitializareCazRadacinaGoala(nod_nou);
        }
        this->EditareNodCurentExistent(nod_nou);
    }

    delete p_informatie_descendent_1;
    delete p_informatie_descendent_2;
    delete p_directie;
}

vector<ArboreBinar::NodDto>
ArboreBinar::RSD(ArboreBinar::Nod p_nod)
{
    if (p_nod == nullptr)
    {
        return vector<ArboreBinar::NodDto>();
    }

    vector<ArboreBinar::NodDto> vector_stanga = this->RSD(p_nod->_stanga);
    vector<ArboreBinar::NodDto> vector_dreapta = this->RSD(p_nod->_dreapta);

    vector<ArboreBinar::NodDto> vector_rsd = vector<ArboreBinar::NodDto>({{._id_nod = p_nod->_id, ._informatie_nod = p_nod->_informatie}});
    vector_rsd.insert(vector_rsd.end(), vector_stanga.begin(), vector_stanga.end());
    vector_rsd.insert(vector_rsd.end(), vector_dreapta.begin(), vector_dreapta.end());

    return vector_rsd;
}

vector<ArboreBinar::NodDto>
ArboreBinar::SRD(ArboreBinar::Nod p_nod)
{
    if (p_nod == nullptr)
    {
        return vector<ArboreBinar::NodDto>();
    }

    vector<ArboreBinar::NodDto> vector_stanga = this->SRD(p_nod->_stanga);
    vector<ArboreBinar::NodDto> vector_dreapta = this->SRD(p_nod->_dreapta);

    vector<ArboreBinar::NodDto> vector_srd = vector(vector_stanga.begin(), vector_stanga.end());
    vector_srd.push_back({._id_nod = p_nod->_id, ._informatie_nod = p_nod->_informatie});
    vector_srd.insert(vector_srd.end(), vector_dreapta.begin(), vector_dreapta.end());

    return vector_srd;
}

vector<ArboreBinar::NodDto>
ArboreBinar::SDR(ArboreBinar::Nod p_nod)
{
    if (p_nod == nullptr)
    {
        return vector<ArboreBinar::NodDto>();
    }

    vector<ArboreBinar::NodDto> vector_stanga = this->SDR(p_nod->_stanga);
    vector<ArboreBinar::NodDto> vector_dreapta = this->SDR(p_nod->_dreapta);

    vector<ArboreBinar::NodDto> vector_sdr = vector(vector_stanga.begin(), vector_stanga.end());
    vector_sdr.insert(vector_sdr.end(), vector_dreapta.begin(), vector_dreapta.end());
    vector_sdr.push_back({._id_nod = p_nod->_id, ._informatie_nod = p_nod->_informatie});

    return vector_sdr;
}

vector<ArboreBinar::NodDto>
ArboreBinar::ParcurgereInLatime(ArboreBinar::Nod p_nod)
{
    vector<ArboreBinar::NodDto> parcurgere;
    vector<Nod> urmatoarele_noduri({p_nod});

    while (!urmatoarele_noduri.empty())
    {
        auto urmatorul_nod = urmatoarele_noduri.front();

        parcurgere.push_back({._id_nod = urmatorul_nod->_id, ._informatie_nod = urmatorul_nod->_informatie});

        if (urmatorul_nod->_stanga != nullptr)
        {
            urmatoarele_noduri.push_back(urmatorul_nod->_stanga);
        }

        if (urmatorul_nod->_dreapta != nullptr)
        {
            urmatoarele_noduri.push_back(urmatorul_nod->_dreapta);
        }

        urmatoarele_noduri.erase(urmatoarele_noduri.begin());
    }

    return parcurgere;
}

ArboreBinar::InformatiiNodDto
ArboreBinar::GetInformatiiNodCurent()
{
    unsigned int id_nod_curent = 0;
    auto informatie_nod_curent = string();
    auto informatie_descendent_stang = string();
    auto informatie_descendent_drept = string();

    if (this->_nod_curent != nullptr)
    {
        id_nod_curent = this->_nod_curent->_id;
        informatie_nod_curent = this->_nod_curent->_informatie;
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
            ._nod_curent = {
                    ._id_nod = id_nod_curent,
                    ._informatie_nod = informatie_nod_curent,
            },
            ._informatie_descendent_stang = informatie_descendent_stang,
            ._informatie_descendent_drept = informatie_descendent_drept
    };
}

ArboreBinar::StatisticiDto
ArboreBinar::GetStatisticiArbore()
{
    return {
            ._numar_noduri = to_string(this->_numar_noduri),
            ._numar_frunze = to_string(this->_numar_frunze),
            ._numar_niveluri = to_string(this->_numar_niveluri)
    };
}

void
ArboreBinar::SalvareNod
        (string p_informatie_nod,
         string p_informatie_descendent_stang,
         string p_informatie_descendent_drept)
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

vector<ArboreBinar::NodDto>
ArboreBinar::ParcurgerePreordineDeLaRadacina()
{
    return this->RSD(this->_radacina);
}

vector<ArboreBinar::NodDto>
ArboreBinar::ParcurgerePreordineDeLaNodulCurent()
{
    return this->RSD(this->_nod_curent);
}

vector<ArboreBinar::NodDto>
ArboreBinar::ParcurgereInordineDeLaRadacina()
{
    return this->SRD(this->_radacina);
}

vector<ArboreBinar::NodDto>
ArboreBinar::ParcurgereInordineDeLaNodulCurent()
{
    return this->SRD(this->_nod_curent);
}

vector<ArboreBinar::NodDto>
ArboreBinar::ParcurgerePostordineDeLaRadacina()
{
    return this->SDR(this->_radacina);
}

vector<ArboreBinar::NodDto>
ArboreBinar::ParcurgerePostordineDeLaNodulCurent()
{
    return this->SDR(this->_nod_curent);
}

vector<ArboreBinar::NodDto>
ArboreBinar::ParcurgereInLatimeDeLaRadacina()
{
    return this->ParcurgereInLatime(this->_radacina);
}

vector<ArboreBinar::NodDto>
ArboreBinar::ParcurgereInLatimeDeLaNodulCurent()
{
    return this->ParcurgereInLatime(this->_nod_curent);
}

vector<ArboreBinar::NodDto>
ArboreBinar::GetNodDtoInitVect()
{
    return vector<NodDto>();
}
