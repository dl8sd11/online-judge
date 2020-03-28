import java.util.*
private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints

fun main() {
    var t = readInt();

    for (ul in 1..t) {
        var (n, k) = readInts();

        var ai = arrayListOf<Pair<Int,Int>>();
        var aa = readInts();
        var a = arrayListOf<Int>();
        var ans = Array(n){0};

        for (i in 0..n-1) {
            ai.add(Pair(aa[i], i));
            a.add(aa[i]);
        }

        ai.sortBy({it.first});

        for (i in n-2 downTo 0) {
            var gap = a[ai[i+1].second] - a[ai[i].second] - 1;
            if (k >= gap) {
                a[ai[i].second] += gap;
                ans[ai[i].second] += gap;
                k -= gap;
            } else {
                a[ai[i].second] += k;
                ans[ai[i].second] += k;
                k = 0;
            }
        }

        for (i in 0..n-1) {
            a[ai[i].second] += k / n;
            ans[ai[i].second] += k/n;
        }

        for (i in 1..k%n) {
            var j = n-i;
            a[ai[j].second] += 1;
            ans[ai[j].second] += 1;
        }

        println(ans.joinToString(" "));
    }
}