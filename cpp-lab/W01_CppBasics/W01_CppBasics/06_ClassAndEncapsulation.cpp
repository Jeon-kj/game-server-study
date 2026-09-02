#include <iostream>
using namespace std;

/*
[실습 06] 클래스와 캡슐화

Knight 클래스를 만든다.
- hp, attack 멤버 변수
- TakeDamage(), Attack() 멤버 함수

1. hp를 public으로 두고 외부에서 직접 수정해본다.
2. hp를 private으로 바꾼다.
3. GetHp(), SetHp() 또는 TakeDamage()를 통해서만 변경되게 만든다.
4. hp가 0 미만이 되지 않도록 클래스 내부에서 처리한다.

확인:
- 데이터를 함수와 묶어두면 어떤 장점이 있는가?
- public 변수보다 함수를 통한 수정이 안전한 이유는?
*/

class Knight {
public:
	void TakeDamage(int dmg) {
		cout << dmg << "의 피해를 받았습니다." << endl;

		_hp -= dmg;
		if (_hp < 0) _hp = 0;
	}
	void Attack() {
		;
	}
	int GetHp() { return _hp; }
	void SetHp(int hp) { _hp = hp; }

private:
	int _hp;
	int _attack;
};

void Run06Lab() {
	Knight k1;
	// k1._hp = 100; 멤버변수가 private이므로 외부에서 접근할 수 없음.
	k1.SetHp(100);
	cout << "k1 Hp: " << k1.GetHp() << endl;
	k1.TakeDamage(8);
	cout << "k1 Hp: " << k1.GetHp() << endl;
}