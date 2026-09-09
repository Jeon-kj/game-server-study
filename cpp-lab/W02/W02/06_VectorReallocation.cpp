#include <iostream>
#include <vector>

using namespace std;

/*
[실습 02_06] vector reallocation

1. vector<int>에 값 몇 개 추가
2. 첫 원소의 주소와 v.data() 저장
3. push_back을 반복해 capacity 증가 유도
4. 재할당 전/후 v.data() 주소 비교
5. 기존에 저장한 원소 포인터가 여전히 유효한지 확인

추가:
- reserve를 충분히 한 뒤 같은 실험 반복

확인:
- capacity 증가 시 기존 포인터가 깨질 수 있는 이유는?
*/

void Run06Lab() {
	vector<int> v;

	for (int i = 0; i < 10; ++i) {
		v.push_back(i);
	}
	int* vptr = &v[0];
	int* vdata = v.data();

	cout << vptr << " " << vdata << endl;

	for (int i = 10; i < 30; ++i) {
		v.push_back(i);
	}

	cout << &v[0] << " " << v.data() << endl;
	// 값이 다른 걸 확인할 수 있음

	cout << *vptr << " " << *vdata << endl;
	// 0 이 아닌 이상한 값이 출력  -> 정확하게 말하자면 Undefined Behavior
	// 즉, capacity가 증가하면서 메모리 주소를 새로운 곳으로 복사 이동하고
	// 기존 포인터 주소가 유효하지 않게 됨
}