// 15638. [Pro] 삼국지게임
#include <unordered_map>
#include <unordered_set>
#include <string>
#define MAX_N 25 // N의 최댓값
#define MAX_C 8625 // 최대로 만들어질 수 있는 국가의 개수. 25*25 + 8000(attack()의 최대 호출 횟수) = 8625

using namespace std;

typedef struct{
  int idx, soldiers;
} info;
info board[MAX_N][MAX_N];
// board[i][j].idx: (i, j)에 있는 국가의 인덱스(군주 이름을 m에 매핑한 결과값. 0~8624).
// board[i][j].soldiers: (i, j)에 있는 국가의 병사 수.

int n, countries; // n: board의 한 변의 길이(N). countries: 만들어진 국가의 수.
unordered_map<string, int> m; // m[str]: 군주 이름이 str인 국가의 인덱스. 그것을 사용하여 enemy, parent_ally에 접근, 적대/연합 정보를 얻는다.
unordered_set<int> enemy[MAX_N*MAX_N]; // enemy[idx]: 인덱스가 idx인 국가의 적대 국가 정보. 이때, idx는 0~624이다.
// 왜냐? init으로 만들어진 초기 국가 외에, 다른 국가들은 attack을 통해 만들어지게 된다. 이때, 해당 신생 국가들은 기존에 존재하던 국가를 
// parent로 가지게 된다. 즉, 어떠한 국가의 parent는 반드시 초기 국가이다. 이때, find를 통해 얻는 root 값으로만 enemy에 접근할 것이기에, 
// idx는 반드시 초기 국가의 인덱스이고, 그렇기에 0~624임.

int parent_ally[MAX_C]; // parent_ally[idx]: 인덱스가 idx인 국가의 parent 값.

int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1}; // attack 함수 실행 시, 특정 국가의 인접 칸들 방문을 위해 사용.
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int find_ally(int x); // 인덱스가 x인 국가의 root 값을 찾아 리턴.
void union_ally(int x, int y); // 인덱스가 x인 국가와 y인 국가를 union. 이때, enemy 정보도 합친다.
bool out_of_bound(int r, int c); // board 범위 벗어났는지 체크.

void init(int N, int mSoldier[25][25], char mMonarch[25][25][11])
{
  n = N;
  countries = 0;
  m = unordered_map<string, int>();

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      board[i][j] = {countries, mSoldier[i][j]};
      enemy[countries] = unordered_set<int>(); // 처음에 적대 정보는 비어있다.
      parent_ally[countries] = countries;

      m[string(mMonarch[i][j])] = countries++;
    }
  }
}

void destroy()
{

}

int ally(char mMonarchA[11], char mMonarchB[11])
{
  int ra = find_ally(m[string(mMonarchA)]);
  int rb = find_ally(m[string(mMonarchB)]);

  if(ra == rb) return -1;

  for(auto e: enemy[ra]) // ra의 적대 국가 중에, rb의 연합에 소속된 국가가 있다면, ra와 rb는 적대 관계이다.
    if(find_ally(e) == rb) return -2;

  union_ally(ra, rb);

  return 1;
}

int attack(char mMonarchA[11], char mMonarchB[11], char mGeneral[11])
{
  int a = m[string(mMonarchA)];
  int b = m[string(mMonarchB)];

  if(find_ally(a) == find_ally(b)) return -1;

  int r = -1, c = -1;

  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      if(board[i][j].idx == b){
        r = i;
        c = j;

        i = n; // 첫 for문 탈출용
        break;
      }
    }
  }

  bool attacked = false;

  for(int i=0; i<8; i++){
    int nr = r + dr[i];
    int nc = c + dc[i];

    if(!out_of_bound(nr, nc) && (find_ally(board[nr][nc].idx) == find_ally(a))){ // 인접 국가 중 a와 연합인 국가 발견 -> 공격
      attacked = true;
      board[r][c].soldiers -= (board[nr][nc].soldiers / 2);
      board[nr][nc].soldiers -= (board[nr][nc].soldiers / 2);
    }
  }

  if(!attacked) return -2;

  enemy[find_ally(a)].insert(find_ally(b));
  enemy[find_ally(b)].insert(find_ally(a));

  for(int i=0; i<8; i++){
    int nr = r + dr[i];
    int nc = c + dc[i];

    if(!out_of_bound(nr, nc) && (find_ally(board[nr][nc].idx) == find_ally(b))){ // 인접 국가 중 b와 연합인 국가 발견 -> 방어
      board[r][c].soldiers += (board[nr][nc].soldiers / 2);
      board[nr][nc].soldiers -= (board[nr][nc].soldiers / 2);
    }
  }

  if(board[r][c].soldiers < 0){ // 남은 병력이 음수이면, 공격 병사가 더 많았다는 것.
    board[r][c].idx = countries;
    board[r][c].soldiers *= -1;
    parent_ally[countries] = find_ally(a); // 해당 신생 국가도 a와 같은 root를 가지도록 설정.

    m[string(mGeneral)] = countries++;
    
    return 1;
  }
  else return 0;
}

