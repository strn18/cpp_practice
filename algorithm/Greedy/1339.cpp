#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

int alpha_used[26] = {0};

void update_alpha_used(string str);
bool Compare(int a, int b);

int main(){
  int N;
  int result = 0, n = 9;
  string str;
  
  scanf("%d", &N);

  for(int i=0; i<N; i++){
    cin >> str;
    update_alpha_used(str);
  }

  sort(alpha_used, alpha_used+26, Compare);

  for(int i=0; alpha_used[i]; i++)
    result += alpha_used[i]*(n--);

  printf("%d", result);

  return 0;  
}

void update_alpha_used(string str){
  for(int i=0; i<str.size(); i++){
    int cur = str[i]-'A';
    alpha_used[cur] += pow(10, (str.size()-1)-i);
  }
}

bool Compare(int a, int b){
  return a>b;
}

/*
어렵지 않았던 그리디 문제. alpha_used[i]는 i번째 알파벳(0based)이 자릿수에 따라 몇 번 쓰였는지 구한 값이다. 예를 들어, C가 백의 자리에 2번,
일의 자리에 3번 쓰였다면 alpha_used[2] = 203이 된다. 알파벳들에 대해 이 값을 모두 구한 다음, 값이 가장 큰 알파벳부터 9, 8, 7...을 부여한다.
그 다음, 부여된 수를 alpha_used 값에 곱하고 그 값을 모두 더하면 답이 된다.

처음에는 alpha_used[9][26] 이렇게 선언하고, C가 천의 자리에 3번 쓰였다면 alpha_used[3][2] = 3 이런 식으로, 각 자리마다 따로 세도록 나누는
방식을 생각했었다. 그 다음, 높은 자리부터 내려오면서 가장 많이 쓰인 알파벳에 9부터 부여하는 식으로 짤까 했었음. 근데 그렇게 하면 기본적으로
좀 복잡해서 계산이 쓸데없이 많아지고, 쓰인 횟수가 동일한 알파벳들이 있으면 그 밑의 자리도 보고 비교하는 식으로 해야하는데 어쨌든 너무 복잡함.
그래서 위의 방식으로 바꿨다. 
*/