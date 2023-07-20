#include <iostream>
#include <string>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string num;

  cin >> num;

  while(num != "0"){
    bool is_palin = true;

    for(int i=0; i<num.size()/2; i++){
      if(num[i] != num[num.size()-1-i]){
        is_palin = false;
        break;
      }
    }

    cout << (is_palin ? "yes" : "no") << '\n';

    cin >> num;
  }

  return 0;
}