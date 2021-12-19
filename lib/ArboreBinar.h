#ifndef PROIECT_FINAL_ARBOREBINAR_H
#define PROIECT_FINAL_ARBOREBINAR_H

#include <string>
#include <stdexcept>

using std::string;

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
        Celula *_stanga;
        Celula *_dreapta;
        E_Directie _directie;

        Celula(string);

        Celula(string, Celula *, Celula *, E_Directie);
    };

    typedef Celula *Nod;

    Nod _radacina;
    Nod _nod_curent;

    Nod CreareNod(string);

    Nod CreareNod(string, string, E_Directie);

    Nod CreareNod(string, string, string);

    Nod RouterCreareNod(string, string *, string *, E_Directie *);

    void EditareNodCurentExistent(Nod);

    bool NoduriCuInformatiiEgale(Nod, Nod);

    void DeplasareNodCurentSus(Nod);

    bool DeplasareNodCurent(E_Directie);

    void SalvareNod(string, string *, string *, E_Directie *);

    void DezalocareArbore(Nod);

public:
    struct NodDto // data transfer object
    {
        string _informatie_nod;
        string _informatie_descendent_stang;
        string _informatie_descendent_drept;
    };

    ArboreBinar();

    ~ArboreBinar();

    NodDto GetInformatiiNodCurent();

    void SalvareNod(string, string, string);

};


#endif
