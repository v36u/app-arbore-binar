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
        string _informatie;
        unsigned short _nivel;
        Celula *_stanga;
        Celula *_dreapta;
        E_Directie _directie;

        Celula(string, unsigned short);

        Celula(string, unsigned short, Celula *, Celula *, E_Directie);
    };

    typedef Celula *Nod;

    Nod _radacina;
    Nod _nod_curent;

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
    EditareNodCurentExistent(Nod);

    bool
    NoduriCuInformatiiEgale(Nod, Nod);

    void
    DeplasareNodCurentSus(Nod);

    bool
    DeplasareNodCurent(E_Directie);

    void
    InitializareCazRadacinaGoala(Nod);

    void
    SalvareNod(string, string *, string *, E_Directie *);

    void
    DezalocareArbore(Nod);

    vector<string>
    RSD(Nod); //=> Rădăcină, Stânga, Dreapta

    vector<string>
    SRD(Nod); //=> Stânga, Rădăcină, Dreapta

    vector<string>
    SDR(Nod); //=> Stânga, Dreapta, Rădăcină

    vector<string>
    ParcurgereInLatime(Nod);

public:
    struct NodDto
    {
        string _informatie_nod;
        string _informatie_descendent_stang;
        string _informatie_descendent_drept;
    };

    struct StatisticiDto
    {
        string _numar_noduri;
        string _numar_frunze;
        string _numar_niveluri;
    };

    ArboreBinar();

    ~ArboreBinar();

    NodDto
    GetInformatiiNodCurent();

    StatisticiDto
    GetStatisticiArbore();

    void
    SalvareNod(string, string, string);

    vector<string>
    ParcurgerePreordineDeLaRadacina();

    vector<string>
    ParcurgerePreordineDeLaNodulCurent();

    vector<string>
    ParcurgereInordineDeLaRadacina();

    vector<string>
    ParcurgereInordineDeLaNodulCurent();

    vector<string>
    ParcurgerePostordineDeLaRadacina();

    vector<string>
    ParcurgerePostordineDeLaNodulCurent();

    vector<string>
    ParcurgereInLatimeDeLaRadacina();

    vector<string>
    ParcurgereInLatimeDeLaNodulCurent();

};

#endif
