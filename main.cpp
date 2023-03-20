#include <iostream>
#define ll long long

using namespace std;

int main(){
  ll N, count = 0;
  ll num[6], min_num[3];

  scanf("%d", &N);

  min_num[0] = 51;
  for(int i=0; i<6; i++){
    scanf("%lld", &num[i]);
    min_num[0] = min(min_num[0], num[i]);
  }
  
  if(N==1){
    ll max_num = 0;
    for(int i=0; i<6; i++){
      count += num[i];
      max_num = max(max_num, num[i]);
    }
    count -= max_num;
  }
  else{
    int a = min(num[0], num[5]);
    int b = min(num[1], num[4]);
    int c = min(num[2], num[3]);
    min_num[1] = min(min(a+b, a+c), b+c);
    min_num[2] = a+b+c;

    count += (min_num[0]*(N-2)*(N-2)*5);
    count += (min_num[1]*(N-2)*8 + min_num[0]*(N-2)*4);
    count += (min_num[2]*4 + min_num[1]*4);
  }

  printf("%lld", count);

  return 0;
}