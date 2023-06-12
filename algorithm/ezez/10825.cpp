#include <iostream>
#include <string>
#include <algorithm>
#define MAX 100000

using namespace std;

typedef struct{
  string name;
  int korean, english, math;
} student;

student st[MAX];

bool compare(student a, student b);

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;

  cin >> N;

  for(int i=0; i<N; i++)
    cin >> st[i].name >> st[i].korean >> st[i].english >> st[i].math;
  
  sort(st, st+N, compare);

  for(int i=0; i<N; i++)
    cout << st[i].name << '\n'; 

  return 0;
}

bool compare(student a, student b){
  if(a.korean != b.korean) return a.korean > b.korean;
  else if(a.english != b.english) return a.english < b.english;
  else if(a.math != b.math) return a.math > b.math;
  else return a.name < b.name;
}