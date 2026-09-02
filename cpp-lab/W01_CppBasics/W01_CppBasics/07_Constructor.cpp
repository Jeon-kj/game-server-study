#include <iostream>
using namespace std;

/*
[실습 07] 생성자와 복사 생성자

Knight 클래스를 만든다.

1. 생성자를 하나도 만들지 않고 Knight 객체를 생성한다.
2. Knight(int hp)를 추가한 뒤 Knight k;가 가능한지 확인한다.
3. 직접 기본 생성자 Knight()를 추가한다.
4. Knight k2 = k1;으로 복사 생성자를 호출한다.
5. 직접 복사 생성자를 만들어 호출 시점을 출력한다.

추가:
- Knight(int hp)에 explicit을 붙이기 전/후
  Knight k = 100;이 가능한지 확인한다.

확인:
- 생성자를 하나 만들면 암시적 기본 생성자는 어떻게 되는가?
- 복사 생성자는 언제 호출되는가?
- explicit은 무엇을 막는가?
*/

class Knight {
public:
	Knight() {}
	explicit  Knight(int hp) {
		_hp = hp;
	}
	Knight(int hp, int attack, int defence) {
		_hp = hp;
		_attack = attack;
		_defence = defence;
	}
	
	Knight(const Knight& k) {
		this-> _hp = k._hp;
		this->_attack = k._attack;
		this->_defence = k._defence;
	}

public:
	int _hp;
	int _attack;
	int _defence;
};

void KnightHello(const Knight& k) {
	cout << "Hello" << endl;
}

void Run07Lab() {
	Knight k1(100, 20, 10);
	//k1._hp = 100;

	Knight k4(k1);
	Knight k2 = k1; // 1

	Knight k3;		// 2
	k3 = k1;

	// explicit 타입 변환 생성자 앞에 explicit을 붙이니 막힘.
	// 암시적 형변환을 방지함.
	//Knight k5;
	//k5 = 1;	
	//KnightHello(4);	

	// 1번과 2번의 차이
	// 1번은 복사 생성자
	// 2번은 일반 생성자로 생성 후 값 복사
}
