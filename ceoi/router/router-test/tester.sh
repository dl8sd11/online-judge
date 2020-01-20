
for i in {1..7}
do
    a=$i-router.in
    cp $a router.in
    ../router < $a > router.out
    cp router.out router-out/$i-router.out
    ./a.out
done
