#include <iostream>
#include <cmath>
#define MAX 20

using namespace std;

long long filled = 0; // 채운 총 부피. 이 값이 L*W*H와 같아야 상자를 다 채운 것.
int cube_count = 0;
int cube[MAX];

void fill_box(long long L, long long W, long long H);

int main(){  
  long long L, W, H;
  int N;

  scanf("%lld %lld %lld %d", &L, &W, &H, &N);
  
  for(int i=0; i<N; i++){
    int A, B;
    scanf("%d %d", &A, &B);
    cube[A] = B;
  }

  fill_box(L, W, H);
  
  printf("%d", (filled == (L*W*H) ? cube_count : -1));

  return 0;
}

void fill_box(long long L, long long W, long long H){
  if(!L || !W || !H) return;

  for(int i=MAX-1; i>=0; i--){
    if(cube[i]){
      long long edge = pow(2, i);

      if(edge > L || edge > W || edge > H) continue;

      long long L_use = L/edge, W_use = W/edge;
      long long max_use = L_use * W_use;
      int L_mod = L%edge, W_mod = W%edge;      

      if(cube[i] >= max_use){
        filled += max_use * (edge*edge*edge);
        cube_count += max_use;
        cube[i] -= max_use;
      }
      else{
        int cubes = cube[i];
        filled += cube[i] * (edge*edge*edge);
        cube_count += cube[i];
        cube[i] = 0;

        fill_box(edge, (W_use-(cubes%W_use))*edge, edge);
        fill_box((L_use-(cubes/W_use + 1))*edge, W_use*edge, edge);
      }

      fill_box(L_mod, W, edge);
      fill_box(L-L_mod, W_mod, edge);

      fill_box(L, W, H-edge);

      return;
    }
  }
}

/*
좀 복잡했던 분할 정복 문제.

우선 문제를 보면 상자를 어떻게 채워야하는지 감이 안 오지만, 잘 생각해보면 그리디로 접근하면 된다.
즉, 어떠한 크기의 상자를 채울 때, 우선 가장 크기가 큰 큐브부터 최대로 쓰고, 그 다음으로 큰 큐브를 쓰고... 를 반복하면 된다.
왜냐? 큐브의 크기가 배수 관계이기 때문이다. 즉, 문제에서 각 큐브의 변의 길이는 반드시 2의 제곱꼴이라 했기 때문에, 두 큐브 A와 B가
있을 때, A가 B보다 크면, A의 변의 길이는 반드시 B의 변의 길이의 x배이다. 그렇기 때문에 위의 그리디 방식으로 접근해도 답을 구할 수 있다.

여기까지 알아낸 상황에서, 풀이 방식 떠올리기 자체는 어렵지 않았음. 우선 크기가 큰 큐브부터 돌면서, 쓸 수 있는 만큼 최대로 쓰고, 다 썼거나
더 이상 쓸 수 없다면 다음 큐브로 넘어간다. 이를 위해, (L*W*H)크기의 상자를 채우는 함수인 fill_box 함수를 정의했다. 근데 이때, 쓰고 남은
칸에 대해서 다시 재귀적으로 fill_box를 쳐줘야하는데, 쓰고 남는 공간을 계산해줄 때 좀 더 편하게 하기 위해서, 어떠한 큐브를 쓸 때 한 층에
대해서만 쓰고, 나머지는 바로 fill_box를 쳐주기로 함. 뭔소리냐? 가령 8*6*12 상자가 있고, 변의 길이가 4인 큐브를 쓴다고 했을 때, 우선 그 큐브
기준 한 층, 즉 높이 4인 공간, 다시 말해 8*6*4의 공간에 대해서 최대한 그 큐브를 써주고, 나머지 8*6*8의 공간은 다시 fill_box에 인자로 줘서
재귀 친다는 소리임. 왜 이렇게 하냐? 큐브 쓸만큼 쓰고 남는 공간 따져야 하는데, 높이까지 한 번에 따지면 귀찮을 것 같아서 그랬다. 방금 말한,
남는 공간 재귀치는 부분은 63행에 있다.

여기까지 왔다면, 이제 남은 부분은 '선택한 큐브'를 '한 층'에 대해서 최대한 많이 써줘야 한다. 즉 위의 예시로 따지면, 변의 길이가 4인 큐브를
8*6*4의 공간에 최대한 많이 써줘야 함. 이걸 구하기 위해서, 우선 그 큐브를 최대 몇 번 쓸 수 있는지 구해야 한다. 이건 간단한데, 가로 세로
길이를 큐브의 변의 길이로 나눈 몫을 각각 곱해주면 된다(max_use). 근데, 그러고나서 남은 나머지(자투리) 공간에 대해서도 다시 fill_box를
쳐줘야 한다. 그 부분은 60, 61행에 있다. 이 부분 한 번 빼먹었었다(상자의 변의 길이도 2의 제곱꼴인 줄 알았음).

이제 남은 건, 큐브를 L_use * W_use 넣을 수 있는 공간에 최대한 많이 넣어야 한다. 만약 큐브의 개수가 max_use 이상이라면? 그냥 다 넣으면
된다. 45행인데, 지금까지 채운 부피 갱신해주고, 사용한 큐브 개수 갱신해주고, 남은 큐브 개수 갱신해주면 된다. 

근데 만약 max_use보다 적다면? 조금 복잡해짐. 이건 1493.png에 그려놨다. 대충 설명하자면, 우선 쓸 수 있는 큐브를 써준다(빨간 부분).
그 다음, 남은 두 부분(파랑, 초록)의 크기를 각각 계산해서 fill_box에 넣어준다. 좀 복잡하지만 그래도 나머지, 몫 연산 잘 구해주면 된다.

처음에는 이렇게 안 하고, 쓸 수 있는 큐브를 써주고 남은 공간을 for문으로 max_use-cube[i]번 반복해서 fill_box(edge, edge, edge)를 해줬다.
근데 이렇게 하니깐 틀렸음. 아마 max_use가 최대 1조(상자 가로 세로 길이는 각각 최대 100만이니깐) 정도라서, 시간이 너무 오래 걸린듯. 근데 시간
초과가 안 나고 틀렸다고 뜬 이유는 자세히는 모르겠다. 사실 첫 번째 제출에서 틀리고 나서, 아마 변수들이 오버플로우가 났나보다 해서 long long으로
고쳐줬는데, 또 틀려서 왜 틀리지? 하면서 찾다가, 위의 시간 너무 오래 걸리는 이슈 찾아서 고친 게 세 번째 제출이었음.

하여튼 그렇게 하면 너무 비효울적이니까, 남은 공간을 두 부분(파랑, 초록)으로 나눠서 fill_box를 쳐준다(56, 57행). 
*/