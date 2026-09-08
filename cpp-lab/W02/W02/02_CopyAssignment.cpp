#include <iostream>
using namespace std;

/*
[실습 13] 복사 생성자 / 복사 대입 연산자

Knight가 Pet* _pet을 갖도록 한다.

1. Knight k2 = k1; 로 복사 생성자 호출
2. Knight k3; k3 = k1; 로 복사 대입 호출
3. 직접 복사 생성자를 구현한다.
4. 직접 operator=를 구현한다.
5. 기존 Pet이 있는 객체에 대입해 메모리 누수가 없는지 확인한다.
6. k1 = k1; 자기 자신 대입도 테스트한다.

확인:
- 복사 생성과 복사 대입은 언제 각각 호출되는가?
- operator=에서는 왜 기존 자원을 먼저 고려해야 하는가?
*/

//class Pet {
//public:
//	Pet() : _hp(100) {
//		cout << "Pet()" << endl;
//	}
//	~Pet() {
//		cout << "~Pet()" << endl;
//	}
//
//	int _hp;
//};
//
//class Knight {
//public:
//	Knight() : _hp(100), _mp(50) {
//		cout << "Knight()" << endl;
//	}
//	~Knight() {
//		cout << "~Knight()" << endl;
//		if (_pet)
//			delete _pet;
//	}
//
//	// 복사 생성자
//	Knight(const Knight& knight) : _hp(knight._hp), _mp(knight._mp) {
//		_pet = new Pet(*knight._pet);
//	}
//
//	// 복사 대입 연산자
//	Knight& operator=(const Knight& knight) {
//		if (this == &knight)
//			return *this;
//
//		_hp = knight._hp;
//		_mp = knight._mp;
//
//		delete _pet;
//		_pet = knight._pet ? new Pet(*knight._pet) : nullptr;
//
//		return *this;
//	}
//
//	int _hp;
//	int _mp;
//	Pet* _pet = nullptr;
//};

/*
void Run02Lab() {
	Knight k1;
	k1._pet = new Pet;

	Knight k2 = k1;
	Knight k3;
	k3 = k1;

	Knight k4;
	k4._pet = new Pet;
	k2 = k1;

	k1 = k1;
	// 1. 기존 복사 대입 연산자의 심각한 오류는, _pet이 nullptr이 아닌 경우 delete를 하지 않고 새로운 주소로 변경한다는 것.
	//    이는 메모리 누수로 이어짐.
	// 2. 그렇다고 delete만 한다고 하면, k1 = k1 같은 경우, 자신의 delete한 _pet을 복사하려고 하기 때문에 undefined behavior 발생.
	//    때문에 복사 대입 연산자에 동일 객체일 경우에 대한 예외처리
}*/