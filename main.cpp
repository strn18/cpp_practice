#include <iostream>
#include <algorithm>
#include <string>
#define MAX 100000

using namespace std;

pair<int, string> arr[MAX];

bool compare(pair<int, string> a, pair<int, string> b){
  return a.first < b.first;
}

int main(){
  int N;

  scanf("%d", &N);
  for(int i=0; i<N; i++){
    scanf("%d", &arr[i].first);
    cin >> arr[i].second;
  }

  stable_sort(arr, arr+N, compare);
  
  for(int i=0; i<N; i++){
    printf("%d ", arr[i].first);
    cout << arr[i].second << '\n';
  }

  return 0;
}

/*
#include <iostream>
#define MAX 50

using namespace std;

int N, L, R;
int dr[4] = {-1, 1, 0, 0}, dc[4] = {0, 0, -1, 1};
int po[MAX][MAX], group[MAX][MAX];
int group_po[1300], group_co[1300];
int groups = 0;

void border(int r, int c, int group_num);
int absolute(int a, int b);

int main(){
  int days = 0;

  scanf("%d %d %d", &N, &L, &R);
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      scanf("%d", &po[i][j]);

  while(true){
    for(int i=0; i<N; i++)
      for(int j=0; j<N; j++)
        border(i, j, groups+1);
    
    if(groups == 0) break;

    days++;

    for(int i=1; i<=groups; i++){
      group_po[i] /= group_co[i];
    }

    for(int i=0; i<N; i++){
      for(int j=0; j<N; j++){
        if(group[i][j])
          po[i][j] = group_po[group[i][j]];
        group[i][j] = 0;
      }
    }
  }

  printf("%d", days);

  return 0;
}

void border(int r, int c, int group_num){
  
}

int absolute(int a, int b){
  return (a-b>=0 ? a-b : b-a);
}
*/