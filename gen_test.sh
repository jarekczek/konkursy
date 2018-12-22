#!/bin/bash

shopt -s expand_aliases
if [[ x$OSTYPE == xmsys ]]; then
  alias python=/c/lang/python2/python.exe
fi

export testDir=testy_moje
export test=all
export bDirectOutput=0
export bCompare=1
# export bMierz=1
export bDebug=0
export bGenOdp=1
echo generujemy testy
python ./gen.py
echo generujemy wyniki
./run.sh
echo sprawdzamy wyniki
export bGenOdp=0
./run.sh
