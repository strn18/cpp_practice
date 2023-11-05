#include <iostream>
#include <string>
#define MAX 1000

using namespace std;

int n, m;
int pSum[MAX+1][MAX+1] = {0};

bool checkSquare(int len);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string row;

  cin >> n >> m;

  for(int i=1; i<=n; i++){
    cin >> row;

    for(int j=1; j<=m; j++){
      pSum[i][j] += (row[j-1] - '0');
      pSum[i][j] += (pSum[i-1][j] + pSum[i][j-1] - pSum[i-1][j-1]);
    }
  }

  int ans = 0, low = 0, high = min(n, m);

  while(low <= high){
    int mid = (low + high)/2;

    if(checkSquare(mid)){
      ans = mid;
      low = mid + 1;
    }
    else{
      high = mid - 1;
    }
  }

  cout << ans * ans;

  return 0;
}

bool checkSquare(int len){
  int area = len * len;

  for(int i=len; i<=n; i++){
    for(int j=len; j<=m; j++){
      int total = pSum[i][j];
      total -= (pSum[i-len][j] + pSum[i][j-len] - pSum[i-len][j-len]);

      if(area == total) return true;
    }
  }

  return false;
}

/*
나는 부분합 + 파라메트릭 서치로 풀긴 했는데 분류는 dp로 되어 있어서 그냥 그거로 함. 

내가 푼 방식은 이렇다. 
1) low = 0, high = min(n, m) 으로 해서 정사각형의 길이를 기준으로 파라메트릭 서치. 
2) 길이가 len인 정사각형이 존재하는지 찾으려면(checkSquare)? 부분합을 이용한다. pSum[i][j] = (1, 1)을 좌상, (i, j)를 우하로 하는 사각형 속의 
1의 개수이다. 이때, (i, j)를 우하로 하였을 때 길이가 len인 정사각형(그러면 (i-len+1, j-len+1)이 좌상이겠지)이 성립하는지 보려면, 
pSum[i][j] - pSum[i-len][j] - pSum[i][j-len] + pSum[i-len][j-len] == len * len 인지 아닌지 보면 된다. 이걸 체크하는 것은 O(1)이고, 
그걸 대~충 O(n*n)정도 하고(다만 len가 1일 때만 그렇고, len가 길어지면 그거보다 작아지겠지), 파라메트릭 서치니까 O(logn)을 곱해주면 대충 
O(n*n*logn)이라 충분히 풀 수 있다. 

dp로 푸는 거는 인터넷 검색 ㄱㄱ
*/