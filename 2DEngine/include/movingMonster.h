#ifndef MOVINGMONSTER_H
#define MOVINGMONSTER_H
#include "Monster.h"
class MovingMonster : Monster {
public:
	int getSpeed();
private:
	int speed;
};
#endif