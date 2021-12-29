#include "ArboreBinar.h"

// --- Private ---

string ArboreBinar::_PREFIX_NOD_CURENT = "\u00BB";
string ArboreBinar::_POSTFIX_NOD_CURENT = "\u00AB";

string ArboreBinar::_PREFIX_DESCENDENT_STANG = "\u02E2";
string ArboreBinar::_PREFIX_DESCENDENT_DREPT = "\u1D48";

bool
ArboreBinar::NoduriCuInformatiiEgale(ArboreBinar::Nod p_nod_1,
                                     ArboreBinar::Nod p_nod_2)
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

vector<ArboreBinar::NodDto>
ArboreBinar::RSD(ArboreBinar::Nod p_nod)
{
    if (p_nod == nullptr)
    {
        return vector<ArboreBinar::NodDto>();
    }

    vector<ArboreBinar::NodDto> vector_stanga = ArboreBinar::RSD(p_nod->_stanga);
    vector<ArboreBinar::NodDto> vector_dreapta = ArboreBinar::RSD(p_nod->_dreapta);

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

    vector<ArboreBinar::NodDto> vector_stanga = ArboreBinar::SRD(p_nod->_stanga);
    vector<ArboreBinar::NodDto> vector_dreapta = ArboreBinar::SRD(p_nod->_dreapta);

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

    vector<ArboreBinar::NodDto> vector_stanga = ArboreBinar::SDR(p_nod->_stanga);
    vector<ArboreBinar::NodDto> vector_dreapta = ArboreBinar::SDR(p_nod->_dreapta);

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

string
ArboreBinar::GetCaleCatrePyLib()
{
    auto os = py::module::import("os");
    return os
      .attr("path")
      .attr("abspath")(os
                         .attr("path")
                         .attr("join")("..", "lib"))
      .cast<string>();
}

py::module
ArboreBinar::GetPySys()
{
    auto sys = py::module::import("sys");
    sys
      .attr("path")
      .attr("append")(ArboreBinar::GetCaleCatrePyLib());
    return sys;
}

ArboreBinar::Nod
ArboreBinar::CreareNod(string p_informatie_nod,
                       unsigned short p_nivel)
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
        this->_nod_curent->_directie = E_Directie::Sus;
        if (this->_nod_curent->_dreapta != nullptr)
        {
            this->_nod_curent = this->_nod_curent->_dreapta;
            return true;
        }
        return false;
    }

    if (p_directie == E_Directie::Sus)
    {
        if (this->_nod_curent == this->_radacina)
        {
            if (!this->DeplasareNodCurent(E_Directie::Stanga))
            {
                this->DeplasareNodCurent(E_Directie::Dreapta);
            }
        } else
        {
            this->_nod_curent->_directie = E_Directie::Stanga;
            this->DeplasareNodCurentSus(this->_radacina);
        }
        return true;
    }

    return false;
}

void
ArboreBinar::DeplasareNodCurentUndeEstePosibil()
{
    while (!this->DeplasareNodCurent(this->_nod_curent->_directie))
    { /* Maxim 3 iterații, deoarece DeplasareNodCurent(E_Directie::Sus) va fi mereu true. */}
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

            if (this->_nod_curent->_stanga->_nivel >= this->_noduri_per_nivel.size())
            {
                this->_noduri_per_nivel.push_back(1);
            } else
            {
                this->_noduri_per_nivel[this->_nod_curent->_stanga->_nivel]++;
            }
            if (this->_nod_curent->_dreapta != nullptr)
            {
                this->_numar_frunze++;
            }
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

            if (this->_nod_curent->_dreapta->_nivel >= this->_noduri_per_nivel.size())
            {
                this->_noduri_per_nivel.push_back(1);
            } else
            {
                this->_noduri_per_nivel[this->_nod_curent->_dreapta->_nivel]++;
            }
            if (this->_nod_curent->_stanga != nullptr)
            {
                this->_numar_frunze++;
            }
        } else
        {
            this->_nod_curent->_dreapta->_informatie = p_nod->_dreapta->_informatie;
        }
    }

    this->_nod_curent->_directie = E_Directie::Stanga;
    this->DeplasareNodCurentUndeEstePosibil();
}

