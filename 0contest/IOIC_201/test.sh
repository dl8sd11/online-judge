for i in {1..30};do
./a.out > out
echo $i
./pK < out
done;