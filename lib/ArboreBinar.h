#ifndef PROIECT_FINAL_ARBOREBINAR_H
#define PROIECT_FINAL_ARBOREBINAR_H

#include <string>

using std::string;

// Convenții:
// 1) Directie: false = stânga, true = dreapta

class ArboreBinar
{
private:
// --- Structuri ---
    struct Celula
    {
        string _informatie;
        Celula *_stanga;
        Celula *_dreapta;
    };
    typedef Celula *Nod;

// --- Membrii ---
    Nod _radacina;
    Nod _nod_curent;

    bool _directie;
    bool _deplasat; // până găsesc o soluție mai elegantă

// --- Metode ---
    Nod CreareNod(string);

    Nod CreareNod(string, string, bool);

    Nod CreareNod(string, string, string);

    void DeplasareInapoiNodCurent(Nod);

    void RouterSalvareNod(string, string *, string *, bool *);

    void DezalocareArbore(Nod);

public:
// --- Structuri ---
    struct NodDto // data transfer object
    {
        string _informatie_nod;
        string _informatie_descendent_stang;
        string _informatie_descendent_drept;
    };

// --- Constructori ---
    ArboreBinar();

    ~ArboreBinar();

// --- Metode ---
    NodDto GetInformatiiNodCurent();

    void SalvareNod(string, string, string);

};


#endif
