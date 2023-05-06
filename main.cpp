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