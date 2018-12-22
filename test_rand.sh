#!/bin/bash

echo generujemy testy
C:/lang/python2/python.exe gen.py
export testDir=testy_moje
echo generujemy odpowiedzi
bGenOdp=1 ./run.sh
export test=all
export bDirectOutput=0
# export bMierz=1
export bDebug=0
echo sprawdzamy wyniki
./run.sh
