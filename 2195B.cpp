#include <iostream>
#include <cstring>

using namespace std;

int t;
const int MAXN = 2e5+10;
int a[MAXN];
bool b[MAXN];

void inni();


int main(){
    cin >> t;
    for(int i = 0; i < t; i++){
        inni();

        int n;
        cin >> n;
        int half = n/2;

        bool halfOdd = 1;
        for(int o = 1; o <= n; o++){
            cin >> a[o];
            if(o > half && o % 2 == 1){
                if(a[o] != o){
                    halfOdd = 0;
                }
            }
        }
        if(!halfOdd){
            cout << "NO" << endl;
        }
        else{
            bool isAns = 1;
            //对于每个小于等于half的奇数下标o，判定下标p一直*2直到小于等于n的a的集合是不是下标的集合
            for(int o = 1; o <= half; o += 2){
                memset(b, 0, sizeof(b));
                for(int p = o; p <= n; p*= 2){
                    b[a[p]] = 1;
                }
                bool isOK = 1;
                for(int p = o; p <= n; p*= 2){
                    if(!b[p]){
                        isOK = 0;
                    }
                }
                if(!isOK){
                    cout << "NO" << endl;
                    isAns = 0;
                    break;
                }

            }
            if(isAns){
                cout << "YES" << endl;
            }
        }


    }


}


void inni(){
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));


}