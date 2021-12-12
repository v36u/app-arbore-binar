#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include "ArboreBinar.h"

ArboreBinar::ArboreBinar() {
    this->_radacina = nullptr;
    this->_nod_curent = nullptr;
    this->_directie = false;
}

ArboreBinar::~ArboreBinar() {
    // TODO: Dezalocă toate nodurile și apoi și rădăcina
}

ArboreBinar::Nod ArboreBinar::CreareNod(const string &p_informatie_nod) {
    return new Celula {
            ._informatie = p_informatie_nod,
            ._stanga = nullptr,
            ._dreapta = nullptr
    };
}

ArboreBinar::Nod ArboreBinar::CreareNod(const string &p_informatie_nod, const string &p_informatie_copil, const bool &p_directie) {
    return new Celula {
            ._informatie = p_informatie_nod,
            ._stanga = !p_directie ? this->CreareNod(p_informatie_copil) : nullptr,
            ._dreapta = p_directie ? this->CreareNod(p_informatie_copil) : nullptr
    };
}

ArboreBinar::Nod ArboreBinar::CreareNod(const string &p_informatie_nod, const string &p_informatie_copil_stang, const string &p_informatie_copil_drept) {
    return new Celula {
            ._informatie = p_informatie_nod,
            ._stanga = this->CreareNod(p_informatie_copil_stang),
            ._dreapta = this->CreareNod(p_informatie_copil_drept)
    };
}

// TODO: Pare cam complicat.. se poate simplifica?
ArboreBinar::Nod ArboreBinar::GasireTataNodCurent(const Nod &p_nod)
{
    if (p_nod == nullptr) {
        return nullptr;
    }
    if (p_nod->_stanga == this->_nod_curent || p_nod->_dreapta == this->_nod_curent) {
        return p_nod;
    }
    if (p_nod->_stanga != nullptr) {
        return GasireTataNodCurent(p_nod->_stanga);
    }
    if (p_nod->_dreapta != nullptr) {
        return GasireTataNodCurent(p_nod->_dreapta);
    }
    return nullptr;
}

void ArboreBinar::DeplasareInapoi()
{
    if (this->_radacina == this->_nod_curent) {
        return;
    }
    this->_nod_curent = GasireTataNodCurent(this->_radacina);
}

string ArboreBinar::GetRadacina() {
    if (this->_radacina == nullptr) {
        return "";
    }
    return this->_radacina->_informatie;
}

// TODO: Minimizează nesting și maximizează reutilizarea
void ArboreBinar::SalvareNod(const string &p_informatie_nod) {
    if (this->_radacina == nullptr) {
        if (p_informatie_nod.empty()) {
            return;
        }
        this->_radacina = this->CreareNod(p_informatie_nod);
        this->_nod_curent = this->_radacina;
        return;
    }

    if (!this->_directie) {
        if (!p_informatie_nod.empty()) {
            if (this->_nod_curent->_stanga != nullptr) {
                this->_nod_curent->_stanga->_informatie = p_informatie_nod;
            } else {
                this->_nod_curent->_stanga = CreareNod(p_informatie_nod);
            }
            this->_nod_curent = this->_nod_curent->_stanga;
        } else {
          this->_directie = true;
        }
    } else {
        if (!p_informatie_nod.empty()) {
            if (this->_nod_curent->_dreapta != nullptr) {
                this->_nod_curent->_dreapta->_informatie = p_informatie_nod;
            } else {
                this->_nod_curent->_dreapta = CreareNod(p_informatie_nod);
            }
            this->_nod_curent = this->_nod_curent->_dreapta;
        } else {
            DeplasareInapoi();
        }
        this->_directie = false;
    }
}

// TODO: Minimizează nesting și maximizează reutilizarea
void ArboreBinar::SalvareNod(const string &p_informatie_nod, const string &p_informatie_copil, const bool &p_directie) {

}

// TODO: Minimizează nesting și maximizează reutilizarea
void ArboreBinar::SalvareNod(const string &, const string &, const string &) {

}

#pragma clang diagnostic pop