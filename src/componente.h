#ifndef APP_ARBORE_BINAR_COMPONENTE_H
#define APP_ARBORE_BINAR_COMPONENTE_H

#include "utilitare.h"

Component
GetInputNodCrt(string &nod_curent);

shared_ptr<ComponentBase>
GetButonSalvareNod(string &nod_curent,
                   string &copil_stang,
                   string &copil_drept,
                   ButtonOption &optiune_buton_salvare);

shared_ptr<ComponentBase>
GetButonSalvareCopilStang(ButtonOption &optiune_buton_salvare);

shared_ptr<ComponentBase>
GetButonSalvareCopilDrept(ButtonOption &optiune_buton_salvare);

shared_ptr<ComponentBase>
RandareInputAdancime1(shared_ptr<ComponentBase> container_input_adancime_1);

shared_ptr<ComponentBase>
RandareButonAdancime1(shared_ptr<ComponentBase> buton_copil_stang);

shared_ptr<ComponentBase>
GetContainerAdancime1(shared_ptr<ComponentBase> randare_input,
                      shared_ptr<ComponentBase> randare_buton);

shared_ptr<ComponentBase>
GetModalCopilStang(shared_ptr<ComponentBase> &container_adancime_1);

shared_ptr<ComponentBase>
RandareInputAdancime2(shared_ptr<ComponentBase> container_input_adancime_1);

shared_ptr<ComponentBase>
RandareButonAdancime2(shared_ptr<ComponentBase> buton_copil_drept);

shared_ptr<ComponentBase>
GetContainerAdancime2(shared_ptr<ComponentBase> randare_input,
                      shared_ptr<ComponentBase> randare_buton);

shared_ptr<ComponentBase>
GetModalCopilDrept(shared_ptr<ComponentBase> &container_adancime_2);

shared_ptr<ComponentBase>
GetTabDetaliiArbore();

shared_ptr<ComponentBase>
GetTabDetaliiNodCrt();

shared_ptr<ComponentBase>
GetButoaneCopiiTabNod(ButtonOption &optiune_buton_copil_stang,
                      ButtonOption &optiune_buton_copil_drept);

shared_ptr<ComponentBase>
GetContainerTabNod(shared_ptr<ComponentBase> input_val_nod,
                   shared_ptr<ComponentBase> buton_salvare_nod,
                   shared_ptr<ComponentBase> butoane_salvare_copii_tab_nod);

shared_ptr<ComponentBase>
GetButonStergereSubarbore(ButtonOption &optiune_buton_stergere_subarbore);

shared_ptr<ComponentBase>
GetButonResetareArbore(ButtonOption &optiune_buton_resetare);


shared_ptr<ComponentBase>
GetTabEditareNodCurent(shared_ptr<ComponentBase> container_tab_nod,
                       shared_ptr<ComponentBase> input_val_nod,
                       shared_ptr<ComponentBase> buton_salvare_nod,
                       shared_ptr<ComponentBase> butoane_salvare_copii_tab_nod);

shared_ptr<ComponentBase>
GetTabAlteOptiuni(shared_ptr<ComponentBase> container_tab_alte_optiuni);

shared_ptr<ComponentBase>
GetTabOptiuniParcurgeri(shared_ptr<ComponentBase> container_meniu_parcurgeri);

shared_ptr<ComponentBase>
GetTabCheckboxuri(shared_ptr<ComponentBase> container_checkboxuri);

shared_ptr<ComponentBase>
GetTabReprezentareGrafica(shared_ptr<ComponentBase> meniu_final_parcurgeri);

shared_ptr<ComponentBase>
RandareAdancime0(shared_ptr<ComponentBase> container_adancime_0,
                 shared_ptr<ComponentBase> tab_detalii_arbore,
                 shared_ptr<ComponentBase> tab_detalii_nod,
                 shared_ptr<ComponentBase> tab_editare_nod_crt,
                 shared_ptr<ComponentBase> tab_alte_optiuni,
                 shared_ptr<ComponentBase> tab_reprezentare_grafica);

shared_ptr<ComponentBase>
RandareLayere(shared_ptr<ComponentBase> container_principal,
              shared_ptr<ComponentBase> randare_adancime_0,
              shared_ptr<ComponentBase> randare_adancime_1_st,
              shared_ptr<ComponentBase> randare_adancime_2_dr);

#endif //APP_ARBORE_BINAR_COMPONENTE_H
