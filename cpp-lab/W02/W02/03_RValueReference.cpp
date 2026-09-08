#include <iostream>
#include <utility>
using namespace std;

/*
[실습 02_03] lvalue / rvalue reference

다음 함수들을 만든다.

Test(Knight& knight)
Test(const Knight& knight)
Test(Knight&& knight)

1. Knight k; 를 각각 어떤 함수에 전달할 수 있는지 확인
2. Knight() 임시 객체를 전달해본다.
3. std::move(k)를 전달해본다.
4. 어떤 overload가 호출되는지 출력한다.

확인:
- Knight&는 어떤 값을 받을 수 있는가?
- const Knight&가 임시 객체도 받을 수 있는 이유는?
- Knight&&는 무엇을 받기 위한 참조인가?
- std::move는 실제로 객체를 이동시키는 함수인가?
*/

//class Knight {
//public:
//	Knight() {
//		;
//	}
//	~Knight() {
//		;
//	}
//
//	int _hp;
//	int _mp;
//};

//void Test(Knight& knight) {
//	cout << "Test(Knight& knight)" << endl;
//	knight._hp = 90;
//	knight._mp = 10;
//}
//
//void Test(const Knight& knight) {
//	cout << "Test(const Knight& knight)" << endl;
//	//knight._hp = 90;
//	//knight._mp = 10;
//}
//
//void Test(Knight&& knight) {
//	cout << "Test(Knight&& knight)" << endl;
//	knight._hp -= 10;
//	knight._mp -= 5;
//}
//
//void Run03Lab() {
//	Knight k1;
//	k1._hp = 100;
//	k1._mp = 30;
//
//	// 동일한 이름이라면 k1은 Knight& knight 쪽으로 분류됨.
//	Test(k1);
//	Test(static_cast<const Knight&>(k1));
//	Test(Knight());
//	Test(move(k1));
//	Test(static_cast<Knight&&>(k1));
//	// Test(Knight&& knight)를 호출하는 아래 3 경우는 값을 변경시키지 않을 줄 알았다. 왜냐하면 rvalue는 임시 객체니까.
//	// 그치만 static_cast<Knight&&>()나 move는 "이 객체를 rvalue로 취급한다"고 바꾸는 캐스팅이고 엄연히 원본이 있는 변수라서 바뀜.
//	// 물론 Test(Knight());의 경우 내 의도대로 값을 바꾸지 못함. -> 애초에 k1의 값을 넘겨주지 않았으니 당연.
//}