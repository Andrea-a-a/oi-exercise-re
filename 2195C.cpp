#include <iostream>
#include <cstring>
using namespace std;

int t;
const int MAXN = 3e5+10;
int a[MAXN];

//b[o] 表示a[o-1]和a[o]的关系
bool b[MAXN];


bool isAdjacent(int, int);
void inni();

int main(){
    cin >> t;
    for(int i = 0; i < t; i++){
        //cout << "testcase : " << i+1 << endl;
        inni();
        int n;
        cin >> n;
        for(int o = 1; o <= n; o++){
            cin >> a[o];
            if(o > 1){
                b[o] = isAdjacent(a[o-1], a[o]);
                //cout << b[o] << " ";
            }
            
        }
        //cout << endl;
        int ans = 0;
        for(int o = 2; o <= n; o++){
            //int index = o;
            if(b[o] == 0){
                int p;
                for(p = o; p <= n; p++){
                    if(b[p]){
                        break;
                    }
                }
                
                //cout << "o: " << o << " p: " << p << endl;
                ans += (p - o + 1) / 2;
                o = p;

            }
        }
        cout << ans << endl;
        
        //cout << isAdjacent(3, 4);


    }






    return 0;
}


bool isAdjacent(int a, int b){
    if(a == b){
        return 0;
    }
    else{
        if(a > b){
            int temp = b;
            b = a;
            a = temp;
        }

        if(a == 1 && b == 6){
            return 0;
        }
        else if(a == 2 && b == 5){
            return 0;
        }
        else if(a == 3 && b == 4){
            return 0;
        }
        else{
            return 1;
        }
    }
}

void inni(){
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));

}