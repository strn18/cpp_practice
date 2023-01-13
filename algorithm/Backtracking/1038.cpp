#include <iostream>
#include <cmath>

using namespace std;

// 감소하는 수의 개수: 10C1 + 10C2 + ... + 10C10과 같다. 0~9 중 n개를 고르면, 고른 수로 만들 수 있는 감소하는 수의 종류는 단 하나이기 때문.
long long nums[1024]; // 감소하는 수의 개수는 2^10-1 = 1023, 그러므로 인덱스 0부터 인덱스 1022까지 들어간다.
int nums_idx = 0;
int temp[10];

void make_nums(void); // 모든 감소하는 수 만들어서 넣기(오름차순)
void choose(int n, int end, int count); // 총 n개를 고르는데, 이번 수는 end보단 작을 때까지 커지고 현재 count개 고르는 중
long long temp_to_nums(int n); // 수 n개를 골라서 n-1 인덱스 까지 차있는 temp를 long long 형 수로 바꿔 nums에 넣기

int main(){
  int N;
  scanf("%d", &N);
  make_nums();

  if(N>1022)
    printf("-1");
  else
    printf("%lld", nums[N]);
  return 0;
}

void make_nums(void){
  for(int i=1; i<=10; i++){
    choose(i, 10, 1);
  }
}

void choose(int n, int end, int count){
  for(int i=0; i<end; i++){
    temp[count-1] = i;
    if(count==n)
      nums[nums_idx++] = temp_to_nums(n);
    else
      choose(n, i, count+1);
  }
}

long long temp_to_nums(int n){
  long long result=0;

  for(int i=0; i<n; i++)
    result += temp[(n-1)-i]*pow(10, i); // temp[4] = {4, 3, 2, 1}이면 4321이 되어야 하니깐 뒤에서부터

  return result;
}

/*
백트래킹 문제. 처음에는 멍청하게 감소하는 수는 수가 길어지면서 계속 생기지 않나? N번째 감소하는 수가 왜 없지 라고 생각했는데
제일 큰 감소하는 수가 9876543210 이니까 그거 다음으로는 감소하는 수가 없다..
근데 이때 한자리수인 감소하는 수의 개수는 0~9 중에서 하나를 고르는 경우와 같고, 두자리수인 감소하는 수의 개수는 둘을 고르는 경우와 같다.
왜냐면 그 고른 수로 만들 수 있는 감소하는 수는 어차피 하나밖에 없으니까(예를 들어 4와 7을 골랐다면 어차피 74밖에 없고, 1 4 7 8을 골랐다면
어차피 8741밖에 없음).. 그러므로 감소하는 수의 총 개수는 10C1 + 10C2 + ... + 10C10 = 2^10-1 = 1023개이다.
이걸 이용해서 1023개의 감소하는 수를 모두 만들어 nums에 넣고, 입력된 N에 해당하는 감소하는 수를 출력하는 식으로 풀었음.
처음에 약간 헷갈린 것만 빼면 별로 어려운 문제는 아니었다. 콤비네이션 짤 줄만 알면 됨
*/