// #include <iostream>

// using namespace std;

// int main(){
//   ios_base::sync_with_stdio(false);
//   cin.tie(NULL);

//   int TC;

//   cin >> TC;

//   for(int t=1; t<=TC; t++){

//     cout << '#' << t << ' ' << 777 << '\n';
//   }

//   return 0;
// }

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#define MAX_C 9000
#define MAX_N 25

using namespace std;

typedef struct{
  int idx, soldiers;
} info;
info board[MAX_N][MAX_N];

int n, countries;
unordered_map<string, int> m;
unordered_set<int> enemy[MAX_N*MAX_N];

int parent_ally[MAX_C];

int dr[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dc[8] = {0, 1, 1, 1, 0, -1, -1, -1};

int find_ally(int x);
void union_ally(int x, int y);
bool out_of_bound(int r, int c);

void init(int N, int mSoldier[25][25], char mMonarch[25][25][11])
{
  n = N;
  countries = 0;
  m = unordered_map<string, int>();

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      board[i][j] = {countries, mSoldier[i][j]};
      enemy[countries] = unordered_set<int>();
      parent_ally[countries] = countries;

      m.insert({string(mMonarch[i][j]), countries++});
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

  if(enemy[ra].find(rb) != enemy[ra].end()) return -2;

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
        break;
      }
    }
    if(r != -1) break;
  }

  bool attacked = false;

  for(int i=0; i<8; i++){
    int nr = r + dr[i];
    int nc = c + dc[i];

    if(!out_of_bound(nr, nc) && (find_ally(board[nr][nc].idx) == find_ally(a))){
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

    if(!out_of_bound(nr, nc) && (find_ally(board[nr][nc].idx) == find_ally(b))){
      board[r][c].soldiers += (board[nr][nc].soldiers / 2);
      board[nr][nc].soldiers -= (board[nr][nc].soldiers / 2);
    }
  }

  if(board[r][c].soldiers < 0){
    board[r][c].idx = countries;
    board[r][c].soldiers *= -1;
    parent_ally[countries] = find_ally(a);

    m.insert({string(mGeneral), countries++});
    
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

  if(rx < ry){
    int temp = rx;
    rx = ry;
    ry = temp;
  }
  
  parent_ally[ry] = rx;
  enemy[rx].insert(enemy[ry].begin(), enemy[ry].end());
}

bool out_of_bound(int r, int c){
  if(r<0 || n<=r || c<0 || n<=c) return true;
  else return false;
}

int main(){
  string str[3][3] = {"AA", "BB", "CC", "DD", "EE", "FF", "GG", "HH", "II"};
  int num[3][3] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  n = 3, countries = 0;

  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      board[i][j] = {countries, num[i][j]};
      parent_ally[countries] = countries;
      enemy[countries] = unordered_set<int>();

      m.insert({string(str[i][j]), countries++});
    }
  }

  cout << attack("AA", "DD", "QQ") << '\n';
  cout << attack("BB", "DD", "QQ") << '\n';
  
  for(auto e: enemy[m["AA"]])
    cout << e << ' ';
  cout << '\n';

  for(auto e: enemy[m["DD"]])
    cout << e << ' ';
  cout << '\n';
  
  for(int i=0; i<3; i++){
    for(int j=0; j<3; j++)
      cout << board[i][j].idx << ' ' << board[i][j].soldiers << " / ";
    cout << '\n';
  }


  return 0;
}