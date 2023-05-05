#!/bin/bash
mkdir ejercicio_rutas
cd ejercicio_rutas
mkdir fotos videos documentos
wget https://github.com/td3-frm/practica/raw/master/01-linea-de-comando/Paul-Cezanne_Still-Life-With-Apples.jpeg
mv Paul-Cezanne_Still-Life-With-Apples.jpeg fotos
echo 1342 > 1342.txt
mv 1342.txt documentos
mkdir /home/damian/Tps/01-Linea_de_comandos/ejercicio_rutas/backup
cp /home/damian/Tps/01-Linea_de_comandos/ejercicio_rutas/documentos/1342.txt /home/damian/Tps/01-Linea_de_comandos/ejercicio_rutas/backup/
