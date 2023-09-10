#include <iostream>
#include <algorithm>
#define MAX 8

using namespace std;

int N, M;
int num[MAX+1], arr[MAX+1];

void choose(int n, int start); // arr[n]의 넣을 수를 num[start]부터 선택한다. n과 start는 1-based.
void printArr(void);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  cin >> N >> M;

  for(int i=1; i<=N; i++)
    cin >> num[i];
  
  sort(num + 1, num+N + 1);

  choose(1, 1);

  return 0;
}

void choose(int n, int start){
  for(int i=start; i<=N; i++){
    if(num[i] == num[i-1]) continue;

    arr[n] = num[i];

    if(n == M) printArr();
    else choose(n+1, i);
  }
}

void printArr(void){
  for(int i=1; i<=M; i++)
    cout << arr[i] << ' ';
  cout << '\n';
}