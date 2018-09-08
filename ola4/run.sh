#!/bin/bash
let iris=4
let cancer=9
let iTrain=140
let cTrain=96
let tst=10

rm iris.txt cancer.txt
touch iris.txt cancer.txt

for i in `seq 1 100`; do
    echo $i
    for n in `seq 1 $iTrain`; do
        touch irisTrain.txt irisTest.txt
        cat iris-data.txt | gshuf > tmpI
        head -$iTrain tmpI > irisTrain.txt
        tail -$tst tmpI > irisTest.txt
        #printf "i=$i,k=$n,c=" >> iris.txt
        ./kmeans $i $n $iris irisTrain.txt irisTest.txt >> irisK$n.txt
        rm irisTrain.txt irisTest.txt
    done
    for n in `seq 1 $cTrain`; do
        touch cancerTrain.txt cancerTest.txt
        cat cancer-data.txt | gshuf > tmpC
        head -$cTrain tmpC > cancerTrain.txt
        tail -$tst tmpC > cancerTest.txt
        #printf "i=$i,k=$n,c=" >> cancer.txt
        ./kmeans $i $n $cancer cancerTrain.txt cancerTest.txt >> cancerK$n.txt
        rm cancerTrain.txt cancerTest.txt
    done
done

rm tmpI tmpC


