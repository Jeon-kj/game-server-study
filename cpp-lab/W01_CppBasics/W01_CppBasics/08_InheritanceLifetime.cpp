#include <iostream>
using namespace std;

/*
[실습 08] 상속과 생성/소멸 순서

Player 부모 클래스와
Knight, Mage 자식 클래스를 만든다.

1. 각 생성자와 소멸자에서 이름을 출력한다.
2. Knight 객체를 만들고 호출 순서를 확인한다.
3. 객체가 사라질 때 소멸 순서를 확인한다.
4. Player(int hp)를 만들고
   Knight 생성자 초기화 리스트에서 직접 호출한다.

확인:
- 생성자는 부모/자식 중 누가 먼저 실행되는가?
- 소멸자는 어떤 순서인가?
- 부모 기본 생성자가 없다면 자식은 어떻게 해야 하는가?
*/

class Player {
public:	// 접근 지정자를 명시하지 않으면 private이기 때문에 하위 클래스에서 오류 발생
	/*Player() {
		cout << "Player" << endl;
	}*/
	Player(int hp) {
		_hp = hp;
	}
	~Player() {
		cout << "~Player" << endl;
	}

	int _hp;
};

class Knight : public Player {
public:
	Knight() : Player(100){	// 부모 생성자를 직접 호출하기 위해 초기화 리스트 사용
		cout << "Knight" << endl;
	}
	~Knight() {
		cout << "~Knight" << endl;
	}
};

class Mage : public Player {
public:
	Mage() : Player(100) {	// 부모 생성자를 직접 호출하기 위해 초기화 리스트 사용
		cout << "Mage" << endl;
	}
	~Mage() {
		cout << "~Mage" << endl;
	}
};

void Run08Lab() {
	Knight k1;
	Mage m1;
}