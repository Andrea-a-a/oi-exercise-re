#include <bits/stdc++.h>
using namespace std;

int main() {

    string name[10];
    int score[10];
    int indexround2[10];
    int indexround3[10];
    for (int i = 1; i <= 8; i++) {
        cin >> name[i] >> score[i];
    }
    for (int i = 1; i <= 4; i++) {
        if (score[2 * i - 1] > score[2 * i]) {
            indexround2[i] = 2 * i - 1;

        } else {
            indexround2[i] = 2 * i;
        }
    }
    // for (int i = 1; i <= 4; i++) {
    //     cout << indexround2[i] << " ";
    // }
    for (int i = 1; i <= 2; i++) {
        if (score[indexround2[2 * i - 1]] > score[indexround2[2 * i]]) {
            indexround3[i] = indexround2[2 * i - 1];
            //  cout << 2*i-1 << endl;
        } else {
            //  cout << 2*i << endl;
            indexround3[i] = indexround2[2 * i];
        }
    }
    if (score[indexround3[1]] > score[indexround3[2]]) {
        cout << name[indexround3[1]] << " beats " << name[indexround3[2]];
    } else {
        cout << name[indexround3[2]] << " beats " << name[indexround3[1]];
    }
}