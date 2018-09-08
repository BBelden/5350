#!/bin/bash

let iris=4
let cancer=9
let iTrain=140
let cTrain=96
let tst=10

let n=50

touch irisTrain.txt irisTest.txt cancerTrain.txt cancerTest.txt
cat iris-data.txt | gshuf > tmpI
cat cancer-data.txt | gshuf > tmpC
head -$iTrain tmpI > irisTrain.txt
head -$cTrain tmpC > cancerTrain.txt
tail -$tst tmpI > irisTest.txt
tail -$tst tmpC > cancerTest.txt
./kmeans $RANDOM $n $iris irisTrain.txt irisTest.txt
./kmeans $RANDOM $n $cancer cancerTrain.txt cancerTest.txt
rm irisTrain.txt irisTest.txt cancerTrain.txt cancerTest.txt
rm tmpI tmpC


