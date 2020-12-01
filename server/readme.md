# Szkielet aplikacji serwera:


## Przykładowe uruchomienie projektu na GNU/Linux Ubuntu 20.04


Zakłada się, że użytkownik ma zainstalowane globalnie biblioteki boost. Jeśli nie ma, to może to zrobić tak: `sudo apt-get install libboost-all-dev`

W celu stworzenia środowiska dla pythona:

1. `$ python3 -m venv env`
2. `$ source ./env/bin/activate`
3. `$ pip install flask`

Budowanie projektu. Będąc w katalogu `server`.

4. `$ mkdir build`
5. `cd ./build`
6. `$ cmake ..`
7. `$ make`

Uruchomienie aplikacji:

8. `$ cd ..`
9. `$ export FLASK_APP=./build/src/server.py`
10. `$ flask run`

Ważne, by uruchamiać je znajdując się w aktywnym środowisku wirtualnym interpretera Python.

# Testowanie 
W terminalu zostanie wypisany numer portu (domyślnie 5000), pod którym działa serwer. Wystarczy wpisać `localhost:<numer portu>` w ulubionej przeglądarce internetowej, by otrzymać powitanie. Opóźnienie świadczy o działaniu obliczeń wykonywanych w języku c++.