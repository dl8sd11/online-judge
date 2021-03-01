set -e
while [ 1 ]
do
    ./testgen.py > testcase.in
    python me.py < testcase.in > a1.out
    python ans.py < testcase.in > a2.out
    diff a1.out a2.out
    echo "Accept"
done
