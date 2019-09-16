private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints
 
fun main() {
    var n = readInt()
    var a : IntArray = IntArray(n)

    var mn = 1
    var mx = 1

    var idx = 0;
    for (d in readInts()) {
        a[idx] = d
        idx++;
    }

    for (i in 1..n) {
        if (a[i-1] < a[mn-1]) {
            mn = i;
        }
        if (a[i-1] > a[mx-1]) {
            mx = i;
        }
    }

    var mid = -1
    for (i in 1..n) {
        if (a[i-1] != a[mn-1] && a[i-1] != a[mx-1]) {
            mid = i;
        }
    }

    if (mid == -1) {
        println("-1 -1 -1")
    } else {
        println("%d %d %d".format(mn, mid, mx))
    }
}