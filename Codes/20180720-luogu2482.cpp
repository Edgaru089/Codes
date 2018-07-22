/*
DOCUMENT NAME "20180720-luogu2482.cpp"
CREATION DATE 2018-07-20
SIGNATURE CODE_20180720_LUOGU2482
COMMENT [SDOI2010]猪国杀 / 大模拟（洛谷评级 NOI/NOI+/CTSC）
*/

/*
2 10
MP W W W W
FP K K K K
K K K K K K K K K K
*/


#include "Overall.hpp"

// Check if this code file is enabled for testing
#ifdef CODE_20180720_LUOGU2482

#include <cstdlib>
#include <iostream>
#include <list>
#include <deque>
#include <string>
using namespace std;

const int MaxN = 10 + 10;
int n;


//　游戏状态
enum GameState {
	Running,     // 还在继续
	MasterDied,  // 主公死掉了
	BetrayedDied // 所有反臣死掉了
};

GameState gameState = Running;

// 卡牌
enum Card {
	/*---普通牌---*/
	Peach,   // 桃
	Kill,    // 杀
	Escape,  // 闪
	/*---锦囊牌---*/
	Duel,        // 决斗
	Invasion,    // 南蛮
	ArrowShower, // 万箭
	Unbreakable, // 无懈
	/*---装备牌---*/
	AutomaticCrossbow, // 连弩
	Count // 数量
};

Card getCardFromName(string name) {
	if (name == "P") return Peach;
	if (name == "K") return Kill;
	if (name == "D") return Escape;
	if (name == "F") return Duel;
	if (name == "N") return Invasion;
	if (name == "W") return ArrowShower;
	if (name == "J") return Unbreakable;
	if (name == "Z") return AutomaticCrossbow;
}

string getCardName(Card card) {
	if (card == Peach)             return "P";
	if (card == Kill)              return "K";
	if (card == Escape)            return "D";
	if (card == Duel)              return "F";
	if (card == Invasion)          return "N";
	if (card == ArrowShower)       return "W";
	if (card == Unbreakable)       return "J";
	if (card == AutomaticCrossbow) return "Z";
}


// 玩家角色
enum PlayerChar {
	Master,        // 主公
	LoyalPlayer,   // 忠臣
	BetrayedPlayer // 反臣
};

PlayerChar getChar(string str) {
	if (str == "MP") return Master;
	if (str == "ZP") return LoyalPlayer;
	if (str == "FP") return BetrayedPlayer;
}

// 玩家跳忠/跳反状态
enum PlayerState {
	Unknown,     // 没跳
	Loyal,       // 跳忠
	Betrayed,    // 跳反
	SemiBetrayed // 类反
};

class Pig;
typedef list<Pig> lp;
typedef list<Pig>::iterator lpi;
lp players;

deque<Card> cardPile;
template<typename TargetContainer>
void getFromCardpile(int count, TargetContainer& container) {
	for (int i = 1; i <= count; i++) {
		container.push_back(cardPile.front());
		if (cardPile.size() > 1)
			cardPile.pop_front();
	}
}

void checkGameState();

class Pig {
public:

	template<typename Iterator>
	void setCards(Iterator begin, Iterator end) {
		while (begin != end) {
			cards.push_back(*begin);
			begin++;
		}
	}

	void setCharactor(PlayerChar c) {
		charactor = c;
		if (c == Master)
			state = Loyal;
		else
			state = Unknown;
	}

	void setId(lp::iterator i, int id) {
		pos = i;
		previd = id;
	}

