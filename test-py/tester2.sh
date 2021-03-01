set -e
while [ 1 ]
do
    ./testgen.py > testcase.in
    ./rectME.out < testcase.in > a1.out
    ./rectANS.out < testcase.in > a2.out
    diff a1.out a2.out
    echo "Accept"
done
