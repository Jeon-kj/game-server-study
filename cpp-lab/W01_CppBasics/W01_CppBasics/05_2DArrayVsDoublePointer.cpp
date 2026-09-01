#include <iostream>

using namespace std;

/*
[실습 05] 2차원 배열 vs 이중 포인터

int arr[2][2] = {{1,2}, {3,4}};

1. arr, arr[0], arr[1] 주소 출력
2. 각 원소의 주소를 출력해 메모리 배치 확인
3. arr + 1의 주소 증가량 확인
4. int** pp = (int**)arr; 가 왜 잘못된지 메모리 구조로 설명
5. 실제 int** 구조를 만들어 2차원 배열과 비교

확인:
- int[2][2]와 int**는 메모리 구조가 어떻게 다른가?
*/

void Run2DArrayVsDPtr() {
	int arr[2][2] = { {1,2}, {3,4} };
	cout << &arr << " " << &arr[0] << " " << &arr[1] << endl;
	
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			cout << &arr[i][j] << " ";
		}
		cout << endl;
	}

	int** pp = (int**)arr;
	int(*p)[2] = arr; // 올바른 표현
	// arr는 다차원 배열이어도 결국 1자로 늘어선 형태의 구조를 가짐
	// 즉, arr에 가도 주소값이 아닌 정수형 데이터가 있음.
	// 이는 주소에 가도 다른 주소가 있기를 기대하는 int** 형태와는 다름.
	
	int** arr_pp = new int* [2];
	// int* 타입 2개의 시작주소를 arr_pp의 값으로 초기화
	for (int i = 0; i < 2; i++) {
		arr_pp[i] = new int[2];
		// int 타입 2개의 시작주소를 arr_pp[i]의 값으로 초기화
	}

	int a = 1;
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			arr_pp[i][j] = a++;
			cout << arr_pp[i][j] << " ";
		}
		cout << endl;
	}
}