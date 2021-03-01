set -e
g++ -std=c++17 nq.cpp -o me.out
g++ -std=c++17 mo.cpp -o ans.out
while [ 1 ]
do
    ./gen 1000 500 1000 1000 $(($RANDOM%1000)) > testcase.in
    ./me.out < testcase.in > a1.out
    ./ans.out < testcase.in > a2.out
    diff a1.out a2.out
    echo "Accept"
done
