#include <iostream>
#define ll long long

using namespace std;

int main(){
  ll N, count = 0;
  ll num[6], min_num[3];

  scanf("%d", &N);

  min_num[0] = 51;
  for(int i=0; i<6; i++){
    scanf("%lld", &num[i]);
    min_num[0] = min(min_num[0], num[i]);
  }
  
  if(N==1){
    ll max_num = 0;
    for(int i=0; i<6; i++){
      count += num[i];
      max_num = max(max_num, num[i]);
    }
    count -= max_num;
  }
  else{
    int a = min(num[0], num[5]);
    int b = min(num[1], num[4]);
    int c = min(num[2], num[3]);
    min_num[1] = min(min(a+b, a+c), b+c);
    min_num[2] = a+b+c;

    count += (min_num[0]*(N-2)*(N-2)*5);
    count += (min_num[1]*(N-2)*8 + min_num[0]*(N-2)*4);
    count += (min_num[2]*4 + min_num[1]*4);
  }

  printf("%lld", count);

  return 0;
}

/*
복잡해보이지만, 그냥 규칙 찾으면 간단히 나오는 그리디 문제.

우선 N=1이라면, 그냥 여섯 면 중에서 숫자가 제일 큰 면만 빼고 다 더하면 된다.

그렇지 않다면, 규칙성이 있음. 주사위의 한 면만 보이는 주사위들(N*N*N 정육면체에서, 각 면의 모서리를 제외한 가운데 부분)이 있고, 두 면만 보이는
주사위들(모서리 부분)이 있고, 세 면만 보이는 주사위들(꼭짓점 부분)이 있다. 이때, 보여지는 두 면이나 세 면은 주사위에서 서로 인접한 면들이다. 즉, 
주어진 주사위 그림에서, (A, F), (B, E), (C, D) 이렇게 마주보는 면과 짝을 이루는데, 서로 인접한 두 면 or 세 면이 보이므로, 같은 짝에서 두 면이
보여질 수 없다(같은 짝이라는 건 마주본다는 소린데, 그러면 인접할 수 없기 때문). 그말은? 각 짝에서 하나씩 골라, 총 둘 or 셋이 보여지는 것임.
이때 그 값들이 최소가 되어야 한다. 각 짝에서 더 값이 적은 애들을 각각 골라서 총 셋이 나오면, 걔네들 중 합이 작은 둘 or 셋(이거는 그냥 다 더하는
거겠지)을 고르면 되는 것이다. 한 면만 보여지는 건? 그냥 제일 작은 애를 고르면 되겠지.

하여튼 이걸 N*N*N 일 때 하나하나 세보면, 우선 한 면만 보이는 부분(가운데 부분)은, N*N*N(걍 정육면체라고 부르겠다)의 한 면에 (N-2)(N-2)개가 
들어있는데, 정육면체의 다섯 면이 보이므로 *5를 해주면 된다(33행).

두 면만 보이는 부분(모서리)은, 한 묶음(모서리 하나 당)에 (N-2)개가 들어있는데, 이게 총 12개(정육면체의 모서리는 12개니깐) 있다. 근데 중요한 건,
정육면체의 밑면의 모서리 4개는 바닥에 닿아서 반만 보인다. 즉 걔네들은 두 면이 아니라 한 면이 보이는 것임. 그래서 결국, 두 면 보이는 애들은 8개,
한 면 보이는 애들은 4개이다(34행).

세 면(꼭짓점)은? 8개이다. 근데 마찬가지로 밑의 4개는 가려져서 주사위의 한 면이 안 보이니까, 걔네들은 세 면이 아니라 두 면만 보이는 것임.
그렇기에, 세 면 보이는 애들은 4개, 두 면은 4개이다(35행).

long long을 써야함에 유의해서 다 더해주면 된다.
*/