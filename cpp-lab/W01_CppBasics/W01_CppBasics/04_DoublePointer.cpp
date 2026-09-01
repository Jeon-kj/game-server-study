#include <iostream>

using namespace std;

/*
[실습 04] 이중 포인터

const char* message = "Hello";

1. ChangeMessage(const char* msg)를 만들어
   함수 내부에서 msg가 "World"를 가리키게 한다.
   -> 원본 message가 바뀌는지 확인

2. ChangeMessage(const char** msg)를 만들어
   원본 message가 "World"를 가리키게 한다.

추가:
- const char*&를 이용해서 같은 기능 구현

확인:
- 왜 포인터를 바꾸려면 이중 포인터가 필요한가?
*/

void Lab1();
void ChangeMessage(const char* msg);
void ChangeMessage(const char** msg);

// 문자열 포인터와 배열의 차이
void Lab1() {
	const char* message = "Hello";
	char msg[] = "Hello";
	// 둘의 차이
	// message의 경우는 변수 자체가 문자열의 주소를 값으로 가짐. 
	// 즉, message가 "Hello"를 의미하는게 아니라 "Hello"가 저장된 저장소의 위치를 의미함.
	// msg는 "Hello"자체를 의미하며, msg는 일반적으로 &msg[0]으로 변환됨.

	cout << message << endl;
	cout << msg << endl;

	// char* msg_ptr = msg; 가능
	// message = msg; 역시 가능
	// msg = message; // 이건 안됨;

	// char msg[] = "Hello"는 const 안 붙여도 되면서 message에는 붙여야 하는 이유는?
	// 이유: "Hello"는 수정이 불가능한 데이터(.rodata 영역)
	// char msg[] = "Hello"; 자체는 문자열의 내용으로 초기화하는 것이기 때문에 const가 붙지 않아도 됨.
	// 다만 char* message = "Hello"의 경우 직접 해당 영역에 접근하여 문자열을 수정할 수 있기 때문에 이를 막기 위해 const가 붙어야만 함.
	// 요약: message의 const는 message가 가리키는 문자들을 수정하지 못하게 하기 위해서.
}

void ChangeMessage(const char* msg) {
	msg = "World";
}

void ChangeMessage(const char** msg) {
	*msg = "World";
}

void RunDoublePointerLab() {
	const char* message = "Hello";

	// message는 "Hello" 문자열의 시작 주소를 값으로 가짐.
	// ChangeMessage의 매개변수 msg로 그 시작 주소를 복사함.
	// 함수 내부에서 msg의 값을 "World"의 시작 주소로 변경함.
	// 원본 message는 바뀌는 게 없음.
	ChangeMessage(message);
	cout << message << endl;
	
	// 이번에는 message의 주소 자체를 전달
	// msg는 message의 주소를 값으로 가지며, *msg는 message의 주소가 가리키는 값(= message가 가진 값)을 의미.
	// 즉, message가 갖고 있던 값 자체가 변함.
	ChangeMessage(&message);
	cout << message << endl;
}