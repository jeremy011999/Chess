#include "move.h"
#include "piece.h"



move::move()
{
}

move::move(int pos)
{
	move_position = pos;
	castling_move = false;
	en_passant = false;
}

move::move(int pos, std::string type)
{
	score = 0;
	move_position = pos;
	if (type == "castle")
		castling_move = true;
	else if (type == "passant")
		en_passant = true;
	else if (type == "qcastle")
		qcastling_move = true;
	else if (type == "passant_attack")
		passant_attack = true;
	else if (type == "pawn_attack")
		pawn_attack = true;
	else
	{
		std::cout << "incorrect move type passed!\n";
		assert(0);
	}
}

int move::get_score(std::vector<piece*> whites, std::vector<piece*> blacks)
{
	int temp_score = 0;
	for (int i = 0; i < whites.size(); i++)
	{
		temp_score += whites[i]->value;
	}
	for (int i = 0; i < blacks.size(); i++)
	{
		temp_score -= blacks[i]->value;
	}
	return temp_score;
}

move::~move()
{
}
