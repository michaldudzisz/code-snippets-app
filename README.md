# Szkielet aplikacji desktopowej:

## GNU/Linux Ubuntu 20.04

Aby móc zbudować projekt niezbędne jest zainstalowanie QT oraz biblioteki Boost.

W celu zbudowania projektu na systemie Linux:
1. Pobrać repozytorium.
2. `cd desktop_app`
3. `cmake CMakeLists.txt`
4. `make`

W celu uruchomienia projektu: `./bin/desktop_app`.
W celu uruchomienia testów: `make test` lub `ctest`

Powyższy sposób budowania aplikacji jest typu in-source. Ze względu na dużą liczbę generowanych plików, katalogi robocze stają się nieczytelne. Dlatego też można budować projekt w typie out-source. 
Aby zbudować projekt w ten sposób:
1. `cd desktop_app`
2. `cmake -H. -Bbuild`
3. `cmake --build build --clean-first`

Powyższa metoda nie działa dla niektórych wersji cmake.
Aby uruchomić tak stworzony plik należy wykonać: `./build/bin/desktop_app`
Aby uruchomić testy nalezy: `cd build && make test`


Instalacja biblioteki boost globalnie:
`sudo apt-get install libboost-all-dev`

Instalacja QT5 globalnie:
`sudo apt-get install qt5-default`

