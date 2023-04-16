#include <iostream>
#include <algorithm>
#define MAX 2000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, count = 0;
  int num[MAX];

  cin >> N;
  for(int i=0; i<N; i++)
    cin >> num[i];

  sort(num, num+N);

  for(int i=0; i<N; i++){
    int s = (i==0 ? 1 : 0), e = (i==N-1 ? N-2 : N-1);

    while(s < e){
      int sum = num[s] + num[e];

      if(sum == num[i]){
        count++;
        break;
      }
      else if(sum < num[i]){
        if(++s == i) s++;
      }
      else{
        if(--e == i) e--;
      }
    }
  }

  cout << count;

  return 0;
}