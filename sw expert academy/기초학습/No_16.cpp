// 파핑파핑 지뢰찾기(5. 그래프)
#include <iostream>
#include <string>
#define MAX 300

using namespace std;

int N;

int mines[MAX][MAX]; // mines[i][j]: (i, j)의 인접칸들의 지뢰 개수의 합. (i, j)에 지뢰가 있다면 값은 -1이다.

int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

bool out_of_bound(int r, int c);
void dfs(int r, int c);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;

  cin >> T;

  for(int t=1; t<=T; t++){
    int count = 0;

    cin >> N;

    for(int i=0; i<N; i++)
      for(int j=0; j<N; j++)
        mines[i][j] = 0;

    for(int i=0; i<N; i++){
      string str;

      cin >> str;

      for(int j=0; j<N; j++){
        if(str[j] == '*'){
          mines[i][j] = -1;

          for(int k=0; k<8; k++){
            int nr = i+dr[k];
            int nc = j+dc[k];

            if(!out_of_bound(nr, nc) && mines[nr][nc] != -1) mines[nr][nc]++;
          }
        }
      }
    }

    for(int i=0; i<N; i++){
      for(int j=0; j<N; j++){
        if(mines[i][j] == 0){ // 0인 칸을 누르면 인접칸들도 열림
          count++;
          dfs(i, j);
        }
      }
    }

    for(int i=0; i<N; i++)
      for(int j=0; j<N; j++)
        if(mines[i][j] > 0) count++; // 0이 아닌 칸들은 그 칸만 열림

    cout << '#' << t << ' ' << count << '\n';
  }

  return 0;
}

bool out_of_bound(int r, int c){
  if(r<0 || N<=r || c<0 || N<=c) return true;
  else return false;
}

void dfs(int r, int c){
  mines[r][c] = -1;

  for(int i=0; i<8; i++){
    int nr = r+dr[i];
    int nc = c+dc[i];

    if(!out_of_bound(nr, nc)){
      if(mines[nr][nc] == 0) dfs(nr, nc); // 인접칸이 0이라면 거기서 또 연쇄적으로 열림
      else if(mines[nr][nc] > 0) mines[nr][nc] = -1; // 그렇지 않다면 그냥 열리기만 함
    }
  }
}

/*
좀 까다로워 보였지만, 풀어보니 쉬웠던 dfs/bfs 문제.

mines[i][j]: (i, j)의 인접칸들의 지뢰 개수의 합이다. 만약 (i, j)가 지뢰라면 값은 -1이 된다.
mines 값이 0인 칸은, 누르면 인접칸들까지 모두 눌린다. 즉, 0인 칸을 눌렀는데 그 인접칸에 0인 칸이 또 있었다면, 걔도 눌리게 된다.
그렇기 때문에, 우선 mines 값이 0인 칸들을 모두 누른다(dfs/bfs로 연쇄적으로 눌림을 구현). 그러면 인접한 0인 칸들은 모두 연쇄적으로 눌리게 
된다. 그런 다음, 남은 칸들 중 아직 안 눌린 칸들(값은 1 이상이겠지? 0인 칸들은 다 눌렀으니깐)의 개수를 세서, 위에서 구한 count에 그 개수를 
더한다(64행). 걔들은 누르면 그 칸만 딱 눌리기 때문.

40행에서, 어떤 칸이 지뢰라면 그 칸의 mines 값을 -1로 만들고, 인접칸들(지뢰가 없는)의 mines 값을 1 증가시켜줬다. 이렇게 mines 배열을 구했고,

55행에서 0인 칸들을 누른다. 총 몇 번 눌렀는지 count에 담는다.

그런 다음 64행에서 남아있는 안 열린 칸들을 누른다. 그 횟수를 count에 더하여, count를 출력하면 된다.
*/