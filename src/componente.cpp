#include "componente.h"
#include "globale.h"

Component
GetInputNodCrt(string &nod_curent)
{
    return Input(&nod_curent, "editati valoarea nodului");
}

shared_ptr<ComponentBase>
GetButonSalvareNod(string &nod_curent,
                   string &copil_stang,
                   string &copil_drept,
                   ButtonOption &optiune_buton_salvare)
{
    return Container::Horizontal({
                                   Button("[Urmatorul Nod]", [&]
                                          {
                                              arbore_binar.SalvareNod(nod_curent, copil_stang, copil_drept);
                                              auto informatii_nod_crt = arbore_binar.GetInformatiiNodCurent();
                                              nod_curent = informatii_nod_crt._nod_curent._informatie_nod;
                                              copil_stang = informatii_nod_crt._informatie_descendent_stang;
                                              copil_drept = informatii_nod_crt._informatie_descendent_drept;
                                          },
                                          &optiune_buton_salvare),
                                 });

}

shared_ptr<ComponentBase>
GetButonSalvareCopilStang(ButtonOption &optiune_buton_salvare)
{
    return Container::Horizontal({
                                   Button("[Salveaza copil stang]", [&]
                                          { adancime = 0; },
                                          &optiune_buton_salvare),
                                 });
}

shared_ptr<ComponentBase>
GetButonSalvareCopilDrept(ButtonOption &optiune_buton_salvare)
{
    return Container::Horizontal({
                                   Button("[Salveaza copil drept]", [&]
                                          { adancime = 0; },
                                          &optiune_buton_salvare),
                                 });
}

shared_ptr<ComponentBase>
RandareInputAdancime1(shared_ptr<ComponentBase> container_input_adancime_1)
{
    return Renderer(container_input_adancime_1, [&]
    {
        return vbox({hbox(text(" ")),
                     hbox(text("Copilul stang al nodului curent selectat (" + val_nod + ") : ")),
                     text(""),
                     container_input_adancime_1->Render() | size(ftxui::WIDTH, ftxui::GREATER_THAN, 45),
                     hbox(text(" ")),
                     separator(),
                    }) | size(ftxui::WIDTH, ftxui::GREATER_THAN, 50);
    });
}

shared_ptr<ComponentBase>
RandareButonAdancime1(shared_ptr<ComponentBase> buton_copil_stang)
{
    return Renderer(buton_copil_stang, [&]
    {
        return vbox({buton_copil_stang->Render()
                    }) | center | size(ftxui::WIDTH, ftxui::GREATER_THAN, 50);
    });
}

shared_ptr<ComponentBase>
GetContainerAdancime1(shared_ptr<ComponentBase> randare_input,
                      shared_ptr<ComponentBase> randare_buton)
{
    return Container::Vertical({
                                 randare_input,
                                 randare_buton
                               });
}

shared_ptr<ComponentBase>
GetModalCopilStang(shared_ptr<ComponentBase> &container_adancime_1)
{
    return Renderer(container_adancime_1, [&]
    {
        return window(text("Adaugare Copil Stang"),
                      {container_adancime_1->Render()}) | center;
    });
}

shared_ptr<ComponentBase>
RandareInputAdancime2(shared_ptr<ComponentBase> container_input_adancime_2)
{
    return Renderer(container_input_adancime_2, [&]
    {
        return vbox({hbox(text(" ")),
                     hbox(text("Copilul drept al nodului curent selectat (" + val_nod + ") : ")),
                     text(""),
                     container_input_adancime_2->Render() | size(ftxui::WIDTH, ftxui::GREATER_THAN, 45),
                     hbox(text(" ")),
                     separator(),
                    }) | size(ftxui::WIDTH, ftxui::GREATER_THAN, 50);
    });
}

