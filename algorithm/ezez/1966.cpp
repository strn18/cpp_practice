#include <iostream>
#include <queue>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  
  int T;

  cin >> T;

  while(T--){
    int N, M, count = 0;
    int highest_imp = 9, imp_count[10] = {0};
    queue<pair<int, bool>> printer;

    cin >> N >> M;

    for(int i=0; i<N; i++){
      int imp;

      cin >> imp;
      imp_count[imp]++;
      printer.push({imp, (i==M ? true : false)});
    }

    while(true){
      while(imp_count[highest_imp] == 0)
        highest_imp--;
      
      if(printer.front().first == highest_imp){
        count++;
        imp_count[highest_imp]--;
        if(printer.front().second)
          break;
      }
      else
        printer.push(printer.front());

      printer.pop();
    }

    cout << count << '\n';
  }

  return 0;
}

/*
쪼금 헷갈렸던 큐 문제. 우선순위 큐를 사용하면 좀 더 쉽게 풀 수 있는듯. 
*/