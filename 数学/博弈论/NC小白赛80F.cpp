import java.io.*;
import java.util.*;

public class Main {

    public static void main(String[] args) {
        Scanner sc = new Scanner(new BufferedInputStream(System.in));

        int n = sc.nextInt();
        int m = sc.nextInt();
        int k = sc.nextInt();

        int[] arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }
        int[] brr = new int[m];
        for (int i = 0; i < m; i++) {
            brr[i] = sc.nextInt();
        }
        int maxAlice = Arrays.stream(arr).max().getAsInt();
        int maxBob = Arrays.stream(brr).max().getAsInt();

        // 得用数组hash，替代java容器hashmap，卡常
        int[] alice = new int[maxAlice + 1];
        int[] bob = new int[maxBob + 1];
        for (int i = 0; i < n; i++) {
            alice[arr[i]]++;
        }
        for (int i = 0; i < m; i++) {
            bob[brr[i]]++;
        }

        // --------------------------------------

        // 下面是核心代码
        // 计算被限制的数，以及限制数的种类
        int category = 0;
        int hits = 0;
        for (int i = 0; i <= maxAlice; i++) {
            if (alice[i] > 0 && (i ^ k) <= maxBob && bob[i ^ k] > 0) {
                hits += alice[i];
                category++;
            }
        }

        // 胜负规则
        if (n <= m) {
            if (hits > 1) {
                System.out.println("Bob");
            } else {
                System.out.println("Alice");
            }
        } else {
            if (n - hits + 1 >= m) {
                System.out.println("Alice");
            } else {
                if (m - (n - hits) < category) {
                    System.out.println("Alice");
                } else {
                    System.out.println("Bob");
                }
            }
        }

    }

}