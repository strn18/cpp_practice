#include <iostream>
#include <algorithm>
#define MAX 10000

using namespace std;

int arr[MAX+1] = {0};

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  cin >> N;

  for(int i=0; i<N; i++){
    int num;

    cin >> num;

    arr[num]++;
  }

  for(int i=1; i<=MAX; i++)
    for(int j=0; j<arr[i]; j++)
      cout << i << '\n';

  return 0;
}

/*
첨에는 그냥 sort로 했다가 메모리 초과 나서 바꿔서 풀었음. 주어지는 수는 1~10000 이니까, int arr[10001]을 만들고, arr[i]: 주어진 수 중 i의 개수.
로 정의한 다음, 22행에서처럼 입력받은 수를 인덱스로 써서 arr의 값을 증가시켜줬음. 그 다음 arr[i]의 값만큼 i를 출력시켜주면 됨.
*/