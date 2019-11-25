set -e
g++ -std=c++11 -Dtmd me.cpp -o me.out 
# g++ -std=c++11 -Dtmd ans.cpp -o ans.out 
while [ 1 ]
do
    ./testgen.py > testcase.in
    ./me.out < testcase.in > a1.out
    # ./ans.out < testcase.in
    echo "Accept"
done
