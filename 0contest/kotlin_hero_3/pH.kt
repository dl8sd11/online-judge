import java.util.*
private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints

fun main() {
    var t = readInt();

    for (ul in 1..t) {
        var str = readLn();

        var n = str.length;
        var ans = Array(n){false};

        var lptr = 0;
        var rptr = 1;

        while (lptr < n) {
            println("$lptr $rptr");
            while (lptr < n && ans[lptr]) {
                lptr++;
            }
            if (lptr >= n) {
                break;
            }


            while (rptr <= lptr) {
                rptr++;
            }

            var fnd = -1;
            for (i in rptr..n-1) {
                if (str[i] <= str[lptr]) {
                    if (fnd == -1) {
                        fnd = i;
                    } else if (str[i] > str[fnd]) {
                        fnd = i;
                    }
                }
            }

            if (fnd == -1) {
                break;
            } else {
                ans[fnd] = true;

                if (str[fnd] < str[lptr]) {
                    for (j in fnd..n-1) {
                        ans[j] = true;
                    }
                    break;
                }
            }
            
            rptr = fnd + 1;
            lptr++;
        }

        for (i in 0..n-1) {
            if (ans[i]) {
                print("B");
            } else {
                print("R");
            }
        }
        println();

    }
}