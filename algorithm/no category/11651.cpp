#include <iostream>
#include <algorithm>
#define MAX 100000

using namespace std;

pair<int, int> p[MAX];

bool compare(pair<int, int> a, pair<int, int> b){
  if(a.second != b.second) return a.second < b.second;
  else return a.first < b.first;
}

int main(){
  int N, a, b;

  scanf("%d", &N);

  for(int i=0; i<N; i++){
    scanf("%d %d", &a, &b);
    p[i].first = a;
    p[i].second = b;
  }

  sort(p, p+N, compare);

  for(int i=0; i<N; i++)
    printf("%d %d\n", p[i].first, p[i].second);

  return 0;
}