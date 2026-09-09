#include <iostream>
#include <vector>

using namespace std;

/*
[실습 19] iterator와 erase

vector<int>에 1~10 저장

1. iterator로 전체 순회
2. 순회 중 짝수를 erase
3. erase(it)의 반환값을 사용해서 안전하게 계속 순회
4. 반환값을 사용하지 않는 방식이 왜 위험한지 확인

추가:
- insert 후 기존 iterator가 언제 무효화될 수 있는지 생각

확인:
- erase 후 기존 iterator를 그대로 사용하면 왜 위험한가?
- erase의 반환값은 무엇을 가리키는가?
*/

void Run07Lab() {
	vector<int> v;

	for (int i = 0; i < 10; ++i) {
		v.push_back(i + 1);
	}

	vector<int>::iterator it;
	/*
	for (it = v.begin(); it != v.end();) {
		if (*it % 2 == 0) {
			it = v.erase(it);
		}
		else {
			++it;
		}
	}*/

	for (it = v.begin(); it != v.end();) {
		if (it == v.begin()+5) {
			it =  v.insert(it, 0);
			++it;
		}
		else {
			++it;
		}
	}

	for (it = v.begin(); it != v.end(); ++it) {
		cout << *it << endl;
	}

	// erase를 하게 되면 it는 유효하지 않은 주소값을 가지게 되는데, 그 값을 접근하려고 해서 오류가 발생
	// 따라서 반환값을 받아 it를 갱신해야함
	// erase 의 반환값은 지워진 값의 위치

	// insert 후 반환 값을 받지 않으면 마찬가지로 무효한 값을 받아 Undefined Behavior
	// 반환 값은 삽입된 자리의 포인터
}