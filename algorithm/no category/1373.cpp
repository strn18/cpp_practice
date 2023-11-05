#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  deque<int> bin, oct;
  string temp;

  cin >> temp;

  for(auto ch: temp)
    bin.push_back(ch - '0');
  
  while(bin.size() % 3)
    bin.push_front(0);
  
  for(int i = bin.size()-1; i >= 2; i -= 3){
    int total = 0, mul = 1;

    for(int j = 0; j < 3; j++){
      total += bin[i-j] * mul;
      mul *= 2;
    }

    oct.push_front(total);
  }

  for(auto e: oct)
    cout << e;

  return 0;
}

/*
https://nanyoungkim.tistory.com/174 걍 이거대로 하는 게 더 편했을듯
*/