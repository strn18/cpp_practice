#include <iostream>
#include <cstdlib>
#define MAX 100000
#define INF 2000000001

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, val[MAX];

  cin >> N;
  for(int i=0; i<N; i++)
    cin >> val[i];

  int ans_val = INF, ans_s, ans_e;
  int s = 0, e = N-1;

  while(s<e){
    int sum = val[s]+val[e];
    if(abs(sum) < ans_val){
      ans_val = abs(sum);
      ans_s = s;
      ans_e = e;
    }

    if(sum == 0) break;
    else if(sum < 0) s++;
    else e--;
  }

  cout << val[ans_s] << ' ' << val[ans_e];

  return 0;
}

/*
2470과 거의 유사한 투 포인터 문제.
*/