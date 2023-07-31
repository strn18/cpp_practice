// [Professional] 단어가 등장하는 횟수(9. 해시)
#include <iostream>
#include <string>
#define MAX 100000

using namespace std;

int fail[MAX]; // fail[i] = k라면, S[0]~S[i]라는 부분 문자열에서, k길이의 접두사와 k길이의 접미사가 일치한다.

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int TC;

  cin >> TC;

  for(int t=1; t<=TC; t++){
    string B, S;
    int N, M, count = 0;

    cin >> B >> S;

    N = B.size(); M = S.size();

    // fail value initialization
    for(int i=0; i<M; i++) fail[i] = 0;

    for(int i=1, j=0; i<M; i++){ // i=0부터 한다면, fail[0] = 1이 되어버린다. 실제로는 0이 되어야 함. 
      while(j > 0 && S[i] != S[j]) j = fail[j-1]; // 여기는 밑 KMP 부분과 동일.

      if(S[i] == S[j]){
        fail[i] = j+1; // 만약 일치하는 지점을 찾았다면? S[0]~S[i]라는 부분 문자열에서, 
        j++; // S[i-j]~S[i]라는 접미사 부분과 S[0]~S[j]라는 접두사 부분이 일치하는 것. 접미사/접두사 부분의 길이는 j+1이므로,
      } // fail[i]에 j+1을 대입해준다.
    }

    // KMP
    for(int i=0, j=0; i<N; i++){
      while(j > 0 && B[i] != S[j]) j = fail[j-1]; // j>0인데 B[i]와 S[j]가 다르다면, fail값을 이용하여 j값을 앞으로 땡긴다.

      if(B[i] == S[j]){ // 만약 B[i]와 S[j]가 같다면? 
        if(j == M-1){ // j가 끝까지 왔다면 일치하는 문자열 발견했으므로 count 증가.
          count++;
          j = fail[j]; // 이후 뒤로도 계속 찾아야하니까 j값을 앞으로 땡긴다. 이때, 39행과 달리 B[i]와 S[j]까지 일치하는 거니까 fail[j].
        }
        else j++; // j가 끝이 아니라면 i와 함께 j도 증가하도록 해줌.
      } // j==0인데 B[i]와 S[j]가 다르다면 여기까지 온다. j는 그대로 있고 i만 증가한다. B[i] == S[j]가 될 때까지.
    }

    cout << '#' << t << ' ' << count << '\n';
  }

  return 0;
}

/*
KMP 알고리즘을 사용해 풀이하였다. 해시 강의에 딸린 걸 보니깐 해시를 쓰는 방법이라는 라빈 카프 알고리즘을 쓰는 걸 의도했나본데 그건 나중에 해볼 
예정. 일단 검색하니깐 KMP 알고리즘 쓰는 거라길래 그거 공부해보고 풀어봤음. https://blog.naver.com/kks227/220917078260 여기를 참고해서 
공부했고, 이해하기가 쪼금 어렵긴하지만 막 복잡한 알고리즘은 아니다. 어떻게 돌아가는 건지만 알면 충분히 할만했음. KMP 알고리즘의 자세한 동작은 
주석처리한 부분과, 링크의 글 참고.
*/