#include <iostream>
#include "StatInfo.h"

using namespace std;

/*
[실습 02] 값 / 포인터 / 참조 전달

아래 3개 함수 작성:
- DamageByValue(StatInfo stat, int damage)
- DamageByPointer(StatInfo* stat, int damage)
- DamageByReference(StatInfo& stat, int damage)

1. 각각 hp를 감소시킨다.
2. 호출 전후 원본 hp를 비교한다.
3. main과 각 함수 내부에서 객체 주소를 출력해 비교한다.
4. 읽기 전용 PrintStat 함수의 적절한 매개변수 타입을 선택한다.

확인:
- 어떤 방식이 원본을 변경하는가?
- 값 전달과 참조/포인터 전달의 차이는?
*/

void DamageByValue(StatInfo stat, int damage) {
	stat.hp -= damage;
}

void DamageByPointer(StatInfo* stat, int damage) {
	stat->hp -= damage;
}

void DamageByReference(StatInfo& stat, int damage) {
	stat.hp -= damage;
}

void RunValuePointerReferenceLab() {
	StatInfo player = { 100, 20, 10 };
	int dmg = 10;

	DamageByValue(player, dmg);
	cout << player.hp << endl;
	DamageByPointer(&player, dmg);
	cout << player.hp << endl;
	DamageByReference(player, dmg);
	cout << player.hp << endl;
}