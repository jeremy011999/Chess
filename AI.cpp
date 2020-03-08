#include "AI.h"


/*
Need to fix how AI gets white player moves, since it is moving pawns backwards
also need to fix when i take a black piece it isnt happy
need to fix memory as well i think, but addition of playing_board object should help maybe.
*/



AI::AI()
{
	current_board = new board;
	playing_board = *current_board;
}

void AI::generate_boards()
{
	
}

board* AI::minimax(std::vector<board*> b1, bool is_maxing_player)
{
	if (is_maxing_player)
	{
		board* max = b1[0];
		int max_score = -9999999;
		for (int i = 0; i < b1.size(); i++)
		{
			if (b1[i]->is_valid)
			{
				if (b1[i]->current_score > max_score)
				{
					max_score = b1[i]->current_score;
					max = b1[i];
				}
			}
		}
		max->best_in_this_tier = true;
		return max;
	}
	else
	{
		board* min = b1[0];
		int min_score = 9999999;
		for (int i = 0; i < b1.size(); i++)
		{
			if (b1[i]->is_valid)
			{
				if (b1[i]->current_score < min_score)
				{
					min_score = b1[i]->current_score;
					min = b1[i];
				}
			}
		}
		min->best_in_this_tier = true;
		return min;
	}
}

void AI::AIturn()
{
	purge_boards();
	std::cout << first_move_boards.size() << std::endl;
	for (int i = 0; i < first_move_boards.size(); i++)
	{
		std::cout << first_move_boards[i]->owned_boards.size() << std::endl;
		for (int j = 0; j < first_move_boards[i]->owned_boards.size(); j++)
		{
			std::cout << first_move_boards[i]->owned_boards[j]->owned_boards.size() << std::endl;
		}
		std::cout << std::endl;
	}
	is_white_player = false;

	make_first_moves();
	make_second_moves();
	make_third_moves();
	for (int i = 0; i < first_move_boards.size(); i++)
	{
		for (int j = 0; j < first_move_boards[i]->owned_boards.size(); j++)
		{
			first_move_boards[i]->owned_boards[j]->current_score = minimax(first_move_boards[i]->owned_boards[j]->owned_boards, false)->current_score;
		}
	}
	for (int i = 0; i < first_move_boards.size(); i++)
	{
		first_move_boards[i]->current_score = minimax(first_move_boards[i]->owned_boards, true)->current_score;
	}
	current_board = minimax(first_move_boards, false);
	set_playing_board(current_board);
	std::cout << "Current Board\n";
	current_board->print();
	std::cout << current_board->white_move;
	for (int i = 0; i < current_board->owned_boards.size(); i++)
	{
		if (current_board->owned_boards[i]->best_in_this_tier)
		{
			std::cout << "Next move\n";
			current_board->owned_boards[i]->print();
			std::cout << current_board->owned_boards[i]->white_move;
			for (int j = 0; j < current_board->owned_boards[i]->owned_boards.size(); j++)
			{
				if (current_board->owned_boards[i]->owned_boards[j]->best_in_this_tier)
				{
					std::cout << "last move\n";
					current_board->owned_boards[i]->owned_boards[j]->print();
					std::cout << current_board->owned_boards[i]->owned_boards[j]->white_move;
				}
			}
		}
	}
	system("PAUSE");
	for (int i = 0; i < current_board->black_pieces.size(); i++)
	{
		for (int j = 0; j < current_board->white_pieces.size(); j++)
		{
			if (current_board->black_pieces[i]->position == current_board->white_pieces[j]->position)
			{
				if (is_white_player)
				{
					current_board->take_piece(current_board->white_pieces, j);			//since is_white_player == true this means that it is now whites turn so it was just blacks turn so a white piece needs to be taken
				}
				else
				{
					current_board->take_piece(current_board->black_pieces, i);
				}
			}
		}
	}
}

