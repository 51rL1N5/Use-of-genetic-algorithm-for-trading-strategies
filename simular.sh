#!/bin/bash

MAXIND=30
MAXAVG=50
MAXGEN=100
MAXDAY=60
MUT=0.3


for (( i = 50; i <= $MAXIND; $((i+10)) )) do
 for (( j = 10; j <= $MAXAVG; j=$((j+5)) )) do 
  for (( k = 50; k <= $MAXGEN; k=$((k +10)) )) do
   for (( ww = 10; ww <= $MAXDAY; ww=$((ww+5)) )) do
    cd resultados
    touch "moving1.csv"
    touch "moving2.csv"
    cd ..
    run $i $j $k $ww $MUT
    cd resultados
    file1="moving1-"$i"-"$j"-"$k"-"$ww"-"$MUT".csv"
    mv moving1.csv $file1
    file2="moving2-"$i"-"$j"-"$k"-"$ww"-"$MUT".csv"
    mv moving2.csv $file2
    cd ..
    echo "Simulacao com $i, $j, $k, $ww, $MUT feita com sucesso"
   done
  done
 done
done
