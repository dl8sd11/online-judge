import java.util.*
private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints

fun main() {
    var n = readInt();
    var a = readInts();

    var vis = Array(1001){false};

    var res = ArrayList<Int>();

    for (i in n-1 downTo 0) {
        if (vis[a[i]] == false) {
            res.add(a[i]);
            vis[a[i]] = true;
        }
    }

    var ans = res.reversed();

    println(ans.size);
    println(ans.joinToString(" "));

}