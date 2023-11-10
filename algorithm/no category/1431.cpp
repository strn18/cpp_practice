#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

bool compare(string a, string b){
  int aSum = 0, bSum = 0;

  if(a.size() != b.size()) return a.size() < b.size();

  for(int i=0; i<a.size(); i++){
    if('0' <= a[i] && a[i] <= '9') aSum += a[i] - '0';
    if('0' <= b[i] && b[i] <= '9') bSum += b[i] - '0';
  }

  if(aSum != bSum) return aSum < bSum;
  else return a < b;
}

int main(){
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int N;
  vector<string> serials;

  cin >> N;

  for(int i=0; i<N; i++){
    string str;

    cin >> str;

    serials.push_back(str);
  }

  sort(serials.begin(), serials.end(), compare);

  for(int i=0; i<N; i++)
    cout << serials[i] << '\n';

  return 0;
}