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