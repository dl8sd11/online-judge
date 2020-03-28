import java.util.*;
private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints


fun main() {
    var (m, k) = readInts();
    
    var dp = Array(10000){hashMapOf<Int>()};

    fun genSet (cur : Int) {
        var a = arrayListOf(2, 3, 5, 7);
        state.add(cur);
        for (v in a) {
            if (cur % v == 0 && !(cur/v in state)) {
                genSet(cur/v);
            }
        }
    }
    genSet(m);

    print(state);
}