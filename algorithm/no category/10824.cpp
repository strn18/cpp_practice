#include <iostream>
#include <string>

using namespace std;

long long strToNum(string str);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string A, B, C, D;

  cin >> A >> B >> C >> D;

  cout << strToNum(A + B) + strToNum(C + D);

  return 0;
}

long long strToNum(string str){
  long long total = 0;

  for(int i=0; i<str.size(); i++){
    total *= 10;
    total += (str[i] - '0');
  }

  return total;
}