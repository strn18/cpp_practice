#include <iostream>
#include <queue>

using namespace std;

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N, myVotes, count = 0;
  priority_queue<int> others;

  cin >> N >> myVotes;

  others.push(0);

  while(--N){
    int other;
    cin >> other;
    others.push(other);
  }

  while(myVotes <= others.top()){
    others.push(others.top() - 1);
    others.pop();
    myVotes++;
    count++;
  }
  
  cout << count;

  return 0;
}