void
ArboreBinar::InitializareArboreCazRadacinaGoala(Nod p_nod)
{
    this->_nod_curent = this->_radacina = p_nod;
    this->_noduri_per_nivel = vector<unsigned int>({1});
    this->_numar_frunze = 1;

    if (this->_nod_curent->_stanga != nullptr || this->_nod_curent->_dreapta != nullptr)
    {
        this->_noduri_per_nivel.push_back(1);
        if (this->_nod_curent->_stanga != nullptr && this->_nod_curent->_dreapta != nullptr)
        {
            this->_noduri_per_nivel[1] = this->_numar_frunze = 2;
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
         : 0,

         p_informatie_descendent_1,

         p_informatie_descendent_2,

         p_directie);

    if (ArboreBinar::NoduriCuInformatiiEgale(this->_nod_curent, nod_nou))
    {
        this->DeplasareNodCurentUndeEstePosibil();
        delete nod_nou;
    } else
    {
        if (this->_radacina == nullptr)
        {
            this->InitializareArboreCazRadacinaGoala(nod_nou);
        }
        this->EditareNodCurentExistent(nod_nou);
    }

    delete p_informatie_descendent_1;
    delete p_informatie_descendent_2;
    delete p_directie;
}

void
ArboreBinar::StergereRadacina()
{
    this->DezalocareArbore(this->_radacina);
    this->_nod_curent = this->_radacina = nullptr;
}

py::object
ArboreBinar::ConstruireArboreAfisare(Nod p_nod,
                                     py::function p_py_nod)
{
    if (p_nod != nullptr)
    {
        if (p_nod->_informatie.empty())
        {
            return p_py_nod;
        }

        auto descendenti = vector<py::object>();
        if (p_nod->_dreapta != nullptr)
        {
            descendenti.push_back(this->ConstruireArboreAfisare(p_nod->_dreapta, p_py_nod));
        }
        if (p_nod->_stanga != nullptr)
        {
            descendenti.push_back(this->ConstruireArboreAfisare(p_nod->_stanga, p_py_nod));
        }

        string informatie = p_nod->_informatie;
        if (p_nod == this->_nod_curent)
        {
            informatie = ArboreBinar::_PREFIX_NOD_CURENT + informatie + ArboreBinar::_POSTFIX_NOD_CURENT;
        } else if ((this->_nod_curent->_stanga == nullptr) != (this->_nod_curent->_dreapta == nullptr))
        {
            if (p_nod == this->_nod_curent->_stanga)
            {
                informatie = ArboreBinar::_PREFIX_DESCENDENT_STANG + informatie;
            } else if (p_nod == this->_nod_curent->_dreapta)
            {
                informatie = ArboreBinar::_PREFIX_DESCENDENT_DREPT + informatie;
            }
        }
        py::list py_descendenti = py::cast(descendenti);
        return
          p_py_nod
            (informatie)
            (py_descendenti);
    }
    return p_py_nod();
}

void
ArboreBinar::DezalocareArbore(Nod p_nod)
{
    if (p_nod == nullptr)
    {
        return;
    }

    if (p_nod->_stanga == nullptr && p_nod->_dreapta == nullptr)
    {
        this->_numar_frunze--;
    } else
    {
        if (p_nod->_stanga != nullptr)
        {
            this->DezalocareArbore(p_nod->_stanga);
        }
        if (p_nod->_dreapta != nullptr)
        {
            this->DezalocareArbore(p_nod->_dreapta);
        }
    }

    this->_noduri_per_nivel[p_nod->_nivel]--;
    if (this->_noduri_per_nivel.back() == 0)
    {
        this->_noduri_per_nivel.pop_back();
    }
    delete p_nod;
}

// --- Public ---

vector<ArboreBinar::NodDto>
ArboreBinar::GetNodDtoInitVect()
{
    return vector<NodDto>();
}

ArboreBinar::ArboreBinar()
{
    this->_id_curent = 0;

    this->_radacina = nullptr;
    this->_nod_curent = nullptr;

    this->_noduri_per_nivel = vector<unsigned int>();
    this->_numar_frunze = 0;
}

ArboreBinar::~ArboreBinar()
{
    this->DezalocareArbore(this->_radacina);
}

ArboreBinar::Celula::Celula(string p_informatie,
                            unsigned int p_id,
                            unsigned short p_nivel)
  : Celula(p_informatie,
           p_id,
           p_nivel,
           nullptr,
           nullptr,
           E_Directie::Stanga)
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
    auto numar_noduri = 0;
    for (auto nivel: this->_noduri_per_nivel)
    {
        numar_noduri += nivel;
    }

    return {
      ._numar_noduri = to_string(numar_noduri),
      ._numar_frunze = to_string(this->_numar_frunze),
      ._numar_niveluri = to_string(this->_noduri_per_nivel.size())
    };
}

