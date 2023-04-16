#include <iostream>
#include <algorithm>
#define MAX 2000

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, count = 0;
  int num[MAX];

  cin >> N;
  for(int i=0; i<N; i++)
    cin >> num[i];

  sort(num, num+N);

  for(int i=0; i<N; i++){
    int s = (i==0 ? 1 : 0), e = (i==N-1 ? N-2 : N-1);

    while(s < e){
      int sum = num[s] + num[e];

      if(sum == num[i]){
        count++;
        break;
      }
      else if(sum < num[i]){
        if(++s == i) s++;
      }
      else{
        if(--e == i) e--;
      }
    }
  }

  cout << count;

  return 0;
}

/*
쉬웠지만 끝에서 좀 헷갈렸던 투 포인터 문제.

처음에는 주어지는 수가 모두 자연수인 줄 알고, 그냥 오름차순 정렬한 다음에 이번에 볼 수가 i번째라면, i번째 수는 0 ~ i-1번째 수들로만 만들 수
있으니까, 그 안에서만 투 포인터 탐색을 해주었다. 근데 문제를 잘 읽어보니 음수랑 0도 주어질 수 있었음.

그래서 좀 바꿨다. 0 ~ i-1 구간만 탐색하는 것이 아니라, 0 ~ N-1 구간을 전부 해준다. 이때, 고르는 두 수(num[s] or num[e]) 중에 num[i]가
있으면 안 되므로, 30행과 33행에서 s++ or e--로 s와 e를 갱신해줄 때, 그 값이 i와 같아졌다면 다시 한 번 해줬다(i를 그냥 패스하도록).

그리고 21행에서, 그냥 s = 0, e = N-1로 하면 i가 0 or N-1일 때, s or e가 i와 같아진다. 그래서 그 때는 s나 e에 1이랑 N-2를 넣어서, 마찬가지로
i를 패스하도록 하였다.

https://imnotabear.tistory.com/382 여기 풀이를 보니깐, 나처럼 s나 e값을 갱신할 때 i와 같아지면 패스하는 방식이 아니라, sum == num[i]일 때
그걸 체크해주는 방식이다. 그때 s나 e가 i와 같을 경우 s++ or e--를 쳐주고, i와 다를 경우는 마찬가지로 count++ 하고 break 해주면 된다.
*/