void AI::make_first_moves()
{
	current_board->update_pieces_moves();
	if (is_white_player)
	{
		//std::cout << "made it into if is white player statement.\n";
		for (int i = 0; i < current_board->white_pieces.size(); i++)
		{
			current_board->white_pieces[i]->selected = true;
			for (int j = 0; j < current_board->white_pieces[i]->possible_moves_stored.size(); j++)
			{
				first_move_boards.push_back(new board(current_board, current_board->white_pieces[i], current_board->white_pieces[i]->possible_moves_stored[j]));
				//std::cout << "made first white move board\n";
			}
			current_board->white_pieces[i]->selected = false;
		}
		goto end;
	}
	else
	{
		for (int i = 0; i < current_board->black_pieces.size(); i++)
		{
			current_board->black_pieces[i]->selected = true;
			for (int j = 0; j < current_board->black_pieces[i]->possible_moves_stored.size(); j++)
			{
				first_move_boards.push_back(new board(current_board, current_board->black_pieces[i], current_board->black_pieces[i]->possible_moves_stored[j]));
				//std::cout << "made first black move board\n";
			}
			current_board->black_pieces[i]->selected = false;
		}
	}
end:
	if (is_white_player)
	{
		is_white_player = false;
	}
	else
	{
		is_white_player = true;
	}
}

void AI::make_second_moves()
{
	for (int i = 0; i < first_move_boards.size(); i++)
	{
		first_move_boards[i]->update_pieces_moves();
		if (is_white_player)
		{
			for (int j = 0; j < first_move_boards[i]->white_pieces.size(); j++)
			{
				first_move_boards[i]->white_pieces[j]->selected = true;
				for (int k = 0; k < first_move_boards[i]->white_pieces[j]->possible_moves_stored.size(); k++)
				{
					first_move_boards[i]->owned_boards.push_back(new board(first_move_boards[i], first_move_boards[i]->white_pieces[j], first_move_boards[i]->white_pieces[j]->possible_moves_stored[k]));
					//std::cout << "made second white move board\n";
				}
				first_move_boards[i]->white_pieces[j]->selected = false;
			}
			goto end;
		}
		else
		{
			for (int j = 0; j < first_move_boards[i]->black_pieces.size(); j++)
			{
				first_move_boards[i]->black_pieces[j]->selected = true;
				for (int k = 0; k < first_move_boards[i]->black_pieces[j]->possible_moves_stored.size(); k++)
				{
					first_move_boards[i]->owned_boards.push_back(new board(first_move_boards[i], first_move_boards[i]->black_pieces[j], first_move_boards[i]->black_pieces[j]->possible_moves_stored[k]));
					//std::cout << "made second black move board\n";
				}
				first_move_boards[i]->black_pieces[j]->selected = false;
			}
		}
	end:;
	}
	if (is_white_player)
	{
		is_white_player = false;
	}
	else
	{
		is_white_player = true;
	}
}

void AI::make_third_moves()
{
	for (int i = 0; i < first_move_boards.size(); i++)
	{
		for (int h = 0; h < first_move_boards[i]->owned_boards.size(); h++)
		{
			first_move_boards[i]->owned_boards[h]->update_pieces_moves();
			if (is_white_player)
			{
				for (int j = 0; j < first_move_boards[i]->owned_boards[h]->white_pieces.size(); j++)
				{
					first_move_boards[i]->owned_boards[h]->white_pieces[j]->selected = true;
					for (int k = 0; k < first_move_boards[i]->owned_boards[h]->white_pieces[j]->possible_moves_stored.size(); k++)
					{
						first_move_boards[i]->owned_boards[h]->owned_boards.push_back(new board(first_move_boards[i]->owned_boards[h], first_move_boards[i]->owned_boards[h]->white_pieces[j], first_move_boards[i]->owned_boards[h]->white_pieces[j]->possible_moves_stored[k]));
						//std::cout << "made third white move board\n";
					}
					first_move_boards[i]->owned_boards[h]->white_pieces[j]->selected = false;
				}
				goto end;
			}
			else
			{
				for (int j = 0; j < first_move_boards[i]->owned_boards[h]->black_pieces.size(); j++)
				{
					first_move_boards[i]->owned_boards[h]->black_pieces[j]->selected = true;
					for (int k = 0; k < first_move_boards[i]->owned_boards[h]->black_pieces[j]->possible_moves_stored.size(); k++)
					{
						first_move_boards[i]->owned_boards[h]->owned_boards.push_back(new board(first_move_boards[i]->owned_boards[h], first_move_boards[i]->owned_boards[h] ->black_pieces[j], first_move_boards[i]->owned_boards[h]->black_pieces[j]->possible_moves_stored[k]));
						//std::cout << "made third black move board\n";
					}
					first_move_boards[i]->owned_boards[h]->black_pieces[j]->selected = false;
				}
			}
		end:;
		}
	}
	if (is_white_player)
	{
		is_white_player = false;
	}
	else
	{
		is_white_player = true;
	}
}

