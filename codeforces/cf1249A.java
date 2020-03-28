import java.util.*;

public class cf1249A {

    public static void main (String[] args) {

        Scanner in = new Scanner(System.in);

        int n, q;
        q = in.nextInt();
        
        while (q-- > 0) {
            n = in.nextInt();
            
            int[] a = new int[n];

            for (int i=0; i<n; i++) {
                a[i] = in.nextInt();
            }

            int ans = 1;

            for (int i=0; i<n; i++) {
                for (int j=0; j<i; j++) {
                    if (Math.abs(a[i]-a[j]) == 1) {
                        ans = 2;
                    }
                }
            }

            System.out.println(ans);

        }
        in.close();
    }
}
