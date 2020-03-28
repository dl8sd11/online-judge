import java.util.*;

public class cf1249F {

    static int n, k;
    static int dp[][], a[];
    static ArrayList<Integer> edge[];

    static void init () {
        dp = new int[n+1][n+1];
        a = new int[n+1];

        edge = new ArrayList[n+1];
        for (int i=0; i<=n; i++) {
            edge[i] = new ArrayList<Integer>();
        }
    }

    static void dfs (int nd, int par, int dep) {

        dp[nd][dep] = a[nd];
        for (int v : edge[nd]) {
            if (v != par) {
                dfs(v, nd, dep+1);
                int d2 = dep+k+1;
                if (d2 <= n) {
                    dp[nd][dep] += dp[v][d2];
                }
            }
        }
        
        // System.out.println(nd + ", " + dep + ", " + dp[nd][dep]);
        for (int d=dep+1; d<=n; d++) {
            dp[nd][d] = 0;
            for (int c : edge[nd]) {
                int cur = dp[c][d];

                for (int v : edge[nd]) {
                    if (v != c) {
                        int d2 = Math.max(d, 1+k-(d-dep)+dep);
                        if (d2 <= n) {
                            cur += dp[v][d2];
                        }
                    }
                }

                dp[nd][d] = Math.max(dp[nd][d], cur);
            }

            // System.out.println(nd + ", " + d + ", " + dp[nd][d]);
        }

        for (int i=n-1; i>=dep; i--) {
            dp[nd][i] = Math.max(dp[nd][i], dp[nd][i+1]);
        }
    }

    public static void main (String[] args) {

        Scanner in = new Scanner(System.in);

        n = in.nextInt();
        k = in.nextInt();

        init();

        for (int i=1; i<=n; i++) {
            a[i] = in.nextInt();
        }

        for (int i=0; i<n-1; i++) {
            int u, v;
            u = in.nextInt();
            v = in.nextInt();

            edge[u].add(v);
            edge[v].add(u);
        }

        dfs(1, -1, 0);

        System.out.println(dp[1][0]);

        in.close();
    }
}