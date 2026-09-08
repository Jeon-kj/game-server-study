#include <iostream>
using namespace std;

/*
[실습 12] 얕은 복사 vs 깊은 복사

Knight가 Pet* _pet을 갖도록 만든다.
Pet은 new로 생성하고 Knight 소멸자에서 delete한다.

1. Knight k1 생성
2. Knight k2 = k1; 로 암시적 복사
3. k1._pet과 k2._pet의 주소 비교
4. 한쪽 Pet의 값을 수정하고 다른 쪽도 바뀌는지 확인
5. 두 객체 소멸 시 어떤 문제가 생기는지 예상

이후 직접 복사 생성자를 작성해
Pet까지 새로 생성하는 깊은 복사를 구현한다.

확인:
- 얕은 복사에서 어떤 값이 그대로 복사되는가?
- 왜 raw pointer 멤버에서 문제가 생기는가?
- 깊은 복사 후 두 Pet의 주소는 어떻게 되어야 하는가?
*/

// 얕은 복사의 예
//class Pet {
//public:
//	Pet() {
//		cout << "Pet()" << endl;
//	}
//	~Pet() {
//		cout << "~Pet()" << endl;
//	}
//
//	int hp = 100;
//};
//
//class Knight {
//public:
//	Knight() {
//		cout << "Knight()" << endl;
//	}
//	~Knight() {
//		cout << "~Knight()" << endl;
//		if (_pet)
//			delete _pet;
//	}
//
//	Pet* _pet = nullptr;
//};

//// 깊은 복사의 예
//class Pet {
//public:
//	Pet() {
//		cout << "Pet()" << endl;
//	}
//	~Pet() {
//		cout << "~Pet()" << endl;
//	}
//
//	int hp = 100;
//};
//
//class Knight {
//public:
//	Knight() {
//		cout << "Knight()" << endl;
//	}
//	~Knight() {
//		cout << "~Knight()" << endl;
//		if (_pet)
//			delete _pet;
//	}
//	// 복사 생성자
//	Knight(const Knight& knight) {
//		cout << "Knight(const Knight& knight)" << endl;
//		_pet = new Pet(*knight._pet);
//	}
//
//	Pet* _pet = nullptr;
//};

/*
void Run01Lab() {
	Knight k1;
	k1._pet = new Pet;

	Knight k2 = k1;

	k2._pet->hp -= 10;
	// 1. k1가 가리키는 pet과 k2가 가리키는 pet은 동일함 (얕은 복사)
	//    따라서 이대로 k1가 delete 되고, k2가 delete 된다면, 이는 Double Free 버그
	//	  당연히 한쪽 값을 수정하면 _pet이 가진 주소 값이 동일하기에 k1._pet->hp 같은 값을 수정하면, 나머지 pet도 동일하게 바뀜.
	// 2. 깊은 복사의 경우에는 아예 새로운 객체를 생성하여 할당하기 때문에 새로운 _pet 값을 가짐.
}
*/