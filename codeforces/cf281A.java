import java.util.*;

public class cf281A {
    public static void main (String[] args) {

        Scanner in = new Scanner(System.in);

        String str = in.next();

        str = (str.charAt(0)+"").toUpperCase() + str.substring(1);

        System.out.println(str);

        in.close();
    }
}