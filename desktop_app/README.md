## Uruchomienie i budowa projektu na GNU/Linux Ubuntu 20.04

Aby móc zbudować projekt niezbędne jest zainstalowanie QT.

W celu zbudowania projektu na systemie Linux:
1. `cd desktop_app`
2. `cmake -H. -Bbuild`
3. `cd build && make`

W celu uruchomienia projektu: `./desktop_app`.

Powyższy sposób budowania aplikacji jest typu out-source. Jednakże metoda ta może nie zadziałać dla niektórych wersji cmake. W takim przypadku można posłużyć się metodą opisaną poniżej.
W celu zbudowania projektu:
1. `cd desktop_app`
2. `cmake CMakeLists.txt`
3. `make`

Aby uruchomić tak stworzony plik należy wykonać: `./desktop_app` w folderze "build".
Instalacja QT5 globalnie:
`sudo apt-get install qt5-default`

## Uruchomienie i budowa programu na systemie Windows 10:
Najprostszym rozwiąniem jest pobranie programu QTCreator, który sam zadba o poprawną instalację i linkowanie biblioteki Qt. Przy pomocy programu można zbudować i uruchomić projekt. Możliwa jest też instalacja manuala. W tym celu należy globalnie zainstalować biblioteki Qt5 oraz pakiet Visual Studio (aplikacja testowana była przy użyciu Visula Studio 2019).

Aby zbudować projekt:
W konsoli (**Developer Command Prompt for VS 2019**) przejść do folderu z projektem, następnie:


## Sposób użytkowania aplikacji.
Po uruchomieniu pojawia się główne okno aplikacji.  Wyszukiwanie snippetów odbywa się przy użyciu przycisku find. Żadne z pól wyszukiwania tj. title, author, date from, date to, language, nie jest obowiązkowe do użyciu przy wyszukiwaniu. Zarówno można użyć wszystkich jak i żadnego. 
Pola, title i author działają na zasadzie podciągu czyli wyszukiwane są wszystkie snippety, które zawierają dany string w tytule.  
Po lewej stronie wyśwetla się lista wyszukanych snippetów, klikając na nazwę snippetu, pojawia się jego zawartość.
Można dodawać nowe snippety używając opcji "new". Wyświetlane jest nowe okno, gdzie można ustawić tytuł, autora, język oraz zawartość snippetu. Zawartość snippetu można wczytać z pliku, używając opcji "browse". Aby wysłać snippet do bazy danych należy użyć przycisku "add".
Aby zapisać snippet do pliku, należy w liście snippetów, kliknąć na wybrany snippet oraz następnie użyć opcji "save".

## Testowanie
Testowanie komunikacji pomiędzy serwerem, a klientem odbyło się poprzez wysyłanie danych na serwer i sprawdzaniem odpowiedzi. Natomiast testowanie interfejsu graficznego, manualnie poprzez sprawdzenie działania wszystkich dostępnych opcji.
