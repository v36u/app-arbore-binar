#ifndef PROIECT_FINAL_ARBOREBINAR_H
#define PROIECT_FINAL_ARBOREBINAR_H

#include <string>
#include <vector>

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

    Nod _radacina;
    Nod _nod_curent;

    unsigned int _id_curent;

    unsigned short _numar_noduri;
    unsigned short _numar_frunze;
    unsigned short _numar_niveluri;

    Nod
    CreareNod(string, unsigned short);

    Nod
    CreareNod(string, unsigned short, string, E_Directie);

    Nod
    CreareNod(string, unsigned short, string, string);

    Nod
    RouterCreareNod(string, unsigned short, string *, string *, E_Directie *);

    bool
    EsteFrunza(Nod);

    void
    DeplasareNodCurentSus(Nod);

    bool
    DeplasareNodCurent(E_Directie);

    void
    DeplasareNodCurentUndeEstePosibil();

    void
    DezalocareArbore(Nod);

    void
    EditareNodCurentExistent(Nod);

    bool
    NoduriCuInformatiiEgale(Nod, Nod);

    void
    InitializareCazRadacinaGoala(Nod);

    void
    SalvareNod(string, string *, string *, E_Directie *);

    vector<NodDto>
    RSD(Nod); //=> Rădăcină, Stânga, Dreapta

    vector<NodDto>
    SRD(Nod); //=> Stânga, Rădăcină, Dreapta

    vector<NodDto>
    SDR(Nod); //=> Stânga, Dreapta, Rădăcină

    vector<NodDto>
    ParcurgereInLatime(Nod);

    void
    StergereRadacina();

public:
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

    vector<NodDto>
    GetNodDtoInitVect();

    void
    StergereSubArboreAlNoduluiCurent();

    void
    ResetareArbore();
};

#endif
