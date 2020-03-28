import java.util.*
private fun readLn() = readLine()!! // string line
private fun readInt() = readLn().toInt() // single int
private fun readStrings() = readLn().split(" ") // list of strings
private fun readInts() = readStrings().map { it.toInt() } // list of ints

fun main() {
    var (n, k) = readInts();

    var r = readInts();
    var skill = arrayListOf<Pair<Int,Int>>();
    var edge = Array(n+1){arrayListOf<Int>()};

    for (i in 0..n-1) {
        skill.add(Pair(r[i], i));
    }

    for (i in 0..k-1) {
        var (u, v) = readInts();
        u--;
        v--;
        edge[u].add(v);
        edge[v].add(u);
    }

    skill.sortBy({it.first})
    // println(skill);

    var vis = Array(n+1){false};
    var ans = Array(n){0};

    var j = 0;
    for (i in 0..n-1) {
        while (j < n && skill[j].first < skill[i].first) {
            vis[skill[j].second] = true;
            j++;
        }

        var id = skill[i].second;

        ans[id] = j;
        for (adj in edge[id]) {
            if (vis[adj]) {
                ans[id]--;
            }
        }
    }

    println(ans.joinToString(" "));
}