int recruit(char mMonarch[11], int mNum, int mOption)
{
  int m_idx = m[string(mMonarch)];

  if(mOption == 0){
    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        if(board[i][j].idx == m_idx)
          return (board[i][j].soldiers += mNum);
      }
    }
    return -999; // never happens
  }

  else{
    int sum = 0;

    for(int i=0; i<n; i++){
      for(int j=0; j<n; j++){
        if(find_ally(board[i][j].idx) == find_ally(m_idx))
          sum += (board[i][j].soldiers += mNum);
      }
    }

    return sum;
  }
}

int find_ally(int x){
  if(parent_ally[x] == x) return x;

  return (parent_ally[x] = find_ally(parent_ally[x]));
}

void union_ally(int x, int y){
  int rx = find_ally(x);
  int ry = find_ally(y);
  
  parent_ally[ry] = rx; // 이제 rx가 대표가 된다.

  enemy[rx].insert(enemy[ry].begin(), enemy[ry].end());
}

bool out_of_bound(int r, int c){
  if(r<0 || n<=r || c<0 || n<=c) return true;
  else return false;
}

/*
와 정말 복잡하다...

자세한 건 주석 처리된 거랑 해설 참조하면 될 것 같다.

거의 다 짰는데 계속 테케 몇 개만 맞고 틀렸음. No_1 풀 때랑 비슷하게(그때 보다 테케를 덜 맞긴 했음)...

그래서 또 sample_input 넣으면서 틀린 부분 찾아봤는데, 결국 enemy 다루는 부분이 문제였다.

기존에는, 두 연합이 enemy인지 테스트 해볼 때, 즉 ally 함수에서 두 국가가 적대인지 아닌지 테스트 해볼 때, enemy[ra]에 rb가 있는지(또는 그 
반대도)만 확인했었다. 근데 이러면 문제가 생김. 가령, 국가 1 2 3 4가 있다고 하자. 이때, 국가 2와 4가 싸움. 그러면 둘은 적대 관계다. 
enemy[2]에는 4가 있고, enemy[4]에는 2가 있는 상태. 그러다가 1과 2가 연합. 그러면, enemy[1]에는 enemy[2]의 정보가 들어오니깐, enemy[1]에는 
4가 있다. 그리고 3과 4도 연합. 그러면, enemy[3]에는 2가 있는 상태. 이때, 1과 3을 연합시키려 한다고 하자. 그러면, enemy[1]에 3이 있는지, 
enemy[3]에 1이 있는지만 확인하게 되는데, 둘 다 없다! 실제로는 (3, 4)가 연합, (1, 2)가 연합이니깐 1과 3은 적대인데, 그걸 체크 못 하고 그냥 
넘어가버리고 둘이 연합시켜버린다. 이래서 틀린 거임.

이렇게 하지 말고, enemy[1]에 3만 있는지만 확인하는게 아니라, enemy[1]의 원소 중에서, root로 3을 가지는 원소가 있는지 확인해야 한다. 즉, 
enemy[1]의 원소가 3의 연합에 들어가 있는지 확인해야 함. 그러면, enemy[1]에는 4가 있고, 4의 root는 3이니까 적대 관계가 확인된다.

이런 방향으로 코드 고치니까 맞았음.
*/