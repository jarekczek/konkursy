#!/bin/bash

#set -x
PS4='${LINENO}:'

# SPOSOB UZYCIA {{{
# system dziala w oparciu o bash, na windowsie uzywamy msysa i mingw
# na kazde zadanie katalog z nazwa zadania i do niego te pliki
# plik z rozwiazaniem ma te sama nazwe co katalog i rozszerzenie cpp
#   (sa tez zaremowane wywolania javy)
# mozna stworzyc rowniez plik abc_tepe.cpp z brutem
# majac bruta i generator testow (gen.py) mozna automatycznie sprawdzac
#   lepszy algorytm, przyklad w pliku gen_test.sh
# dostrajamy opcje wykonania w sekcji parametry albo przez linie polecen,
#   np. testDir=testyMoje ./run.sh
# }}}
# CZESC STALA {{{
curDir=`dirname $0`
if [[ $curDir == . ]]; then
  curDir=`readlink -f $curDir`
fi
cd $curDir

sysop=`uname`
sysop=${sysop:0:5}
function setIfNotSet() {
  eval if [[ ! '$'$1 ]]'; then '$1=$2'; fi'
}

sourceExt=kt
JDK=C:/lang/java/jdk_current_link/bin
KOTLINC=C:/lang/kotlinc/bin/kotlinc

# }}}
# PROBLEM GENERATORS {{{

function genProb
{
  mkdir $1
  for f in run.sh gen.py gen_test.sh test_rand.sh; do
    cp $f $1
  done
  touch $1/$1.$sourceExt
    mkdir $1/testy
  echo "touched $1/$1.$sourceExt"
}

if [[ x$1 == xgencf ]]; then
  for prob in A B C D E; do
    genProb $prob
  done
  exit 0
fi

if [[ x$1 == xgenprob ]]; then
  shift
  while [[ -n $1 ]]; do
    genProb $1
    shift
  done
  exit 0
fi
# }}}

# PARAMETERS
setIfNotSet testDir testy
setIfNotSet test all
setIfNotSet bCompile 1
setIfNotSet bCompare 1
setIfNotSet bSilent 0
setIfNotSet bShowDiff 1
setIfNotSet bShowOutput 0
setIfNotSet bDebug 0
setIfNotSet bMierz 0
setIfNotSet bAsserts 0
setIfNotSet bPause 1
setIfNotSet bDirectOutput 1
setIfNotSet bGenOdp 0
setIfNotSet bUsaco 0
setIfNotSet bDistributed 0

if [[ $bCompare == 1 ]]; then
  bDirectOutput=0
fi

if [[ $(hostname) == lenovo8g ]]; then
  CPP="C:/lang/MinGW/bin/g++.exe"
else
  CPP="g++"
fi
mem=32M
CPPOPTS="-static-libstdc++ -static-libgcc"
CPPOPTS=""
CPPOPTS="-g -O2 -static"
CPPOPTS="-std=c++11 -O3 -lm"
if [[ $bDistributed == 1 ]]; then
  CPPOPTS="-DHOME message_internal.c zeus_local.c teatr.cpp -DxINPUTSTDIN"
  parunner=J:/lang/konkursy/pa2018/rpa_minimal/executable/parunner.exe
  if [[ $bDebug == 1 ]]; then
    #bDirectOutput=1
    #PARUNNEROPTS="-trace_comm -warn_unreceived -stdout contest -stderr files -n 3"
    PARUNNEROPTS="-stdout all -n 100"
  else
    PARUNNEROPTS="-stdout contest -n 100"
  fi
else
  CPPOPTS2="-lm -DHOME -DSINGLEINSTANCE -DINPUTSTDINx"
fi

# PARAMETRY Z LINII POLECEÑ
if [[ $1 ]]; then
  test=$1
  # bDebug=0
  # bAsserts=0
  # bPause=0
fi

# ZMIENNE
plikKompilacji=compOut.txt

