#include "utilitare.h"


vector <Elements> ImpartireVector(Elements el_parcurse, size_t nr_segmente)
{
    vector <Elements> vector_out;

    int lungime = el_parcurse.size() / nr_segmente;
    int rest = el_parcurse.size() % nr_segmente;

    int inceput = 0;
    int sfarsit = 0;

    for (int i = 0; i < min<int>(nr_segmente, el_parcurse.size()); i++)
    {
        sfarsit += lungime + (rest-- > 0);
        vector_out.push_back(Elements (el_parcurse.begin() + inceput, el_parcurse.begin() + sfarsit));
        inceput = sfarsit;
    }
    return vector_out;
}

Elements AfisareElementeParcurseImpartite(vector <vector<Element>> vector)
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

Elements ConversieStringMulti(string arbore, string delimiter)
{
    Elements stringuri;

    std::string::size_type pos{};
    std::string::size_type prev{};
    while ((pos = arbore.find(delimiter, prev)) != std::string::npos)
    {
        stringuri.push_back(text(arbore.substr(prev, pos - prev)));
        prev = pos + 1;
    }

    // To get the last substring (or only, if delimiter is not found)
    stringuri.push_back(text(arbore.substr(prev)));

    return stringuri;
}

string GetCaleCatrePyLib()
{
    auto os = py::module::import("os");
    return os
      .attr("path")
      .attr("abspath")(os
                         .attr("path")
                         .attr("join")("..", "lib"))
      .cast<string>();
}

py::module_ GetPySys()
{
    auto sys = py::module::import("sys");
    sys
      .attr("path")
      .attr("append")(GetCaleCatrePyLib());
    return sys;
}

string GetStringReprezentareGrafica()
{
    pybind11::scoped_interpreter guard{};
    auto sys = GetPySys();
    auto modul_test = py::module::import("afisare_arbore");
    auto functie_convertita = modul_test.attr("get_string_reprezentare_grafica");
    auto preluat = functie_convertita();
    return preluat.cast<string>();
}
