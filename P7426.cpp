#include <bits/stdc++.h>
using namespace std;
#define zbyb(x, y, name)   ( (x <= name) && (y >= name) )
#define zbyk(x, y, name)   ( (x <= name) && (y > name) )

const int MAXN = 1e5+10;
int n, m;
char gender[MAXN];
int freshmanTrainTime[MAXN];
int finalScore[MAXN];

const int month[13] = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//用于存储学生的学号和序号，序号从1开始，学号,序号。
unordered_map<long long, int> number;
//also存储学号
long long number2[MAXN];

//校园跑记录
//日期在前
vector<pair<long long, long long>> xyp[MAXN];

//函数喵
void durum(void);
long long dateStoL(string date);
long long timeStoL(string t);
bool compareDate(int y, int m, int d, long long time1, long long date2, long long time2);

void calc(int index);
void shuchu(int index);

//读入长跑时间（秒数）和性别（M/F），返回长跑的分数（百分制）
int calcChangpao(int sec, char gen){
    if(gen == 'M'){
        if(sec > 18 * 60)                                   return 0;
        else if(17 * 60 + 10 < sec && sec <= 18 * 60     )  return 2;
        else if(16 * 60 + 30 < sec && sec <= 17 * 60 + 10)  return 4;
        else if(15 * 60 + 50 < sec && sec <= 16 * 60 + 30)  return 6;
        else if(15 * 60 + 10 < sec && sec <= 15 * 60 + 50)  return 8;
        else if(14 * 60 + 30 < sec && sec <= 15 * 60 + 10)  return 10;
        else if(14 * 60      < sec && sec <= 14 * 60 + 30)  return 12;
        else if(13 * 60 + 30 < sec && sec <= 14 * 60     )  return 14;
        else if(13 * 60      < sec && sec <= 13 * 60 + 30)  return 16;
        else if(12 * 60 + 30 < sec && sec <= 13 * 60     )  return 18;
        else if(sec <= 12 * 60 + 30)  return 20;
    }
    if(gen == 'F'){
        if(sec > 9 * 60)                                    return 0;
        else if(8 * 60 + 50 < sec && sec <= 9 * 60     )    return 2;
        else if(8 * 60 + 35 < sec && sec <= 8 * 60 + 50)    return 4;
        else if(8 * 60 + 20 < sec && sec <= 8 * 60 + 35)    return 6;
        else if(8 * 60 + 5  < sec && sec <= 8 * 60 + 20)    return 8;
        else if(7 * 60 + 50 < sec && sec <= 8 * 60 + 5)     return 10;
        else if(7 * 60 + 31 < sec && sec <= 7 * 60 + 50)    return 12;
        else if(7 * 60 + 14 < sec && sec <= 7 * 60 + 31)    return 14;
        else if(6 * 60 + 57 < sec && sec <= 7 * 60 + 14)    return 16;
        else if(6 * 60 + 40 < sec && sec <= 6 * 60 + 57)    return 18;
        else if(sec <= 6 * 60 + 40)  return 20;
    }

    return 0;

    
}



//读入前半部分中每行的值
void durun(int index){
    finalScore[index] = 0;
    //输入学号、性别、体育课专项成绩
    long long xuehao;
    cin >> xuehao;

    number.insert(pair(xuehao, index));
    number2[index] = xuehao;

    int temp;
    cin >> gender[index] >> temp;
    finalScore[index] += temp;

    //输入长跑时间并计算成绩
    int min, sec;
    scanf("%d'%d\"", &min, &sec);
    int changpaoSec = min * 60 + sec;
    finalScore[index] += calcChangpao(changpaoSec, gender[index]);

    //输入体测是否通过
    char tice;
    cin >> tice;
    if(tice == 'P')     finalScore[index] += 10;

    //输入「大一专项计划」的期末检测成绩
    cin >> temp;
    finalScore[index] += temp;

    //输入参加「班级训练营」的次数
    cin >> freshmanTrainTime[index];
}


int main(){
    cin >> n;
    for(int i = 1; i <= n; i++){
        durun(i);
    }

    cin >> m;
    for(int i = 1; i <= m; i++){
        durum();
    }

    for(int i = 1; i <= n; i++){
        //cout << finalScore[i] << endl;


        calc(i);
        shuchu(i);
    }


    return 0;
}

