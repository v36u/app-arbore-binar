#ifndef PROIECT_FINAL_ARBOREBINAR_H
#define PROIECT_FINAL_ARBOREBINAR_H

#include <string>

using std::string;

// Convenții:
// 1) Directie: false = stânga, true = dreapta

class ArboreBinar
{
private:
    struct Celula {
        string _informatie;
        Celula *_stanga;
        Celula *_dreapta;
    };
    typedef Celula *Nod;
    Nod _radacina;
    Nod _nod_curent;
    bool _directie;

    Nod CreareNod(const string&);
    Nod CreareNod(const string&, const string&, const bool&);
    Nod CreareNod(const string&, const string&, const string&);

    Nod GasireTataNodCurent(const Nod&);
    void DeplasareInapoi();

public:
    ArboreBinar();
    ~ArboreBinar();
    string GetRadacina();
    void SalvareNod(const string&);
    void SalvareNod(const string&, const string&, const bool&);
    void SalvareNod(const string&, const string&, const string&);
};


#endif
