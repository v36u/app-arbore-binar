# Acesta este un repo care conține proiectul la materia Algoritmi si structuri de date - Arbori Binari

## Continut Proiect
* Diverse tipuri de traversari cum ar fi:
  - Preordine
  - Inordine
  - Postordine
  - Adancime
* O interfata grafica interactiva care permite:
    - Adaugarea unui nod in arborele binar creat.
    - Adaugarea de copii (stang si drept) cu optiunea de a stabili proprietatea de frunza pentru nodul curent.
    - Reprezentarea grafica a arborelui binar in fiecare etapa de adaugare.
    - Prezentarea unor statistici precum numarul de noduri, numarul de niveluri ale arborelui si numarul de frunze.
    - Reprezentarea succesiunii nodurilor pentru traversarea aleasa.
## IDE-ul folosit
Am folosit [CLion](https://www.jetbrains.com/clion/) deoarece consider că este un editor puternic și avem acces la licență via [Github Student Pack](https://education.github.com/pack).

## Convenții cod
Am folosit ca și bază convențiile de [aici](https://manual.gromacs.org/documentation/5.1-current/dev-manual/naming.html), însă am mai modificat puțin.
Convențiile pentru acest repo sunt:
* `under_line` pentru variable;
* `PascalCase` pentru funcții, clase, structuri, etc;
* `_` - prefix pentru proprietăți;
* `s_` - prefix pentru proprietăți statice;
* `p_` - prefix pentru parametrii;
* `e_` - prefix pentru enum-uri;
* `g_` - prefix pentru variabile globale;
* `Abstr` - sufix pentru clase abstracte;
* `Interf` - sufix pentru interfețe.

## Convenții Git
Acestea sunt convenții pentru a ușura navigarea pe Git:
* Atunci când lucrăm la un issue, ar trebui ca fiecare titlu de commit să fie de forma `#N - titlu commit`, unde `N` este numărul issue-ului. Asta pentru ca Github să ne creeze un hyperlink frumos și pentru a se vedea mai ușor în grafic.