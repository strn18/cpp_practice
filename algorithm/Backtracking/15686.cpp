#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

typedef struct{int r, c; bool closed;}pos;
vector<pos> chicken, house;

int N, M, close_n, min_dist = 9999; // 닫을 치킨집의 개수, 도시의 치킨 거리의 최솟값
int city[50][50];

void make_close(int start, int n); // 치킨집을 총 close_n개 폐업시킨다. 이번엔 chicken의 start 인덱스부터 폐업시키며, 이번이 n번째 폐업이다.
void find_dist(void); // 모든 집을 돌면서, 각 집의 치킨 거리를 구하고 도시의 치킨 거리를 구해서 min_dist를 갱신한다.

int main(){
  scanf("%d %d", &N, &M);
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      scanf("%d", &city[i][j]);      
      if(city[i][j] == 2)
        chicken.push_back({i, j, false});
      else if(city[i][j] == 1)
        house.push_back({i, j, false});
    }
  }
  close_n = chicken.size()-M;
  
  if(close_n==0)
    find_dist();
  else
    make_close(0, 1);

  printf("%d", min_dist);

  return 0;
}

void make_close(int start, int n){
  for(int i=start; i<chicken.size(); i++){
    chicken[i].closed = true; // 치킨집을 닫고

    if(n!=close_n) // 아직 닫을 치킨집이 남았으면 닫는다.
      make_close(i+1, n+1);
    else // close_n개를 모두 닫았으면 도시의 치킨 거리 계산
      find_dist();  

    chicken[i].closed = false; // 다시 연다
  }
}

void find_dist(void){
  int dist_count = 0;

  for(int i=0; i<house.size(); i++){
    int temp = 9999;
    for(int j=0; j<chicken.size(); j++)
      if(!chicken[j].closed)
        temp = min(temp, abs(house[i].r-chicken[j].r)+abs(house[i].c-chicken[j].c));
    dist_count += temp; // 각 집의 치킨 거리를 더해준다.
  }
  min_dist = min(min_dist, dist_count);
}

/*
크게 어렵진 않았던 백트래킹 문제. 나는 close_n개를 폐업시킨 후, 모든 집을 돌며 각 집마다 폐업되지 않은 치킨집들을 돌아보면서
각 집의 치킨 거리를 구해서 min_dist를 갱신하는 식으로 했는데 다른 사람들 풀이를 보니까 그냥 애초에 치킨집 중 M개를 골라서
따로 만든 벡터에 넣고, 각 집마다 해당 벡터를 돌아보면서 각 집의 치킨 거리를 구하고 최솟값을 갱신하는 식으로 풀었더라.
사실 거기서 거기긴 한데 후자가 좀 더 직관적이고 시간도 덜 걸릴 것 같음. 왜냐면 내 풀이는 chicken 벡터를 모두 돌면서
closed 값을 확인하는 과정이 들어가 있는데, 후자는 애초에 고른 치킨집(폐업 안 된 치킨집)만 들어있는 벡터만 도니까..
어째됐든 2차원 좌표값 넣는게 좀 귀찮긴 했지만 어려운 문제는 아니었다.
*/