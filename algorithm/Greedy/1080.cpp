#include <iostream>

using namespace std;

int A[50][50], B[50][50];

void change(int r, int c);

int main(){
  int N, M, count = 0;
  string temp;
  
  scanf("%d %d", &N, &M);

  for(int i=0; i<N; i++){
    cin >> temp;
    for(int j=0; j<M; j++){
      A[i][j] = temp[j] - '0';
    }
  }

  for(int i=0; i<N; i++){
    cin >> temp;
    for(int j=0; j<M; j++){
      B[i][j] = temp[j] - '0';
    }
  }

  for(int i=0; i<N; i++){
    for(int j=0; j<M; j++){
      if(A[i][j] != B[i][j]){
        if(i>N-3 || j>M-3){
          printf("-1");
          return 0;
        }
        else{
          change(i, j);
          count++;
        }
      }
    }
  }

  printf("%d", count);
  return 0;
}

void change(int r, int c){
  for(int i=r; i<r+3; i++){
    for(int j=c; j<c+3; j++){
      A[i][j] = A[i][j] ^ 1;
    }
  }
}

/*
쉬웠던 그리디 문제. 배열 A의 (0, 0)부터 시작해서, (N-1, M-1)로 내려가면서 어떠한 칸이 배열 B의 칸과 다르다면, change를 수행해주면 된다.
change는 문제에 주어진 행렬 변환 연산으로, 해당 칸을 좌상단으로 삼아서 3*3칸의 원소를 뒤집는다. 이때, 배열 B와 다른 그 칸이 (i, j)일 때,
i>N-3이거나 j>M-3이라면, 아래쪽이나 오른쪽으로 남은 칸이 3칸 미만이라 change를 수행해줄 수 없다. 그렇기에, A를 B로 바꿀 수 없는 거니까
-1을 출력한다.

https://guiyum.tistory.com/48 쉬운 문제였지만, 여기 코드 보면서 한 가지 배웠음. 그동안 숫자로 된 데이터가 띄어쓰기 없이 주어질 경우,
숫자 하나하나 따로 받아야하니까 char형으로 받은 다음 int로 바꿔서 저장하거나, 이번 코드에서처럼 string으로 받아서 한 칸씩 읽어서 저장하는
식으로 했다. 근데 여기 코드 보니깐, scanf("%1d", &a[i][j]) 이런 식으로 해서, 숫자를 하나씩 받는 걸 봄. 
https://modoocode.com/36 여기를 참고해보니, %1d 이렇게 하면 숫자를 무조건 하나씩 받고, %3d 면 세 개씩 받고.. 하는 방식인듯.
*/