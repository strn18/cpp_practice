#include <iostream>
#include <algorithm>

using namespace std;

int L, C;
char targets[15]; // C가지 문자들
char guess[15]; // targets에서 고른 L개 문자들

void choose(int start, int n); // targets에서 총 L개를 고르는데, targets의 start 인덱스부터 시작하고 현재 n번째(1base) 고를 차례
bool possible(void); // 고른 guess가 모음 한 개, 자음 두 개 이상인지 확인

int main(){
  scanf("%d %d", &L, &C);

  getchar();
  for(int i=0; i<C; i++){
    scanf("%c", &targets[i]);
    getchar();
  }

  sort(targets, targets+C);

  choose(0, 1);

  return 0;
}

void choose(int start, int n){
  for(int i=start; i<C; i++){
    guess[n-1] = targets[i];

    if(n!=L){
      choose(i+1, n+1);
    }
    else{
      if(possible()){
        for(int i=0; i<L; i++)
          printf("%c", guess[i]);
        printf("\n");
      }
    }
  }
}

bool possible(void){
  int vowels=0, consonants=0; // 모음, 자음 개수
  for(int i=0; i<L; i++){
    if(guess[i]=='a'||guess[i]=='e'||guess[i]=='i'||guess[i]=='o'||guess[i]=='u')
      vowels++;
    else
      consonants++;
    
    if(vowels>=1 && consonants>=2)
      return true;
  }
  return false;
}

/*
별로 안 어려웠던 백트래킹 문제. 그냥 주어진 알파벳들을 오름차순 정렬 후 그 중 L개를 고르는 조합을 모두 찾은 다음, 조합이 모음 1개 이상
자음 2개 이상일 때 출력하면 되는 문제였다. 다만 남의 풀이 보는 과정에서, cin은 scanf와 다르게 공백을 받지 않는다는 것을 확인했다.
즉 main 함수에서 귀찮게 getchar 쓸 필요 없이 그냥 cin 쓰면 되었던 것임. 
*/