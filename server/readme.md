# Szkielet aplikacji serwera:

  
  

## Przykładowe uruchomienie projektu na GNU/Linux Ubuntu 20.04

  
  

Zakłada się, że użytkownik ma zainstalowane globalnie biblioteki qt5. Jeśli nie ma, to może to zrobić tak: `sudo apt-get install qt5-default`.

  

Serwer wykorzystuje zewnętrzną bibliotekę opartą na qt - [QHTTPEngine](https://github.com/nitroshare/qhttpengine). Jej pliki źródłowe są dołączone do projektu<sup>1)</sup> code-snippet-app, nie trzeba więc jej dodatkowo pobierać. Aby ją zainstalować (w folderze projektu, nie globalnie) należy przejść w terminalu do folderu z projektem i wywołać komendy:

  

1. `$ cd server/lib/qhttpengine`

2. `$ cmake CMakeLists.txt -B build`

3. `$ cd build`

4. `$ make install` - nie przejmować się błędem :( naprawię

  
Budowanie projektu. Będąc w katalogu `server`.


5. `$ cd src`

6. `$ qmake`

7. `$ make`

  

Uruchomienie aplikacji (będąc w katalogu `server/src`):

  

8. `$ ./server`

<sup>1)</sup> jedyną zmianą w kodzie źródłowym jest zmiana zmiennych `BIN_INSTALL_DIR`, `LIB_INSTALL_DIR`, `INCLUDE_INSTALL_DIR` w pliku CMakeLists.txt na ścieżki w obrębie folderu aplikacji (by nie instalować biblioteki globalnie). Może skutkować brakiem działania dołączonych do biblioteki przykładów (examples).

# Testowanie

Serwer nasłuchuje na porcie 8000 pod adresem `app` (`localhost:8000/app`). Przyjmuje zapytania `POST` z body w formacie json z polami:

  

* `author` - string (np. `QString`) max 30 znaków

* `title` - string max 100 znaków

* `created` - obiekt klasy `QDateTime` sparsowany na string (`QDateTime::toString()`)

* `lang` - jeden z dozwolonych przez zmienną `Snippet::availableLangs_` napisów identyfikujących język

* `content` - string o długości max 1000 znaków

  

oraz zapytania `GET` o dowolnym body. Odpowiedzą na zapytanie typu `GET` jest lista maksymalnie 5 snippetów w formacie json ostatnio dodanych przez zapytania `POST`. Nie jest ona przechowywana w pamięci nieulotnej - by otrzymać snippety z serwera, należy je zapostować w ciągu działania programu.

  


