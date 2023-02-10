#include <iostream>
#include <cmath>

using namespace std;

int N, N_digit, count;
bool broken[10] = {false};

int get_digit(int n);
void solve(int cur, int cur_digit);

int main(){
  int M, temp;

  scanf("%d", &N);
  scanf("%d", &M);
  for(int i=0; i<M; i++){
    scanf("%d", &temp);
    broken[temp] = true;
  }

  N_digit = get_digit(N);
  count = abs(N-100); // 처음 채널에서 +, -로만 이동
  if(!broken[0])
    count = min(count, N+1); // 0으로 간 후 +, -로만 이동

  for(int i=1; i<=9 && count!=0; i++)
    if(!broken[i])
      solve(i, 1);

  printf("%d", count);

  return 0;
}

int get_digit(int n){
  for(int i=1; 1; i++)
    if(n<pow(10, i))
      return i;
}

void solve(int cur, int cur_digit){
  count = min(count, abs(N-cur)+cur_digit);

  if(cur_digit == N_digit+1) return;

  for(int i=0; i<=9; i++)
    if(!broken[i])
      solve(cur*10+i, cur_digit+1);
}

/*
별로 안 어려운 문젠데 마지막에 좀 헷갈렸던 문제.
현재 채널이 100번이고, N번 채널로 가고 싶을 때, 0~9 버튼과 +, - 버튼을 가장 적게 누를 때, 그 횟수를 구하면 된다. 이때, 0~9 버튼 중 몇 개는 
망가져서 못 쓴다.

대충 생각해보니 브루트포스로 풀면 될 것 같았다. 숫자 한 자리당 0~9를 모두 넣어보면서 최솟값을 갱신해나가도, N이 최대 50만 밖에 되지 않아서,
10^6(50만의 자릿수) = 백만 정도라서 걍 모두 대입하면서 풀기로 함. 

solve 함수는, 현재까지 만든 수가 cur이고, 만든 수의 자릿수가 cur_digit일 때, cur 뒤에 0~9를 넣으면서 재귀를 친다. 그러다가 cur_digit이
N의 자릿수(N_digit)과 같아지면, cur번으로 이동한 후 N번으로 이동하는데 걸리는 횟수(|N-cur|(+, - 누르는 횟수)+cur_digit(숫자 버튼 누르는
횟수))를 통해 count를 갱신해준다. 그러고 나서 리턴한다.

여기까지는 쉽게 짰는데, 자꾸 틀리는 부분이 있었다. 우선 0번으로 간 후 +, -로 이동하는 것을 추가해야했다. 27행에서 solve 함수를 시작해줄 때,
0번으로 시작하는 경우는 배제했기에 따로 추가했음. 그리고 cur_digit이 N_digit과 같을 때만 count를 갱신해주면 안 된다. cur_digit이 하나 작거나
클 때도 갱신을 해줘야한다. 왜냐면, N이 99이고 0, 1번 버튼만 쓸 수 있다면, 100번으로 간 다음 -버튼을 한 번 눌러서 가줘야하는데, N_digit과
cur_digit이 같을 때만 갱신을 해주면 이걸 구할 수 없다. 반대의 경우도 마찬가지. 그래서 43행에서, solve함수를 들어가면 우선 무조건 갱신을
해주었다. 그리고 cur_digit이 N_digit+2 이상일 때는 볼 필요가 없으니까 45행에서 리턴해줌.

근데 이렇게 해도 틀렸다. 그래서 뭐지 싶었는데, 아까 추가했던 0번으로 시작하는 경우가 문제였음. solve함수 시작하기 전에 무조건 그 경우를
보고 count를 갱신해줬는데, 0번 버튼을 못 쓸 때는 그 경우를 보면 안 된다. 그래서 24행에 if문 추가하고 제출하니 맞았다.
*/