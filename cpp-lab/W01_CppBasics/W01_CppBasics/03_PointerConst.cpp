#include <iostream>

using namespace std;

/*
[실습 03] 포인터 const

다음 타입을 각각 테스트한다.

int*
const int*
int* const
const int* const
const int&

각 타입에서 확인:
1. 가리키는 값 변경 가능?
2. 다른 대상을 가리키도록 변경 가능?

컴파일 전에 O/X를 예상하고 실제 결과와 비교한다.

확인:
- const가 값에 붙은 것인지 포인터에 붙은 것인지 구분할 수 있는가?
*/

void ChangeInt(int* ptr) {
	*ptr = 2;
}

void ChangeInt(const int* ptr) {
	// 불가능
	*ptr = 2;
	
	// 가능
	int tmp;
	ptr = &tmp;
}

void ChangeInt(int* const ptr) {
	// 가능
	*ptr = 2;

	// 불가능
	int tmp;
	ptr = &tmp;
}

void ChangeInt(const int* const ptr) {
	// 불가능
	*ptr = 2;

	// 불가능
	int tmp;
	ptr = &tmp;
}

void ChangeInt(const int& ref) {
	// 불가능
	ref = 2;
}

// const 뒤에 뭐가 오는지 알면 쉬움
// const 뒤에 *이 오면 "가리키는 값"을 수정할 수 없음.
// const 뒤에 변수명이 오면 "변수가 담은 값"을 수정할 수 없음.