#include <iostream>
#include <cmath>
#define MAX 20

using namespace std;

long long filled = 0; // 채운 총 부피. 이 값이 L*W*H와 같아야 상자를 다 채운 것.
int cube_count = 0;
int cube[MAX];

void fill_box(long long L, long long W, long long H);

int main(){  
  long long L, W, H;
  int N;

  scanf("%lld %lld %lld %d", &L, &W, &H, &N);
  
  for(int i=0; i<N; i++){
    int A, B;
    scanf("%d %d", &A, &B);
    cube[A] = B;
  }

  fill_box(L, W, H);
  
  printf("%d", (filled == (L*W*H) ? cube_count : -1));

  return 0;
}

void fill_box(long long L, long long W, long long H){
  if(!L || !W || !H) return;

  for(int i=MAX-1; i>=0; i--){
    if(cube[i]){
      long long edge = pow(2, i);

      if(edge > L || edge > W || edge > H) continue;

      long long L_use = L/edge, W_use = W/edge;
      long long max_use = L_use * W_use;
      int L_mod = L%edge, W_mod = W%edge;      

      if(cube[i] >= max_use){
        filled += max_use * (edge*edge*edge);
        cube_count += max_use;
        cube[i] -= max_use;
      }
      else{
        int cubes = cube[i];
        filled += cube[i] * (edge*edge*edge);
        cube_count += cube[i];
        cube[i] = 0;

        fill_box(edge, (W_use-(cubes%W_use))*edge, edge);
        fill_box((L_use-(cubes/W_use + 1))*edge, W_use*edge, edge);
      }

      fill_box(L_mod, W, edge);
      fill_box(L-L_mod, W_mod, edge);

      fill_box(L, W, H-edge);

      return;
    }
  }
}