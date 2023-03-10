#include <iostream>
#include <string.h>
#define MAX 100
#define DEN 1000000000

using namespace std;

int dp[10][10][MAX+1][10];

int DP(int left, int right, int i, int j); // left~right 수를 쓰는, i자리이고 j로 시작하는 계단 수의 개수.

int main(){
  int N;
  long long count = 0;

  scanf("%d", &N);
  
  memset(dp, -1, 10*10*(MAX+1)*10*sizeof(int));
  
  for(int j=1; j<=9; j++)
    count += DP(0, 9, N, j);

  printf("%lld", count % DEN);

  return 0;
}

int DP(int left, int right, int i, int j){
  if(dp[left][right][i][j] != -1) return dp[left][right][i][j];

  
  if(right<left || (left==right && i>1) || right-left+1>i || j<left || right<j || i==0){
    dp[left][right][i][j] = 0;
    return dp[left][right][i][j];
  }
  else if(right-left+1==i){
    if(j==left || j==right) dp[left][right][i][j] = 1;
    else dp[left][right][i][j] = 0;
    return dp[left][right][i][j];
  }
  

  if(left<j && j<right){
    dp[left][right][i][j] = DP(left, right, i-1, j-1) + DP(left, right, i-1, j+1);
  }
  else if(j == left){
    dp[left][right][i][j] = DP(left+1, right, i-1, j+1) + DP(left, right, i-1, j+1);
  }
  else{
    dp[left][right][i][j] = DP(left, right-1, i-1, j-1) + DP(left, right, i-1, j-1);
  }

  dp[left][right][i][j] %= DEN;

  return dp[left][right][i][j];
}

