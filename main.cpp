/*
Scieżka bezwzględna w programie, metody
ścieżka względna zmienić na bezwzględną i operować na niej
dane są wartościami bezwzględnymi
*/

#include <iostream>
#include "main_frame.h"
#include <typeinfo>

using namespace std;

//typedef void (*fun)(int, int);

int main()
{
    cout << "Hello world!" << endl;

    Main_frame *tmp=new Main_frame(2, 1, 10, 10, '*', '*', '*', '*', '*', '*', ' ', "Glowne");
    Main_frame::Frame *f_tmp=new Main_frame::Frame(tmp, nullptr, 2, 2, 6, 6, '-', '|', '*', '*', '*', '*', "tymczasowe");
    Main_frame::Frame *f_tmp2=new Main_frame::Frame(tmp, f_tmp, 2, 2, 4, 4, '-', '|', '*', '*', '*', '*', "do sprawdzenia");
    Main_frame::Frame *f_tmp3=new Main_frame::Frame(tmp, f_tmp, 2, 2, 2, 2, '-', '|', '*', '*', '*', '*', "do sprawdzenia2");
    //f_tmp.cast();

    tmp->all_cast();
    tmp->show();
    /*auto T=(*f_tmp2)[0][0];
    cout << typeid(T).name() << endl;
    cout << T << endl;*/

    cout << *f_tmp << endl;

    delete tmp;

    return 0;
}


/*
Proszę o zastosowanie następujących elementów:

Dziedziczenie, funkcje wirtualne, obsługa sytuacji wyjątkowych, współpraca ze strumieniami, klasy kontenerowe i iteratory, dokumentacja.

Projekt należy wcześniej skonsultować mejlem lub osobiście, jak chce Pan zaimplementować w/w elementy.

W dokumentacji końcowej trzeciego projektu powinny znaleźć się:

rozwinięcie tematu projektu,

opis działania programu,

lista stworzonych klas, opis nietrywialnych klas i pól, opis nietrywialnych algorytmów.



Zadanie 3.1. Okienka

Typowe okienko w aplikacji okienkowej jest kolekcją komponentów (np. napis, obrazek, prostokąt o zadanej barwie), z których każdy zajmuje pewien prostokąt.
Każdy komponent może sam zawierać kolekcję innych komponentów (potomków). Spełniony musi być warunek, że komponent zawiera swoich potomków także w sensie geometrycznym.

Zaproponować kolekcję abstrakcyjnych klas umożliwiających budowę i łatwy dostęp do powyższej hierarchii komponentów. Kolekcja ta ma umożliwiać w szczególności:

    Dodawanie/usuwanie komponentów.
    Iteracyjny dostęp do wszystkich bezpośrednich potomków wskazanego komponentu.
    Iteracyjny dostęp do wszystkich potomków wskazanego komponentu.

Napisać program umożliwiający interakcyjną budowę i przebudowę hierarchii komponentów opisujących prostokąt na konsoli. Niech komponenty będą co najmniej dwóch typów:
np. zawierające zadany napis i wypełnione w sposób jednorodny zadanym znakiem.

*/
