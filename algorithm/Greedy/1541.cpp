#include <iostream>

using namespace std;

int Sum(int num[], int start, int end){ // num[start]부터 num[end]까지 더해서 리턴
  int count = 0;
  for(int i=start; i<=end; i++)
    count += num[i];
  return count;
}

int main(){
  int len = 0, count = 0, idx = 0; // 숫자의 개수, 식의 값, 판단할 숫자의 인덱스
  int num[50];
  char op[50];

  while(1){
    scanf("%d", &num[len]);
    scanf("%c", &op[len]);
    if(op[len++] == '\n') // 입력이 끝나면 리턴
      break;
  }

  count += num[0]; // 우선 첫번째 수는 무조건 더하고 인덱스 증가
  idx++;

  while(idx<len){
    if(op[idx-1] == '+'){ // 이번 숫자의 앞에 있는 연산자가 +라면 더하면 됨
      count += num[idx];
      idx++;
    }
    else{ // 만약 -라면, +로 연결되어있는 수를 모두 더해서 빼주면 됨
      int start = idx; // count에서 빼줄 첫 수(이번 숫자)의 인덱스 저장
      while(1){
        if(op[idx] == '-' || op[idx] == '\n') // 만약 -나 식의 끝에 도달하면 break
          break;
        idx++; // 그렇지 않고 +라면 idx를 증가시켜줌
      }
      count -= Sum(num, start, idx); // start부터 idx(-나 식의 끝에 도달하기 전 숫자의 인덱스)까지를 모두 합해 count에서 빼주기
      idx++;
    }
  }

  printf("%d", count);
  
  return 0;  
}

/*
어떻게 푸는지는 쉽게 알았는데 구현이 좀 ㅈ같았던 문제.. 푸는 방법은 그냥 식의 처음부터 쭉 훑으면서, +가 나오면 그 다음 수를 더해주고
-가 나오면 -나 개행(식의 끝)이 나올 때까지 그 다음 수를 계속 빼주면 된다. 이거 그냥 반복하면 되는데, c++로 구현하기가 좀 까다로웠다.

나는 우선 수와 연산자(또는 개행)을 따로 입력받았다. 그 다음, '어떠한 수'를 더할지 뺄지는 그 수보다 1 작은 인덱스를 가진 연산자(그 수 앞에
있는 연산자)를 보고 판단한다. 만약 앞의 연산자가 +라면 그냥 더해주면 된다. 만약 -라면, -나 개행을 찾을 때까지 계속 인덱스를 증가시키다가,
찾으면 '어떠한 수'부터 방금 찾은 -나 개행 앞에 있는 수까지 싹 다 더한 다음 그걸 (결과값인 count에서)빼주면 된다. 

근데 다 풀고나서 다른 풀이 보면서 안건데, 그냥 파이썬으로 split쓰면서 쓰는게 훨씬 편한듯. 처음에는 파이썬에서 +랑 -를 둘 다 구분자로 써서
식을 split해야하나? 생각하면서 에이 귀찮아 그냥 c++로 풀어야지 하고 풀었는데, 그냥 -만 구분자로 사용한 다음, 구분된 리스트의 첫 번째 원소
(처음 수)에서 나머지 원소 다 빼주면 된다.. 그래서 파이썬으로 한 번 풀어봄
*/