shared_ptr<ComponentBase>
RandareButonAdancime2(shared_ptr<ComponentBase> buton_copil_drept)
{
    return Renderer(buton_copil_drept, [&]
    {
        return vbox({buton_copil_drept->Render()
                    }) | center | size(ftxui::WIDTH, ftxui::GREATER_THAN, 50);
    });
}

shared_ptr<ComponentBase>
GetContainerAdancime2(shared_ptr<ComponentBase> randare_input,
                      shared_ptr<ComponentBase> randare_buton)
{
    return Container::Vertical({
                                 randare_input,
                                 randare_buton
                               });
}

shared_ptr<ComponentBase> GetModalCopilDrept(shared_ptr<ComponentBase> &container_adancime_2)
{
    return Renderer(container_adancime_2, [&]
    {
        return window(text("Adaugare Copil Drept"),
                      {container_adancime_2->Render()}) | center;
    });
}

shared_ptr<ComponentBase>
GetTabDetaliiArbore()
{
    return Renderer([&]
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
}

shared_ptr<ComponentBase>
GetTabDetaliiNodCrt()
{
    return Renderer([&]
                    {
                        return window(text("Detalii Nod Curent"),//
                                      vbox({
                                             hbox(text(" ")),
                                             hbox(text(val_nod.empty() ? "Nod curent: - " :
                                                       "Nod curent: "), text(val_nod)
                                                                        | color(Color::GreenLight)),
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
}

shared_ptr<ComponentBase>
GetButoaneCopiiTabNod(ButtonOption &optiune_buton_copil_stang,
                      ButtonOption &optiune_buton_copil_drept)
{
    return Container::Horizontal({
                                   Button(
                                     "[Copil stang]", [&]
                                     { adancime = 1; },
                                     &optiune_buton_copil_stang),
                                   Button(
                                     "[Copil drept]", [&]
                                     { adancime = 2; },
                                     &optiune_buton_copil_drept),
                                 });
}

shared_ptr<ComponentBase>
GetContainerTabNod(shared_ptr<ComponentBase> input_val_nod,
                   shared_ptr<ComponentBase> buton_salvare_nod,
                   shared_ptr<ComponentBase> butoane_salvare_copii_tab_nod)
{
    return Container::Vertical({
                                 input_val_nod,
                                 buton_salvare_nod,
                                 butoane_salvare_copii_tab_nod
                               });
}

shared_ptr<ComponentBase>
GetTabEditareNodCurent(shared_ptr<ComponentBase> container_tab_nod,
                       shared_ptr<ComponentBase> input_val_nod,
                       shared_ptr<ComponentBase> buton_salvare_nod,
                       shared_ptr<ComponentBase> butoane_salvare_copii_tab_nod)
{
    return Renderer(container_tab_nod, [&]
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
                             text(""),
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
                                                   : butoane_salvare_copii_tab_nod->Render()}) | center
                           })
        ) | size(ftxui::WIDTH, ftxui::EQUAL, 40);
    });
}

shared_ptr<ComponentBase>
GetButonStergereSubarbore(ButtonOption &optiune_buton_stergere_subarbore)
{
    return Container::Horizontal({
                                   Button("1. Stergeti Subarbore Nod Crt.", [&]
                                   {
                                       arbore_binar.StergereSubArboreAlNoduluiCurent();
                                       auto informatii_nod_crt = arbore_binar.GetInformatiiNodCurent();
                                       val_nod = informatii_nod_crt._nod_curent._informatie_nod;
                                       val_copil_stang = informatii_nod_crt._informatie_descendent_stang;
                                       val_copil_drept = informatii_nod_crt._informatie_descendent_drept;

                                   }, &optiune_buton_stergere_subarbore)
                                 });
}

