#include <iostream>
#include <string>

using namespace std;

int main(){
  ios::sync_with_stdio(false);
  cin.tie(NULL);

  int M, S = 0;

  cin >> M;
  
  while(M--){
    string str;
    int x;

    cin >> str;
    
    if(str[1] == 'd'){
      cin >> x;
      S |= (1<<x);
    }
    else if(str[1] == 'e'){
      cin >> x;
      S &= ~(1<<x);
    }
    else if(str[1] == 'h'){
      cin >> x;
      cout << ((S & (1<<x)) ? 1 : 0) << '\n';
    }
    else if(str[1] == 'o'){
      cin >> x;
      S ^= (1<<x);
    }
    else if(str[1] == 'l')
      S = (1<<21)-1;
    else
      S = 0;
  }

  return 0;
}

/*
기본적인 비트마스킹 문제. 처음에는 S를 그냥 bool 타입 배열로 만들고 풀어도 되지 않나? 싶어서 그렇게 했는데, 그러면 all이나 empty 연산을 할 때,
20칸의 배열을 돌면서 true/false로 바꿔줘야 하는데, 이걸 M(최대 3백만)번 하게 되면, 총 6천만이다. 거기에, 입력받은 str이 어떤 명령인지 비교하는
연산까지 해버리게 되니까 시간초과가 나게 된다.

그래서 S를 비트마스킹 용도로 쓰는 변수로 바꾸고 풀었다. https://rebro.kr/63 여기를 많이 참고했는데,
add부터 순서대로 x 추가, x 제거, x 있는지 확인, x 토글, 모든 원소 추가, 모든 원소 제거 연산이다. 
그런데도 시간초과가 났는데, 아무리 봐도 비트마스킹 연산 부분에는 문제가 없어보여서, scanf나 cin, cout 등등을 하며 생긴 문제일 것이라고 판단해서,
싹다 scanf와 printf로 바꿔봤다(str 입력받는 것 빼고). 근데 여전히 시간초과가 나서, 그동안 다른 사람들 풀이에서 많이 봐왔던
ios::sync_with_stdio(false); 랑 cin.tie(NULL); 를 추가하고, scanf와 printf를 cin과 cout으로 모두 대체했다. 이후 제출하니 맞았음.

맞고 나서 https://donggoolosori.github.io/2020/09/24/boj-11723/ 여기 풀이를 보니까, 37행에서 S에 넣어주는 최댓값(1번째~20번째 비트가 모두
1인 값)을 굳이 2^21-1 로 구할 필요 없이, 그냥 (1<<21)-1 로도 구할 수 있었다.
*/