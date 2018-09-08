#!/bin/bash
let iris=4
let cancer=9
let iTrain1=147
let iTest1=3
let iTrain2=135
let iTest2=15
let cTrain1=103
let cTest1=3
let cTrain2=91
let cTest2=15

rm iris1.txt iris2.txt cancer1.txt cancer2.txt
touch iris1.txt iris2.txt cancer1.txt cancer2.txt

for i in `seq 1 5000`; do
    touch iris1Train.txt iris1Test.txt iris2Train.txt iris2Test.txt
    touch cancer1Train.txt cancer1Test.txt cancer2Train.txt cancer2Test.txt
    cat iris-data.txt | gshuf > tmpI
    cat cancer-data.txt | gshuf > tmpC
    head -$iTrain1 tmpI > iris1Train.txt
    tail -$iTest1 tmpI > iris1Test.txt
    head -$iTrain2 tmpI > iris2Train.txt
    tail -$iTest2 tmpI > iris2Test.txt
    head -$cTrain1 tmpC > cancer1Train.txt
    tail -$cTest1 tmpC > cancer1Test.txt
    head -$cTrain2 tmpC > cancer2Train.txt
    tail -$cTest2 tmpC > cancer2Test.txt
    ./id3 $iris iris1Train.txt iris1Test.txt >> iris1.txt
    ./id3 $iris iris2Train.txt iris2Test.txt >> iris2.txt
    ./id3 $cancer cancer1Train.txt cancer1Test.txt >> cancer1.txt
    ./id3 $cancer cancer2Train.txt cancer2Test.txt >> cancer2.txt
    rm iris1Train.txt iris1Test.txt iris2Train.txt iris2Test.txt
    rm cancer1Train.txt cancer1Test.txt cancer2Train.txt cancer2Test.txt
done

rm tmpI tmpC