shared_ptr<ComponentBase>
GetButonResetareArbore(ButtonOption &optiune_buton_resetare)
{
    return Container::Horizontal({
                                   Button("2. Resetati Arborele Binar", [&]
                                   {
                                       arbore_binar.ResetareArbore();
                                       auto informatii_nod_crt = arbore_binar.GetInformatiiNodCurent();
                                       val_nod = informatii_nod_crt._nod_curent._informatie_nod;
                                       val_copil_stang = informatii_nod_crt._informatie_descendent_stang;
                                       val_copil_drept = informatii_nod_crt._informatie_descendent_drept;

                                   }, &optiune_buton_resetare)
                                 });
}

shared_ptr<ComponentBase>
GetTabOptiuniParcurgeri(shared_ptr<ComponentBase> container_meniu_parcurgeri)
{
    return Renderer(container_meniu_parcurgeri, [&]
    {
        return vbox({hbox(text(" ")),
                     hbox(vbox(text("Selectati parcurgerea: ")),
                          vbox({container_meniu_parcurgeri->Render()})),
                     hbox(text(" ")),
                     separator()
                    });
    });
}

shared_ptr<ComponentBase>
GetTabCheckboxuri(shared_ptr<ComponentBase> container_checkboxuri)
{
    return Renderer(container_checkboxuri, [&]
    {
        return vbox(container_checkboxuri->Render() | frame |
                    size(HEIGHT, LESS_THAN, 10));
    });
}

shared_ptr<ComponentBase>
GetTabReprezentareGrafica(shared_ptr<ComponentBase> meniu_final_parcurgeri)
{
    return Renderer(meniu_final_parcurgeri, [&]
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

        auto vector_noduri_parcurse = ArboreBinar::GetNodDtoInitVect();

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

        auto vector_linii_arbore = ConversieStringMulti(arbore_binar.GetReprezentareGrafica(), "\n");
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
                      )) | size(ftxui::WIDTH, ftxui::GREATER_THAN, 185);
    });
}

shared_ptr<ComponentBase>
GetTabAlteOptiuni(shared_ptr<ComponentBase> container_tab_alte_optiuni)
{
    return Renderer(container_tab_alte_optiuni, [&]
    {
        return window(text("Alte Optiuni"),
                      {
                        vbox({
                               text(""),
                               container_tab_alte_optiuni->Render(),
                               filler()
                             })
                      }) | size(ftxui::WIDTH, ftxui::EQUAL, 40) | size(ftxui::HEIGHT, ftxui::GREATER_THAN, 15);
    });
}

shared_ptr<ComponentBase>
RandareAdancime0(shared_ptr<ComponentBase> container_adancime_0,
                 shared_ptr<ComponentBase> tab_detalii_arbore,
                 shared_ptr<ComponentBase> tab_detalii_nod,
                 shared_ptr<ComponentBase> tab_editare_nod_crt,
                 shared_ptr<ComponentBase> tab_alte_optiuni,
                 shared_ptr<ComponentBase> tab_reprezentare_grafica)
{
    return Renderer(container_adancime_0, [&]
    {
        return hbox({hbox({vbox({
                                  tab_detalii_arbore->Render(),
                                  tab_detalii_nod->Render(),
                                  tab_editare_nod_crt->Render(),
                                  tab_alte_optiuni->Render(),
                                })
                          }),
                     hbox({tab_reprezentare_grafica->Render()}) | flex
                    });
    });
}

shared_ptr<ComponentBase>
RandareLayere(shared_ptr<ComponentBase> container_principal,
              shared_ptr<ComponentBase> randare_adancime_0,
              shared_ptr<ComponentBase> randare_adancime_1_st,
              shared_ptr<ComponentBase> randare_adancime_2_dr)
{
    return Renderer(container_principal, [&]
    {
        Element document = randare_adancime_0->Render();

        if (adancime == 1 && !val_nod.empty())
        {
            document = dbox({document,
                             randare_adancime_1_st->Render() | clear_under | center,
                            });
        } else if (adancime == 2 && !val_nod.empty())
        {
            document = dbox({document,
                             randare_adancime_2_dr->Render() | clear_under | center,
                            });
        }
        return document;
    });
}






