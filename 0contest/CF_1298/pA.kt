import java.util.*
private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints

fun main() {
    var x = readInts();
    
    var y = x.sorted();

    var a = arrayListOf<Int>();
    
    for (i in 0..2) {
        a.add(y[3] - y[i]);
    }
    println(a.joinToString(" "));
}