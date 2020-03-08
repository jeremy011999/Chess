#pragma once
#include "board.h"

class AI
{
public:
	AI();
	void generate_boards();
	void start();
	~AI();
	friend class board;
	void save_positions();
	void load_positions();
	void AIturn();
	void make_first_moves();
	void make_second_moves();
	void make_third_moves();
	void purge_boards();
	void print_current_positions();
	void set_playing_board(board* b);
	void remove_piece(std::vector<piece*> v1, piece* sel);
	board* minimax(std::vector<board*> b1, bool is_max_player);
private:
	bool is_white_player = false;
	bool is_playing_white;
	board playing_board;
	board* current_board;
	std::vector<board*> first_move_boards;
	std::vector<board*> second_move_boards;
	std::vector<board*> third_move_boards;
	move* best_move;
	int score;
	std::vector<int> white_positions, black_positions;
};

