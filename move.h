#pragma once

#include <assert.h>
#include <iostream>
#include <vector>
#include <string>

class piece;

class move
{
public:
	move();
	move(int pos);
	move(int pos, std::string type);
	bool castling_move = false;
	bool qcastling_move = false;
	bool en_passant = false;
	bool passant_attack = false;
	bool pawn_attack = false;
	int move_position;
	int score;
	int get_score(std::vector<piece*> whites, std::vector<piece*> blacks);
	piece* parent;
	~move();
};

