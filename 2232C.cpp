//反悔贪心
#include <iostream>

int t;

int main() {
    
    std::cin >> t;
    while(t--) {
        int n, x, s;
        std::cin >> n >> x >> s;
        char c;
        long long aAse{}, cntT{}, cntSfE{}, ans{};

        while(n--) {
            std::cin >> c;
            if(c == 'I') {
                if(cntT < x) {
                    cntT++;
                    ans++;
                    cntSfE += s - 1;
                }
            }
            else if(c == 'E') {
                if(cntSfE > 0) {
                    ans++;
                    cntSfE--;
                }
                else if(cntT < x && aAse > 0){
                    ans++;
                    cntSfE += s - 1;
                    cntT++;
                    aAse--;
                }
            }
            else if(c == 'A') {
                if(cntSfE > 0) {
                    ans++;
                    cntSfE--;
                    aAse++;
                }
                else if(cntT < x) {
                    cntT++;
                    ans++;
                    cntSfE += s - 1;
                }
            }
            
        }

        std::cout << ans << std::endl;


    }



    return 0;
}