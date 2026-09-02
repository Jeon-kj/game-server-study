#include <iostream>
using namespace std;

/*
[실습 10] 다형성과 virtual

Player, Knight, Mage 클래스를 만든다.
각 클래스에 Move()를 작성한다.

void MovePlayer(Player* player)
{
    player->Move();
}

1. Move()에 virtual 없이 Knight를 전달한다.
2. 어떤 Move()가 실행되는지 예상하고 확인한다.
3. Player::Move()에 virtual을 붙이고 다시 확인한다.
4. Mage도 전달해서 동일하게 확인한다.

디버거:
- Player* 변수의 타입
- 실제로 생성된 객체 타입
- 가능하면 객체 메모리에서 vftable 관련 정보를 확인

확인:
- Player*로 Knight를 가리킬 수 있는 이유는?
- virtual 전/후 실행 결과가 왜 달라지는가?
- 정적 바인딩과 동적 바인딩의 차이는?
*/

class Player {
public: 
    Player() {
        _hp = 100;
        _level = 1;
    }
    void virtual Move() {
        cout << "Player Move" << endl;
    }

    int _hp;
    int _level;
};

class Knight : public Player {
public:
    Knight() {
        _attack = 10;
    }
    void Move() {
        cout << "Knight Move" << endl;
    }
    
    int _attack;
};

class Mage : public Player {
public:
    Mage() {
        _mp = 50;
    }
    void Move() {
        cout << "Mage Move" << endl;
    }
    
    int _mp;
};

void MovePlayer(Player* player)
{
    player->Move();
}

void Run10Lab() {
    Knight k1;
    Mage m1;
    MovePlayer(&k1);
    MovePlayer(&m1);
}