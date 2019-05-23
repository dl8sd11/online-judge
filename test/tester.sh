set -e
while [ 1 ]
do
    ./testgen.py 2 > testcase.in
    ./$1 < testcase.in > a1.out
    ./$2 < testcase.in > a2.out
    diff a1.out a2.out
    echo "Accept"
done
