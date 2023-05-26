#include <iostream>
#include <cmath>
#define MAX 100
#define INF 2100000000

using namespace std;

typedef struct{float x, y;} pos;

float key[MAX];
bool checked[MAX] = {false};

float dist(pos a, pos b);
int min_key_idx(int n);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  pos star[MAX];
  float cost = 0;

  cin >> n;

  for(int i=0; i<n; i++){
    cin >> star[i].x >> star[i].y;
    key[i] = dist(star[0], star[i]);
  }

  for(int i=0; i<n; i++){
    int idx = min_key_idx(n);

    cost += key[idx];
    checked[idx] = true;

    for(int j=0; j<n; j++){
      float distance = dist(star[idx], star[j]);

      if(!checked[j] && distance < key[j])
        key[j] = distance;
    }
  }

  cout << cost;

  return 0;
}

float dist(pos a, pos b){
  return sqrt(pow(a.x-b.x, 2)+pow(a.y-b.y, 2));
}

int min_key_idx(int n){
  int min_key = INF;
  int idx = -1;

  for(int i=0; i<n; i++){
    if(!checked[i] && key[i] < min_key){
      min_key = key[i];
      idx = i;
    }
  }

  return idx;
}

/*
프림 알고리즘으로 풀어 본 MST 문제. 원래 배운대로라면 PQ를 써야했겠지만 노드의 개수가 최대 100개밖에 되지 않아서 그냥 배열로 썼다.

지금까지 고른 노드들로부터 어떠한 노드 i까지의 최소 거리를 key[i]에 담는다. 이때, 32행에서 key값이 최소인(동시에 not checked인, 즉 아직 고르기
전인) 노드의 인덱스를 찾아 idx에 담고, 걔를 고른 다음 다시 key값을 37행에서 갱신해준다.
*/