#include <iostream>
#define ll long long

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;

  while(cin >> n){
    ll target = 1;
    int digits = 1;

    while(target % n){
      target *= 10;
      target++;
      digits++;

      target %= n;
    }

    cout << digits << '\n';
  }

  return 0;
}

/*
좀 많이 헤메다가 https://nanyoungkim.tistory.com/115 여기 참고하고 푼 문제. 
21행을 안 하고, 그냥 1 11 111 이렇게 늘리면서 나머지 연산 했을 때 0인지를 체크한다면 long long의 범위를 벗어나게 됨. 
그래서 어떻게 푸는거지 하고 ㅈㄴ 고민하다가 모르겠어서 위의 링크를 참고함. 근데 코드는 맞는데 설명은 좀 애매한 것 같아서 부가 설명함. 
어떠한 수 m이 있다고 하자. 이때, (10*m + 1) % n == (10*(m % n)) + 1 % n 이다. 즉, 1 11 111 이렇게 늘릴 때, 그냥 무지성으로 늘리지 
말고, 늘린 다음 n으로 나머지 연산을 해주면, 오버플로우 없이 풀 수 있음. 
왜 저렇게 되냐면, 가령 11을 3으로 나머지 연산을 해본다 치자. 11 중에서 9는 3으로 나눠지고, 2는 안 나눠지는 부분임. 
얘한테 10을 곱하고 1을 더한다고 하자. 근데 11 전체에 하지 말고 9와 2에 대해 따로 한다고 생각해보자. 
그러면, 9는 10을 곱해도 여전히 3으로 나눠지는 게 당연함. 그러므로, (11*10 + 1) % 3은 그냥 (2*10 + 1) % 3 이 부분만 보면 되는 것임. 
*/