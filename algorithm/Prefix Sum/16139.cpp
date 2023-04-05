#include <iostream>
#include <string>
#define MAX 200000

using namespace std;

int p_sum[MAX][26] = {0};

int main(){
  cin.sync_with_stdio(false); cin.tie(NULL);
  
  char ch;
  int q, left, right;
  string S;

  cin >> S;

  for(int i=0; i<S.size(); i++)
    p_sum[i][S[i]-'a'] = 1;
  
  for(int i=1; i<S.size(); i++)
    for(int j=0; j<26; j++)
      p_sum[i][j] += p_sum[i-1][j];

  cin >> q;

  while(q--){
    cin >> ch >> left >> right;

    if(left == 0)
      cout << p_sum[right][ch-'a'];
    else
      cout << p_sum[right][ch-'a']-p_sum[left-1][ch-'a'];

    cout << '\n';
  }

  return 0;
}

/*
어렵지 않았지만 시간 초과 관리를 해야했던 문제.

l~r번째 문자 중에서, 어떠한 문자가 몇 번 등장하는지 세면 된다. 근데 문자열의 길이는 최대 20만이고, 그러한 쿼리를 20만 번 하기 때문에, 그냥
하나하나 다 세면 시간 초과가 난다. 그래서 누적합을 써야했다. p_sum[i][j]는, 0~i번째 문자 중에서 j번째 알파벳이 몇 번 등장하는지를 의미한다.
그렇기에, l~r번째 문자 중에서 j번째 알파벳이 몇 번 등장하는지 알고 싶다면? p_sum[r][j] - p_sum[l-1][j]를 해주면 된다(물론 l이 0일 때는 
예외처리를 해주어야 함).

처음에는 p_sum을 채워주는 걸 너무 비효율적으로 해서(문자열의 길이가 L일 때, O(L*L)로 해버림) 시간초과가 났다. 그래서 지금의 방법대로, 
우선 문자열의 각 문자를 돌면서, 해당 문자의 위치가 i일 때, p_sum[i][해당문자] = 1을 해준다(18~19행). 그런 다음, 모든 i를 돌면서,
p_sum[i][j] += p_sum[i-1][j] 를 모든 j(0~25)에 대해서 차례대로 해준다. 물론 i=0일 때는 이미 다 채워져있는 거니까 패스.

그러고 나서 제출했는데 또 시간 초과가 났다. 이게 왜 시간 초과인가 싶었는데, 혹시 몰라서 cin을 안 쓰고 다 scanf만 쓰도록 바꿨더니(이때 버퍼를
비우기 위해 getchar() 사용) 맞았음. 근데 시간이 다른 풀이들보다 좀 길길래, 다 cin cout으로 바꾸고 10행에 저거 넣어줬더니 시간 줄어들었다.
*/