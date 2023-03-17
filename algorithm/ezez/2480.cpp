#include <iostream>

using namespace std;

int main(){
    int num[3], num_count[7] = {0};
    int maximum = 0, ans = 0;
    
    for(int i=0; i<3; i++){
        cin >> num[i];
        num_count[num[i]]++;
    }
    
    for(int i=1; i<=6; i++){
        if(num_count[i] == 3){
            ans = 10000+(i*1000);
            break;
        }
        else if(num_count[i] == 2){
            ans = 1000+(i*100);
            break;
        }
        else if(num_count[i] == 1)
            maximum = i;
    }
    
    printf("%d", (ans == 0 ? 100*maximum : ans));
    
    return 0;
}