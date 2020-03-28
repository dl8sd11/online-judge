import java.util.*
private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints

fun main() {
    var t = readInt();

    for (ul in 1..t) {
        var (n, k) = readInts();
        var ans = Array(n+1){true};
        var edge = Array(n+1){arrayListOf<Int>()};
        var deg = Array(n+1){0};

        for (i in 1..n-1) {
            var (u, v) = readInts();
            edge[u].add(v);
            edge[v].add(u);
            deg[u]++;
            deg[v]++;
        }

        var queue = Array(n+1){0};
        var ft = 0;
        var bk = 0;

        var cnt = 0;
        for (i in 1..n) {
            if (deg[i] == 1) {
                queue[bk++] = i;
                cnt++;
            }
        }

        if (cnt < k) {
            println("No");
        } else {
            println("Yes");
            while (cnt > k) {
                var nd = queue[ft++];
                cnt--;
                ans[nd] = false;

                for (v in edge[nd]) {
                    if (--deg[v] == 1) {
                        queue[bk++] = v;
                        cnt++;
                    }
                }
            }

            var opt = arrayListOf<Int>();
            for (i in 1..n) {
                if (ans[i]) {
                    opt.add(i);
                }
            }

            println(opt.size);
            println(opt.joinToString(" "));
        }
    }
}