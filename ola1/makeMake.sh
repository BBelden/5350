declare h=2
declare g=1

echo -n "all : " > myjobs.makefile

for ((x=0;x<1000;x++));do
    echo -n "target$x ";
done >> myjobs.makefile

echo >> myjobs.makefile

for ((x=0;x<1000;x++)); do
    echo -e "target$x : \n\t./random_board $x 100 | ./a-star $h $g > sol$x.txt";
done >> myjobs.makefile