	// 返回值：是否被杀死（已死返回真，会删掉玩家）
	bool kill(lpi killer) {
		for (auto i = cards.begin(); i != cards.end(); i++)
			if (*i == Escape) { //　找闪
				cards.erase(i);
				return false;
			}
		health--; // 没有闪 -> 受伤
		if (health <= 0) { // 如果濒死
			for (auto i = cards.begin(); i != cards.end(); i++)
				if (*i == Peach) { // 找桃
					health++;
					cards.erase(i);
					break;
				}
			if (health <= 0) { // 找完桃还是濒死 -> 死掉
				if (charactor == Master) { // 主公死掉了
				}
				else if (charactor == LoyalPlayer) {
					if (killer->charactor == Master) // 主公杀了忠臣 -> 手牌清空
						killer->cards.clear();
				}
				else if (charactor == BetrayedPlayer) {
					getFromCardpile(3, killer->cards); // 反臣死掉了 -> 摸三张牌
				}
				players.erase(pos);
				checkGameState();
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}


	void onRound() {
		// 1. 摸两张牌
		getFromCardpile(2, cards);

		// 2. 开始出牌
		bool alreadyKilled = false;
		bool cardUsed = false;
		auto i = cards.begin();
		while (i != cards.end()) {
			Card card = *i;
			cardUsed = false;
			if (card == Peach) {
				if (health < maxhealth) {
					health++;
					cardUsed = true;
				}
			}
			else if (card == Kill && (!alreadyKilled || hasCrossbow)) {
				// 杀的判断
				lpi target = pos; target++; if (target == players.end())target = players.begin();
				auto caller = [&] {
					if (charactor == LoyalPlayer || charactor == Master) {
						if (target->state == Betrayed || (charactor == Master && state == SemiBetrayed)) {
							state = Loyal;
							target->kill(pos);
							cardUsed = true;
							alreadyKilled = true;
						}
					}
					else if (charactor == BetrayedPlayer) {
						if (target->state == Loyal || target->charactor == Master) {
							state = Betrayed;
							target->kill(pos);
							cardUsed = true;
							alreadyKilled = true;
						}
					}};
				caller();
				target--; target--; if (target == players.end())target--;
				caller();
			}
			else if (card == AutomaticCrossbow) {
				hasCrossbow = true;
				cardUsed = true;
			}

			if (cardUsed) {
				cards.erase(i);
				i = cards.begin();
			}
			else
				i++;
		}
	}


	lp::iterator pos;
	int previd = 0;

	bool hasCrossbow = false;

	PlayerChar charactor;
	PlayerState state = Unknown;

	int health = 4, maxhealth = 4;

	list<Card> cards;
};



void checkGameState() {
	bool hasBetrayed = false, hasMaster = false;
	for (auto& i : players) {
		if (i.charactor == Betrayed)
			hasBetrayed = true;
		if (i.charactor == Master)
			hasMaster = true;
	}
	if (hasBetrayed&&hasMaster)
		gameState = Running;
	else if (hasBetrayed)
		gameState = MasterDied;
	else if (hasMaster)
		gameState = BetrayedDied;

	if (gameState != Running) { // 游戏结束 -> 输出游戏状态并退出
		if (gameState == MasterDied)
			cout << "FP" << endl;
		else if (gameState == BetrayedDied)
			cout << "MP" << endl;

		int i = 1;
		lpi j = players.begin();
		for (i = 1; i <= n;) {
			if (j == players.end()) {
				for (int k = i; k <= n; k++)
					cout << "DEAD" << endl;
				break;
			}
			else if (i == j->previd) {
				for (auto k : j->cards) {
					cout << getCardName(k) << " ";
				}
				cout << endl;
				i++; j++;
			}
			else if (i < j->previd) {
				cout << "DEAD" << endl;
				i++;
			}
		}

		exit(0);
	}
}

int m;

int main(int argc, char* argv[]) {

	string str, c;

	cin >> n >> m;
	lpi l;
	for (int i = 1; i <= n; i++) {
		cin >> str;
		players.push_back(Pig());
		if (i == 1)
			l = players.begin();
		else
			l++;
		l->setCharactor(getChar(str));
		l->setId(l, i);
		for (int j = 1; j <= 4; j++) {
			cin >> c;
			if (c == "F" || c == "N" || c == "W" || c == "J")
				return 0;
			players.back().cards.push_back(getCardFromName(c));
		}
	}

	for (int i = 1; i <= m; i++) {
		cin >> c;
		cardPile.push_back(getCardFromName(c));
	}

	while (true) {
		for (auto& p : players)
			p.onRound();
	}

	return 0;
}

#endif

