#include <iostream>
#define MAX 500000

using namespace std;

int S[MAX+1] = {0}, J[MAX+1] = {0};

int main(){
  int N, H;

  scanf("%d %d", &N, &H);

  for(int i=1; i<=N; i++){
    int obs_h;

    scanf("%d", &obs_h);

    if(i%2) S[obs_h]++;
    else J[H+1-obs_h]++;
  }

  for(int h=H-1; h>=1; h--)
    S[h] += S[h+1];

  for(int h=2; h<=H; h++)
    J[h] += J[h-1];

  int min_obs = N+1, count = 0;

  for(int h=1; h<=H; h++){
    int obs = S[h]+J[h];

    if(obs < min_obs){
      min_obs = obs;
      count = 1;
    }
    else if(obs == min_obs)
      count++;
  }

  printf("%d %d", min_obs, count);

  return 0;
}