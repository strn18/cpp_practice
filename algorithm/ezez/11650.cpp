#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

bool Compare(pair<int, int> a, pair<int, int> b);

int main(){
  int N, x, y;
  vector<pair<int, int>> points;

  cin >> N;

  for(int i=0; i<N; i++){
    scanf("%d %d", &x, &y);
    points.push_back({x, y});
  }

  sort(points.begin(), points.end(), Compare);

  for(int i=0; i<N; i++)
    printf("%d %d\n", points[i].first, points[i].second);

  return 0;
}

bool Compare(pair<int, int> a, pair<int, int> b){
  if(a.first != b.first) return a.first < b.first;
  else return a.second < b.second;
}