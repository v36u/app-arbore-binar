#ifndef PROIECT_FINAL_ARBOREBINAR_H
#define PROIECT_FINAL_ARBOREBINAR_H

#include <string>

using std::string;

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
public:
    ArboreBinar();
    ~ArboreBinar();
};


#endif
