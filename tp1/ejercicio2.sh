#! /bin/bash
mkdir ejercicio_bash_avanzado
cd ejercicio_bash_avanzado
wget https://github.com/td3-frm/practica/raw/master/01-linea-de-comando/hola.zip
unzip hola.zip
mv hola.c hola_mundo.c
gcc -o hola_mundo hola_mundo.c
./hola_mundo
