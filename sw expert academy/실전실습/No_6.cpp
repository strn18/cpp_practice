// 17695. [Pro] 뉴스알림
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef struct{
  int sendTime, newsID, channelID;
} newsInfo;

unordered_map<int, vector<int>> registeredUser;

unordered_map<int, vector<newsInfo>> receivedNews;

struct compare{
  bool operator()(newsInfo a, newsInfo b){
    if(a.sendTime != b.sendTime) return a.sendTime > b.sendTime;
    else return a.newsID > b.newsID;
  }
};
priority_queue<newsInfo, vector<newsInfo>, compare> newsPQ;

unordered_set<int> validNews;

void init(int N, int K)
{
  registeredUser = unordered_map<int, vector<int>>();
  receivedNews = unordered_map<int, vector<newsInfo>>();
  newsPQ = priority_queue<newsInfo, vector<newsInfo>, compare>();
  validNews = unordered_set<int>();
}

void registerUser(int mTime, int mUID, int mNum, int mChannelIDs[])
{
  while(!newsPQ.empty() && newsPQ.top().sendTime <= mTime){
    newsInfo topNews = newsPQ.top();
    newsPQ.pop();

    if(validNews.count(topNews.newsID) == 0) continue;

    for(auto uID: registeredUser[topNews.channelID])
      receivedNews[uID].push_back(topNews);
  }

  for(int i=0; i<mNum; ++i)
    registeredUser[mChannelIDs[i]].push_back(mUID);
}

int offerNews(int mTime, int mNewsID, int mDelay, int mChannelID)
{
  newsPQ.push({mTime + mDelay, mNewsID, mChannelID});

  validNews.insert(mNewsID);

	return registeredUser[mChannelID].size();
}

void cancelNews(int mTime, int mNewsID)
{
  validNews.erase(mNewsID);
}

int checkUser(int mTime, int mUID, int mRetIDs[])
{
  int countSaved = 0, countTotal = 0;

  while(!newsPQ.empty() && newsPQ.top().sendTime <= mTime){
    newsInfo topNews = newsPQ.top();
    newsPQ.pop();

    if(validNews.count(topNews.newsID) == 0) continue;

    for(auto uID: registeredUser[topNews.channelID])
      receivedNews[uID].push_back(topNews);
  }

  for(int i=receivedNews[mUID].size()-1; i>=0; i--){
    newsInfo topNews = receivedNews[mUID][i];
    
    if(validNews.count(topNews.newsID) == 0) continue;

    if(countSaved < 3) mRetIDs[countSaved++] = topNews.newsID;

    ++countTotal;
  }

  receivedNews[mUID].clear();

	return countTotal;
}

/*
어렵지 않게 잘 짰는데, 테케 24/25만 맞고 마지막 하나에서 시간초과가 계속 났던 문제.

고민 ㅈㄴ 하다가 해설을 참고했는데, 크게 다른 부분이 없어서 당황함. 이것저것 비교하다가, 원래 13행 registeredUser의 value를 
unordered_set<int>로 했었는데, 풀이 보고 벡터로 바꿨다. 근데 똑같이 시간초과 났음. 
그리고 또 해설을 보니까 receivedNews에서 value를 스택이 아니라 벡터를  사용했길래, 혹시나?하고 이것도 바꿔봤더니 맞았음. 둘의 
시간복잡도 차이는 없다고 생각했는데 왜 그런지 모르겠다.
*/