#include <stdio.h>

int main() {
    // 变量 n 代表数值范围 1~n
    // 变量 m 代表质数的个数
    long long n;
    int m;
    scanf("%lld %d", &n, &m);

    // 数组 primes 用来存储 m 个质数
    int primes[15];
    for (int i = 0; i < m; i++) {
        scanf("%d", &primes[i]);
    }

    // 变量 result 用于存储最终结果
    long long result = 0;

    /********** Begin **********/
    // 在此区域编写核心代码
    // 1. 遍历 m 个质数的所有非空子集
    // 2. 对于每一个子集：
    //    a. 计算子集中所有质数的乘积
    //    b. 根据子集中元素的个数（奇数或偶数）
    //    c. 对 n / 乘积 的结果进行加或减运算，累加到 result 中

    for(int k = 1; k <= m; k++){
        int p[25];
        for (int i = 0; i < k; i++) {
            p[i] = i;
        }
        
       

        while (1) {
            // 2. 按照题目要求格式输出当前组合
            long long sum = 1;

            //printf("{");
            for (int i = 0; i < k; i++) {
                //printf("%d", primes[p[i]]);
                sum*=primes[p[i]];
                // if (i < k - 1) {
                //     printf(",");
                // }
            }
            //printf("}%d\n", sum);

            if(k % 2 == 1){
                result += n/sum;
            }
            else{
                result -= n/sum;
            }
            
            // 3. 寻找下一个字典序的组合
            int j = k - 1;
            while (j >= 0 && p[j] == m - k + j) {
                j--;
            }
            
            if (j < 0) {
                break;
            }
            
            p[j]++;
            
            for (int u = j + 1; u < k; u++) {
                p[u] = p[u - 1] + 1;
            }
        }


    }



    /********** End **********/

    // 输出最终结果
    printf("%lld\n", result);

    return 0;
}
