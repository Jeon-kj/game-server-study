#include <iostream>
#include <utility>
using namespace std;

/*
[실습 02_04] 이동 생성자 / 이동 대입

Knight가 Pet* _pet을 소유하도록 한다.

1. 복사 생성 시 Pet이 새로 생성되는지 확인
2. 이동 생성자 Knight(Knight&&)를 직접 구현
3. 상대 객체의 _pet 주소를 그대로 가져온다.
4. 이동된 원본의 _pet을 nullptr로 만든다.
5. 이동 대입 operator=(Knight&&)도 구현한다.
6. std::move 사용 전후 _pet 주소를 출력한다.

확인:
- 깊은 복사와 이동의 차이는?
- 이동 후 원본 포인터를 nullptr로 만드는 이유는?
- move가 복사보다 저렴할 수 있는 이유는?
*/

class Pet {
public:
	Pet() {
		cout << "Pet()" << endl;
	}
	~Pet() {
		cout << "~Pet()" << endl;
	}

	int _hp = 123;
};

class Knight {
public:
	Knight(){
		cout << "Knight()" << endl;
	}
	~Knight() {
		cout << "~Knight()" << endl;
		delete _pet;
	}
	// 복사 생성자
	Knight(const Knight& knight) : _hp(knight._hp), _mp(knight._mp), _pet(knight._pet ? new Pet(*knight._pet) : nullptr) {
		cout << "Knight(const Knight& knight)" << endl;
	}
	// 이동 생성자
	Knight(Knight&& knight) noexcept : _hp(knight._hp), _mp(knight._mp), _pet(knight._pet) {
		cout << "Knight(Knight&& knight)" << endl;
		knight._pet = nullptr;
	}

	// 이동 대입 연산자
	Knight& operator=(Knight&& knight) noexcept {
		if (this == &knight) return *this;
		
		delete _pet;
		
		_pet = knight._pet;
		_hp = knight._hp;
		_mp = knight._mp;
		knight._pet = nullptr;

		return *this;
	}

	Pet* _pet = nullptr;
	int _hp = 100;
	int _mp = 30;
};

void Run04Lab() {
	Knight k1;
	k1._pet = new Pet;

	Knight k2 = k1;	// 복사 생성자 실행 확인
	
	Knight k3;
	k3._pet = new Pet;
	Knight k4(move(k3));

	Knight k5;
	k5._pet = new Pet;
	Knight k6;
	k6 = move(k5);

	// 내가 놓친 점
	// 1. 소멸자에서 _pet을 해제해야 함
	// 2. 이동 대입 연산자에서 복사 받는 기존 _pet에 객체 주소가 들어있는 경우 delete를 해줘야 함
	// 3. 이동 대입 연산자에서 k1 = move(k1) 과 같은 경우 예외처리 해야 함
	// 4. (참고) 소멸자에서 delete를 할 경우, 분명하게 복사 대입 연산자를 깊은 복사로 구현 해줘야 함 (double delete 방지)
}