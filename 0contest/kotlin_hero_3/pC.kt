import java.util.*
private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints

fun main() {
    var t = readInt();

    for (ul in 1..t) {
        var n = readInt();
        var a = readInts();
        var ans = arrayListOf<Boolean>();

        var sum = 0;
        var mnid = -1;

        for (i in 0..n-1) {
            var v = a[i];

            if (v > 0) {
                sum += v;
            }
            ans.add(v > 0);

            if (v != 0) {
                if (mnid == -1) {
                    mnid = i;
                } else if (Math.abs(v) < Math.abs(a[mnid])) {
                    mnid = i;
                }
            }
        }

        sum -= Math.abs(a[mnid]);

        if (a[mnid] > 0) {
            ans[mnid] = false;
        } else {
            ans[mnid] = true;
        }

        println(sum);
        for (b in ans) {
            if (b) {
                print(1);
            } else {
                print(0);
            }
        }
        println();


    }
}