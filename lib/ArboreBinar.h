#ifndef PROIECT_FINAL_ARBOREBINAR_H
#define PROIECT_FINAL_ARBOREBINAR_H

#include "utilitare.h"

#include <string>
#include <vector>

#include <Python.h>
#include "pybind11/embed.h"
#include "pybind11/stl.h"

namespace py = pybind11;
using namespace py::literals;

using std::string;
using std::to_string;
using std::vector;

class ArboreBinar
{
private:
    enum E_Directie
    {
        Stanga,
        Dreapta,
        Sus,
    };

    class Celula
    {
    public:
        unsigned int _id;
        string _informatie;
        unsigned short _nivel;
        Celula *_stanga;
        Celula *_dreapta;
        E_Directie _directie;

        Celula(string, unsigned int, unsigned short);

        Celula(string, unsigned int, unsigned short, Celula *, Celula *, E_Directie);
    };

    typedef Celula *Nod;

    struct NodDto
    {
        unsigned int _id_nod;
        string _informatie_nod;
    };

    struct InformatiiNodDto
    {
        NodDto _nod_curent;
        string _informatie_descendent_stang;
        string _informatie_descendent_drept;
    };

    struct StatisticiDto
    {
        string _numar_noduri;
        string _numar_frunze;
        string _numar_niveluri;
    };

    static string _PREFIX_NOD_CURENT;
    static string _POSTFIX_NOD_CURENT;

    unsigned int _id_curent;

    Nod _radacina;
    Nod _nod_curent;

    vector<unsigned int> _noduri_per_nivel;
    unsigned short _numar_frunze;

    static bool
    NoduriCuInformatiiEgale(Nod, Nod);

    static vector<NodDto>
    RSD(Nod); //=> Rădăcină, Stânga, Dreapta

    static vector<NodDto>
    SRD(Nod); //=> Stânga, Rădăcină, Dreapta

    static vector<NodDto>
    SDR(Nod); //=> Stânga, Dreapta, Rădăcină

    static vector<NodDto>
    ParcurgereInLatime(Nod);

    static string
    GetCaleCatrePyLib();

    static py::module
    GetPySys();

    Nod
    CreareNod(string, unsigned short);

    Nod
    CreareNod(string, unsigned short, string, E_Directie);

    Nod
    CreareNod(string, unsigned short, string, string);

    Nod
    RouterCreareNod(string, unsigned short, string *, string *, E_Directie *);

    void
    DeplasareNodCurentSus(Nod);

    bool
    DeplasareNodCurent(E_Directie);

    void
    DeplasareNodCurentUndeEstePosibil();

    void
    EditareNodCurentExistent(Nod);

    void
    InitializareArboreCazRadacinaGoala(Nod);

    void
    SalvareNod(string, string *, string *, E_Directie *);

    void
    StergereRadacina();

    py::object
    ConstruireArboreAfisare(Nod, py::function);

    void
    DezalocareArbore(Nod);

public:
    static vector<NodDto>
    GetNodDtoInitVect();

    ArboreBinar();

    ~ArboreBinar();

    InformatiiNodDto
    GetInformatiiNodCurent();

    StatisticiDto
    GetStatisticiArbore();

    void
    SalvareNod(string, string, string);

    vector<NodDto>
    ParcurgerePreordineDeLaRadacina();

    vector<NodDto>
    ParcurgerePreordineDeLaNodulCurent();

    vector<NodDto>
    ParcurgereInordineDeLaRadacina();

    vector<NodDto>
    ParcurgereInordineDeLaNodulCurent();

    vector<NodDto>
    ParcurgerePostordineDeLaRadacina();

    vector<NodDto>
    ParcurgerePostordineDeLaNodulCurent();

    vector<NodDto>
    ParcurgereInLatimeDeLaRadacina();

    vector<NodDto>
    ParcurgereInLatimeDeLaNodulCurent();

    void
    StergereSubArboreAlNoduluiCurent();

    void
    ResetareArbore();

    string
    GetReprezentareGrafica();
};

#endif
