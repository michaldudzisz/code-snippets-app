# Serwer
## Aby uruchomić aplikację serwera ze źródeł należy:

### Na platformie Linux:

W celu stworzenia środowiska dla pythona:

`$ python3 -m venv env`
`$ source ./env/bin/activate`
`$ pip install flask`

Budowanie projektu:

`$ cd ./build`
`$ cmake ..`
`$ make`

Uruchomienie aplikacji:

`$ cd ..`
`$ export FLASK_APP=./build/src/server.py`
`$ flask run`



