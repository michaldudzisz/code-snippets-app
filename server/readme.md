# Szkielet aplikacji serwera:


## Przykładowe uruchomienie projektu na GNU/Linux Ubuntu 20.04


W celu stworzenia środowiska dla pythona:

1. `$ python3 -m venv env`
2. `$ source ./env/bin/activate`
3. `$ pip install flask`

Budowanie projektu:

4. `$ cd ./build`
5. `$ cmake ..`
6. `$ make`

Uruchomienie aplikacji:

7. `$ cd ..`
8. `$ export FLASK_APP=./build/src/server.py`
9. `$ flask run`


# Testowanie 
W terminalu zostanie wypisany numer portu (domyślnie 5000), pod którym działa serwer. Wystarczy wpisać `localhost:<numer portu>` w ulubionej rpzeglądarce internetowej, by otrzymać powitanie. Opóźnienie świadczy o działaniu obliczeń wykonywanych w języku c++.