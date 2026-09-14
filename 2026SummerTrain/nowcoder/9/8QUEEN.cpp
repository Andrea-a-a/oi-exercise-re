#include <iostream>
using namespace std;

int N;
int arr[100], total_cnt;
// arr记录每一行(X)皇后的Y坐标
char ar[100][100];

bool isPlaceOK(int *a, int n, int c) {
    for (int i = 1; i <= n - 1; ++i) {
        if (a[i] == c)
            return false;
        //检查位置是否可以放
        //c是将要放置的位置
        //a[i] == c如果放在同一列，false
        //a[i] -+ i = c -+ n 如果在对角线上，false
    }
    return true;
}

int checkSol() {
    int ans = -1;
    //int index = 0;
    int curcnt = 1;
    while(curcnt > 0){
        curcnt = 0;
        for (int i = 1; i <= N; i++){
            for(int j = 1; j <= N; j++){
                int cnt = 0;
                if(ar[i][j] != 'X' && ar[i][j] != 'o') {
                    if(ar[i-1][j] == 'X' || ar[i-1][j] == 'o')   cnt++;
                if(ar[i+1][j] == 'X'|| ar[i+1][j] == 'o')   cnt++;
                if(ar[i][j-1] == 'X'|| ar[i][j-1] == 'o')   cnt++;
                if(ar[i][j+1] == 'X'|| ar[i][j+1] == 'o')   cnt++;
                if(cnt >= 2)    {ar[i][j] = 'o'; curcnt++;}
                }
            }
        }
        if(curcnt>0) ans++;
    }
    cout << ans<< endl;

    return ans;

}

void printSol(int *a) {
    for(int k = 0; k <= N+1; k++){
        ar[0][k] = '=';
        ar[N+1][k] = '=';
        ar[k][0] = '=';
        ar[k][N+1] = '=';
    }
    for (int i = 1; i <= N; ++i) { //遍历每一行
        for (int j = 1; j <= N; ++j) { //遍历每一列
            a[i] == j ? ar[i][j] = 'X' : ar[i][j] = '-';
            
        } 
    }
    

   checkSol();
            for (int i = 1; i <= N; ++i) { //遍历每一行
        for (int j = 1; j <= N; ++j) { //遍历每一列
            //a[i] == j ? ar[i][j] = 'X' : ar[i][j] = '-';
            
            cout << ar[i][j]<< " ";;
        } //如果标记数组中这一行的皇后放在j位置，则输出X，否则输出-，
        //用空格分隔
        cout << endl; //每一行输出一个换行
    }
    //cout << "ans = " << checkSol();
    cout << endl; //每一组数据一个换行分隔
    //}
}


void addQueen(int *a, int n) {
    if (n > N) { //n代表从第一行开始放置
        printSol(a);
        total_cnt++;
        return ;
    }
    for (int i = 1; i <= N; ++i) { //i从第1列到第N列遍历
        if (isPlaceOK(a, n, i)) {
            a[n] = i; //如果可以放置，就把皇后放在第n行第i列
            addQueen(a, n + 1);
        }
    }

}

int main() {

    
    cin >> N;
    addQueen(arr, 1);
    cout << "total: " << total_cnt << " solutions.\n";
    return 0;
}