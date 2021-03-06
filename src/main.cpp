#include "utilitare.h"
#include "componente.h"

ArboreBinar arbore_binar{};
string val_nod{};
string val_copil_stang{};
string val_copil_drept{};
int adancime{};
int parcurgere_selectata{};
bool stare_1{};
bool stare_2{};
bool schimbat{};

int main(void)
{
    auto screen = ScreenInteractive::Fullscreen();

    //Constructia modalului de pe adancimea 1 (Copil Stang)
    auto optiune_buton_salv_copil_stang = ButtonOption();
    optiune_buton_salv_copil_stang.border = false;

    auto buton_salvare_copil_stang = GetButonSalvareCopilStang(optiune_buton_salv_copil_stang, adancime);
    auto container_input_adancime_1_st = Container::Vertical({});
    container_input_adancime_1_st->Add(Input(&val_copil_stang, "introduceti valoarea copilului stang"));
    auto randare_input_adancime_1_st = RandareInputAdancime1(container_input_adancime_1_st, val_nod);
    auto randare_buton_adancime1_st = RandareButonAdancime1(buton_salvare_copil_stang);
    auto container_adancime_1_st = GetContainerAdancime1(randare_input_adancime_1_st,
                                                         randare_buton_adancime1_st);
    auto randare_adancime_1_st = GetModalCopilStang(container_adancime_1_st);

    //Constructia modalului de pe adancimea 2 (Copil Drept)
    auto optiune_buton_salv_copil_drept = ButtonOption();
    optiune_buton_salv_copil_drept.border = false;

    auto buton_salvare_copil_drept = GetButonSalvareCopilDrept(optiune_buton_salv_copil_drept, adancime);
    auto container_input_adancime_2_dr = Container::Vertical({});
    container_input_adancime_2_dr->Add(Input(&val_copil_drept, "introduceti valoarea copilului drept"));
    auto randare_input_adancime_2_dr = RandareInputAdancime2(container_input_adancime_2_dr, val_nod);
    auto randare_buton_adancime_2_dr = RandareButonAdancime2(buton_salvare_copil_drept);
    auto container_adancime_2_dr = GetContainerAdancime2(randare_input_adancime_2_dr,
                                                         randare_buton_adancime_2_dr);
    auto randare_adancime_2_dr = GetModalCopilDrept(container_adancime_2_dr);

    //Constructia tabului in care se regasesc detaliile arborelui (nr. frunze, nr. noduri, nr. niveluri)
    auto tab_detalii_arbore = GetTabDetaliiArbore(arbore_binar);

    //Constructia tabului in care se regasesc detaliile nodului curent selectat
    auto tab_detalii_nod = GetTabDetaliiNodCrt(val_nod, val_copil_stang, val_copil_drept);

    //Constructia tabului de editare a detaliilor nodului curent selectat
    auto input_val_nod = GetInputNodCrt(val_nod);

    auto optiune_buton_salv_nod = ButtonOption();
    optiune_buton_salv_nod.border = false;

    auto buton_salvare_nod = GetButonSalvareNod(val_nod,
                                                val_copil_stang,
                                                val_copil_drept,
                                                optiune_buton_salv_nod,
                                                arbore_binar);
    auto butoane_salvare_copii_tab_nod = GetButoaneCopiiTabNod(optiune_buton_salv_copil_stang,
                                                               optiune_buton_salv_copil_drept,
                                                               adancime);
    auto container_tab_nod_crt = GetContainerTabNod(input_val_nod,
                                                    buton_salvare_nod,
                                                    butoane_salvare_copii_tab_nod);

    auto tab_editare_nod_crt = GetTabEditareNodCurent(container_tab_nod_crt,
                                                      input_val_nod,
                                                      buton_salvare_nod,
                                                      butoane_salvare_copii_tab_nod,
                                                      val_nod,
                                                      val_copil_stang,
                                                      val_copil_drept);
    //Constructia tabului care contine Alte Optiuni (stergere subarbore nod curent, resetare arbore, iesire din program
    auto optiune_buton_stergere_subarbore = ButtonOption();
    optiune_buton_stergere_subarbore.border = false;
    auto optiune_buton_resetare_arbore = ButtonOption();
    optiune_buton_resetare_arbore.border = false;


    auto buton_stergere_subarbore = GetButonStergereSubarbore(optiune_buton_stergere_subarbore,
                                                              arbore_binar,
                                                              val_nod,
                                                              val_copil_stang,
                                                              val_copil_drept);
    auto buton_resetare_arbore = GetButonResetareArbore(optiune_buton_resetare_arbore,
                                                        arbore_binar,
                                                        val_nod,
                                                        val_copil_stang,
                                                        val_copil_drept);

    auto container_tab_alte_optiuni = Container::Vertical({
                                                            buton_stergere_subarbore,
                                                            buton_resetare_arbore,
                                                          });
    auto tab_alte_optiuni = GetTabAlteOptiuni(container_tab_alte_optiuni);


    //Constructia meniului de parcurgeri
    MenuOption optiuni_meniu;
    optiuni_meniu.style_selected = color(Color::CadetBlue);
    optiuni_meniu.style_focused = bgcolor(Color::CadetBlue);
    optiuni_meniu.style_selected_focused = bgcolor(Color::CadetBlue);


    vector<string> elemente_meniu_parcurgeri = {"Preordine", "Inordine", "Postordine", "In Latime"};

    auto container_meniu_parcurgeri = Container::Vertical({});
    container_meniu_parcurgeri->Add(Menu(&elemente_meniu_parcurgeri, &parcurgere_selectata, &optiuni_meniu));

    auto tab_optiuni_parcurgeri = GetTabOptiuniParcurgeri(container_meniu_parcurgeri);

    //Constructia tabului de selectare a tipului de parcurgere (prin intreg arborele / prin subarborele nodului curent)
    auto container_checkboxuri = Container::Vertical({});
    container_checkboxuri->Add(Checkbox("parcurgeti intreg arborele", &stare_1));
    container_checkboxuri->Add(Checkbox("parcurgeti subarborele nodului curent", &stare_2));
    auto tab_checkboxuri = GetTabCheckboxuri(container_checkboxuri);

    auto meniu_final_parcurgeri = Container::Vertical({
                                                        tab_optiuni_parcurgeri,
                                                        tab_checkboxuri
                                                      });

    //Constructia tabului care cuprinde reprezentarea grafica a arborelui + meniuri de parcurgeri
    auto tab_reprezentare_grafica = GetTabReprezentareGrafica(meniu_final_parcurgeri,
                                                              arbore_binar,
                                                              val_nod,
                                                              val_copil_stang,
                                                              val_copil_drept,
                                                              schimbat,
                                                              stare_1,
                                                              stare_2,
                                                              parcurgere_selectata);

    auto container_adancime_0 = Container::Vertical({
                                                      tab_detalii_arbore,
                                                      tab_detalii_nod,
                                                      tab_editare_nod_crt,
                                                      tab_alte_optiuni,
                                                      tab_reprezentare_grafica
                                                    });

    auto randare_adancime_0 = RandareAdancime0(container_adancime_0,
                                               tab_detalii_arbore,
                                               tab_detalii_nod,
                                               tab_editare_nod_crt,
                                               tab_alte_optiuni,
                                               tab_reprezentare_grafica);

    auto container_principal = Container::Tab({randare_adancime_0,
                                               randare_adancime_1_st,
                                               randare_adancime_2_dr
                                              }, &adancime);

    auto randare_principala = RandareLayere(container_principal,
                                            randare_adancime_0,
                                            randare_adancime_1_st,
                                            randare_adancime_2_dr,
                                            adancime,
                                            val_nod);
    screen.Loop(randare_principala);
    return EXIT_SUCCESS;
}
