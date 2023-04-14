#include <iostream>
#define MAX 100000

using namespace std;

int rope[MAX], temp[MAX];

void merge_sort(int p, int r);
void now_merge(int p, int q, int r);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, ans = 0;

  cin >> N;
  for(int i=0; i<N; i++)
    cin >> rope[i];
  
  merge_sort(0, N-1);

  for(int i=0; i<N; i++)
    ans = max(ans, rope[i]*(N-i));

  cout << ans;

  return 0;
}

void merge_sort(int p, int r){
  if(p < r){
    int q = (p+r)/2;

    merge_sort(p, q);
    merge_sort(q+1, r);

    now_merge(p, q, r);
  }
}

void now_merge(int p, int q, int r){
  int i = p, j = q+1, idx = p;

  while(i<=q && j<=r){
    temp[idx++] = (rope[i] < rope[j] ? rope[i++] : rope[j++]);
  }

  while(i<=q){
    temp[idx++] = rope[i++];
  }
  while(j<=r){
    temp[idx++] = rope[j++];
  }

  for(int i=p; i<=r; i++)
    rope[i] = temp[i];
}