/*
갱 장 히 어려웠던 dp문제.. 처음에 일단 답을 몇 개 구해보면서 점화식 & 연관성을 찾아보려했는데, N이 12만 되어도 복잡하고 길어서 구하기가 좀 힘듦.
그래서 수를 0~4만 쓴다고 가정하고, 길이가 5, 6, 7... 일 때 계단수를 구해보면서 점화식을 찾아보려했다.
찾아보니, 예를 들어 num[i][j]: 길이가 i이고, j로 시작하는 계단수(수를 0~4만 쓴다고 가정). 라고 하면, num[7][3]에 해당하는 수를 구하는 방법은
바로 num[6][2]와 num[6][4]에 해당하는 수의 앞에 3을 붙이는 것이다. 왜냐? 6자리이고 2로 시작하는 계단수가 있으면, 그 앞에 3을 붙이면 3으로 
시작하고 길이가 7인 계단수가 된다. 마찬가지로, 6자리이고 4로 시작하는 계단수가 있으면, 그 앞에 3을 붙이면 됨. 

근데 이게 끝이 아니었다. num[6][3]에 해당하는 수도 봐야했다. 그 수의 뒤에 다른 수를 붙이고 7자리로 만드는 것도 생각해야했음.

왜 그걸 해야하냐? 예를 들어, 다시 수를 0~9를 쓴다고 하고, num[11][9]를 생각해보자. 그거에 해당되는 수로 98765432101 이 있다. 
근데 만약 이걸 구할 때, 아까 말한 방법 1) num[i][j]를 구하려면 num[i-1][j-1]과 num[i-1][j+1]을 보고, 그 앞에 j를 붙인다. 이 방법만 쓴다면, 
98765432101 은 만들 수 없다. 왜냐면, 8765432101 을 보고 9를 붙인다는 건데, 8765432101 은 0~9를 모두 쓰지 않기에, num[i-1][j-1]이나 
num[i-1][j+1]에 없었을 것이다. 그렇기 때문에, 방법 2) num[i][j]를 구하려면 num[i-1][j]를 보고, 그 뒤에 수를 잘 붙인다(계단 수가 되도록). 도
써야한다. num[i-1][j] = num[10][9]에 해당하는, 9876543210 을 보고, 그 뒤에 1을 붙이게 되어 98765432101 를 만들 수 있게 되는 것이다.

근데 이 방법에는 문제가 있다. 1562 memo를 보면 알겠지만, 저 방법을 쓰면 계단 수를 모두 구할 수는 있으나 중복이 발생한다. 예를 들어, 
num[12][8]로 898765432101 가 있다고 치자. 얘는, 98765432101 의 앞에 8을 붙여서도 만들 수 있고, 89876543210 의 뒤에 1을 붙여서도 만들 수 있다.
즉, 방법 1)과 2)에서 중복이 생기는 것이다. 이걸 어떻게 해결할 수 있을까? 에 대해서 고민을 많이 했음.

근데 곰곰히 생각해보니, 방법 1)만 쓴다고 하면, 중복은 절대 안 생긴다. 근데 num[i][0]이나 num[i][9]는 방법 1)만 쓰면 모두 구할 수 없다. 왜냐?
67행에서 말했던 것처럼, 9를 붙이기 전까지는 0~9를 모두 쓰는 계단 수가 아니었는데, 앞에 9를 붙임으로써 계단 수가 되는 경우를 방법 1)을 통해서는
구할 수 없기 때문임. 0도 마찬가지(문제 답에는 0으로 시작하는 건 포함이 안 되지만 내가 쓰는 풀이 방식에서는 필요하니까 걍 포함함).
근데, 0과 9 말고, 1~8은? 걔들도 방법 1)만 썼을 때 모두 구할 수 없나? 그건 아님. 왜냐? n이 1~8일 때, n을 앞에 붙이기 전까지는 0~9를 모두 쓰지 
않았는데, 앞에 붙임으로써 0~9를 쓰게 된다? 그 말인즉슨 n을 앞에 붙이기 전까지는 0~9에서 n만 안 썼다 이거임. 근데 그럴 수가 있냐?
가령 n이 3이면 3만 빼고 다 썼다 이건데, 0 1 2랑 4 5 6 7 8 9는 썼는데 3은 안 썼다? 그건 계단 수가 아니다. 즉 n이 1~8일 때 그건 말이 안 됨.
그건 무슨 뜻? num[i][j]에서 j가 1~8일 때는 방법 1)만 써도 모두 구할 수 있다 이거임. 그건 곧, 중복이 안 생긴다는 거다.
다시 말해, num[i][j]에서 j가 1~8이면, num[i][j]는 num[i-1][j-1]과 num[i-1][j+1]의 앞에 j를 붙인 것들이다.
dp[i][j]를 i자리이고, j로 시작하며, 0~9를 모두 쓰는 계단 수의 개수. 라고 정의하면, dp[i][j] = dp[i-1][j-1] + dp[i-1][j+1] 이 된다는 것임.

이제 1~8은 해결됐고, 0 or 9일 때만 해결하면 된다. 이걸 설명하기 위해, 아까 말했던, num[11][9]로 있는 98765432101 얘를 보자. 얘는 어디서
튀어나왔을까? 위에서 설명했다시피, 방법 1)로는 구할 수 없었으니까 다른 방식으로 구해야한다. 얘는, 9을 붙이기 전까지는 0~9를 쓰지 않다가
(9만 빼고 쓰다가) 9를 붙임으로써 0~9를 쓰게 되었기에 num에 추가되는 놈이다. 그 말은, 9를 붙이기 전까지는 0~8만 쓰는 계단 수였다 이거임.
num[11][0]을 볼까? num[11][0]에는 01234567898 얘가 있음. 얘도 마찬가지로, 0을 붙이기 전까지는 1~9로만 이루어진 계단 수였음.
두 경우를 보면 알 수 있다시피, j는 0 or 9일 때, 방법 1)로 구할 수 없었던 계단 수들은, 각각 1~9 or 0~8로만 이루어진 계단 수의 앞에 0 or 9를
붙임으로써 구할 수 있다. 즉, 가령 num2[i][j]: 1~9로만 이루어진 계단 수, num3[i][j]: 0~8로만 이루어진 계단 수. 라고 하면, 
j가 0일 때는 num2[10][1]의 앞에 0을 붙임으로써 구할 수 있고, j가 9일 때는 num3[10][8]의 앞에 9를 붙임으로써 구할 수 있는 거임.

이제 일반화 ㄱㄱ. dp[left][right][i][j]: i자리이고 j로 시작하는, left~right로 이루어진 계단 수의 개수. 라고 하자.
j가 1~8일 때는 쉬움. 85행에서 말한 거에서 left랑 right만 추가하면 되는 것임.
dp[left][right][i][j] = dp[left][right][i-1][j-1] + dp[left][right][i-1][j+1]. 이거다. 
그렇다면 j가 0일 때는? 우선 방법 1)로 구할 수 있는 애들은, dp[0][9][i-1][j+1] 이걸로 구할 수 있음. 그렇다면, 방법 1)로 구할 수 없던
애들은? 1~9를 쓰는 계단 수에서 구한댔으니까, dp[1][9][i-1][1] 이거겠지? 이걸 일반화하면 dp[1][9][i-1][j+1] 이게 될 거고.
그렇다면 j가 9일 때는? 마찬가지로 구해보면, dp[0][9][i-1][j-1] 이거랑, dp[0][8][i-1][j-1] 이걸로 구할 수 있다.
정리해보자. j가 0일 때: dp[left][right][i][j] = dp[0][9][i-1][j+1] + dp[1][9][i-1][1].
j가 9일 때: dp[left][right][i][j] = dp[0][9][i-1][j-1] + dp[0][8][i-1][j-1].

조금만 더 일반화해보자. j가 0일 때를 구한 이유는, dp[left][right][i][j]를 구할 때, 0 == left(왼쪽 끝 수)이기 때문임. j가 9일 때는
9 == right(오른쪽 끝 수)이기 때문이고. 그렇다면, 이렇게 일반화할 수 있겠다.
j == left: dp[left][right][i][j] = dp[left+1][right][i-1][j+1] + dp[left][right][i-1][j+1];
j == right: dp[left][right][i][j] = dp[left][right-1][i-1][j-1] + dp[left][right][i-1][j-1];

요거를 DP 함수에 넣으면 끝임. 근데 좀 문제가 남았음. 바로 base condition 처리. 32행부터 40행 부분인데, 뭔가 깔끔하게 처리하기는 어려워
보여서, 그냥 dp값이 0 or 1이 나오는 경우를 다 생각해서 조건문으로 넣었다. 
우선 right보다 left가 커질 때 당연히 0이다. 그리고 left==right인데, i가 2 이상이면, 써야하는 수는 단 하나인데 채워야하는 자릿수는 
2 이상이 된다. 이것도 말이 안 되니 당연히 0. 그리고 right-left+1은 써야하는 수의 개수인데, 그 개수가 자릿수보다 많다면? 자릿수를 다 
채워도 수를 다 쓸 수 없다. 그러므로 0. 그리고 j로 시작할텐데, 그 j가 left보다 작거나 right보다 크다면? 역시 말이 안 되니 0.
마지막으로 i가 0이라면, 자릿수가 0일 때니까 당연히 0이다. 이상이 dp값이 0일 때의 base condition이었다.

그리고, 만약 써야하는 수의 개수(=right-left+1)가 i와 같다면? left부터 right까지 1씩 증가하는 오르막수 or right부터 left까지 1씩 감소하는
내리막수일 것임. 만약 j가 left라면, j부터 시작하는 오르막수 단 하나만 가능하고, j가 right라면 내리막수만 가능. 그러므로 dp값은 1이다.
만약 j가 둘 다 아니면? 말이 안 되므로 dp값은 0이 된다.

여기까지가 base condition의 끝인데, 이 부분이 좀 부족해서 처음 제출할 때 out of boundary가 났다. 아마 base condition에 안 걸리는 바람에
인덱스가 음수일 때까지 내려가버린듯. 그 부분 수정하고 제출하니 맞았다(두번째 제출은 23행에서 DEN로 나머지 연산 안 쳐서 틀림 ㅋ).

좀 어렵지만 메모 보면 이해갈 것..
*/