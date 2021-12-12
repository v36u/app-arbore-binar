#include <memory>  // pentru allocator, __shared_ptr_access
#include <stdlib.h>// pentru EXIT_SUCCESS
#include <string>  // pentru string, operator+ (supraincarcare), basic_string, to_string, char_traits
#include <vector>  // pentru vector, __alloc_traits<>::value_type

#include "ftxui/component/captured_mouse.hpp"    // pentru ftxui
#include "ftxui/component/component.hpp"         // pentru clasele Menu, Renderer, Horizontal, Vertical
#include "ftxui/component/component_base.hpp"    // pentru clasa ComponentBase
#include "ftxui/component/component_options.hpp" // pentru clasele InputOption, ButtonOption
#include "ftxui/component/screen_interactive.hpp"// pentru clasele Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"                // pentru text, Element, operator| (supraincarcare), window, flex, vbox
#include "ftxui/util/ref.hpp"                    // pentru clasa Ref

using namespace ftxui;
using namespace std;

int main(int argc, const char *argv[])
{
    // Am declarat variabilele in care se vor stoca valorile aferente nodului curent
    string val_nod, val_copil_stang, val_copil_drept;

    // Aici am creat componenta care stocheaza valoarea introdusa de la tastatura a nodului curent (in input)
    Component input_val_nod = Input(&val_nod, "editati valoarea nodului");

    //    Component input_copil_stang = Input(&val_copil_stang, "introduceti valoarea");
    //    Component input_copil_drept = Input(&val_copil_drept, "introduceti valoarea");

    // Sectiune in care se definesc proprietatile butonului de salvare din fereastra "Editare si Adaugare Nod Curent"
    auto optiune_buton_salv_nod = ButtonOption();
    optiune_buton_salv_nod.border = false;
    auto buton_salvare_nod = Container::Horizontal({
            Button(
                    "[Salveaza si adauga nod]", [&] { /* urmeaza sa adaugam logica aici */ },
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
            Button(
                    "[Salveaza copil stang]", [&] { adancime = 0; },
                    &optiune_buton_salv_copil_stang),
    });
    // sfarsit sectiune

    // Sectiune care se ocupa de butonul de salvare a copilului drept
    // Acest buton face posibila revenirea la adancimea 0 a programului
    auto optiune_buton_salv_copil_drept = ButtonOption();
    optiune_buton_salv_copil_drept.border = false;
    auto buton_salvare_copil_drept = Container::Horizontal({
            Button(
                    "[Salveaza copil drept]", [&] { adancime = 0; },
                    &optiune_buton_salv_copil_drept),
    });
    // sfarsit sectiune

    // Sectiune care se ocupa cu randarea meniului Pop-Up de pe nivelul 1
    auto container_adancime_1_st = Container::Vertical({
            Input(&val_copil_stang, "copil stang"),
            buton_salvare_copil_stang,
    });
    auto randare_adancime_1_copil_st = Renderer(container_adancime_1_st, [&] {
        return vbox({hbox(text("Introduceti valoare: ")),
                     container_adancime_1_st->Render() | center}) |
               border;
    });
    // sfarsit sectiune

    // Sectiune care se ocupa cu randarea meniului Pop-Up de pe nivelul 2
    auto container_adancime_2_dr = Container::Vertical({

            Input(&val_copil_drept, "copil drept"),
            buton_salvare_copil_drept,
    });

    auto randare_adancime_2_copil_dr = Renderer(container_adancime_2_dr, [&] {
        return vbox({hbox(text("Introduceti valoare: ")),
                     container_adancime_2_dr->Render() | center}) |
               border;
    });
    // sfarsit sectiune

    // Sectiune in care se definesc proprietatile butoanelor de salvare si adaugare ale copiilor nodului curent
    auto butoane_salvare_copii = Container::Horizontal({
            Button(
                    "[Copil stang]", [&] { adancime = 1; },
                    &optiune_buton_salv_copil_stang),
            Button(
                    "[Copil drept]", [&] { adancime = 2; },
                    &optiune_buton_salv_copil_drept),
    });
    // sfarsit sectiune

    // Aici se definesc proprietatile care vor fi "pasate" in componenta de editare a nodului
    auto proprietati_nod = Container::Vertical({
            input_val_nod,
            buton_salvare_nod,
    });

    // Sectiune care se ocupa cu randarea ferestrei Detalii Arbore
    auto tab_detalii_arbore = Renderer([&] {
        return window(text("Detalii Arbore"),//
                      vbox({hbox(text(" ")),
                            hbox(text("Nr. niveluri: -")),
                            hbox(text("Nr. noduri: -")),
                            hbox(text("Nr. frunze: -")),
                            hbox(text(" "))})) |

               size(ftxui::WIDTH, ftxui::EQUAL, 40);
    });
    // Sectiune care se ocupa cu randarea ferestrei Detalii Nod Curent
    auto tab_detalii_nod = Renderer([&] {
        return window(text("Detalii Nod Curent"),//
                      vbox({
                              hbox(text(" ")),
                              hbox(text(val_nod.empty() ? "Nod curent: - " : "Nod curent: " + val_nod)),
                              hbox(text(
                                      val_copil_stang.empty() ? "Copil stang: - " : "Copil stang: " + val_copil_stang)),
                              hbox(text(
                                      val_copil_drept.empty() ? "Copil drept: - " : "Copil drept: " + val_copil_drept)),
                              hbox(text(" ")),
                      })) |
               size(ftxui::WIDTH, ftxui::EQUAL, 40);
    });
    // Sectiune care se ocupa cu randarea ferestrei de Editare si Adaugare Nod Curent
    auto tab_editare_nod = Renderer(proprietati_nod, [&] {
        return window(text("Editare si Adaugare Nod Curent"),//
                      vbox({hbox(text(" ")),
                            hbox(text("Nod Crt.: "), input_val_nod->Render()),
                            hbox(text(" ")),
                            separator(),
                            hbox({buton_salvare_nod->Render()}) | center})) |
               size(ftxui::WIDTH, ftxui::EQUAL, 40);
    });

    // Aici se definesc proprietatile care vor fi "pasate" in componenta de editare a copiilor nodului curent
    auto proprietati_copii = Container::Vertical({butoane_salvare_copii});

    // Sectiune care se ocupa cu randarea ferestrei de Editare si Adaugare Copii Nod Curent
    auto tab_editare_copii = Renderer(proprietati_copii, [&] {
        return window(text("Editare Copii Nod Curent"),//
                      vbox({hbox(text(" ")),
                            hbox(text("Nod Crt. Selectat: " + val_nod)),
                            hbox(text(val_copil_stang.empty() && val_copil_drept.empty()
                                              ? "* Nodul curent nu are copii (frunza)"
                                              : "")) |
                                    color(Color::RedLight),
                            hbox(text(val_copil_stang.empty() ? "* Nu exista copil stang " : "Copil stang: " + val_copil_stang)),

                            hbox(text(val_copil_drept.empty() ? "* Nu exista copil drept " : "Copil drept: " + val_copil_drept)),
                            hbox(text(" ")),
                            separator(),
                            hbox({val_nod.empty() ? text("* Completati campul \"Nod Crt.\"") | color(Color::RedLight) : butoane_salvare_copii->Render()}) | center})) |
               size(ftxui::WIDTH, ftxui::EQUAL, 40);
    });

    // Sectiune care se ocupa cu randarea meniului cu traversari
    int selectat = 0;
    vector<string> elemente_meniu_travers = {"Preordine", "Inordine", "Postordine", "In adancime"};

    auto meniu_traversari = Menu(&elemente_meniu_travers, &selectat);

    auto tab_traversari = Renderer(meniu_traversari, [&] {
        return window(text("Parcurgere"),
                      {vbox({hbox(text(" ")),
                             meniu_traversari->Render() | frame})}) |
               size(ftxui::WIDTH, ftxui::EQUAL, 40);
    });


    // Sectiune care se ocupa cu randarea tab-ului de reprezentare grafica a arborelui binar
    auto reprezentare_grafica = Renderer([&] {
        return window(text("Arbore Binar - Reprezentare Grafica"),//
                      vbox({


                      })) |
               flex;
    });

    // Sectiune care se ocupa cu randarea intregului nivel de adancime 0 (Principal)
    auto container_adancime_0 = Container::Vertical(
            {tab_detalii_arbore, tab_detalii_nod, tab_editare_nod, tab_editare_copii, tab_traversari,
             reprezentare_grafica});
    auto randare_adancime_0 = Renderer(container_adancime_0, [&] {
        return hbox({hbox({vbox({tab_detalii_arbore->Render(),
                                 tab_detalii_nod->Render(),
                                 tab_editare_nod->Render(),
                                 tab_editare_copii->Render(),
                                 tab_traversari->Render()})}),
                     hbox({reprezentare_grafica->Render()}) | flex});
    });

    // Containerul principal tine toate elementele de pe toate nivelurile
    auto container_principal = Container::Tab({randare_adancime_0, randare_adancime_1_copil_st,
                                               randare_adancime_2_copil_dr},
                                              &adancime);
    // Sectiune in care se randeaza containerul principal
    auto randare_principala = Renderer(container_principal, [&] {
        Element document = randare_adancime_0->Render();

        if (adancime == 1 && !val_nod.empty())
        {
            document = dbox({
                    document,
                    randare_adancime_1_copil_st->Render() | clear_under | center,
            });
        } else if (adancime == 2 && !val_nod.empty())
        {
            document = dbox({
                    document,
                    randare_adancime_2_copil_dr->Render() | clear_under | center,
            });
        }
        return document;
    });

    cout << endl
         << endl;
    // Aici se face loop-ul bufferului de afisare pentru actualizarea in timp real
    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(randare_principala);
    return EXIT_SUCCESS;
}
