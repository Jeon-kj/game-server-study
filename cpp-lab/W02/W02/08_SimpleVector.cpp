#include <iostream>
using namespace std;

/*
[실습 20] 간단한 Vector 구현

직접 MyVector 클래스를 만든다.

필수 기능:
- push_back()
- reserve()
- size()
- capacity()
- operator[]
- clear()

내부에 필요한 상태:
- 데이터 저장 주소
- size
- capacity

추가:
- begin()
- end()

확인:
- capacity가 부족하면 어떤 순서로 새 공간을 확보해야 하는가?
- 기존 데이터는 어떻게 옮겨야 하는가?
- 기존 메모리는 언제 해제해야 하는가?
*/

template<typename T>
class Iterator {
public:
	Iterator() : _ptr(nullptr) {

	}
	Iterator(T* ptr) : _ptr(ptr) {

	}
	~Iterator() {

	}

	Iterator& operator++() {
		_ptr++;
		return *this;
	}

	Iterator operator++(int) {
		Iterator temp = *this;
		_ptr++;
		return temp;
	}
	Iterator& operator--() {
		_ptr--;
		return *this;
	}

	Iterator operator--(int) {
		Iterator temp = *this;
		_ptr--;
		return temp;
	}

	Iterator operator+(const int count) {
		Iterator temp = *this;
		temp._ptr += count;
		return temp;
	}

	Iterator operator-(const int count) {
		Iterator temp = *this;
		temp._ptr -= count;
		return temp;
	}

	bool operator==(const Iterator& right) {
		return _ptr == right._ptr;
	}

	bool operator!=(const Iterator& right) {
		return _ptr != right._ptr;
	}

	T& operator*() {
		return *_ptr;
	}

public:
	T* _ptr;
};

template<typename T>
class Vector {
public:
	Vector() : _data(nullptr), _size(0), _capacity(0) {
		;
	}
	~Vector() {
		if(_data)
			delete[] _data;
	}

	void push_back(const T& value) {
		if (_size == _capacity) {
			int newCapacity = 1.5 * _capacity;

			if (newCapacity == _capacity) newCapacity++;
			reserve(newCapacity);
		}

		_data[_size] = value;
		_size++;
	}

	void reserve(int capacity) {
		_capacity = capacity;

		T* newData = new T[_capacity];

		for (int i = 0; i < _size; i++) {
			newData[i] = _data[i];
		}

		if (_data) delete[] _data;

		_data = newData;
	}

	int size() { return _size; }

	int capacity() { return _capacity; }

	void clear() { _size = 0; }

	T& operator[](const int i) { return _data[i]; }

public:
	typedef Iterator<T> iterator;

	iterator begin() { return iterator(&_data[0]); }
	iterator end() { return begin() + _size; }

private:
	T* _data;
	int _size;
	int _capacity;
};

void Run08Lab() {
	Vector<int> v;
	
	v.reserve(100);

	for (int i = 0; i < 100; i++) {
		v.push_back(i);
		cout << v.size() << " " << v.capacity() << endl;
	}

	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << endl;
	}

	cout << "----------------" << endl;

	for (Vector<int>::iterator it = v.begin(); it != v.end(); ++it) {
		cout << *it << endl;
	}

	// 거의 보고 했다. 반복적으로 연습하면 문법에도 구조 이해에도, 포인터와 레퍼런스 이해에도 도움이 될 거 같음
}