#include "utilitare.h"

int main(int argc, const char *argv[])
{
    SetConsoleOutputCP(65001);

    ArboreBinar arbore_binar;

    auto screen = ScreenInteractive::Fullscreen();

    string val_nod{}, val_copil_stang{}, val_copil_drept{};


    Component input_val_nod = Input(&val_nod, "editati valoarea nodului");

    auto optiune_buton_salv_nod = ButtonOption();
    optiune_buton_salv_nod.border = false;

    auto buton_salvare_nod = Container::Horizontal({
                                                     Button("[Salveaza si adauga nod]", [&]
                                                            {
                                                                arbore_binar.SalvareNod(val_nod, val_copil_stang, val_copil_drept);
                                                                auto informatii_nod_crt = arbore_binar.GetInformatiiNodCurent();
                                                                val_nod = informatii_nod_crt._nod_curent._informatie_nod;
                                                                val_copil_stang = informatii_nod_crt._informatie_descendent_stang;
                                                                val_copil_drept = informatii_nod_crt._informatie_descendent_drept;
                                                            },
                                                            &optiune_buton_salv_nod),
                                                   });


    int adancime = 0;

    auto optiune_buton_salv_copil_stang = ButtonOption();
    optiune_buton_salv_copil_stang.border = false;
    auto buton_salvare_copil_stang = Container::Horizontal({
                                                             Button("[Salveaza copil stang]", [&]
                                                                    { adancime = 0; },
                                                                    &optiune_buton_salv_copil_stang),
                                                           });

    auto optiune_buton_salv_copil_drept = ButtonOption();
    optiune_buton_salv_copil_drept.border = false;
    auto buton_salvare_copil_drept = Container::Horizontal({
                                                             Button("[Salveaza copil drept]", [&]
                                                                    { adancime = 0; },
                                                                    &optiune_buton_salv_copil_drept),
                                                           });

    auto container_adancime_1_st = Container::Vertical({
                                                         Input(&val_copil_stang, "copil stang"),
                                                         buton_salvare_copil_stang,
                                                       });

    auto randare_adancime_1_copil_st = Renderer(container_adancime_1_st, [&]
    {
        return vbox({hbox(text("Introduceti valoare: ")),
                     container_adancime_1_st->Render() | center}) | border;
    });

    auto container_adancime_2_dr = Container::Vertical({
                                                         Input(&val_copil_drept, "copil drept"),
                                                         buton_salvare_copil_drept,
                                                       });

    auto randare_adancime_2_copil_dr = Renderer(container_adancime_2_dr, [&]
    {
        return vbox({hbox(text("Introduceti valoare: ")),
                     container_adancime_2_dr->Render() | center}) |
               border;
    });

    auto butoane_salvare_copii = Container::Horizontal({
                                                         Button(
                                                           "[Copil stang]", [&]
                                                           { adancime = 1; },
                                                           &optiune_buton_salv_copil_stang),
                                                         Button(
                                                           "[Copil drept]", [&]
                                                           { adancime = 2; },
                                                           &optiune_buton_salv_copil_drept),
                                                       });

    auto tab_detalii_arbore = Renderer([&]
                                       {
                                           auto statistici = arbore_binar.GetStatisticiArbore();
                                           return window(text("Detalii Arbore"),//
                                                         vbox({hbox(text(" ")),
                                                               hbox(text("Nr. niveluri: " + statistici._numar_niveluri)),
                                                               hbox(text("Nr. noduri: " + statistici._numar_noduri)),
                                                               hbox(text("Nr. frunze: " + statistici._numar_frunze)),
                                                               hbox(text(" "))
                                                              })
                                           ) | size(ftxui::WIDTH, ftxui::EQUAL, 40);
                                       });

    auto tab_detalii_nod = Renderer([&]
                                    {
                                        return window(text("Detalii Nod Curent"),//
                                                      vbox({
                                                             hbox(text(" ")),
                                                             hbox(text(val_nod.empty() ? "Nod curent: - " :
                                                                       "Nod curent: "), text(val_nod) | color(Color::GreenLight)),
                                                             hbox(text(
                                                               val_copil_stang.empty() ? "Copil stang: - " :
                                                               "Copil stang: " + val_copil_stang)),
                                                             hbox(text(
                                                               val_copil_drept.empty() ? "Copil drept: - " :
                                                               "Copil drept: " + val_copil_drept)),
                                                             hbox(text(" ")),
                                                           })
                                        ) | size(ftxui::WIDTH, ftxui::EQUAL, 40);
                                    });

    auto proprietati_nod = Container::Vertical({
                                                 input_val_nod,
                                                 buton_salvare_nod,
                                                 butoane_salvare_copii
                                               });

    auto tab_editare_copii = Renderer(proprietati_nod, [&]
    {

        return window(text("Editare Nod Curent"),//
                      vbox({
                             hbox(text(" ")),
                             hbox(text("Nod Crt.: "), input_val_nod->Render()),
                             hbox(text(" ")),
                             separator(),
                             hbox({val_nod.empty() ? text("* Completati campul \"Nod Crt.\"") | color(Color::RedLight)
                                                   : buton_salvare_nod->Render()}) | center,

                             separator(),
                             hbox(text(val_copil_stang.empty() && val_copil_drept.empty()
                                       ? "* Nodul curent nu are copii (frunza)"
                                       : "")) | color(Color::GreenLight),
                             hbox(text(val_copil_stang.empty() ? "* Nu exista copil stang " : "Copil stang: " +
                                                                                              val_copil_stang)),

                             hbox(text(val_copil_drept.empty() ? "* Nu exista copil drept " : "Copil drept: " +
                                                                                              val_copil_drept)),
                             hbox(text(" ")),
                             separator(),
                             hbox({val_nod.empty() ? text("* Completati campul \"Nod Crt.\"") | color(Color::RedLight)
                                                   : butoane_salvare_copii->Render()}) | center
                           })
        ) | size(ftxui::WIDTH, ftxui::EQUAL, 40);
    });

    int parcurgere_selectata = 0;
    MenuOption optiuni_meniu;
    optiuni_meniu.style_selected = color(Color::CadetBlue);
    optiuni_meniu.style_focused = bgcolor(Color::CadetBlue);
    optiuni_meniu.style_selected_focused = bgcolor(Color::CadetBlue);

    bool stare_1{};
    bool stare_2{};
    bool schimbat = false;
    vector<string> elemente_meniu_parcurgeri = {"Preordine", "Inordine", "Postordine", "In Latime"};


    auto container_meniu_parcurgeri = Container::Vertical({});
    container_meniu_parcurgeri->Add(Menu(&elemente_meniu_parcurgeri, &parcurgere_selectata, &optiuni_meniu));

    auto optiuni_parcurgeri = Renderer(container_meniu_parcurgeri, [&]
    {
        return vbox({hbox(text(" ")),
                     hbox(vbox(text("Selectati parcurgerea: ")),
                          vbox({container_meniu_parcurgeri->Render()})),
                     hbox(text(" ")),
                     separator()
                    });
    });

    auto container_checkboxuri = Container::Vertical({});
    container_checkboxuri->Add(Checkbox("parcurgeti intreg arborele", &stare_1));
    container_checkboxuri->Add(Checkbox("parcurgeti subarborele nodului curent", &stare_2));

    auto meniu_checkboxuri = Renderer(container_checkboxuri, [&]
    {
        return vbox(container_checkboxuri->Render() | frame |
                    size(HEIGHT, LESS_THAN, 10));
    });

    auto meniu_final_parcurgeri = Container::Vertical({
                                                        optiuni_parcurgeri,
                                                        meniu_checkboxuri
                                                      });

    Elements vector_linii_arbore = ConversieStringMulti(GetStringReprezentareGrafica(), "\n");
    auto reprezentare_grafica = Renderer(meniu_final_parcurgeri, [&]
    {
        if (stare_1 && !schimbat)
        {
            schimbat = true;
            if (schimbat)
            {
                stare_2 = false;
            }
        } else if (stare_2 && schimbat)
        {
            schimbat = false;
            if (!schimbat)
            {
                stare_1 = false;
            }
        } else if (!stare_1 && !stare_2)
        {
            stare_1 = true;
        }

        auto informatii_nod = arbore_binar.GetInformatiiNodCurent();

        auto vector_noduri_parcurse = arbore_binar.GetNodDtoInitVect();

        if (!informatii_nod._nod_curent._informatie_nod.empty())
            switch (parcurgere_selectata)
            {
                case 0:
                {
                    if (stare_1)
                        vector_noduri_parcurse = arbore_binar.ParcurgerePreordineDeLaRadacina();
                    else if (stare_2)
                        vector_noduri_parcurse = arbore_binar.ParcurgerePreordineDeLaNodulCurent();
                    break;
                }
                case 1:
                {
                    if (stare_1)
                        vector_noduri_parcurse = arbore_binar.ParcurgereInordineDeLaRadacina();
                    else if (stare_2)
                        vector_noduri_parcurse = arbore_binar.ParcurgereInordineDeLaNodulCurent();
                    break;
                }
                case 2:
                {
                    if (stare_1)
                        vector_noduri_parcurse = arbore_binar.ParcurgerePostordineDeLaRadacina();
                    else if (stare_2)
                        vector_noduri_parcurse = arbore_binar.ParcurgerePostordineDeLaNodulCurent();
                    break;
                }
                case 3:
                {
                    if (stare_1)
                        vector_noduri_parcurse = arbore_binar.ParcurgereInLatimeDeLaRadacina();
                    else if (stare_2)
                        vector_noduri_parcurse = arbore_binar.ParcurgereInLatimeDeLaNodulCurent();
                    break;
                }
                default:
                {
                    throw std::logic_error("Eroare fatala!");
                }
            }

        Elements elemente_parcurse, vector_final;
        size_t parte_intreaga{};

        if (!informatii_nod._nod_curent._informatie_nod.empty() && !vector_noduri_parcurse.empty())
        {
            if (vector_noduri_parcurse.front()._id_nod == informatii_nod._nod_curent._id_nod)
                elemente_parcurse.push_back(
                  hbox(hbox(text(vector_noduri_parcurse.front()._informatie_nod))
                       | border
                       | color(Color::GreenLight)
                       | center)
                );
            else
            {
                elemente_parcurse.push_back(hbox((text(vector_noduri_parcurse.front()._informatie_nod)) | border
                                                 | center)
                );
            }

            for (int i = 1; i < vector_noduri_parcurse.size(); i++)
            {
                if (vector_noduri_parcurse[i]._id_nod == informatii_nod._nod_curent._id_nod)
                    elemente_parcurse.push_back(hbox({text("→") | center,
                                                      hbox(text(vector_noduri_parcurse[i]._informatie_nod)) | border |
                                                      color(Color::GreenLight) | center}));
                else
                {
                    elemente_parcurse.push_back(
                      hbox({text("→") | center, hbox(text(vector_noduri_parcurse[i]._informatie_nod)) | border | center}));
                }
            }

            parte_intreaga = elemente_parcurse.size() / 10;

            if (parte_intreaga > 1)
            {
                auto vector_out = ImpartireVector(elemente_parcurse, parte_intreaga);
                vector_final = AfisareElementeParcurseImpartite(vector_out);
            } else
            {
                vector_final = elemente_parcurse;
            }
        }

        return window(text("Arbore Binar - Reprezentare Grafica"),
                      vbox({

                             filler(),
                             vbox(vector_linii_arbore) | center,
                             filler(),
                             !informatii_nod._nod_curent._informatie_nod.empty() ?
                             hbox({
                                    window(text("Meniu Parcurgere"),
                                           hbox({meniu_final_parcurgeri->Render()
                                                 | size(ftxui::WIDTH, ftxui::GREATER_THAN, 70),
                                                 separator(),
                                                 hbox({
                                                        hbox({hbox(parte_intreaga > 1 ?
                                                                   vbox(vector_final)
                                                                   | size(ftxui::WIDTH, ftxui::GREATER_THAN, 115)
                                                                                      :
                                                                   vbox({hbox(text(" ")),
                                                                         hbox({text(
                                                                           "Ordine noduri parcurse: ")}) |
                                                                         center,
                                                                         hbox({vector_final}) |
                                                                         center

                                                                        })
                                                                   | size(ftxui::WIDTH, ftxui::GREATER_THAN, 135))
                                                             })
                                                      })
                                                })
                                    )}
                             )
                                                                                 : hbox({})}
                      ))
               | size(ftxui::WIDTH,
                      ftxui::GREATER_THAN,
                      185);
    });

    auto container_adancime_0 = Container::Vertical(
      {tab_detalii_arbore, tab_detalii_nod, tab_editare_copii,
       reprezentare_grafica});
    auto randare_adancime_0 = Renderer(container_adancime_0, [&]
    {
        return hbox({hbox({vbox({tab_detalii_arbore->Render(),
                                 tab_detalii_nod->Render(),
                                 tab_editare_copii->Render(),
                                })
                          }),
                     hbox({reprezentare_grafica->Render()}) | flex
                    });
    });

    auto container_principal = Container::Tab({randare_adancime_0,
                                               randare_adancime_1_copil_st,
                                               randare_adancime_2_copil_dr
                                              }, &adancime);

    auto randare_principala = Renderer(container_principal, [&]
    {
        Element document = randare_adancime_0->Render();

        if (adancime == 1 && !val_nod.empty())
        {
            document = dbox({document,
                             randare_adancime_1_copil_st->Render() | clear_under | center,
                            });
        } else if (adancime == 2 && !val_nod.empty())
        {
            document = dbox({document,
                             randare_adancime_2_copil_dr->Render() | clear_under | center,
                            });
        }
        return document;
    });

    screen.Loop(randare_principala);
    return EXIT_SUCCESS;
}
