# Szkielet aplikacji serwera:

  
  

## Przykładowe uruchomienie projektu na GNU/Linux Ubuntu 20.04

  
  

Zakłada się, że użytkownik ma zainstalowane globalnie biblioteki qt5 oraz sterownik do obsługi bazy danych SQLite3. 

Jeśli nie ma, to może to zrobić tak: 
`sudo apt-get install qt5-default`
`sudo apt-get install sqlite3`
  

Serwer wykorzystuje zewnętrzną bibliotekę opartą na qt - [QHTTPEngine](https://github.com/nitroshare/qhttpengine). Jej pliki źródłowe są dołączone do projektu<sup>1)</sup> code-snippet-app, nie trzeba więc jej dodatkowo pobierać. Aby ją zainstalować (w folderze projektu, nie globalnie) należy przejść w terminalu do folderu z projektem i wywołać komendy:

  

1. `$ cd server/lib/qhttpengine`

2. `$ cmake CMakeLists.txt -B build` - nie przejmować się błędem :( naprawię

3. `$ cd build`

4. `$ make install`

Tworzenie bazy danych:

5. `$ ./unix-setup.sh`
  
Budowanie projektu. Będąc w katalogu `server`.


6. `$ mkdir build && cd build`

7. `$ cmake ..`

8. `$ make`

  

Uruchomienie aplikacji (będąc w katalogu `server`):


9. `$ cd bin`
10. `$ ./server`

Uruchomienie testów jednostkowych:

11. `$ cd bin`
12. `$ ./test`

<sup>1)</sup> jedyną zmianą w kodzie źródłowym jest zmiana zmiennych `BIN_INSTALL_DIR`, `LIB_INSTALL_DIR`, `INCLUDE_INSTALL_DIR` w pliku CMakeLists.txt na ścieżki w obrębie folderu aplikacji (by nie instalować biblioteki globalnie). Może skutkować brakiem działania dołączonych do biblioteki przykładów (examples).

# Testowanie

Serwer nasłuchuje na porcie 8000 pod adresem `app` (`localhost:8000/app`). Przyjmuje zapytania `POST` z body w formacie json z polami:

  

* `author` - string (np. `QString`) max 30 znaków

* `title` - string max 100 znaków

* `created` - obiekt klasy `QDateTime` zamieniony na liczbę w formacie **Unix time** z dokładnością co do sekundy (`QDateTime::toSecsSinceEpoch()`)

* `lang` - jeden z dozwolonych przez zmienną `Snippet::availableLangs_` napisów identyfikujących język

* `content` - string o długości max 1000 znaków

  

oraz zapytania `GET` o body będącym pustym obiektem json lub obiektem klasy SnippetSearchPattern zamienionym na json (`SnippetSearchPattern::toJson()`). 

Odpowiedzą na zapytanie typu `GET` z body w postaci pustego obiektu json jest lista maksymalnie 5 snippetów w formacie json ostatnio dodanych przez zapytania `POST` (formalnie są to obiekty o najwyższym id w bazie danych). 

Klasa `SnippetSearchPattern` ma pola:
* authorSubsequence_ - string nie dłuższy niż 30 znaków, jeśli pusty - dowolny autor
* titleSubsequence_ - string nie dłuższy niż 100 znaków, jeśli pusty - dowolny tytuł
* createdFrom_ - data w tej samej postaci **Unix time** jak wyżej lub **null** jeśli niesprecyzowane
* createdTo_ - data w tej samej postaci **Unix time** jak wyżej lub **null** jeśli niesprecyzowane
* lang_ - jeden z napisów identyfikujących język lub pusty string oznaczający dowolny język

Wszystkie pola są opcjonalne i można je dowolnie łączyć. Do zamieniania klasy `SnippetSearchPattern` na json służy funkcja `SnippetSearchPattern::toJson()` - zamienia ona dobrze niesprecyzowane daty (które normalnie są nieokreślone) na nulle w postaci jsona. 

Klasy `SnippetSearchPattern` można użyć tak:

```c++
SnippetSearchPattern pattern;
pattern.setAuthorSubsequence("userna")
pattern.setLang("c++");
```

Każde nieustwione pole ma domyślnie pustą wartość.

Wynikiem każdego poprawnego zapytania `GET` jest json - lista obiektów snippet. Może być pusta.

W wyniku niepoprawnego zapytania w sockecie ustawiany jest kod błędu **Bad Request** i w jsonie w polu `"message"` powinien zostać zwrócony odpowiedni komunikat.

