import java.util.*
private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints

fun main() {
    var t = readInt();

    for (ul in 1..t) {

        var (n, m) = readInts();
        var rng = arrayListOf<Pair<Int,Int> >();
        var srng = arrayListOf<Pair<Int,Int> >();
        val pq = PriorityQueue<Pair<Int,Int>>(compareBy {it.first})
        var wt = Array(n){0};

        for (i in 0..n-1) {
            var (u,v) = readInts();
            rng.add(Pair(u,v));
            srng.add(Pair(u,i));
        }

        srng.sortBy({it.first});
        // print(rng);

        var idx = 0;
        var ctime = srng[0].first;

        var mxDelay = 0;

        while (true) {
            // print(ctime);
            // print(pq);
            while ((idx<n) && (srng[idx].first <= ctime)) {
                pq.add(Pair(rng[srng[idx].second].second, srng[idx].second));
                idx++;
            }

            var it = minOf(pq.size, m);
            for (i in 1..it) {
                var tp = pq.poll();
                wt[tp.second] = ctime;
                mxDelay = maxOf(mxDelay, ctime - rng[tp.second].second);
            }

            if (pq.size == 0) {
                if (idx == n) {
                    break;
                } else {
                    ctime = srng[idx].first;
                }
            } else {
                ctime++;
            }
        }

        println(mxDelay);
        println(wt.joinToString(" "));

    }
}