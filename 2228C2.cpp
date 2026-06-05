//似乎是dfs？
#include <iostream>
#include <algorithm>

using namespace std;

int t, n, len;
string a;
char d[10];
bool isIn[10];
string larger, smaller;

long long returningl(int index){
    //当前需要对index位（1based）进行回退操作
    
    if(index == 0){
        if(d[0] == '0' && n > 1){
            larger = d[1];
        }
        else{
            larger = d[0];
        }
        for(int i = 1; i <= len; i++){
            larger += d[0];
        }
        return 1;
    }

    //index位应该在d中
    if(a[index-1] == d[n-1]){
        return returningl(index - 1);
    }
    else if(a[index-1] < d[n-1]){
        larger = larger.substr(0, index-1);
        //cout << "subl: " << larger << endl;
        larger += *upper_bound(d, d + n, a[index - 1]);
        for(int i = index; i <= len - 1; i++){
            larger += d[0];
        }
        return 1;
    }

    return -1;

}

//index从1开始，-1说明找不到这样的值
long long solvel(int index){
    //cout << "current index = " << index << endl;
    
    if(n == 1 && d[0] == '0'){
        if(a == "0"){
            larger = "0";
            return 1;
        }
        else{
            return -1;
        }
    }

    if(index == len + 1){
        return 1;
    }

    if(isIn[a[index-1] - '0']){

        
        larger += a[index-1];
        index++;
        //cout << "meow " << larger << endl;
        return solvel(index);
    }
    else if(a[index-1] < d[n-1]){
        
        larger += *upper_bound(d, d + n, a[index - 1]);
        for(int i = index; i <= len - 1; i++){
            larger += d[0];
        }
        return 1;
    }
    else{
        //cout << "rolling back at " << index-1 << ", digit is " << a[index-2] << endl;
        return returningl(index-1);
    }
}

long long returnings(int index){
    //当前需要对index位（1based）进行回退操作
    
    if(index == 0){
        smaller = "";
        if(len == 1){
            return -1;
        }
        for(int i = 1; i <= len - 1; i++){
            smaller += d[n-1];
        }
        return 1;
    }

    

    //index位应该在d中
    if(a[index-1] == d[0]){
        return returnings(index - 1);
    }
    else if(a[index-1] > d[0]){
        smaller = smaller.substr(0, index-1);
        //cout << "subl: " << larger << endl;
        smaller += *(lower_bound(d, d + n, a[index - 1])-1);
        for(int i = index; i <= len - 1; i++){
            smaller += d[n-1];
        }
        return 1;
    }

    return -1;

}

//index从1开始，-1说明找不到这样的值
long long solves(int index){
    //cout << "current index = " << index << endl;

    if(index == len + 1){
        return 1;
    }

    if(isIn[a[index-1] - '0']){

        
        smaller += a[index-1];
        index++;
        //cout << "meow " << smaller << endl;
        return solves(index);
    }
    else if(a[index-1] > d[0]){
        
        smaller += *(lower_bound(d, d + n, a[index - 1]) - 1);
        for(int i = index; i <= len - 1; i++){
            smaller += d[n-1];
        }
        return 1;
    }
    else{
        //cout << "rolling back at " << index-1 << ", digit is " << a[index-2] << endl;
        return returnings(index-1);
    }
}



int main() {

    cin >> t;
    while(t--) {



        //cout << t << endl;
        for(int i = 0; i < 10; i++){
            isIn[i] = 0;
        }


        cin >> a >> n;
        len = a.length();

        for(int i = 0; i < n; i++){
            cin >> d[i];
            isIn[d[i] - '0'] = 1;
        }

        // if(t == 8976){
        //     cout << a<<n<<d[0]<<endl;
        // }

        long long ans = 1e18;
        larger = "";
        if(solvel(1) != -1){
            //cout << "larger = " << larger;
            ans = abs(stoll(a)-stoll(larger));
            if(ans == 0){
                cout << "0" << endl;
                continue;
            }
        }

        smaller = "";

        if(solves(1) != -1){
            //cout << "smaller = " << smaller;
            ans = min(ans, abs(stoll(a)-stoll(smaller)));
        }
        
        cout << ans << endl;

    }
    return 0;
}