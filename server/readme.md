# Szkielet aplikacji serwera


Serwer wykorzystuje biblioteki Qt5, sterownik do bazy danych SQLite3 oraz zewnętrzną bibliotekę opartą na qt - [QHTTPEngine](https://github.com/nitroshare/qhttpengine). Jej pliki źródłowe są dołączone do projektu<sup>1)</sup> code-snippet-app, nie trzeba więc jej dodatkowo pobierać. Kroki niezbędne do zbudowania jej ze źródeł zostaną przedstawione dla każdej platformy poniżej.


## Zbudowanie i uruchomienie projektu na Ubuntu 20.04

### Konfiguracja systemu

Zakłada się, że użytkownik ma zainstalowane globalnie biblioteki qt5 oraz sterownik do obsługi bazy danych SQLite3. 

Jeśli nie ma, to może to zrobić tak: 


`$ sudo apt-get install qt5-default`


`$ sudo apt-get install sqlite3`
  
### Budowanie i uruchomienie projektu

Budowanie (lokalnie, w folderze z projektem) biblioteki QHTTPEngine:

  

1. `$ cd server/lib/qhttpengine`

2. `$ cmake CMakeLists.txt -B build` - nie przejmować się błędem :( naprawię

3. `$ cd build`

4. `$ make install`

Tworzenie bazy danych. Będąc w katalogu `server`:

5. `$ cd database && ./unix-setup.sh`
  
Budowanie projektu. Będąc w katalogu `server`:


6. `$ mkdir build && cd build`

7. `$ cmake ..`

8. `$ make`

  

Uruchomienie aplikacji. Będąc w katalogu `server`:


9. `$ cd bin`
10. `$ ./server`

Uruchomienie testów jednostkowych:

11. `$ cd bin`
12. `$ ./test`

<sup>1)</sup> jedyną zmianą w kodzie źródłowym jest zmiana zmiennych `BIN_INSTALL_DIR`, `LIB_INSTALL_DIR`, `INCLUDE_INSTALL_DIR` w pliku CMakeLists.txt na ścieżki w obrębie folderu aplikacji (by nie instalować biblioteki globalnie). Może skutkować brakiem działania dołączonych do biblioteki przykładów (examples).

## Zbudowanie i urochomienie na Windows 10

### Konfiguracja systemu

Zakłada się, że użytkownik ma zainstalowane globalnie biblioteki Qt5, sterownik do obsługi bazy danych SQLite3, oraz pakiet Visual Studio (testowane z Visual Studio 2019). 


Wskazówki dotyczące isntalacji:
* Qt5 - pobrać i uruchomić online installer ze [strony Qt](https://www.qt.io/download-open-source), następnie postępować zgodnie z instrukcjami, by pobrać najnowsze subwersje wersji 5 bibliotek Qt. Po zainstalowaniu może być konieczne dodanie do zmiennej PATH folderu z bibliotekami Qt.
* SQLite3 - postępować zgodnie z instrukcjami na [stronie](https://www.tutorialspoint.com/sqlite/sqlite_installation.htm).

### Budowanie i uruchomienie projektu

Pobrać repozytorium i wypakować do wybranego folderu. W konsoli (**Developer Command Prompt for VS 2019** lub adekwatnej dla innej wersji Visual Studio) przejść do folderu z projektem, następnie:

1. `> cd server\lib\qhttpengine`

2. `> mkdir build`

3. `> cmake .. `  - może być potrzebne sprecyzowanie generatora (np. opcja `/G "Visual Studio 16 2019"`). Listę dostępnych w systemie generatorów można uzyskać komendą `cmake /help`.

4. `> msbuild ALL_BUILD.vcxproj`

Stworzenie bazy danych zaczynając w katalogu `code-snippet-app\server\`:

5. `> cd database`

6. `> windows-setup.bat` 

Budowanie projektu zaczynając w katalogu `code-snippet-app\server\`:

7. `> mkdir build`

8. `> cd build`

9. `> cmake ..`- może być potrzebne sprecyzowanie generatora (np. opcja `/G "Visual Studio 16 2019"`). Listę dostępnych w systemie generatorów można uzyskać komendą `cmake /help`.

10. `> cd ..\src`

11. `> windows-after-build-setup.bat`

Uruchomienie:

12. `> cd bin`

13. `> .\server.exe`

# Testowanie

Serwer nasłuchuje na porcie 8000 pod adresem `app` (`localhost:8000/app`). Przyjmuje zapytania `POST` z body w formacie json z polami:

  

* `author` - string (np. `QString`) max 30 znaków

* `title` - string max 100 znaków

* `created` - obiekt klasy `QDateTime` zamieniony na liczbę w formacie **Unix time** z dokładnością co do sekundy (`QDateTime::toSecsSinceEpoch()`)

* `lang` - jeden z dozwolonych przez zmienną `Snippet::availableLangs_` napisów identyfikujących język

* `content` - string o długości max 1000 znaków

  

oraz zapytania `GET` o body będącym pustym obiektem json (`{}`) lub obiektem klasy SnippetSearchPattern zamienionym na json (`SnippetSearchPattern::toJson()`). 

Odpowiedzą na zapytanie typu `GET` z body w postaci pustego obiektu json jest lista maksymalnie 5 snippetów w formacie json ostatnio dodanych przez zapytania `POST` (formalnie są to obiekty o najwyższym id w bazie danych). 

Klasa `SnippetSearchPattern` ma pola:
* authorSubsequence_ - string nie dłuższy niż 30 znaków, jeśli pusty - dowolny autor
* titleSubsequence_ - string nie dłuższy niż 100 znaków, jeśli pusty - dowolny tytuł
* createdFrom_ - data w tej samej postaci **Unix time** jak wyżej lub **null** jeśli niesprecyzowane
* createdTo_ - data w tej samej postaci **Unix time** jak wyżej lub **null** jeśli niesprecyzowane
* lang_ - jeden z napisów identyfikujących język lub pusty string oznaczający dowolny język

Wszystkie pola są opcjonalne i można je dowolnie łączyć. Do zamieniania klasy `SnippetSearchPattern` na json służy funkcja `SnippetSearchPattern::toJson()` - zamienia ona dobrze niesprecyzowane daty (które normalnie są nieokreślone) na nulle w postaci jsona. 

Obiekt klasy `SnippetSearchPattern` można stworzyć tak:

```c++
SnippetSearchPattern pattern;
pattern.setAuthorSubsequence("userna")
pattern.setLang("c++");
```
Każde nieustwione pole ma domyślnie pustą wartość.

Przykładowy json obiektu `SnippetSearchPattern`:

```json
{
    "author_subsequence": "",
    "title_subsequence": "titl",
    "created_from": 1609675073,
    "created_to": null,
    "lang": ""
}
```

Wynikiem każdego poprawnego zapytania `GET` jest json - lista obiektów snippet. Może być pusta.

W wyniku niepoprawnego zapytania w sockecie ustawiany jest kod błędu **Bad Request** i w jsonie w polu `"message"` powinien zostać zwrócony odpowiedni komunikat.

