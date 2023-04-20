#include <iostream>
using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int A, B, count = 1;

  cin >> A >> B;

  while(true){
    if(A == B) break;
    if(A > B){
      count = -1;
      break;
    }

    if(B%10 == 1)
      B/=10;
    else if(B%2 == 1){
      count = -1;
      break;
    }
    else
      B/=2;
    
    count++;
  }

  cout << count;

  return 0;
}