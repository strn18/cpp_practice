#include <iostream>
#include <algorithm>
#define MAX 10

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  int left[MAX+1], pos[MAX+1], result[MAX+1];

  cin >> N;

  for(int i=1; i<=N; i++)
    cin >> left[i];
  
  for(int i=1; i<=N; i++){
    pos[i] = left[i];

    sort(pos+1, pos+i);

    for(int j=1; j<i; j++){
      if(pos[j] <= pos[i]) pos[i]++;
      else break;
    }

    result[pos[i]] = i;
  }

  for(int i=0; i<N; i++)
    cout << result[i] << ' ';

  return 0;
}

/*
left[i]: i번 사람 왼쪽에 그보다 키 큰 사람의 수.
pos[i]: i번 사람의 위치(0 ~ N-1)

i(1~N)번 사람의 위치인 pos[i]를 구하는 법: 
  pos[i] = left[i];
  pos[1]~pos[i-1]을 오름차순 정렬한다.
  걔네들을 돌면서, pos[j]와 pos[i]를 비교하여, 
    if pos[j]<=pos[i] then pos[i]++; 
    else break;
  result[pos[i]] = i; (pos[i+1]을 구할 때 pos[i]까지 다시 정렬되므로 결과값을 저장해둔다)

이렇게 풀었다. pos[i]를 구할 때마다 그 앞을 정렬해줘서 좀 비효율적이지만 N=10이라 그냥 풀었음. 
https://kpumangyou.tistory.com/33 이게 좀 더 효율적인 코드다. pos[i]를 구할 때, result를 사용하여 pos를 따로 정렬하여 사용하지 않는다고 보면 됨. 
*/