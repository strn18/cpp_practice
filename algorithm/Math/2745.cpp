#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int charToInt(char ch);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string N;
  int B, total = 0;
  
  cin >> N >> B;

  for(int i=0; i<N.size(); i++)
    total += pow(B, i) * charToInt(N[N.size()-1 - i]);
  
  cout << total;

  return 0;
}

int charToInt(char ch){
  if(ch <= '9') return ch - '0';
  else return ch - 'A' + 10;
}