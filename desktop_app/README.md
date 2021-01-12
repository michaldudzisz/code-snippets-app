## Przykładowe uruchomienie projektu na GNU/Linux Ubuntu 20.04

Aby móc zbudować projekt niezbędne jest zainstalowanie QT.

W celu zbudowania projektu na systemie Linux:
1. Pobrać repozytorium.
2. `cd desktop_app`
3. `cmake CMakeLists.txt`
4. `make`

W celu uruchomienia projektu: `./build/desktop_app`.

Powyższy sposób budowania aplikacji jest typu in-source. Ze względu na dużą liczbę generowanych plików, katalogi robocze stają się nieczytelne. Dlatego też można budować projekt w typie out-source. 
Aby zbudować projekt w ten sposób:
1. `cd desktop_app`
2. `cmake -H. -Bbuild`
3. `cmake --build build --clean-first`

Powyższa metoda nie działa dla niektórych wersji cmake.
Aby uruchomić tak stworzony plik należy wykonać: `./desktop_app`

Instalacja QT5 globalnie:
`sudo apt-get install qt5-default`

## Sposób użytkowania aplikacji.
Po uruchomieniu pojawia się główne okno aplikacji.  Wyszukiwanie snippetów odbywa się przy użyciu przycisku find. Żadne z pól wyszukiwania tj. title, author, date from, date to, language, nie jest obowiązkowe do użyciu przy wyszukiwaniu. Zarówno można użyć wszystkich jak i żadnego. 
Pola, title i author działąją na zasadzie podciągu czyli wyszukiwane są wszystkie snippety, które zawierają dany string w tytule.  
Po lewej stronie wyśwetla się lista wyszukanych snippetów, klikając na nazwę snippetu, pojawia się jego zawartość.
Można dodawać nowe snippety używając opcji "new". Wyświetlane jest nowe okno, gdzie można ustawić tytuł, autora, język oraz zawartość snippetu. Zawartość snippetu można wczytać z pliku, używając opcji "browse". Aby wysłać snippet do bazy danych należy użyć przycisku "add".
Aby zapisać snippet do pliku, należy w liście snippetów, kliknąć na wybrany snippet oraz następnie użyć opcji "save".
