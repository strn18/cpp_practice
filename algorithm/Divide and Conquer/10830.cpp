#include <iostream>
#include <vector>
#define MAX 5
#define MOD 1000

using namespace std;

int N;
vector<vector<int>> matrix;

vector<vector<int>> mat_pow(long long b);
vector<vector<int>> mat_mul(vector<vector<int>> a, vector<vector<int>> b);

int main(){
  int temp;
  long long B;

  scanf("%d %lld", &N, &B);
  for(int i=0; i<N; i++){
    vector<int> v;

    for(int j=0; j<N; j++){
      scanf("%d", &temp);
      v.push_back(temp % MOD);
    }

    matrix.push_back(v);
  }

  vector<vector<int>> result = mat_pow(B);

  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++)
      printf("%d ", result[i][j]);
    printf("\n");
  }

  return 0;
}

vector<vector<int>> mat_pow(long long b){
  if(b==1) return matrix;

  vector<vector<int>> half = mat_pow(b/2);

  if(b%2)
    return mat_mul(mat_mul(half, half), matrix);
  else
    return mat_mul(half, half);
}

vector<vector<int>> mat_mul(vector<vector<int>> a, vector<vector<int>> b){
  vector<vector<int>> result;

  for(int r=0; r<N; r++){
    vector<int> row;

     for(int i=0; i<N; i++){
      int count = 0;

      for(int j=0; j<N; j++)
        count += (a[r][j] * b[j][i]);

      row.push_back(count % MOD);
     }
    
    result.push_back(row);
  }

  return result;
}

/*
쫌 힘들었던 문제. 1629랑 거의 유사하지만, 그거는 어떠한 수의 거듭제곱이고, 이 문제는 어떠한 행렬의 거듭제곱이다. 그렇기에 전체적인 틀은
비슷하지만, 배열 곱셈(dot)을 수행해줘야 함.

우선 처음에는, b번 거듭제곱한 결과 행렬의 (r, c)칸의 값을 리턴하는, int형의 int mat_pow(int r, int c, long long b) 함수를 만들고, 이걸
이용해서 한 칸씩 구해주는 그런 방식을 써봤는데, 시간초과가 났다(첫번째 제출).

그래서 그냥 b번 거듭제곱한 결과 행렬 전체를 리턴값으로 가지는 함수로 풀어야겠다는 생각이 들었는데, 파이썬이면 그냥 리스트 리턴하면 되지만,
c++에서는 어떻게 하지? 하고 좀 고민하다가, https://leeeegun.tistory.com/3 여기랑
https://www.delftstack.com/ko/howto/cpp/how-to-return-a-vector-from-a-function-efficiently-in-cpp/ 여기 글을 보고, 2차원 벡터를
리턴값으로 갖는 함수를 만들기로 했다.

그래서 41행의 함수를 선언했다. 우선 b가 1이면 원본을 그대로 리턴한다. 만약 b가 짝수일 경우(48행), b/2번 제곱한 행렬인 half를 곱하여 리턴한다.
만약 b가 홀수일 경우, 거기에 +1제곱 더 해야하므로 원본을 한 번 더 곱해주고 리턴한다.

mat_mul은 행렬 곱셈을 담당하는 함수이다. 인자로 2차원 벡터인 a와 b를 받고, 0행 0열부터 N-1행 N-1열까지의 값을 하나하나 구하여 result에 넣고,
다 구하면 리턴한다. 이때, 2차원 벡터인 것에 유의하여, 매 행을 벡터에 저장하고(64행), 행을 다 만들었다면 result에 넣어준다(67행). 각 칸의 값을
구하는 방법은, 행렬 곱셈의 성질인, 'i행 j열 칸의 값 = a의 i행 * b의 j열' 을 이용하여 구해준다.

근데 제출했더니 두 번 틀렸는데, 하나는 B를 입력받을 때 %lld로 안 해서 그렇고, 하나는 B가 1이고, 행렬의 어떠한 칸에 1000이 들어오면, 그 행렬을
1제곱한 결과를 1000으로 나눈 나머지를 출력해야 하니깐 그 칸은 0이 되어야 하는데, 그 부분 처리를 안 해서 틀렸다. 그래서 애초에 입력받을 값을
1000으로 나눈 나머지를 matrix에 넣도록 바꾸니까 맞았다.

https://cocoon1787.tistory.com/293 이 풀이 보니까, 훨씬 간단하게 푼듯. B를 계속해서 나눠가면서, 즉 대량 logB번 동안 ans(처음에는 단위
행렬도 되어있음)에 A(원본 행렬, 내 코드에서는 matrix)를 곱해주고, A *= A를 해준다. 가령 B가 4라면, 처음에는 A *= A를 하니까 A는 A의 2제곱이
된다. 그 다음, B를 나눠주니 2가 되고, 이번엔 A는 A(원래 A라는 의미임)의 4제곱이 된다. 그 다음 B는 1이 되고, if문에 들어가면서 ans에 A를
곱해주니, ans는 A의 4제곱이 된다. 그 다음엔 B가 0이 되니 while문을 나오고, ans를 출력한다. 확실히 이 방식이 좀 깔끔해보임. 내 코드는 파이썬으로
했다면 더 편한 코드였던 것 같다.
*/