void
ArboreBinar::SalvareNod
  (string p_informatie_nod,
   string p_informatie_descendent_stang,
   string p_informatie_descendent_drept)
{
    TrimStrings({
                  &p_informatie_nod,
                  &p_informatie_descendent_stang,
                  &p_informatie_descendent_drept
                });

    if (p_informatie_nod.empty())
    {
        return;
    }

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
    return ArboreBinar::RSD(this->_radacina);
}

vector<ArboreBinar::NodDto>
ArboreBinar::ParcurgerePreordineDeLaNodulCurent()
{
    return ArboreBinar::RSD(this->_nod_curent);
}

vector<ArboreBinar::NodDto>
ArboreBinar::ParcurgereInordineDeLaRadacina()
{
    return ArboreBinar::SRD(this->_radacina);
}

vector<ArboreBinar::NodDto>
ArboreBinar::ParcurgereInordineDeLaNodulCurent()
{
    return ArboreBinar::SRD(this->_nod_curent);
}

vector<ArboreBinar::NodDto>
ArboreBinar::ParcurgerePostordineDeLaRadacina()
{
    return ArboreBinar::SDR(this->_radacina);
}

vector<ArboreBinar::NodDto>
ArboreBinar::ParcurgerePostordineDeLaNodulCurent()
{
    return ArboreBinar::SDR(this->_nod_curent);
}

vector<ArboreBinar::NodDto>
ArboreBinar::ParcurgereInLatimeDeLaRadacina()
{
    return ArboreBinar::ParcurgereInLatime(this->_radacina);
}

vector<ArboreBinar::NodDto>
ArboreBinar::ParcurgereInLatimeDeLaNodulCurent()
{
    return ArboreBinar::ParcurgereInLatime(this->_nod_curent);
}

void
ArboreBinar::StergereSubArboreAlNoduluiCurent()
{
    if (this->_nod_curent == this->_radacina)
    {
        this->StergereRadacina();
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

    if (this->_nod_curent->_stanga == nullptr && this->_nod_curent->_dreapta == nullptr)
    {
        this->_numar_frunze++;
    }
}

void
ArboreBinar::ResetareArbore()
{
    this->StergereRadacina();
}

string
ArboreBinar::GetReprezentareGrafica()
{
    if (this->_radacina == nullptr)
    {
        return string();
    }

    py::scoped_interpreter interpreter{};

    auto sys = ArboreBinar::GetPySys();
    auto modul_afisare = sys.import("AfisareArbore");
    auto py_nod = modul_afisare.attr("Node");
    auto arbore_construit = this->ConstruireArboreAfisare(this->_radacina, py_nod);

    string reprezentare_grafica =
      modul_afisare.attr("DrawTree")
          (py::bool_(false))
          (py::bool_(false))
          (arbore_construit)
        .cast<string>();

    return reprezentare_grafica;
}
