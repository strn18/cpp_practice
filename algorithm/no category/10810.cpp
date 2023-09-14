#include <iostream>
#define MAX 100

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, M;
  int basket[MAX+1] = {0};

  cin >> N >> M;

  while(M--){
    int i, j, k;

    cin >> i >> j >> k;

    for(int num = i; num <= j; num++)
      basket[num] = k;
  }

  for(int num = 1; num <= N; num++)
    cout << basket[num] << ' ';

  return 0;
}