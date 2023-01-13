/*
#include <iostream>

using namespace std;

int N;
int nums[10];
int used[10] = {0};
int max_nums[10] = {0}, min_nums[10] = {9, 9, 9, 9, 9, 9, 9, 9, 9, 9};
char inequal[10];

void dfs(int n);
void update(void);

int main(){
  char temp;
  scanf("%d", &N);
  getchar();
  
  for(int i=0; i<2*N; i++){
    scanf("%c", &temp);
    if(!(i%2))
      inequal[i/2] = temp;
  }

  dfs(0);

  for(int i=0; i<=N; i++)
    printf("%d", max_nums[i]);
  printf("\n");
  for(int i=0; i<=N; i++)
    printf("%d", min_nums[i]);
  
  return 0;
}

void dfs(int n){
  for(int i=0; i<10; i++){
    if(n!=0){
      if(inequal[n-1]=='<' && nums[n-1]>i) continue;
      else if(inequal[n-1]=='>' && nums[n-1]<i) continue;
      if(used[i]) continue;
    }
    used[i] = 1;
    nums[n] = i;
    if(n==N)
      update();
    else
      dfs(n+1);
    used[i] = 0;
  }
}

void update(void){
  for(int i=0; i<=N; i++){
    if(nums[i]<max_nums[i])
      return;
    else if(nums[i]==max_nums[i])
      continue;
    else{
      for(int j=0; j<=N; j++)
        max_nums[j] = nums[j];
      break;
    }
  }
  for(int i=0; i<=N; i++){
    if(nums[i]>min_nums[i])
      return;
    else if(nums[i]==min_nums[i])
      continue;
    else{
      for(int j=0; j<=N; j++)
        min_nums[j] = nums[j];
      break;
    }
  }
}

백트래킹 문제. 부등호 입력받는 거랑, 정수가 최대 10자리라 int 범위를 넘어가는 바람에 숫자 변수 사용 안 하고 int형 배열 쓰게 된 것 때문에 최댓값/최솟값 갱신이 좀 귀찮아진(update 함수) 것 제외하면 별로 어렵진 않았던 문제. 코드 보면 dfs는 짧은데 update 함수는 길다.. 
문제 다 풀고 남들 풀이 보면서 안 건데, 처음에 완성된 수열이 제일 작은 수고, 마지막에 완성된 수열이 제일 큰 수다. 이걸 이용하면 update 함수 내용을 저렇게 귀찮게 안 하고 더 쉽게 풀 수 있을듯..
https://jeongminhee99.tistory.com/84 여기처럼 처음에 완성된 수열, 마지막 수열을 따로 저장할 수도 있고
https://gdlovehush.tistory.com/337 여기처럼 벡터에 넣고 처음이랑 마지막 요소를 출력할 수도 있다. 
그리고 남들 풀이 보니까 나처럼 int형 배열을 쓰는게 아니라 string을 많이들 쓰네.. 나도 다음에 써보면 좋을듯
*/