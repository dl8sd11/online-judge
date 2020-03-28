import java.util.*
private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints

fun main() {
    var (n,w) = readInts();

    var a = readInts();

    var mn = 0;
    var mx = 0;
    var cur = 0;

    for (i in 0..n-1) {
        cur += a[i];
        mn = Math.min(mn, cur);
        mx = Math.max(mx, cur);
    }

    println(Math.max(0, w+1-(mx-mn)));
}