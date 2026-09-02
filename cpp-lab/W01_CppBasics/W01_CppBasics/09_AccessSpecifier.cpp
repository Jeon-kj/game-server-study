#include <iostream>
using namespace std;

/*
[실습 09] public / protected / private

Player에 다음 멤버를 하나씩 만든다.
- public 변수
- protected 변수
- private 변수

Knight가 Player를 public 상속한다.

1. main에서 각각 접근해본다.
2. Knight 내부에서 각각 접근해본다.
3. 컴파일 오류가 나는 경우 이유를 확인한다.

추가:
- public 상속을 protected/private 상속으로 바꿔
  외부에서 접근 가능한 범위가 어떻게 달라지는지 확인한다.

확인:
- public / protected / private의 차이는?
- protected가 private과 다른 점은? 
*/

/*
class Player {
public:
	int _public;
protected:
	int _protected;
private:
	int _private;
};

class Knight : public Player {	// public -> protected : Run09Lab(외부)에서도 _public에 접근 불가
								// public -> private : 외부에서도, 내부에서도 아무것도 접근 불가
public:
	void SetPublic() { _public = 10; }
	void SetProtected() { _protected = 10; }
	// 접근할 수 없음
	//void SetPrivate() { _private = 10; }
};

void Run09Lab() {
	Knight k1;
	k1._public = 10;
	// 접근할 수 없음
	//k1._protected = 10;
	//k1._private = 10;
}*/