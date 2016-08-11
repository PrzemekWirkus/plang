# Struktury danych
int
char ???
double
string

# Kontenery
string
lista
mapa
$array jak w PHP (?)

# Slowa kluczowe
## gramatyka
if, else, as, while, select, where, break, continue

## biblioteka standardowa
print, println

# Zalozenia
* brak zmiennych globalnych
* brak const i volatile (cv-qualified)
* brak bool (wszystko co logiczne jest int)
* brak roznicy miedzy float i double (zawsze uzywamy double)
* brak wskaznikow
* brak dynamicznej alokacji
* brak wyjatkow
* brak objektowosci
* brak wsparcia dla  UNICODE
* brak operatora !, zamiast tego 'not'
* srednik na koncu wyrazenia
* RAII
* komentarze jednoliniowe '#'
* stringi jak w C
* raw stringi
* arytmetyka na int / double
* konkatanacja stringow operator+()
* funkcje
    * zawsze zwracaja wartosc
    * argumenty dostepne jako lista (na zadanie)
    * zmienne lokalne
    * brak dostepu do zmiennych globalnych -> brak zmiennych globalnych
    * implementacja jako funktory (?)
* Typy wbudowane:
    * parametry funkcji jak w typed javascript:  @funkcja(typ : param1, typ : param2)
* lambda:
    * jak funkcje (zawsze zwracaja, argumenty)
    * implementacja jako funktory
    Przyklad:
        @() { }
        func = @(arg, arg, ...) {}
    
* Sterowanie zawsze z blokiem {}
* sterowanie:
    * if (expr) {}
    * if (expr) {} else {}
    * if (expr) as e {} 
    * if (expr) as e {} else {}
* petle:
    * break & continue
    * while (expr) {}
    * while (expr) as e {}
    * select k from (kontener) {}
    * select k from (kontener) where () {}
* rzutowanie:
    * str()
    * int()
    * double()
    * map()
    * list()
* biblioteka standardowa
    * dostep do plikow: "r", "w", "rw"/"wr", "a"
    * operacje na plikach:
        read(f, n)     - czyta n bajtow z f
        readline(f)    - czyta do wystapienia '\n' lub konca pliku
        write(f, buf)  - zapisauje bufor/zmienna do pliku
        append(f, buf) - zapisuje na koniec pliku
        size(f)        - podaje rozmiar pliku
        seek(f, pos)   - przesuwa sie po pliku do pos
* inne:
    * operator=     - przypisanie
    * operator&=    - jezeli kontener to mutuje element kontenera
    * static_assert - http://en.cppreference.com/w/cpp/language/static_assert
    * RTTI
        * typeid zwraca typ zmiennej _var do int, print typeid zwraca string
* Konsola:
    * print
    * println
* kompilator
    * plang plik.pw -o wynik
        Generuje pliki C++ do katalogu build/wynik
        Generuje GNU makefile i uzywa GCC zeby kompilowac projekt
    * yotta jako build system ?
        * plang plik.pw plik2.pw plik3.pw --yt modul_yotta
            Generuje modul yotta
    
# Funkcjonalnosc    
## v1.0 Funkcjonalnosc
DONE* program start: @main() {}
DONE* @main() z lista argumentow (id,*)
* typy: int, double, char
DONE* komentarze jednoliniowe '#'
* arytmetyka na int/double +, -, *, /
* _var op _var  ==, !=, >, <, >=, <=
* if (expr) {} else {}
* if (expr) as e {} else {}
DONE* if (expr) {}
DONE* if (expr) as e {}
DONE* while (expr) {}
DONE* while (expr) as e {}
    
## v2.0 Funkcjonalnosc
        
* main(argc, argv) {}
* select k from (kontener) {}
* select k from (kontener) where () {}
* kontenery: string, lista
* return z funkcji

## v3.0 Funkcjonalnosc [FutureDev]
* przejscie z projektem do GNU make, GCC (C++11)
* moduly
    * modul biblioteki standadowej
    * modul unit testow
* namespaces
* wsparcie dla debugowania
* lambda
* iteratory ?

## v4.0 Funkcjonalnosc [FutureDev]
* operacje na plikach: fopen(path, attr)
    * Przyklad:

```    
if (fopen(plik)) as f {
    // otwiera plik
    
    // Jakie operacje na pliku, jak read, write ?
    
    // Zamyka plik
} else {
    // Plik sie nie otwarl
}
```

## v5.0 Funkcjonalnosc [FutureDev]
* Bootstrapping
