#pragma once

#include "piece.h"


class board
{
public:
	board();
	~board();
	board(board* prev, piece* sel, move* mov);
	void print();
	void load_pieces();
	void select(int turn);
	void movement(piece* selected, int turn);
	void get_possible_moves(piece* selected, int i);
	void start();
	void reverse_pieces();
	void reverse_board();
	void check_moves(piece* selected);
	void take_piece(std::vector<piece*>& v1, int i);
	void check_for_check(piece* king);
	void update_pieces_moves();
	void check_castle(piece* king, std::string side);
	void make_straight_line(int increment, int size, piece* selected);
	void AIturn();
	void perform_move(piece* piece);
	int get_score();
	move* get_best_move(int depth);
	//int maxi(move* current_move,int depth);
	//int mini(move* current_move, int depth);
	//move* find_best_move(int depth, bool white_player, int score);
	//void make_move(piece* current, move* current_move);
	//board& operator=(board& board_);
	//int get_score();
	//int test_move(piece* currnet, move* current_move);
	friend class piece;
	std::vector<piece*> white_pieces;
	std::vector<piece*> black_pieces;
	std::string output_board[120];
	piece* black_king, *white_king;
	bool game_over = false;
	piece* selected_piece;
	std::vector<move*> possible_moves;
	bool white_move = true;
	bool white_board = true;
	bool qcastle = false, castle = false;
	bool two_player = true;
	int current_score;
	bool best_in_this_tier = false;
	std::vector<move*> AI_moves;
	move* next_move;
	piece* taken = nullptr;
	std::vector<piece*> saved_whites, saved_blacks;
	std::vector<int> white_positions, black_positions;
	//void save_positions();
	//void load_positions();
	std::vector<piece*> taken_pieces;
	//void sort_pieces();
	//void swap_pieces(piece* p1, piece* p2);
	std::vector<int> taken_place_in_vector;
	//void reset_taken_pieces();
	board* previous_board;
	move* move_to_get_here;
	bool is_valid = true;
	std::vector<board*> owned_boards;
};