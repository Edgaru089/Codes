/*
DOCUMENT NAME "20180720-luogu2482.cpp"
CREATION DATE 2018-07-20
SIGNATURE CODE_20180720_LUOGU2482
COMMENT [SDOI2010]���ɱ / ��ģ�⣨������� NOI/NOI+/CTSC��
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


//����Ϸ״̬
enum GameState {
	Running,     // ���ڼ���
	MasterDied,  // ����������
	BetrayedDied // ���з���������
};

GameState gameState = Running;

// ����
enum Card {
	/*---��ͨ��---*/
	Peach,   // ��
	Kill,    // ɱ
	Escape,  // ��
	/*---������---*/
	Duel,        // ����
	Invasion,    // ����
	ArrowShower, // ���
	Unbreakable, // ��и
	/*---װ����---*/
	AutomaticCrossbow, // ����
	Count // ����
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


// ��ҽ�ɫ
enum PlayerChar {
	Master,        // ����
	LoyalPlayer,   // �ҳ�
	BetrayedPlayer // ����
};

PlayerChar getChar(string str) {
	if (str == "MP") return Master;
	if (str == "ZP") return LoyalPlayer;
	if (str == "FP") return BetrayedPlayer;
}

// �������/����״̬
enum PlayerState {
	Unknown,     // û��
	Loyal,       // ����
	Betrayed,    // ����
	SemiBetrayed // �෴
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

	// ����ֵ���Ƿ�ɱ�������������棬��ɾ����ң�
	bool kill(lpi killer) {
		for (auto i = cards.begin(); i != cards.end(); i++)
			if (*i == Escape) { //������
				cards.erase(i);
				return false;
			}
		health--; // û���� -> ����
		if (health <= 0) { // �������
			for (auto i = cards.begin(); i != cards.end(); i++)
				if (*i == Peach) { // ����
					health++;
					cards.erase(i);
					break;
				}
			if (health <= 0) { // �����һ��Ǳ��� -> ����
				if (charactor == Master) { // ����������
				}
				else if (charactor == LoyalPlayer) {
					if (killer->charactor == Master) // ����ɱ���ҳ� -> �������
						killer->cards.clear();
				}
				else if (charactor == BetrayedPlayer) {
					getFromCardpile(3, killer->cards); // ���������� -> ��������
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
		// 1. ��������
		getFromCardpile(2, cards);

		// 2. ��ʼ����
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
				// ɱ���ж�
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

	if (gameState != Running) { // ��Ϸ���� -> �����Ϸ״̬���˳�
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

