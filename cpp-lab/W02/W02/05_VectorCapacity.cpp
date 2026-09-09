#include <iostream>
#include <vector>

using namespace std;

/*
[실습 02_05] vector size / capacity

vector<int> v;

1. push_back을 반복하면서 size, capacity 출력
2. capacity가 증가하는 순간을 기록
3. reserve(100) 후 같은 실험 반복
4. resize와 reserve 사용 후 size/capacity 비교

확인:
- size와 capacity의 차이는?
- reserve가 복사 횟수를 줄일 수 있는 이유는?
*/

void Run05Lab() {
	vector<int> v;

	/*cout << v.size() << " " << v.capacity() << endl;

	for (int i = 0; i < 100; ++i) {
		v.push_back(i);

		cout << v.size() << " " << v.capacity() << endl;
	}*/
	// size == capacity일 때 capacity = 1.5 * capacity;
	// size는 1씩 증가

	v.reserve(100);

	cout << v.size() << " " << v.capacity() << endl;

	for (int i = 0; i < 100; ++i) {
		v.push_back(i);

		cout << v.size() << " " << v.capacity() << endl;
	}
	// size는 실제로 벡터 내부에 있는 값의 수
	// capacity는 벡터가 확보한 메모리의 크기
	// reserve로 초기 크기를 확보한다면, 초기 0부터 1, 2, 3, 4, 6,..
	// 조금씩 늘어나면서 메모리 공간을 이동하는 과정에서 발생하는 복사를 줄일 수 있음
	// 복사는 왜 발생하는가? 벡터는 연속된 메모리 공간을 가져야 하기 때문에 
	// 추가 메모리를 확보하는 과정에서 기존 공간을 버리고 다른곳을 확보 후 값을 복사함
}