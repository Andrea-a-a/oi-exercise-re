#include <bits/stdc++.h>
using namespace std;

bool solve(){
    vector<int> t(16, 0);
    vector<bool>    b(16, false);
    
    
    
    for(int i = 0; i < 33; i++){
        char tmp;
        cin >> tmp;
        if(tmp == 'T')  t[8]++;
        else if(tmp == 'J') t[9]++;
        else if(tmp == 'Q') t[10]++;
        else if(tmp == 'K') t[11]++;
        else if(tmp == 'A') t[12]++;
        else if(tmp == '2') t[13]++;
        else if(tmp == 'w') t[14]++;
        else if(tmp == 'W') t[15]++;
        else{
            t[tmp-'0'-2]++;
        }
        //cout << tmp;
    }

    // for(int i = 1; i <= 15; i++){
    //     cout << "t[" << i << "] = " << t[i] << endl;
    // }

    //枚举农民的最大炸弹
    int farmer = 0;

    if(t[14] == 0 && t[15] == 0){
        farmer = 14;
    }
    else{
        for(int i = 13; i >= 1; i--){
            if(t[i] <= 4){
                farmer = i;
                break;
            }
        }
    }

    cout << "farmer max " << farmer << endl;

    for(int i = 14; i >= farmer; i--){
        //判断
        int cntelse = 0;
        vector<int> index[16];
        vector<int> m(10, 0);
        for(int i = 1; i <= 15; i++){
            if(!b[i]){
                if(t[i] != 0){
                    m[t[i]]++; 
                    index[t[i]].push_back(i);
                    cntelse++;}
            }
        }

        if(m[1] != 0){
            if(m[1] == 1)   {
                ///单张
                if(cntelse == 1)    return true;
                
            }
            else{

                if(cntelse == m[2]){
                    ///顺子
                    int l = 16, r = 0;
                    for(auto i : index[1]){
                        l = min(i, l);
                        r = max(r, i);
                    }

                    bool lianxu = 1;
                    for(int i = l; i <= r; i++){
                        if(t[i] != 1)   lianxu = false;
                    }

                    if(lianxu){
                        //扩展！
                        for(; l >= 1; l--){
                            if((!b[l] && t[l] == 1) || (l <= 13 && b[l] && t[l] - 4 >= 1) || (l >= 14 && t[l] == 1)) continue;
                            else    break;
                        }
                        for(; r <= 15; r++){
                            if((!b[l] && t[l] == 1) || (l <= 13 && b[l] && t[l] - 4 >= 1) || (l >= 14 && t[l] == 1)) continue;
                            else    break;
                        }
                        if(r-l >= 4)    return true;
                    }
                    
                }
            }
        }

        if(m[2] != 0){
            if(m[2] == 1){
                ///对子
                if(cntelse == 1)    return true;
                ///三带二
                else if(cntelse == 2 && m[3] == 1)  return true;
                else if(cntelse == m[2]){
                    //连对
                    int l = 16, r = 0;
                    for(auto i : index[2]){
                        l = min(i, l);
                        r = max(r, i);
                    }
                    //判断[r,l]
                    bool lianxu = 1;
                    for(int i = l; i <= r; i++){
                        if(t[i] != 2)   lianxu = false;
                    }

                    if(lianxu){
                        //扩展！
                        for(; l >= 1; l--){
                            if((!b[l] && t[l] == 2) || (l <= 13 && b[l] && t[l] - 4 >= 2) || (l >= 14 && t[l] == 2)) continue;
                            else    break;
                        }
                        for(; r <= 15; r++){
                            if((!b[l] && t[l] == 1) || (l <= 13 && b[l] && t[l] - 4 >= 1) || (l >= 14 && t[l] == 2)) continue;
                            else    break;
                        }
                        if(r-l >= 4)    return true;
                    }
                }
            }
        }

        if(m[3] != 0 && cntelse == m[3]){
            ///三张
            if(m[3] == 1)   return true;
            else{
                ///钢板
                int l = 16, r = 0;
                for(auto i : index[3]){
                    l = min(i, l);
                    r = max(r, i);
                }
                //判断[r,l]
                for(int i = l; i <= r; i++){
                    if(t[i] != 1)   return false;
                }

                //扩展！
                for(; r <= 13; r++){
                    if((!b[r] && t[r] == 3) || (b[r] && t[r] - 4 >= 3)) continue;
                    else    break;
                }

                if(r-l >= 1)    return true;
                else    return false;
            }
        }
        
        //飞机！
        int l = 16, r = 0, cnt2 = 0;
        for(int i = 1; i <= 13; i++){
            if(b[i])    break;
            if(t[i] % 2 == 0)   cnt2 += t[i]/2;
            else if(t[i] % 2 == 1)  l = min(l, i), r = max(r, i), cnt2+= (t[i]-3)/2;
        }

        for(int i = l; i <= r; i++){
            if(t[i] % 2 != 1)   return false;
        }

        if(r-l+1 == cnt2)   return true;
        else if(r-l+1 > cnt2){
            //需要借2
            int cnt2b = 0;
            int i = 13;
            while(b[i]){
                i--;
                cnt2b += (t[i]-4)/2;
            }
            if(r-l+1 <= cnt2+cnt2b){
                return true;
            }
            else{
                //还是不够！
            }
        }


        if(i == 14 && t[14] == 2 && t[15] == 2){
            b[14] = 0;
            b[15] = 0;
        }
        else if(t[i] >= 4){
            b[i] = 0;
        }
    }
    
    


}

int main(){
    int t;
    cin >> t;
    while(t--){
        solve() ? cout << "YES" << endl : cout << "NO" << endl;
    }
}