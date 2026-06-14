#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

const int MAXN = 2e5+10;

using namespace std;
int t, a[MAXN*2], n;

//pos[i][0]: i第一次出现的位置；pos[i][1]: i第二次出现的位置
int pos[MAXN][2];

int b[MAXN*2];

//判断[l, r]是不是回文串
bool isPal(int l, int r){
    int lenS2 = (r-l+1)/2;
    for(int i = 0; i < lenS2; i++){
        if(a[l+i] != a[r-i]){
            return false;
        }

    }
    return true;

}


int findMex(int l, int r){
    int len = r - l + 1;

    for(int i = 0; i < len; i++){
        b[i] = a[l+i];
        //cout << i << " " << b[i] <<endl;
    }
    sort(b, b+len);

    

    int mex = 0, index = 0;

    //cout << b[1] << endl;
    while(mex == b[index] && index < len){
        if(b[index+1] == b[index])  index++;
        index++;
        mex++;
        //cout << b[mex] << endl;
    }
    return mex;








}

//扩展作为[l, r]的回文串，返回最大回文串的左边的坐标
int leftIndex(int l, int r){
    int index = 1;
    while(l-index >= 0 && r + index <= 2 * n - 1){
        //cout << "Meow" << index << endl;
        if(a[l-index] != a[r+index]){
            return l-index+1;
            
        }
        index++;
    }
    return l-index+1;
}


int main(){

    cin >> t;
    while(t--){
        memset(pos, -1, sizeof(pos));
        memset(a, 0, sizeof(a));

        //int n;
        cin >> n;
        for(int i = 0; i < 2*n; i++){
            cin >> a[i];

            if(pos[a[i]][0] == -1)   pos[a[i]][0] = i;
            else    pos[a[i]][1] = i;
        }

        // int tmp;
        // cin >> tmp;
        // while(tmp--){
        //     int x, y;
        //     cin >> x >> y;
        //     cout << findMex(x, y) << endl;
        // }

        int mex = 0;
        if(isPal(pos[0][0], pos[0][1])){
            int lindex = leftIndex(pos[0][0], pos[0][1]);
            int midindex = (pos[0][0] + pos[0][1])/2;
            //在[lindex, midindex]里求mex
            
            mex = max(mex, findMex(lindex, midindex));
        }
        else{

            int lindex1 = leftIndex(pos[0][0], pos[0][0]);
            //在[lindex1, pos[0][1]]里求mex
            mex = max(mex, findMex(lindex1, pos[0][0]));

            int lindex2 = leftIndex(pos[0][1], pos[0][1]);
            mex = max(mex, findMex(lindex2, pos[0][1]));






        }

        cout << mex << endl;

        //枚举？
        //对于每一个回文中心点，找到对应的回文串的最大长度，求mex

        //还是说，从0开始找，包括0的最大回文串，如果包括1就更好了……

        //tips：对于回文串，找mex的过程只需要看一边就可以

        //


    }





    return 0;
}