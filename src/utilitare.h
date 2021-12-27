#ifndef APP_ARBORE_BINAR_UTILITARE_H
#define APP_ARBORE_BINAR_UTILITARE_H

#include <windows.h>
#include <algorithm>
#include <memory>  // pentru allocator, __shared_ptr_access
#include <cstdlib>// pentru EXIT_SUCCESS
#include <string>  // pentru string, operator+ (supraincarcare), basic_string, to_string, char_traits
#include <vector>  // pentru vector, __alloc_traits<>::value_type
#include <stdio.h>

#include "ftxui/component/captured_mouse.hpp"    // pentru ftxui
#include "ftxui/component/component.hpp"         // pentru clasele Menu, Renderer, Horizontal, Vertical
#include "ftxui/component/component_base.hpp"    // pentru clasa ComponentBase
#include "ftxui/component/component_options.hpp" // pentru clasele InputOption, ButtonOption
#include "ftxui/component/screen_interactive.hpp"// pentru clasele Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"                // pentru text, Element, operator| (supraincarcare), window, flex, vbox
#include "ftxui/util/ref.hpp"                    // pentru clasa Ref

using namespace ftxui;
using namespace std;

vector<Elements>
ImpartireVector(Elements el_parcurse,
                size_t nr_segmente);

Elements
AfisareElementeParcurseImpartite(vector<vector<Element>> vector);

Elements
ConversieStringMulti(string arbore, string delimiter);

void
TrimString(string &);

void
TrimStrings(initializer_list<string *>);

#endif //APP_ARBORE_BINAR_UTILITARE_H
