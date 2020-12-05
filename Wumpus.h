#pragma once
#include "Room.h"

enum class wump_dir
{
	left, right, forward, stay
};

class Wumpus
{
private:
	const Room* pos;
public:
	Wumpus(const Room*);
	void move();
	const Room* position() const;
};

wump_dir get_direction();