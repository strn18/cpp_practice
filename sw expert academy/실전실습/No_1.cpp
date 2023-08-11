// 14616. [Pro] 가게관리
#include <unordered_map>
#include <vector>
#include <queue>
#define MAX 30000
#define PROD 600

using namespace std;

unordered_map<int, int> bId_map; // bId(1~10억)를 인덱스(0~29999)로 매핑. 
int bId_count; // 0부터 시작해서, 새로운 bId가 생길 때마다 1씩 증가.

unordered_map<int, int> sId_map; // sId(1~10억)를 인덱스(0~29999)로 매핑.
int sId_count; // 0부터 시작해서, 새로운 sId가 생길 때마다 1씩 증가.

unordered_map<int, int> product_map; // 상품 번호(1~10억)를 인덱스(0~599)로 매핑.
int product_count; // 0부터 시작해서, 새로운 상품이 생길 때마다 1씩 증가.

typedef struct{
  int product, price, cur_quantity, ori_quantity;
} buy_info;
vector<buy_info> buy_history; // buy가 발생했을 때, 그 bId에 대한 새로운 인덱스를 얻고, buy_history에 push.

typedef struct{
  int bId, product, price, quantity;
} sell_info;
vector<sell_info> sell_history[MAX]; // sell이 발생했을 때, 그 sId에 대한 새로운 인덱스를 얻고, sell_history[인덱스]에 push. 

typedef struct{
  int price, bId, quantity;
} stock_info;
struct compare{
  bool operator()(stock_info a, stock_info b){
    if(a.price != b.price) return a.price > b.price;
    else return a.bId > b.bId;
  }
};
priority_queue<stock_info, vector<stock_info>, compare> product_pq[PROD]; // 어떠한 product의 인덱스를 product_map으로 얻고, 
// product_pq[인덱스]에 접근하여 해당 상품의 재고 확인. 이때, 구매 가격이 낮고 bId 값이 작은 순으로 정렬. 

vector<int> total_quantity; // total_quantity[인덱스]에 접근하여 해당 상품의 총 재고 확인. 새로운 상품이라면 push.

void init() {
  bId_map = unordered_map<int, int>();
  bId_count = 0;

  sId_map = unordered_map<int, int>();
  sId_count = 0;

  product_map = unordered_map<int, int>();
  product_count = 0;

  buy_history = vector<buy_info>();

  for(int i=0; i<MAX; i++)
    sell_history[i] = vector<sell_info>();

  for(int i=0; i<PROD; i++)
    product_pq[i] = priority_queue<stock_info, vector<stock_info>, compare>();
  
  total_quantity = vector<int>();

	return;
}

int buy(int bId, int mProduct, int mPrice, int mQuantity) {
  bId_map[bId] = bId_count++;

  buy_history.push_back({mProduct, mPrice, mQuantity, mQuantity});

  if(product_map.count(mProduct) == 0){
    product_map[mProduct] = product_count++;
    total_quantity.push_back(mQuantity);
  }
  else total_quantity[product_map[mProduct]] += mQuantity;
  
  product_pq[product_map[mProduct]].push({mPrice, bId, mQuantity});

	return total_quantity[product_map[mProduct]];
}

int cancel(int bId) {
  if(bId_map.count(bId) == 0) return -1;
  
  int buy_idx = bId_map[bId];

  if(buy_history[buy_idx].cur_quantity == buy_history[buy_idx].ori_quantity){
    bId_map.erase(bId);

    int product_idx = product_map[buy_history[buy_idx].product];

    total_quantity[product_idx] -= buy_history[buy_idx].ori_quantity;

    return total_quantity[product_idx];
  }

  else return -1;
}

int sell(int sId, int mProduct, int mPrice, int mQuantity) {
  if(product_map.count(mProduct) == 0 || total_quantity[product_map[mProduct]] < mQuantity) return -1;
  
  sId_map[sId] = sId_count++;

  int product_idx = product_map[mProduct];

  int sold_count = 0, margin_count = 0; // 판매한 수량, 판매 수익.

  while(sold_count < mQuantity){
    stock_info top_element = product_pq[product_idx].top();

    int bId = top_element.bId;

    if(bId_map.count(bId) == 0){
      product_pq[product_idx].pop();
      continue;
    }

    if(top_element.quantity <= (mQuantity - sold_count)){
      int cheapest_quantity = top_element.quantity;

      sold_count += cheapest_quantity;
      margin_count += (cheapest_quantity * (mPrice - top_element.price));

      buy_history[bId_map[bId]].cur_quantity -= cheapest_quantity;

      sell_history[sId_map[sId]].push_back({bId, mProduct, top_element.price, cheapest_quantity});
      // bId로 mProduct를 top_element.price 가격에 샀었는데, 그 재고 중 cheapest_quantity개를 팔았다는 뜻이다.

      total_quantity[product_idx] -= cheapest_quantity;

      product_pq[product_idx].pop();
    }
    else{
      int sell_quantity = mQuantity - sold_count;

      top_element.quantity -= sell_quantity;

      sold_count += sell_quantity;
      margin_count += (sell_quantity * (mPrice - top_element.price));

      buy_history[bId_map[bId]].cur_quantity -= sell_quantity;

      sell_history[sId_map[sId]].push_back({bId, mProduct, top_element.price, sell_quantity});
      // bId로 mProduct를 top_element.price 가격에 샀었는데, 그 재고 중 sell_quantity개를 팔았다는 뜻이다.

      total_quantity[product_idx] -= sell_quantity;

      product_pq[product_idx].pop();

      product_pq[product_idx].push(top_element);
    }
  }

	return margin_count;
}

int refund(int sId) {
  if(sId_map.count(sId) == 0) return -1;

  int sell_idx = sId_map[sId];

  int count = 0;

  for(auto s: sell_history[sell_idx]){
    int buy_idx = bId_map[s.bId];

    buy_history[buy_idx].cur_quantity += s.quantity;

    total_quantity[product_map[s.product]] += s.quantity;

    product_pq[product_map[s.product]].push({s.price, s.bId, s.quantity});

    count += s.quantity;
  }

  sId_map.erase(sId);

	return count;
}

/*
실전실습 문제 중에서는 처음 풀어봤는데, 다 구현하기가 좀 힘들었다...

우선 주어지는 bId, sId의 값이 1~10억이라, 인덱스를 통해 벡터(또는 배열 등)에 저장할 수가 없다. 그래서 매핑을 통해, 각각 bId_map, sId_map을 
사용하여 인덱스를 얻고, 그 인덱스로 buy_history, sell_history에 접근하도록 했다.

나머지 풀이 과정은 잘 읽어봐...

다 풀고 올려준 풀이 보는데, 굳이 1) 매핑으로 인덱스 얻기. 2) 인덱스로 벡터에 접근. 이렇게 이중으로 할 필요가 없었다. 그냥 애초에 
unordered_map<int, buy_info> buy_history 이런 식으로 해서, 바로 접근하면 되었음.

그리고 나는 특정 상품을 {특정 가격, 개수}로 샀을 때, 그 정보를 buy_history와 product_pq에 모두 저장해두고, 수정이 필요할 때는 둘 다 
수정해주었다. 그런데 풀이를 보니깐, pq에는 가격(이랑 bId)만 저장해두고, 개수 정보는 넣지 않았음. 대신, pq에서 꺼내서 볼 때 어차피 
bId가 있으니깐 그걸로 buy_history에 접근해서 개수를 보고, 몇 개 팔았다면 buy_history의 정보를 수정하고 하는 방식이었음. 
*/