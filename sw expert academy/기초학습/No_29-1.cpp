// 중간값 구하기(9. 해시)
#include <iostream>
#include <string>
#include <algorithm>
#define MAX 100000

using namespace std;

string set1[MAX], set2[MAX];

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    int N, M;

    cin >> N >> M;

    for(int i=0; i<N; i++)
      cin >> set1[i];

    for(int j=0; j<M; j++)
      cin >> set2[j];

    sort(set1, set1 + N);
    sort(set2, set2 + M);

    int count=0, i=0, j=0;

    while(i<N && j<M){
      if(set1[i] == set2[j]){
        count++; i++; j++;
      }
      else if(set1[i] < set2[j]) i++;
      else j++;
    }

    cout << '#' << t << ' ' << count << '\n';
  }

  return 0;
}

/*
걍 정렬해놓고 투포인터 써서 풀었다. 근데 해시 문제였네?? 해시 강의 듣고 다시 풀어 볼 예정
*/