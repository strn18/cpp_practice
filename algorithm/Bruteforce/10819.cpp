#include <iostream>
#include <vector>
#include <cstdlib>
#define MAX 8

using namespace std;

int N, ans = 0;
int arr[MAX];
bool visited[MAX] = {false};

void choose(vector<int> num);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N;

  for(int i=0; i<N; i++)
    cin >> arr[i];

  choose(vector<int>());

  cout << ans;

  return 0;
}

void choose(vector<int> num){
  if(num.size() == N){
    int count = 0;

    for(int i=0; i<N-1; i++)
      count += abs(num[i]-num[i+1]);
    
    ans = max(ans, count);

    return;
  }
  
  for(int i=0; i<N; i++){
    if(!visited[i]){
      visited[i] = true;
      num.push_back(arr[i]);

      choose(num);

      visited[i] = false;
      num.pop_back();
    }
  }
}

/*
혼자 쉐복 존1나 한 문제. 주어진 수를 {1번째로 큰 수, 1번째로 작은 수, 2번째로 큰 수, 2번째로 작은 수, ...}로 만든 후 주어진 식의 계산을 해주면
답을 구할 수 있을 거라 생각했다(또는 1번째로 작은 수부터 시작하든가). 근데 그렇게 아무리 해봐도 주어진 예제에서 답이 안 나옴. 그래서 개똥꼬쇼
하다가 결국 https://lu-coding.tistory.com/7 이거 보고 브루트포스+백트래킹으로 풀었다..
*/