# zadanie to nazwa katalogu pozbawiona ewentualnie ?_ z pocz¹tku
zad=`basename $curDir`
zad=${zad#*_}

function pause() {
  if [[ $bPause == 1 ]]; then
    read -n1 -p "$1"
  fi
  }

if [[ $mem ]]; then
  javaOpts="${javaOpts} -Xmx$mem -Xms$mem -Xss$mem"
fi
if [[ $bDebug != 0 ]]; then
  javaOpts="${javaOpts} -Ddebug=1"
fi
if [[ $bMierz != 0 ]]; then
  javaOpts="${javaOpts} -Dmierz=1"
fi
if [[ $bAsserts != 0 ]]; then
  javaOpts="${javaOpts} -ea"
fi

if [[ $bCompile != 0 ]]; then
  echo -n Kompilacja"... "
  if [[ $sourceExt == "java" ]]; then
    "${JDK}/javac.exe" $zad.java >$plikKompilacji 2>&1
  elif [[ $sourceExt == "kt" ]]; then
    "${KOTLINC}" $zad.kt >$plikKompilacji 2>&1
  else

    #CPP
    defs="-DWIN"
    if [[ $bDebug -eq 1 ]]; then defs="$defs -DDEBUG"; fi
    if [[ $bMierz -eq 1 ]]; then defs="$defs -DMIERZ"; fi
    if [[ $bGenOdp == 1 ]]; then
      $CPP $CPPOPTS ${zad}_tepe.cpp -O $defs -o ${zad}_tepe.exe $CPPOPTS2 >$plikKompilacji 2>&1 
    else
      $CPP $CPPOPTS $zad.cpp -O $defs -o $zad.exe >$plikKompilacji $CPPOPTS2 2>&1 
    fi
  fi
  status=$?
  cat $plikKompilacji
  
  if [[ $status != 0 ]]; then
    echo blad kompilacji $status
    # pause
    exit
  else
    echo ok
  fi;
fi

echo uruchamiamy $zad

if [[ $test == all ]]; then
  listaTestow=$testDir/*.in
else
  for i in $test; do
    listaTestow="$listaTestow $testDir/$i.in"
  done
fi

cOk=0
cErr=0
for testNrIn in $listaTestow; do
  testNr=${testNrIn%.*}
  plikOut=$testNr.tes
  plikErr=$testNr.err
  plikFc=$testNr.fc
  plikIn=$testNr.in
  plikOutWzor=$testNr.out
  if [[ $bUsaco == 1 ]]; then cp $plikIn ${zad}.in; fi

  if [[ $bGenOdp == 1 ]]; then
    if [[ $bCompile == 1 && $sourceExt == "java" ]]; then
      echo Kompilujemy tepe.
      "${JDK}/javac.exe" ${zad}_tepe.java >$plikKompilacji 2>&1
    fi
    if [[ $sourceExt == "java" ]]; then
      java.exe $javaOpts ${zad}_tepe <$plikIn >$plikOutWzor 2>$plikErr
    else
      ./${zad}_tepe.exe <$plikIn >$plikOutWzor 2>$plikErr
    fi
  else

    if [[ $bDirectOutput == 1 ]]; then
      if [[ $sourceExt == "java" ]]; then
        java.exe $javaOpts $zad <$plikIn >$plikOut
      else
        if [[ $bDistributed == 1 ]]; then
          echo launching parunner 205
          $parunner $PARUNNEROPTS $zad.exe <$plikIn
        else
          if [[ $bMierz == 1 ]]; then
            runlimwin.exe -t 20000 ./$zad.exe <$plikIn
          else
            ./$zad.exe <$plikIn
          fi
        fi
      fi
      rv=$?
    else
  
      if [[ $sourceExt == "java" ]]; then
        java.exe $javaOpts $zad <$plikIn >$plikOut 2>$plikErr
      elif [[ $sourceExt == "kt" ]]; then
        java.exe $javaOpts -cp '.;'"${KOTLINC%/*/*}"/lib/kotlin-runtime.jar programkt$zad <$plikIn >$plikOut 2>$plikErr
      else
        if [[ $sysop == MINGW ]]; then
          if [[ $bDistributed == 1 ]]; then
            echo launching parunner 223
            $parunner $PARUNNEROPTS $zad.exe <$plikIn >$plikOut 2>$plikErr
          else
            # runlimwin mierzy czas, pamiec, kontroluje zuzycie tych zasobow
            if [[ $bMierz == 1 ]]; then
              runlimwin.exe -t 20000 ./$zad.exe <$plikIn >$plikOut 2>$plikErr
            else
              ./$zad.exe <$plikIn >$plikOut 2>$plikErr
            fi
          fi
        else
          runlimwin.exe -t 20000 ./$zad.exe <$plikIn >$plikOut 2>$plikErr
          ./$zad.exe <$plikIn >$plikOut 2>$plikErr
        fi
      fi
      if [[ $bUsaco == 1 ]]; then cp ${zad}.out $plikOut; fi
      rv=$?
      if [[ $bShowOutput -ne 0 ]]; then
        cat $plikOut
      fi
      cat $plikErr
    fi
  
    if [[ $rv != 0 ]]; then
      echo '***************' BLAD WYKONANIA NA TESCIE $plikIn - $rv
      cErr=$(( $cErr + 1 ))
    else
      if [[ $bCompare -ne 0 ]]; then
        diff -w $plikOutWzor $plikOut >$plikFc 2>&1
        if [[ $? == 0 ]]; then
          cOk=$(( $cOk + 1 ))
          if [[ $bSilent -eq 0 ]]; then echo test $plikIn OK; fi
          #rm $plikFc
        else
          cErr=$(( $cErr + 1 ))
          echo '***************' BLAD NA TESCIE $plikIn '**********************'
          if [[ $bShowDiff == 1 ]]; then
            cat $plikFc
          fi
        fi
      fi
    fi
  fi
  
done

if [[ $bCompare != 0 ]]; then
  echo "ok:$cOk err:$cErr"
fi

#pause "gotowe"

# opcje edycji dla edytora jedit
# :collapseFolds=1:folding=explicit:
