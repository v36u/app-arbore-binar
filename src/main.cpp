#include <algorithm>
#include <memory>  // pentru allocator, __shared_ptr_access
#include <cstdlib>// pentru EXIT_SUCCESS
#include <string>  // pentru string, operator+ (supraincarcare), basic_string, to_string, char_traits
#include <vector>  // pentru vector, __alloc_traits<>::value_type

#include "ftxui/component/captured_mouse.hpp"    // pentru ftxui
#include "ftxui/component/component.hpp"         // pentru clasele Menu, Renderer, Horizontal, Vertical
#include "ftxui/component/component_base.hpp"    // pentru clasa ComponentBase
#include "ftxui/component/component_options.hpp" // pentru clasele InputOption, ButtonOption
#include "ftxui/component/screen_interactive.hpp"// pentru clasele Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"                // pentru text, Element, operator| (supraincarcare), window, flex, vbox
#include "ftxui/util/ref.hpp"                    // pentru clasa Ref

#include "../lib/ArboreBinar.h"

using namespace ftxui;
using namespace std;

template<typename T>
vector<vector<T>> ImpartireVector(vector<T> el_parcurse, size_t nr_segmente)
{
    vector<vector<T>> vector_out;

    int lungime = el_parcurse.size() / nr_segmente;
    int rest = el_parcurse.size() % nr_segmente;

    int inceput = 0;
    int sfarsit = 0;

    for (int i = 0; i < min<int>(nr_segmente, el_parcurse.size()); i++)
    {
        sfarsit += lungime + (rest-- > 0);
        vector_out.push_back(vector<T>(el_parcurse.begin() + inceput, el_parcurse.begin() + sfarsit));
        inceput = sfarsit;
    }
    return vector_out;
}

Elements AfisareElementeParcurseImpartite(vector<vector<Element>> vector)
{
    Elements vector_final;
    vector_final.push_back(hbox(text(" ")));
    vector_final.push_back(hbox({text("Ordine noduri parcurse: ")}) | center);

    for (int i = 0; i < vector.size() - 1; i++)
    {
        vector_final.push_back(hbox(vector[i], text("→") | center) | center);
    }
    vector_final.push_back(hbox(vector.back()) | center);
    return vector_final;
}

