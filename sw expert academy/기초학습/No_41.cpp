// 3차원 농부(11. 이분탐색)
#include <iostream>
#include <algorithm>
#include <cstdlib>
#define MAX 500000
#define INF 2100000000

using namespace std;

int cow[MAX], horse[MAX];

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int N, M, c1, c2;

    cin >> N >> M;

    cin >> c1 >> c2;
    
    for(int i=0; i<N; i++)
      cin >> cow[i];
    for(int i=0; i<M; i++)
      cin >> horse[i];

    sort(cow, cow+N);
    sort(horse, horse+M);
    
    int c = 0, h = 0, min_dist = INF, min_count = -1;

    while(c<N && h<M){
      int dist = abs(cow[c] - horse[h]);
      
      if(dist < min_dist){
        min_dist = dist;
        min_count = 1;
      }
      else if(dist == min_dist)
        min_count++;

      if(cow[c] <= horse[h]) c++;
      else h++;
    }

    cout << '#' << t << ' ' << min_dist + abs(c1 - c2) << ' ' << min_count << '\n';
  }

  return 0;
}

/*
이진탐색으로 풀어보라는 문제였는데 걍 투포인터가 더 좋아보여서 그걸로 풀었다.

문제를 읽어보면 3차원이라 어려워보이지만, 실제로는 x좌표(소와 말은 각각 c1, c2)와 y좌표(0)는 고정되어있어서, 결국 1차원만을 다루게 되는 쉬운 문제. 

우선 소와 말들의 좌표(z좌표)를 담은 배열인 cow, horse를 오름차순으로 정렬한다. 그런 다음, 각각을 가리키는 인덱스인 c와 h를 투포인터로 전진시키면 
된다. 우선 cow[c]와 horse[h]의 거리(z좌표만을 다루는 거리, 즉 |cow[c] - horse[h]|)를 구해보고, 그것과 min_dist를 비교해본다. 만약 min_dist보다 
작으면 새로운 최솟값을 찾은 것(40행). 같다면 count만 증가(44행)시킨다. 그 후, cow[c]와 horse[h]의 값을 비교해보고, 전자가 작거나 같다면, cow의 
더 높은 좌푯값이 필요하므로 c++하여 포인터를 전진시킨다. 반대라면 h++을 해주면 된다.

이진탐색 풀이는 다음과 같았다.

우선 정렬까지는 똑같음. 그런 다음, cow를 돌면서(0 ~ N-1), 이진탐색을 통해 horse에서 나와 가장 가까운 놈을 찾는다. 그런 다음 나와 그놈의 거리를 
비교하고, 필요할 경우 최솟값을 갱신해준다(위의 방식과 같음). 
*/