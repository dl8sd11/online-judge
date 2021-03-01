set -e
g++ -std=c++17 -O2 me.cpp -o me.out
g++ -std=c++17 -O2 ans.cpp -o ans.out
while [ 1 ]
do
    ./a.out 1000000 1000000 > testcase.in
    ./me.out < testcase.in > a1.out
    ./ans.out < testcase.in > a2.out
    diff a1.out a2.out
    echo "Accept"
done
