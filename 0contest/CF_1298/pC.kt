import java.util.*
private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints

fun main() {
    var n = readInt();
    var word = readLn();

    var cnt = 0;
    var ans = 0;

    for (i in 0..n-1) {
        if (word[i] == 'x') {
            if (cnt == 2) {
                ans++;
            } else {
                cnt++;
            }
        } else {
            cnt = 0;
        }
    }

    println(ans);
}