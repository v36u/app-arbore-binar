#ifndef PROIECT_FINAL_ARBOREBINAR_H
#define PROIECT_FINAL_ARBOREBINAR_H

#include <string>

using std::string;

// Convenții:
// 1) Directie: false = stânga, true = dreapta

class ArboreBinar
{
private:
// --- Membrii ---
    struct Celula
    {
        string _informatie;
        Celula *_stanga;
        Celula *_dreapta;
    };
    typedef Celula *Nod;

    Nod _radacina;
    Nod _nod_curent;

    bool _directie;

// --- Metode ---
    Nod CreareNod(const string &);

    Nod CreareNod(const string &, const string &, const bool &);

    Nod CreareNod(const string &, const string &, const string &);

    Nod GasireTataNodCurent(const Nod &);

    void DeplasareInapoi();

    void RouterSalvareNod(const string &, const string *, const string *, const bool *);

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

    void SalvareNod(const string &);

    void SalvareNod(const string &, const string &, const bool &);

    void SalvareNod(const string &, const string &, const string &);

};


#endif
