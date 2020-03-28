import java.util.*
private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints

fun main() {
    var t = readInt();

    for (ul in 1..t) {
        var n = readInt();
        var seg = arrayListOf<Pair<Int,Int>>();
        var can = arrayListOf<Int>();

        for (i in 1..n) {
            var (u, v) = readInts();
            seg.add(Pair(u, v));
            can.add(u);
            can.add(u-1);
            can.add(v);
            can.add(v+1);
        }

        var ans = -1;

        for (v in can) {
            var cnt = 0;
            for (p in seg) {
                if (v >= p.first && v <= p.second) {
                    cnt++;
                }
            }
            if (cnt == 1) {
                ans = v;
            }
        }

        println(ans);
    }
}