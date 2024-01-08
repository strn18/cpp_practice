#include <iostream>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, A, B, count = 1;

  cin >> N >> A >> B;

  if(A > B){
    int temp = A;
    A = B;
    B = temp;
  }

  while(!(A%2 == 1 && A+1 == B)){
    A = (A+1)/2;
    B = (B+1)/2;
    count++;
  }

  cout << count;

  return 0;
}