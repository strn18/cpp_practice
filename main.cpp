#include <iostream>
#include <algorithm>
#define MAX 10

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  int left[MAX+1], pos[MAX+1], result[MAX+1];

  cin >> N;

  for(int i=1; i<=N; i++)
    cin >> left[i];
  
  for(int i=1; i<=N; i++){
    pos[i] = left[i];

    sort(pos+1, pos+i);

    for(int j=1; j<i; j++){
      if(pos[j] <= pos[i]) pos[i]++;
      else break;
    }

    result[pos[i]] = i;
  }

  for(int i=0; i<N; i++)
    cout << result[i] << ' ';

  return 0;
}