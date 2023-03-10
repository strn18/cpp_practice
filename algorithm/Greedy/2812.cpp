#include <iostream>
#include <queue>
#define MAX 500000

using namespace std;

int main(){
  int N, K, num;
  int count, start, end;
  queue<int> num_idx[10];

  scanf("%d %d", &N, &K);
  count = N-K; start = 0; end = K;

  for(int i=0; i<N; i++){
    scanf("%1d", &num);
    num_idx[num].push(i);
  }
  
  while(1){
    for(int i=9; i>=0; i--){
      while(!num_idx[i].empty() && num_idx[i].front()<start)
        num_idx[i].pop();

      if(!num_idx[i].empty() && num_idx[i].front()<=end){
        printf("%d", i);
        count--;
        
        K -= num_idx[i].front()-start;
        start = num_idx[i].front()+1;
        end = start+K;
        num_idx[i].pop();
        break;
      }
    }
    if(!count) break;
  }
  
  return 0;
}

/*
좀 어려웠던 그리디 문제. 처음에 생각한 방식은 다음과 같다.
숫자가 N개 있고 그 중에 K개를 지워야할 때, 우선 0번째 수부터 시작한다. 이때 취할 수 있는 선택은, 아무것도 지우지 않고 0번째 수를 받기 /
0번째 수를 지우고 1번째 수를 받기 / 0~1번째 수를 지우고 2번째 수를 받기 / ... / 0~K-1번째 수를 지우고 K번째 수를 받기. 이렇게 있다.
그 중에서(0~K번째 수) 제일 큰 값을 받으면 되므로, 0~K번째 수 중에서 최댓값을 받고, 그 전까지의 수는 모두 지워버리면 된다.
왜냐? N개의 수 중에서 K개를 지우고 N-K자리의 수를 만드는데, 그게 최대가 되려면 앞자리에 최대한 큰 수가 와야함. 근데 지울 수 있는 수는 딱
K개니까, K+i번째(i>0)에 있는 수들은, 얼마나 크든 절대 받을 수가 없음. 그걸 앞에 두려고 받으려면 K개보다 많이 지워야하니깐. 그렇기 때문에
앞에 둘 수 있는 수는 0~K번째 수(0개를 지웠을 때~K개를 지웠을 때)이고, 그 중에서 제일 큰 수를 받고 그 전 수까지는 다 지워버리면 된다.
이 과정을 해서, a번째 수가 최대여서 그걸 받고 그 앞의 a개의 수는 지워버렸다고 하자. 그 다음에는, a+1번째 수부터 시작해서, 이제 K-a개의
수를 지울 수 있음을 인지하고 위의 과정을 그대로 반복하면 됨. 그러다가 총 K-N개의 수를 모두 받았다면 그게 최댓값이다.

이렇게 방법을 짜봤는데, 시간초과가 날 것 같았다. N=50만, K=25만이라고 쳤을 때, 주어진 수가 999...999 라면, 앞에서부터 약 25만 개의 수를
보면서 그 중에서 max값을 찾아줘야하고, 그렇게 찾는 걸 약 25만 번 반복해야하므로 25만 개의 원소에서 최댓값 찾기*25만 번 = 25만*25만 이 된다.

그래서 이 방법은 갖다버리고, 살짝 바꿔서 만든게 위의 코드임. 최댓값 찾는 과정에 불필요하게 시간을 들이지 않도록, num_idx 큐를 썼다.
num_idx[i] = {j, k}라면, i라는 수의 위치(인덱스)는 j와 k라는 뜻이다. 이렇게 한 다음, 위에서 0~K번째 수 중에서 최댓값을 찾는 과정이 
있었는데 이때 0과 K는 각각 start와 end 변수와 같다. 그 다음, 총 K-N개의 수를 받을 때까지 num_idx[9]부터 num_idx[0] 순으로 방문하며, 고를 수
있는 인덱스 값을 찾아 고르는 과정을 반복하면 된다. 그리고 위에서 최댓값을 고르는 수의 범위가 어떠한 수를 고르고 그 앞의 수들을 지우면서
변화하는데, 그것도 29~31행을 통해 구현했음(이때 K는 위에서 상수로 표현했는데 여기서는 그냥 변수로 썼다. 어떠한 수를 고를 때마다, 그 앞의
수들을 지움으로써, 지울 수 있는 수의 개수가 줄어드니까 K를 줄여줌).

근데 제출했더니 틀렸다고 떴는데, 알고보니까 그냥 수가 범위를 초과해서 그랬다. 여기 코드와 달리 첨에 제출한 코드는 정답(N-K자리의 수)을 int형
변수에 담아두는 방식이었는데, N이 최대 50만이라 수가 ㅈㄴ 커진다(변수에 담기는 불가능). 그래서 수를 담아놓는 게 아니라 문자열 같은 거에 넣든지
아니면 하나하나 출력해야함. 수를 받을 때마다 하나하나 출력하는 식으로 바꾸니까 맞았다.

https://gusdnr69.tistory.com/244 다 풀고나서 다른 코드를 봤는데, 생각보다 ㅈㄴ 간단했다..
N개의 수를 왼쪽부터 하나하나 스택에 넣어주면서, 만약 스택의 top이 이번에 넣어줄 수보다 작다면, 그걸 빼주면 된다. 그렇게 빼준 다음에는 K--를
해주면 됨. 이거를 스택이 비거나 스택의 top이 넣어줄 수보다 작지 않을 때까지 반복한다. 그렇게 N개의 수를 다 넣었는데 스택의 size가 N-K(K는 상수)
보다 크다면, 그냥 스택 맨 처음(top이 아니고 맨 밑. 맨 처음에 들어간 값)부터 총 N-K개를 출력해주면 된다.
*/