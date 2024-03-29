import java.math.BigInteger;
import java.util.Scanner;

/**
 * @author xiaoyaosheny
 * @discription 洛谷P1018 [NOIP2000 提高组] 乘积最大
 * @date 2021/7/30
 */
public class Main {

    /**
     * 程序入口
     * @param args 输入参数
     */
    public static void main(String[] args) {
        // 获取输入
        Scanner scanner = new Scanner(System.in);
        int N = scanner.nextInt();
        int K = scanner.nextInt();
        String value = scanner.next();
        BigInteger[][] dp = new BigInteger[N][K + 1];
        for (int i = 0; i < N; i++) dp[i][0] = new BigInteger("1");
        for (int i = 0; i < K + 1; i++) dp[0][i] = new BigInteger("1");
        for (int i = 1; i < N; i++) {
            for (int j = 1; j < K + 1; j++) {
                BigInteger max = new BigInteger("0");
                for (int k = j - 1; k <= i - 1; k++) {
                    BigInteger number = new BigInteger(value.substring(k, i));
                    max = max.max(dp[k][j - 1].multiply(number));
                }
                dp[i][j] = max;
            }
        }
        BigInteger result = new BigInteger("0");
        for (int i = K; i <= N - 1; i++) {
            result = result.max(dp[i][K].multiply(new BigInteger(value.substring(i, N))));
        }
        // 输出结果
        System.out.println(result);
    }
}