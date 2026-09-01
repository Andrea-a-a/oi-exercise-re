#include <iostream>

using namespace std;

int main() {
    int taskId;
    cin >> taskId;
    if (taskId == 1) {
        cout << "2 2 3" << endl;
    } else if (taskId == 2) {
        cout << "150001" << endl;
        cout << "miaomiao" << endl;
            for(int i = 0; i < 150000; i++){
            cout << "std::cerr" << endl;
        }
    }
    return 0;
}
