set -e
g++ -std=c++11 me.cpp -o me.out
g++ -std=c++11 ans.cpp -o ans.out
while [ 1 ]
do
    ./testgen > testcase.in
    ./me.out < testcase.in > a1.out
    ./ans.out < testcase.in > a2.out
    diff a1.out a2.out
    echo "Accept"
done