//读入下半部分中的每一行
void durum(void){
    //输入并进行整理

    long long datelong;
    cin >> datelong;

    long long xuehao;
    cin >> xuehao;
    int index = number[xuehao];

    int hh, mm, ss;
    scanf("%d:%d:%d", &hh, &mm, &ss);
    if(hh == 24)    hh = 0;
    long long time_start = hh * 3600 + mm * 60 + ss;
    scanf("%d:%d:%d", &hh, &mm, &ss);
    if(hh == 24)    hh = 0;
    long long time_end = hh * 3600 + mm * 60 + ss;

    double distance;
    cin >> distance;
    distance *= 1000; //distance的单位是米

    int min, sec;
    scanf("%d'%d\"", &min, &sec);
    int time_pause = min * 60 + sec;

    int step;
    cin >> step;


    //判断
    if(gender[index] == 'M'){
        if(distance < 3000) return;
    }
    else if(gender[index] == 'F'){
        if(distance < 1500) return;
    }

    long long duration = time_end - time_start;
    if(duration < 0)    duration += 86400;
    double speed = distance / duration;
    if(speed < 2.0 || speed > 5.0)  return;

    if(time_pause > 270)    return;

    double bufu = distance / step;
    if(bufu > 1.5)  return;

    int siz = xyp[index].size();
    if(siz == 0)  xyp[index].push_back(pair(datelong, time_end));
    else{
        long long lastdate = xyp[index][siz-1].first;
        long long lasttime = xyp[index][siz-1].second;
        int lastyear = lastdate / 10000;
        int lastmonth = (lastdate / 100) % 100;
        int lastday = lastdate % 100;

        //上一次的时间+6h=21600s
        lasttime += 21600;
        if(lasttime >= 86400){
            lasttime %= 86400;
            lastday += 1;
            if(lastday > month[lastmonth]){
                lastday = 1;
                lastmonth++;
                if(lastmonth > 12){
                    lastmonth = 1;
                    lastyear++;
                }
                
            }
        }

        //比较时间
        if(compareDate(lastyear, lastmonth, lastday, lasttime, datelong, time_start)){
            xyp[index].push_back(pair(datelong, time_end));
        }
    }
}

// //输入字符串time（形如hh:mm:ss），返回longlong（一天中的第几秒）
// long long timeStoL(string t){
//     long long ans = ((t[0] - '0')*10+(t[1] - '0'))*3600
//                     + ((t[3] - '0')*10 + (t[4] - '0'))*60
//                     + (t[6]-'0')*10 + (t[7] - '0');

//     return ans;


// }

//比较时间，如果前面的比后面的小就返回1
bool compareDate(int y, int m, int d, long long time1, long long date2, long long time2){
        long long date1 = y * 10000 + m * 100 + d;
        if(date1 < date2){
            return true;
        }
        else if(date1 == date2){
            if(time1 <= time2){
                return true;
            }
        }

        return false;
}

//计算index同学的分数
void calc(int index){
   // int score = 0.5 * zhuanxiangScore[index] + 0.2 * changpaoScore[index] + 0.1 * ticeScore[index] + 0.05 * freshmanFinalScore[index];

    int xypscore; //10分制
    int xypTime = xyp[index].size();

    if(xypTime >= 21)       xypscore = 10;
    else if(xypTime < 3)    xypscore = 0;
    else if(xypTime <= 6 && xypTime >= 3)   xypscore = 2;
    else if(xypTime <= 10 && xypTime >= 7)   xypscore = 4;
    else if(xypTime <= 13 && xypTime >= 11)   xypscore = 6;
    else if(xypTime <= 16 && xypTime >= 14)   xypscore = 7;
    else if(xypTime <= 18 && xypTime >= 17)   xypscore = 8;
    else if(xypTime <= 20 && xypTime >= 19)   xypscore = 9;

    finalScore[index] += xypscore;

    int trainChuqinScore = 0; // 5分
    int trainTime = xypTime + freshmanTrainTime[index];
    if(zbyb(6, 8, trainTime))   trainChuqinScore = 1;
    else if(zbyb(9, 11, trainTime))   trainChuqinScore = 2;
    else if(zbyb(12, 14, trainTime))   trainChuqinScore = 3;
    else if(zbyb(15, 17, trainTime))   trainChuqinScore = 4;
    else if(trainTime >= 18)    trainChuqinScore = 5;

    finalScore[index] += trainChuqinScore;

}

void shuchu(int index){
    cout << number2[index] << " " << finalScore[index] << " ";
    if(zbyb(95, 100, finalScore[index]))    cout << "A";
    else if(zbyk(90, 95, finalScore[index]))    cout << "A-";
    else if(zbyk(85, 90, finalScore[index]))    cout << "B+";
    else if(zbyk(80, 85, finalScore[index]))    cout << "B";
    else if(zbyk(77, 80, finalScore[index]))    cout << "B-";
    else if(zbyk(73, 77, finalScore[index]))    cout << "C+";
    else if(zbyk(70, 73, finalScore[index]))    cout << "C";
    else if(zbyk(67, 70, finalScore[index]))    cout << "C-";
    else if(zbyk(63, 67, finalScore[index]))    cout << "D+";
    else if(zbyk(60, 63, finalScore[index]))    cout << "D";
    else if(zbyk(0, 60, finalScore[index]))    cout << "F";

    cout << endl;
    
}