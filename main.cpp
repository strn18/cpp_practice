#include <iostream>
#include <algorithm>
#define MAX 10000

using namespace std;

void swap(int *a, int *b){
  int temp = *a;
  *a = *b;
  *b = temp;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  int num[MAX];

  cin >> N;

  for(int i=0; i<N; i++)
    cin >> num[i];
  
  int start = 0; // 내림차순이 시작되는 첫번째 인덱스

  for(int i=1; i<N; i++){
    if(num[i-1] < num[i])
      start = i;
  }

  if(start == 0){
    cout << -1;
    return 0;
  }

  int targetVal = MAX; // num[start-1]보다 크면서 가장 작은 값
  int targetPos; // 그 값의 인덱스

  for(int i=start; i<N; i++){
    if(num[i] > num[start-1] && num[i] < targetVal){
      targetVal = num[i];
      targetPos = i;
    }
  }

  swap(&num[start-1], &num[targetPos]);

  sort(num + start, num + N);

  for(int i=0; i<N; i++)
    cout << num[i] << ' ';

  return 0;
}