int main(int argc, const char *argv[])
{
    ArboreBinar arbore_binar;

    auto screen = ScreenInteractive::Fullscreen();
    // Am declarat variabilele in care se vor stoca valorile aferente nodului curent
    string val_nod{}, val_copil_stang{}, val_copil_drept{};

    // Aici am creat componenta care stocheaza valoarea introdusa de la tastatura a nodului curent (in input)
    Component input_val_nod = Input(&val_nod, "editati valoarea nodului");

    //    Component input_copil_stang = Input(&val_copil_stang, "introduceti valoarea");
    //    Component input_copil_drept = Input(&val_copil_drept, "introduceti valoarea");

    // Sectiune in care se definesc proprietatile butonului de salvare din fereastra "Editare si Adaugare Nod Curent"
    auto optiune_buton_salv_nod = ButtonOption();
    optiune_buton_salv_nod.border = false;

    auto buton_salvare_nod = Container::Horizontal({
                                                           Button("[Salveaza si adauga nod]", [&]
                                                                  {
                                                                      arbore_binar.SalvareNod(val_nod, val_copil_stang, val_copil_drept);
                                                                      auto informatii_nod_crt = arbore_binar.GetInformatiiNodCurent();
                                                                      val_nod = informatii_nod_crt._informatie_nod;
                                                                      val_copil_stang = informatii_nod_crt._informatie_descendent_stang;
                                                                      val_copil_drept = informatii_nod_crt._informatie_descendent_drept;
                                                                  },
                                                                  &optiune_buton_salv_nod),
                                                   });

    // Sectiune in care se definesc meniurile de tip Pop-Up din sectiunea editare copii
    // Variabila "adancime" - se refera la nivelul la care operam.
    // 0 - reprezinta zona de dedesubt
    // 1 - reprezinta nivelul cu meniul "Adaugare copil stanga"
    // 2 - reprezinta nivelul cu meniul "Adaugare copil dreapta"

    // Am setat "depth-ul" sau adancimea default ca fiind 0.
    // Adica default-ul este afisarea ferestrelor principale.
    int adancime = 0;

    // Sectiune care se ocupa de butonul de salvare a copilului stang
    // Acest buton face posibila revenirea la adancimea 0 a programului
    auto optiune_buton_salv_copil_stang = ButtonOption();
    optiune_buton_salv_copil_stang.border = false;
    auto buton_salvare_copil_stang = Container::Horizontal({
                                                                   Button("[Salveaza copil stang]", [&]
                                                                          { adancime = 0; },
                                                                          &optiune_buton_salv_copil_stang),
                                                           });
    // sfarsit sectiune

    // Sectiune care se ocupa de butonul de salvare a copilului drept
    // Acest buton face posibila revenirea la adancimea 0 a programului
    auto optiune_buton_salv_copil_drept = ButtonOption();
    optiune_buton_salv_copil_drept.border = false;
    auto buton_salvare_copil_drept = Container::Horizontal({
                                                                   Button("[Salveaza copil drept]", [&]
                                                                          { adancime = 0; },
                                                                          &optiune_buton_salv_copil_drept),
                                                           });
    // sfarsit sectiune

    // Sectiune care se ocupa cu randarea meniului Pop-Up de pe nivelul 1
    auto container_adancime_1_st = Container::Vertical({
                                                               Input(&val_copil_stang, "copil stang"),
                                                               buton_salvare_copil_stang,
                                                       });

    auto randare_adancime_1_copil_st = Renderer(container_adancime_1_st, [&]
    {
        return vbox({hbox(text("Introduceti valoare: ")),
                     container_adancime_1_st->Render() | center}) | border;
    });
    // sfarsit sectiune

    // Sectiune care se ocupa cu randarea meniului Pop-Up de pe nivelul 2
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
    // sfarsit sectiune

    // Sectiune in care se definesc proprietatile butoanelor de salvare si adaugare ale copiilor nodului curent
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
    // sfarsit sectiune

    // Aici se definesc proprietatile care vor fi "pasate" in componenta de editare a nodului
    auto proprietati_nod = Container::Vertical({
                                                       input_val_nod,
                                                       buton_salvare_nod,
                                               });

    // Sectiune care se ocupa cu randarea ferestrei Detalii Arbore
    auto tab_detalii_arbore = Renderer([&]
                                       {
                                           return window(text("Detalii Arbore"),//
                                                         vbox({hbox(text(" ")),
                                                               hbox(text("Nr. niveluri: -")),
                                                               hbox(text("Nr. noduri: -")),
                                                               hbox(text("Nr. frunze: -")),
                                                               hbox(text(" "))
                                                              })
                                           ) | size(ftxui::WIDTH, ftxui::EQUAL, 40);
                                       });
    // Sectiune care se ocupa cu randarea ferestrei Detalii Nod Curent
    auto tab_detalii_nod = Renderer([&]
                                    {
                                        return window(text("Detalii Nod Curent"),//
                                                      vbox({
                                                                   hbox(text(" ")),
                                                                   hbox(text(val_nod.empty() ? "Nod curent: - " :
                                                                             "Nod curent: " + val_nod)),
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
    // Sectiune care se ocupa cu randarea ferestrei de Editare si Adaugare Nod Curent
    auto tab_editare_nod = Renderer(proprietati_nod, [&]
    {
        return window(text("Editare si Adaugare Nod Curent"),//
                      vbox({hbox(text(" ")),
                            hbox(text("Nod Crt.: "), input_val_nod->Render()),
                            hbox(text(" ")),
                            separator(),
                            hbox({val_nod.empty() ? text("* Completati campul \"Nod Crt.\"") | color(Color::RedLight)
                                                  : buton_salvare_nod->Render()}) | center
                           })
        ) | size(ftxui::WIDTH, ftxui::EQUAL, 40);
    });

    // Aici se definesc proprietatile care vor fi "pasate" in componenta de editare a copiilor nodului curent
    auto proprietati_copii = Container::Vertical({butoane_salvare_copii});

    // Sectiune care se ocupa cu randarea ferestrei de Editare si Adaugare Copii Nod Curent
    auto tab_editare_copii = Renderer(proprietati_copii, [&]
    {
        return window(text("Editare Copii Nod Curent"),//
                      vbox({hbox(text(" ")),
                            hbox(text("Nod Crt. Selectat: " + val_nod)),
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

    // Sectiune care se ocupa cu randarea meniului cu traversari
    int parcurgere_selectata = 0;
    MenuOption optiuni_meniu;
    optiuni_meniu.style_selected = color(Color::CadetBlue);
    optiuni_meniu.style_focused = bgcolor(Color::CadetBlue);
    optiuni_meniu.style_selected_focused = bgcolor(Color::CadetBlue);

    vector<string> elemente_meniu_parcurgeri = {"Preordine", "Inordine", "Postordine", "In adancime"};

    auto meniu_traversari = Menu(&elemente_meniu_parcurgeri, &parcurgere_selectata, &optiuni_meniu);




    // Sectiune care se ocupa cu randarea tab-ului de reprezentare grafica a arborelui binar
    auto reprezentare_grafica = Renderer(meniu_traversari, [&]
    {
        auto informatii_nod = arbore_binar.GetInformatiiNodCurent();
        vector<string> vector_noduri_parcurse{};
        if (parcurgere_selectata == 0 && !informatii_nod._informatie_nod.empty())
        {
            vector_noduri_parcurse = arbore_binar.ParcurgerePreordineDeLaRadacina();
        } else if (parcurgere_selectata == 1 && !informatii_nod._informatie_nod.empty())
        {
            vector_noduri_parcurse = arbore_binar.ParcurgereInordineDeLaRadacina();
        } else if (parcurgere_selectata == 2 && !informatii_nod._informatie_nod.empty())
        {
            vector_noduri_parcurse = arbore_binar.ParcurgerePostordineDeLaRadacina();
        } else
        {
            vector_noduri_parcurse = {"eroare"};
        }


        Elements elemente_parcurse, vector_final;
        size_t parte_intreaga{};
        if (!informatii_nod._informatie_nod.empty() && !vector_noduri_parcurse.empty())
        {
            if (vector_noduri_parcurse.front().compare(informatii_nod._informatie_nod) == 0)
                elemente_parcurse.push_back(hbox((text(vector_noduri_parcurse.front()) | border | color(Color::BlueLight))));
            else
            {
                elemente_parcurse.push_back(hbox((text(vector_noduri_parcurse.front()) | border)));
            }

            for (int i = 1; i < vector_noduri_parcurse.size(); i++)
            {
                if (vector_noduri_parcurse[i].compare(informatii_nod._informatie_nod) == 0)
                    elemente_parcurse.push_back(hbox({text("→") | center, text(vector_noduri_parcurse[i]) | border | color(Color::BlueLight)}));
                else
                {
                    elemente_parcurse.push_back(hbox({text("→") | center, text(vector_noduri_parcurse[i]) | border}));
                }
            }


            parte_intreaga = elemente_parcurse.size() / 10;


            if (parte_intreaga > 1)
            {
                vector<vector<Element>> vector_out = ImpartireVector(elemente_parcurse, parte_intreaga);
                vector_final = AfisareElementeParcurseImpartite(vector_out);
            } else
            {
                vector_final = elemente_parcurse;
            }
        }

        return window(text("Arbore Binar - Reprezentare Grafica"),//
                      vbox({hbox({}),
                            filler(),
                            filler(),
                            !informatii_nod._informatie_nod.empty() ?
                            hbox({window(text("Meniu Parcurgere"),
                                         hbox({vbox({hbox(text(" ")),
                                                     hbox(vbox(text("Selectati parcurgerea: ")),
                                                          vbox({meniu_traversari->Render() | frame})),
                                                     hbox(text(" "))
                                                    }) | size(ftxui::WIDTH, ftxui::GREATER_THAN, 54),
                                               separator(),
                                               hbox({hbox({hbox(parte_intreaga > 1 ? vbox(vector_final) |
                                                                                     size(ftxui::WIDTH,
                                                                                          ftxui::GREATER_THAN,
                                                                                          150)
                                                                                   : vbox({hbox(text(" ")),
                                                                                           hbox({text(
                                                                                                   "Ordine noduri parcurse: ")}) |
                                                                                           center,
                                                                                           hbox({vector_final}) |
                                                                                           center

                                                                                          }) |
                                                                                     size(ftxui::WIDTH,
                                                                                          ftxui::GREATER_THAN,
                                                                                          150))
                                                          })
                                                    })
                                              })
                                 )}
                            ) : hbox({}) |
                                size(ftxui::WIDTH,
                                     ftxui::GREATER_THAN,
                                     150)}
                      ));
    });

    // Sectiune care se ocupa cu randarea intregului nivel de adancime 0 (Principal)
    auto container_adancime_0 = Container::Vertical(
            {tab_detalii_arbore, tab_detalii_nod, tab_editare_nod, tab_editare_copii,
             reprezentare_grafica});
    auto randare_adancime_0 = Renderer(container_adancime_0, [&]
    {
        return hbox({hbox({vbox({tab_detalii_arbore->Render(),
                                 tab_detalii_nod->Render(),
                                 tab_editare_nod->Render(),
                                 tab_editare_copii->Render(),
                                })
                          }),
                     hbox({reprezentare_grafica->Render()}) | flex
                    });
    });

    // Containerul principal tine toate elementele de pe toate nivelurile
    auto container_principal = Container::Tab({randare_adancime_0,
                                               randare_adancime_1_copil_st,
                                               randare_adancime_2_copil_dr
                                              }, &adancime);
    // Sectiune in care se randeaza containerul principal
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

    cout << endl
         << endl;
    // Aici se face loop-ul bufferului de afisare pentru actualizarea in timp real


    screen.Loop(randare_principala);
    return EXIT_SUCCESS;
}
