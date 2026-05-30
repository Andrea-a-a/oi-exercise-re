#include <iostream>
using namespace std;

bool isFire[100000];
int a[1];

int main(){

    //敌方有m个冰系n个火系
    int n, m;
    cin >> n >> m;
    

    //进行一个贪心
    //对于冰系进行一个*1.5, 对于火系进行一个*2, 排序，选择

    //理想的情况当然是全都攻击不同种类的，但是不能做到的话肯定会有一方多一方少，对于必须同类残杀的进行一个排序，挑选靠前的匹配不同类型的对手



}