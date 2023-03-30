#include <iostream>
#include <string>
#define MAX 40

using namespace std;

int messi_len[MAX+1];
string MESSI = " Messi";
string GIMOSSI = " Gimossi";

void find_messi(int n, int m);

int main(){
  int M, N;

  messi_len[0] = 7;
  messi_len[1] = 5;
  for(int i=2; i<=MAX; i++)
    messi_len[i] = messi_len[i-1]+1+messi_len[i-2];

  scanf("%d", &M);
  
  for(int i=1; i<=MAX; i++){
    if(messi_len[i] >= M){
      N = i;
      break;
    }
  }

  find_messi(N, M);

  return 0;
}

void find_messi(int n, int m){
  if(n<=1){
    printf("%c", (n==1 ? MESSI[m] : GIMOSSI[m]));
    return;
  }

  if(m <= messi_len[n-1])
    find_messi(n-1, m);
  else if(m == messi_len[n-1]+1)
    printf("Messi Messi Gimossi");
  else
    find_messi(n-2, m-(messi_len[n-1]+1));
}

/*
어렵지 않았던 분할정복 + dp 문제. messi 문자열에서 M번째 글자를 찾아내면 된다.

주어진 M번째 글자가 처음으로 포함되는 메시의 외침을 messi(N)이라고 할 때, 우선 이 N을 찾는다. 이를 위해, 각 messi(i)의 길이를 계산하여,
이를 messi_len에 넣었다. 이때 messi(0)은 Gimossi 라고 가정하고, messi_len[0]을 7이라고 잡았는데, 이렇게 한 이유는 이따가 설명.
어쨌든 이걸 바텀업으로 다 값을 채워준다음, N을 찾는다(23행).

그 다음, 분할정복 해주는 find_messi 함수를 쓴다. 얘는 messi(n)의 m번째 글자를 찾아 출력한다. 그렇기에, 왼쪽 부분(41행)인지, 가운데 공백
(43행)인지, 오른쪽 부분(45행)인지 찾아서 재귀쳐준다(공백이면 바로 출력). 기저 조건은? n이 1 or 0일 때이다. n이 1이라면 Messi 문자열에서
m번째 글자(이때 m은 1base라고 가정. 이를 위해 string MESSI 얘의 첫 칸은 공백으로 넣었음)를 출력하고, 0이면 마찬가지로 Gimossi에서 m번째를
찾아 출력한다. 이렇게 해야, n이 2일 때 m번째 글자가 Messi와 Gimossi 사이 공백인지 아닌지 귀찮게 찾는 과정이 없어진다. 즉, messi(2)는
messi(1)+' '+messi(0)이라고 생각한 것.
*/