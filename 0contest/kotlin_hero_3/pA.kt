import java.util.*
private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints

fun main() {
    var t = readInt();

    for (ul in 1..t) {
        var n = readInt();
        if (n >= 999500 && n <= 1000000) {
            n += 500;
        }

        if (n < 1000) {
            println(n);
        } else if (n < 1000000) {
            var a = 0;
            if (n%1000 >= 500) a++;
            println("${n/1000+a}K");
        } else {
            var a = 0;
            if (n%1000000 >= 500000) a++;
            println("${n/1000000+a}M");
        }
    }
}