void AI::remove_piece(std::vector<piece*> v1, piece* sel)
{
	std::vector<piece*>::iterator it;
	it = v1.begin();
	for (it; it != v1.end(); ++it)
	{
		if (*it==sel)
		{
			v1.erase(it);
			break;
		}
	}
}

void AI::purge_boards()
{
	for (int i = 0; i < first_move_boards.size(); i++)
	{
		if (first_move_boards[i] != current_board)
		{
			for (int j = 0; j < first_move_boards[i]->owned_boards.size(); j++)
			{
				for (int k = 0; k < first_move_boards[i]->owned_boards[j]->owned_boards.size(); k++)
				{
					delete first_move_boards[i]->owned_boards[j]->owned_boards[k];
				}
				first_move_boards[i]->owned_boards[j]->owned_boards.clear();
				delete first_move_boards[i]->owned_boards[j];
			}
			first_move_boards[i]->owned_boards.clear();
			delete first_move_boards[i];
		}
		first_move_boards.clear();
	}
}

void AI::start()
{
	int input;
	std::cout << "How many players?\n";
	std::cin >> input;
	while (input != 1 && input != 2)
	{
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Please input either 1 or 2\n";
		}
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Please input either 1 or 2\n";
		std::cin >> input;
	}
	playing_board.start();
	playing_board.print();
	if (input == 1)
	{
		playing_board.two_player = false;
		while (!playing_board.game_over)
		{
			playing_board.select(0);
			AIturn();
			playing_board.white_move = true;
			playing_board.white_board = true;
		}
	}
	else
	{
		playing_board.two_player = true;
		while (!playing_board.game_over)
		{
			playing_board.select(0);
		}
	}
}

void AI::print_current_positions()
{
	for (int i = 0; i < first_move_boards.size(); i++)
	{
		for (int j = 0; j < first_move_boards[i]->white_pieces.size(); j++)
		{
			std::cout << "White " << first_move_boards[i]->white_pieces[j]->piece_type << " at " << first_move_boards[i]->white_pieces[j]->position << std::endl;
		}
		for (int j = 0; j < first_move_boards[i]->black_pieces.size(); j++)
		{
			std::cout << "Black " << first_move_boards[i]->black_pieces[j]->piece_type << " at " << first_move_boards[i]->black_pieces[j]->position << std::endl;
		}
	}
	for (int i = 0; i < second_move_boards.size(); i++)
	{
		for (int j = 0; j < second_move_boards[i]->white_pieces.size(); j++)
		{
			std::cout << "White " << second_move_boards[i]->white_pieces[j]->piece_type << " at " << second_move_boards[i]->white_pieces[j]->position << std::endl;
		}
		for (int j = 0; j < second_move_boards[i]->black_pieces.size(); j++)
		{
			std::cout << "Black " << second_move_boards[i]->black_pieces[j]->piece_type << " at " << second_move_boards[i]->black_pieces[j]->position << std::endl;
		}
	}
	for (int i = 0; i < third_move_boards.size(); i++)
	{
		for (int j = 0; j < third_move_boards[i]->white_pieces.size(); j++)
		{
			std::cout << "White " << third_move_boards[i]->white_pieces[j]->piece_type << " at " << third_move_boards[i]->white_pieces[j]->position << std::endl;
		}
		for (int j = 0; j < third_move_boards[i]->black_pieces.size(); j++)
		{
			std::cout << "Black " << third_move_boards[i]->black_pieces[j]->piece_type << " at " << third_move_boards[i]->black_pieces[j]->position << std::endl;
		}
	}
}

void AI::save_positions()
{
	white_positions.clear();
	black_positions.clear();
	for (int i = 0; i < current_board->white_pieces.size(); i++)
	{
		white_positions.push_back(current_board->white_pieces[i]->position);
	}
	for (int i = 0; i < current_board->black_pieces.size(); i++)
	{
		black_positions.push_back(current_board->black_pieces[i]->position);
	}
}

void AI::load_positions()
{
	for (int i = 0; i < current_board->white_pieces.size(); i++)
	{
		current_board->white_pieces[i]->position = white_positions[i];
	}
	for (int i = 0; i < current_board->black_pieces.size(); i++)
	{
		current_board->black_pieces[i]->position = black_positions[i];
	}
}

void AI::set_playing_board(board* b)
{
	playing_board = *b;
}

AI::~AI()
{
	delete current_board;
	for (int i = 0; i < first_move_boards.size(); i++)
	{
		delete first_move_boards[i];
	}
}
