#include <iostream>
#include "StatInfo.h"

using namespace std;

/*
[실습 01] 포인터 연산

1. StatInfo players[3] 생성
2. StatInfo* ptr = players;
3. ptr, ptr + 1, ptr + 2 주소 출력
4. sizeof(StatInfo)와 주소 증가량 비교
5. [] 없이 포인터 연산과 ->로 각 원소의 멤버 출력

확인:
- 포인터 +1은 주소가 몇 byte 증가하는가?
- int*와 StatInfo*의 +1 결과가 다른 이유는?
*/

void Arithmetic(const StatInfo* const ptr) {
    cout << ptr << " " << ptr + 1 << " " << ptr + 2 << endl;
    cout << (ptr + 1) - ptr << endl;
    cout << sizeof(StatInfo) << endl;
    cout << ptr->hp << endl;
    cout << (ptr + 1)->attack << endl;
    cout << (ptr + 2)->defence << endl;
}

void RunPointerArithmeticLab() {
    StatInfo players[3] =
    {
        {100, 10, 5},
        {200, 20, 10},
        {300, 30, 15}
    };

    Arithmetic(players);
}

/*
예상 결과
ptr ptr+12 ptr+24
12      // 오답. 1 : 포인터끼리 뺀 결과는 "바이트 차이"가 아닌 "원소 몇 개 차이인지"가 출력됨(실제로 로우레벨에서 StatInfo 크기로 다시 나눔)
12
100
20
15
*/