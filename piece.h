#pragma once

#include <string>
#include <io.h>
#include <fcntl.h>
#include <stdio.h>
#include <Windows.h>
#include <vector>
#include "move.h"

class move;

class piece
{
public:
	piece();
	piece(piece* p1);
	piece(int type, int value, int num, int color, int pos, bool moved, bool jumped);
	piece(int num, int color_, int pos);
	void move_piece(int new_x, int new_y);
	bool check_move(int new_x, int new_y);
	virtual ~piece();
	virtual void print();
	friend class board;
	int piece_type, num_of_piece, color;
	int x, y;
	char symbol;
	bool is_white, selected = false;
	std::string type, str_color;
	int position;
	virtual std::vector<int> display_moves();
	bool is_targeted = false;
	bool hasnt_moved = true;
	std::vector<move*> possible_moves_stored;
	void set_moves(move* move);
	bool is_in_check = false;
	int value = 0;
	bool just_jumped = false;
	std::string type_name = "piece";
	bool operator>(piece* p1);
	bool operator<(piece* p1);
	friend class move;
	bool has_been_taken = false;
};

class pawn :public piece
{
public:
	pawn(int num, int color_, int pos);
	void print();
	std::vector<int> display_moves();
	bool just_jumped = false;
};

class knight :public piece
{
public:
	knight(int num, int color_, int pos);
	void print();
	std::vector<int> display_moves();
};

class bishop :public piece
{
public:
	bishop(int num, int color_, int pos);
	void print();
	std::vector<int> display_moves();
};

class rook :public piece
{
public:
	rook(int num, int color_, int pos);
	void print();
	std::vector<int> display_moves();
};

class queen :public piece
{
public:
	queen(int num, int color_, int pos);
	void print();
	std::vector<int> display_moves();
};

class king :public piece
{
public:
	king(int num, int color_, int pos);
	void print();
	std::vector<int> display_moves();
	bool is_in_check;
};

