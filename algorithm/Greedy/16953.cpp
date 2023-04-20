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

/*
A에서 어떻게 B를 만들지가 아니라, 반대로 B에서 A를 만들어나간다고 생각하면 쉬운 문제.
B의 1의자리 수가 1이면 그걸 떼주면 되고, 아니라면 반띵을 해준다. 이때, 1의자리 수가 1이 아닌 홀수이거나, B가 A보다 작아졌다면 count 값은
-1이고, B가 A와 같아졌다면 break하고 count 값을 출력.
*/