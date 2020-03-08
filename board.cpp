#include "board.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

//112=black on white
//119 is blank
//128=black on black
//136 is blank
//124 being attacked on white
//140 being attacked on black

/**************
BOARD GOES FROM 21-98 
******************/

board::board()
{
	load_pieces();
}

void board::start()
{
	selected_piece = nullptr;
	update_pieces_moves();
	/*int input;
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
	print();
	if (input == 1)
	{
		two_player == false;
		while (!game_over)
		{
			select(0);
			AIturn();
			white_move = true;
		}
	}
	else
	{
		two_player == true;
		while (!game_over)
		{
			select(0);
		}
	}*/
}

void board::AIturn()
{
	for (int i = 0; i < black_pieces.size(); i++)
	{
		possible_moves.clear();
		get_possible_moves(black_pieces[i], 0);
		check_moves(black_pieces[i]);
		if (possible_moves.size() == 0)
			continue;
		else
			perform_move(black_pieces[i]);
	}
}

move* board::get_best_move(int depth)
{
	int max_score = -9999;
	for (int i = 0; i < black_pieces.size(); i++)
	{
		possible_moves.clear();
		get_possible_moves(black_pieces[i],0);
		check_moves(black_pieces[i]);
		for (int j = 0; j < possible_moves.size(); j++)
		{
			//possible_moves[j]->score = maxi(depth);
		}
	}
	return possible_moves[0];
}



void board::perform_move(piece* piece)
{
	system("CLS");
	piece->selected = true;
	std::cout << piece->piece_type << std::endl;
	selected_piece = piece;
	print();
	system("PAUSE");
}

void board::update_pieces_moves()
{
	//std::cout << "starting updating moves.\n";
	std::vector<move*> temp;
	if (selected_piece!=nullptr&&selected_piece->piece_type == 5)
	{
		//std::cout << "piece was a king.\n";
		for (int i = 0; i < possible_moves.size(); i++)
			temp.push_back(possible_moves[i]);
	}
	for (int i = 0; i < black_pieces.size(); i++)
	{
			get_possible_moves(black_pieces[i], 1);
			check_moves(black_pieces[i]);
			black_pieces[i]->possible_moves_stored.clear();
			for (int j = 0; j < possible_moves.size(); j++)
				black_pieces[i]->set_moves(possible_moves[j]);
			possible_moves.clear();
	}
	//std::cout << "got all black piece moves.\n";
	for (int i = 0; i < white_pieces.size(); i++)
	{
		//std::cout << "white pieces size is " << white_pieces.size() << std::endl;
		//std::cout << "attempting a white piece move.\n";
			get_possible_moves(white_pieces[i], 1);
			//std::cout << "got possible moves.\n";
			check_moves(white_pieces[i]);
			//std::cout << "checked possible moves.\n";
			//std::cout << i << std::endl;
			//std::cout << "piece is " << white_pieces[i]->type_name << std::endl;				//CANT ACCESS PIECE BECAUSE IT WAS TAKEN AND DELETED
			white_pieces[i]->possible_moves_stored.clear();
			//std::cout << "cleared pieces old possible moves and now giving new moves.\n";
			for (int j = 0; j < possible_moves.size(); j++)
				white_pieces[i]->set_moves(possible_moves[j]);
			//std::cout << "finished giving new moves now clearing vector of new moves.\n";
			possible_moves.clear();
			//std::cout << "finished a white piece move.\n";
	}
	//std::cout << "got all white piece moves.\n";
	for (int i = 0; i < black_pieces.size(); i++)
	{
		if (black_pieces[i]->is_targeted == true)
			black_pieces[i]->is_targeted = false;
	}
	for (int i = 0; i < white_pieces.size(); i++)
	{
		if (white_pieces[i]->is_targeted == true)
			white_pieces[i]->is_targeted = false;
	}
	if (selected_piece!=nullptr&&selected_piece->piece_type == 5)
	{
		for (int i=0; i<temp.size();i++)
			possible_moves.push_back(temp[i]);
	}
	for (int i = 0; i < temp.size(); i++)
	{
		delete temp[i];
	}
	//std::cout << "got out of updating.\n";
}

void board::select(int turn)
{
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
	}
	if (white_move)
	{
		for (int i = 0; i < white_pieces.size(); i++)
			white_pieces[i]->just_jumped = false;
	}
	else
	{
		for (int i = 0; i < black_pieces.size(); i++)
			black_pieces[i]->just_jumped = false;
	}
	system("CLS");
	print();
	char letter, number;
	int first, second, pos = 0;
	std::string input = "";
	std::cout << "Please select a piece using the coordinates (A3 for example):\n";
	std::cin >> input;
	while (input.size() != 2)
	{
		system("CLS");
		if (input.size() > 2)
		{
			std::cout << "Woah there cowboy maybe just 2 characters at a time please.\n";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		if (input.size() < 2)
		{
			std::cout << "Come on, I'm gonna need more than just one character to select a piece\n";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
		}
		print();
		std::cin >> input;
	}
	letter = input[0];
	number = input[1];
	if (white_move)
	{
		first = (10 - (static_cast<int>(number) - 48)) * 10;
		second = static_cast<int>(letter) - 64;
		pos = first + second;
	}
	else
	{
		first = ((1+(static_cast<int>(number) - 48)) * 10);
		second = 73 - static_cast<int>(letter);
		pos = first + second;
	}
	bool found = false;
	for (int i = 0; i < white_pieces.size(); i++)
	{
		if (white_pieces[i]->position == pos && white_move)
		{
			white_pieces[i]->selected = true;
			selected_piece = white_pieces[i];
			found = true;
		}
		if (white_pieces[i]->position == pos && !white_move)
		{
			std::cout << "That is not your piece.\n";
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			Sleep(1000);
			select(turn);
		}
	}
	for (int i = 0; i < black_pieces.size(); i++)
	{
		if (black_pieces[i]->position == pos && !white_move)
		{
		black_pieces[i]->selected = true;
		selected_piece = black_pieces[i];
		found = true;
		}
		if (black_pieces[i]->position == pos && white_move)
		{
		std::cout << "That is not your piece.\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		Sleep(1000);
		select(turn);
		}
	}
	if (!found)
	{
		std::cout << "Please choose a square with piece in it.\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		Sleep(1000);
		select(turn);
	}
	system("CLS");
	if (turn != 1)
	{
		movement(selected_piece, turn);
		selected_piece->selected = false;
	}
		possible_moves.clear();
		if (white_move)
		{
			for (int i = 0; i < black_pieces.size(); i++)
				black_pieces[i]->is_targeted = false;
		}
		if (!white_move)
		{
			for (int i = 0; i < white_pieces.size(); i++)
				white_pieces[i]->is_targeted = false;
		}
		if (turn != 1)
		{
			if (white_move)
				white_move = false;
			else
				white_move = true;
		}
		system("CLS");
}

void board::movement(piece* selected, int turn)
{
beginning:
	char letter, number;
	int first, second, pos;
	bool move_found = false;
	std::string move_input;
	possible_moves.clear();
	get_possible_moves(selected_piece, 0);
	check_moves(selected_piece);
	selected_piece->possible_moves_stored.clear();
	for (int i = 0; i < possible_moves.size(); i++)
	{
		selected_piece->set_moves(possible_moves[i]);
	}
	print();
	std::cout << "Where would you like to move?\n";
	std::cin >> move_input;
	if (move_input == "qq" || move_input == "QQ")
	{
		selected_piece->selected = false;
		possible_moves.clear();
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		if (white_move)
		{
			for (int i = 0; i < black_pieces.size(); i++)
				black_pieces[i]->is_targeted = false;
		}
		if (!white_move)
		{
			for (int i = 0; i < white_pieces.size(); i++)
				white_pieces[i]->is_targeted = false;
		}

		select(1);
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		goto beginning;
	}
	while (move_input.size() != 2)
	{
		system("CLS");
		if (move_input.size() > 2)
		{
			std::cout << "Woah there cowboy maybe just 2 characters at a time please.\n";
			std::cin.clear();
			std::cin.ignore(1000,'\n');
		}
		if (move_input.size() < 2)
		{
			std::cout << "Come on, I'm gonna need more than just one character to select a square\n";
			std::cin.ignore();
			std::cin.clear(1000,'\n');
		}
		print();
		std::cin >> move_input;
	}
	letter = move_input[0];
	number = move_input[1];
	if (selected_piece->is_white)
	{
		first = (10 - (static_cast<int>(number) - 48)) * 10;
		second = static_cast<int>(letter) - 64;
		pos = first + second;
	}
	else
	{
		first = ((1 + (static_cast<int>(number) - 48)) * 10);
		second = 73 - static_cast<int>(letter);
		pos = first + second;
	}
	move* move_being_made = nullptr;
	for (int i = 0; i < possible_moves.size(); i++)
	{
		if (pos == possible_moves[i]->move_position)
		{
			move_being_made = possible_moves[i];
			move_found = true;
			if (possible_moves[i]->qcastling_move)
			{
					if (selected_piece->is_white)
					{
						for (int i = 0; i < white_pieces.size(); i++)
						{
							if (white_pieces[i]->position == 98)
							{
								white_pieces[i]->position = 95;
								break;
							}
						}
					}
					else
					{
						for (int i = 0; i < black_pieces.size(); i++)
						{
							if (black_pieces[i]->position == 91)
							{
								black_pieces[i]->position = 94;
								break;
							}
						}
					}
			}
			if (possible_moves[i]->castling_move)
			{
				if (selected_piece->is_white)
				{
					for (int i = 0; i < white_pieces.size(); i++)
					{
						if (white_pieces[i]->position == 91)
						{
							white_pieces[i]->position = 93;
							break;
						}
					}
				}
				else
				{
					for (int i = 0; i < black_pieces.size(); i++)
					{
						if (black_pieces[i]->position == 98)
						{
							black_pieces[i]->position = 96;
							break;
						}
					}
				}
			}
			if (possible_moves[i]->en_passant)
			{
				selected->just_jumped = true;
			}
			if (possible_moves[i]->passant_attack)
			{
				if (white_move)
				{
					for (int j = 0; j < black_pieces.size(); j++)
					{
						if (black_pieces[j]->piece_type == 0 && black_pieces[j]->position == possible_moves[i]->move_position + 10)
							take_piece(black_pieces, j);
					}
				}
			}
		}
	}
	if (white_move && move_found)
	{
		for (int i = 0; i < black_pieces.size(); i++)
		{
			if (pos == black_pieces[i]->position)
			{
				if (black_pieces[i] == black_king)
					game_over = true;
				take_piece(black_pieces, i);
				break;
			}
		}
	}
	else if (move_found)
	{
		for (int i = 0; i < white_pieces.size(); i++)
		{
			if (pos == white_pieces[i]->position)
			{
				if (white_pieces[i] == white_king)
					game_over = true;
				take_piece(white_pieces, i);
				break;
			}
		}
	}
	if (move_found)
	{
		int temp = selected_piece->position;
		selected_piece->position = pos;
		if (white_move&&white_king->is_in_check)
		{
			check_for_check(white_king);
			if (white_king->is_in_check)
			{
				selected_piece->position = temp;
				std::cout << "Invalid move. King must be taken out of check.\n";
				Sleep(1000);
				system("CLS");
				movement(selected_piece, turn);
			}
		}
		if (!white_move&&black_king->is_in_check)
		{
			check_for_check(black_king);
			if (black_king->is_in_check)
			{
				std::cout << "Invalid move. King must be taken out of check.\n";
				Sleep(1000);
				system("CLS");
				selected_piece->position = temp;
				movement(selected_piece, turn);
			}
			
		}
		if (white_move)
		{
			check_for_check(white_king);
			if (white_king->is_in_check)
			{
				selected_piece->position = temp;
				std::cout << "Cannot put own king in check!\n";
				Sleep(1000);
				system("CLS");
				movement(selected_piece, turn);
			}
			if (move_being_made->passant_attack)
			{
				for (int i = 0; i < black_pieces.size(); i++)
				{
					if (black_pieces[i]->piece_type == 0 && black_pieces[i]->position == selected->position + 10)
					{
						take_piece(black_pieces, i);
					}
				}
			}
		}
		else
		{
			check_for_check(black_king);
			if (black_king->is_in_check)
			{
				selected_piece->position = temp;
				std::cout << "Cannot put own king in check!\n";
				Sleep(1000);
				system("CLS");
				movement(selected_piece, turn);
			}
			if (move_being_made->passant_attack)
			{
				if (two_player)
				{
					for (int i = 0; i < white_pieces.size(); i++)
					{
						if (white_pieces[i]->piece_type == 0 && white_pieces[i]->position == selected->position + 10)
						{
							take_piece(white_pieces, i);
						}
					}
				}
				else
				{
					for (int i = 0; i < white_pieces.size(); i++)
					{
						if (white_pieces[i]->piece_type == 0 && white_pieces[i]->position == selected->position - 10)
						{
							take_piece(white_pieces, i);
						}
					}
				}
			}
		}
		if ((selected_piece->piece_type == 0 && selected_piece->hasnt_moved)||(selected_piece->piece_type==5 &&selected_piece->hasnt_moved)||(selected_piece->piece_type==3&&selected_piece->hasnt_moved))
		{
			selected_piece->hasnt_moved = false;
		}
	}
	else if (!move_found)
	{
		std::cout << "Please make a valid move.\n";
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		Sleep(1000);
		system("CLS");
		movement(selected_piece, turn);
	}
	check_for_check(black_king);
	check_for_check(white_king);
}

void board::take_piece(std::vector<piece*>& v1, int i)
{
	v1[i]->possible_moves_stored.clear();
	delete v1[i];
	v1.erase(v1.begin() + i);
}

void board::get_possible_moves(piece* selected, int i)
{
	switch (selected->piece_type)
	{
	case 0: //pawn
	{
		if (two_player)
		{
			if (selected->hasnt_moved)
			{
				possible_moves.push_back(new move(selected->position - 10));
				possible_moves.push_back(new move(selected->position - 20, "passant"));
			}
			else
			{
				possible_moves.push_back(new move(selected->position - 10));
			}
		}
		else
		{
			if (white_move)
			{
				if (selected->hasnt_moved)
				{
					possible_moves.push_back(new move(selected->position - 10));
					possible_moves.push_back(new move(selected->position - 20, "passant"));
				}
				else
				{
					possible_moves.push_back(new move(selected->position - 10));
				}
			}
			else
			{
				if (selected->hasnt_moved)
				{
					possible_moves.push_back(new move(selected->position + 10));
					possible_moves.push_back(new move(selected->position + 20, "passant"));
				}
				else
				{
					possible_moves.push_back(new move(selected->position + 10));
				}
			}
		}
		if (white_move)
		{
			for (int i = 0; i < black_pieces.size(); i++)
			{
				if (black_pieces[i]->position == selected->position - 11 || black_pieces[i]->position == selected->position - 9)
				{
					black_pieces[i]->is_targeted = true;
					possible_moves.push_back(new move(black_pieces[i]->position));
				}
				if (black_pieces[i]->piece_type == 0 && black_pieces[i]->just_jumped && (black_pieces[i]->position == selected->position - 1 || black_pieces[i]->position == selected->position + 1))
				{
					black_pieces[i]->is_targeted = true;
					possible_moves.push_back(new move(black_pieces[i]->position-10, "passant_attack"));
				}
			}
		}
		else if (!white_move&&two_player)
		{
			for (int i = 0; i < white_pieces.size(); i++)
			{
				if (white_pieces[i]->position == selected->position - 11 || white_pieces[i]->position == selected->position - 9)
				{
					white_pieces[i]->is_targeted = true;
					possible_moves.push_back(new move(white_pieces[i]->position));
				}
				if (white_pieces[i]->piece_type == 0 && white_pieces[i]->just_jumped && (white_pieces[i]->position == selected->position - 1 || white_pieces[i]->position == selected->position + 1))
				{
					white_pieces[i]->is_targeted = true;
					possible_moves.push_back(new move(white_pieces[i]->position - 10, "passant_attack"));
				}
			}
		}
		else if (!white_move&&!two_player)
		{
			for (int i = 0; i < white_pieces.size(); i++)
			{
				if (white_pieces[i]->position == selected->position + 11 || white_pieces[i]->position == selected->position + 9)
				{
					white_pieces[i]->is_targeted = true;
					possible_moves.push_back(new move(white_pieces[i]->position,"pawn_attack"));
				}
				if (white_pieces[i]->piece_type == 0 && white_pieces[i]->just_jumped && (white_pieces[i]->position == selected->position + 1 || white_pieces[i]->position == selected->position - 1))
				{
					white_pieces[i]->is_targeted = true;
					possible_moves.push_back(new move(white_pieces[i]->position + 10, "passant_attack"));
				}
			}
		}
		else if (white_move&&!two_player)
		{
			for (int i = 0; i < black_pieces.size(); i++)
			{
				if (black_pieces[i]->position == selected->position - 11 || black_pieces[i]->position == selected->position - 9)
				{
					black_pieces[i]->is_targeted = true;
					possible_moves.push_back(new move(black_pieces[i]->position,"pawn_attack"));
				}
				if (black_pieces[i]->piece_type == 0 && black_pieces[i]->just_jumped && (black_pieces[i]->position == selected->position - 1 || black_pieces[i]->position == selected->position + 1))
				{
					black_pieces[i]->is_targeted = true;
					possible_moves.push_back(new move(black_pieces[i]->position - 10, "passant_attack"));
				}
			}
		}
		break;
	}
	case 1: //knight
	{
		possible_moves.push_back(new move(selected->position + 12));
		possible_moves.push_back(new move(selected->position - 12));
		possible_moves.push_back(new move(selected->position - 19));
		possible_moves.push_back(new move(selected->position - 21));
		possible_moves.push_back(new move(selected->position + 19));
		possible_moves.push_back(new move(selected->position + 21));
		possible_moves.push_back(new move(selected->position - 8));
		possible_moves.push_back(new move(selected->position + 8));
		break;
	}
	case 2: //bishop
	{
		make_straight_line(11, 7, selected);
		make_straight_line(-11, 7, selected);
		make_straight_line(9, 7, selected);
		make_straight_line(-9, 7, selected);
		break;
	}
	case 3: //rook
	{
		make_straight_line(10, 7, selected);
		make_straight_line(-10, 7, selected);
		make_straight_line(1, 7, selected);
		make_straight_line(-1, 7, selected);
		break;
	}
	case 4: //queen
	{
		make_straight_line(11, 7, selected);
		make_straight_line(-11, 7, selected);
		make_straight_line(9, 7, selected);
		make_straight_line(-9, 7, selected);
		make_straight_line(10, 7, selected);
		make_straight_line(-10, 7, selected);
		make_straight_line(1, 7, selected);
		make_straight_line(-1, 7, selected);
		break;
	}
	case 5: //king
	{
		if (i == 1)
			goto AI;
		check_castle(selected, "king");
		check_castle(selected, "queen");
		AI:
		make_straight_line(11, 1, selected);
		make_straight_line(-11, 1, selected);
		make_straight_line(9, 1, selected);
		make_straight_line(-9, 1, selected);
		make_straight_line(10, 1, selected);
		make_straight_line(-10, 1, selected);
		make_straight_line(1, 1, selected);
		make_straight_line(-1, 1, selected);
		break;
	}
	}
}

void board::check_for_check(piece* king)
{
	bool check_found = false;
	update_pieces_moves();
	if (king->is_white)
	{
		for (int i = 0; i < black_pieces.size(); i++)
		{
			for (int j = 0; j < black_pieces[i]->possible_moves_stored.size(); j++)
			{
				if (black_pieces[i]->possible_moves_stored[j]->move_position == king->position)
				{
					check_found = true;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < white_pieces.size(); i++)
		{
			for (int j = 0; j < white_pieces[i]->possible_moves_stored.size(); j++)
			{
				if (white_pieces[i]->possible_moves_stored[j]->move_position == king->position)
				{
					check_found = true;
				}
			}
		}
	}
	if (check_found)
		king->is_in_check = true;
	else
		king->is_in_check = false;
}

void board::check_moves(piece* selected)
{
	int temp;
	std::vector<int> moves_to_remove;
	for (int k = 0; k < possible_moves.size(); k++)
	{
		if (possible_moves[k]->move_position % 10 == 0 || (possible_moves[k]->move_position + 1) % 10 == 0)
			moves_to_remove.push_back(possible_moves[k]->move_position);
		if (possible_moves[k]->move_position > 98 || possible_moves[k]->move_position < 21)
			moves_to_remove.push_back(possible_moves[k]->move_position);
	}
	if (selected->is_white)
	{
		for (int i = 0; i < possible_moves.size(); i++)
		{
			for (int j = 0; j < white_pieces.size(); j++)
			{
				if (white_pieces[j] == selected)
					continue;
				if (possible_moves[i]->move_position == white_pieces[j]->position)
				{
					moves_to_remove.push_back(possible_moves[i]->move_position);
				}
				
			}
			
		}

	w_start_over:
		for (int i = 0; i < possible_moves.size(); i++)
		{
			for (int j = 0; j < moves_to_remove.size(); j++)
			{
				if (possible_moves[i]->move_position == moves_to_remove[j])
				{
					possible_moves.erase(possible_moves.begin() + i);
					goto w_start_over;
				}
			}
		}
		if (selected->piece_type != 0)
		{
			for (int i = 0; i < possible_moves.size(); i++)
			{
				for (int j = 0; j < black_pieces.size(); j++)
				{
					if (possible_moves[i]->move_position == black_pieces[j]->position)
						black_pieces[j]->is_targeted = true;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < possible_moves.size(); i++)
		{
			for (int j = 0; j < black_pieces.size(); j++)
			{
				if (possible_moves[i]->move_position == black_pieces[j]->position)
				{
					if (black_pieces[j] == selected)
						continue;
					moves_to_remove.push_back(possible_moves[i]->move_position);
				}
			}
		}

	b_start_over:
		for (int i = 0; i < possible_moves.size(); i++)
		{
			for (int j = 0; j < moves_to_remove.size(); j++)
			{
				if (possible_moves[i]->move_position == moves_to_remove[j])
				{
					possible_moves.erase(possible_moves.begin() + i);
					goto b_start_over;
				}
			}
		}
		if (selected->piece_type != 0)
		{
			for (int i = 0; i < possible_moves.size(); i++)
			{
				for (int j = 0; j < white_pieces.size(); j++)
				{
					if (possible_moves[i]->move_position == white_pieces[j]->position)
						white_pieces[j]->is_targeted = true;
				}
			}
		}
	}
}

void board::reverse_pieces()
{
	int start, first_dig, second_dig;
	for (int i = 0; i < white_pieces.size(); i++)
	{
		start = white_pieces[i]->position;
		first_dig = (11 - (start / 10)) * 10;
		second_dig = 9 - (start % 10);
		white_pieces[i]->position = first_dig + second_dig;
	}
	for (int i=0; i<black_pieces.size();i++)
	{
		start = black_pieces[i]->position;
		first_dig = (11 - (start / 10)) * 10;
		second_dig = 9 - (start % 10);
		black_pieces[i]->position = first_dig + second_dig;
	}
}

void board::print()
{
	if (output_board[20] == "8 ")
		white_board = true;
	else
		white_board = false;
	if (white_move&&!white_board&&two_player)
	{
			reverse_board();
			reverse_pieces();
	}
	if (!white_move&&white_board&&two_player)
	{
		reverse_board();
		reverse_pieces();
	}
	if (output_board[20] == "8 ")
		white_board = true;
	else
		white_board = false;
	bool check = false; //checking if piece was there
	int row_counter = 0;
	for (int i = 0; i < 120; i++)
	{
		if ((i + 1) % 10 == 0)
			row_counter++;
		if ((i+row_counter)%2==0)
			SetConsoleTextAttribute(hConsole, 119);
		else
			SetConsoleTextAttribute(hConsole, 136);
		if (i%10==0)
			SetConsoleTextAttribute(hConsole, 15);
		for (int j = 0; j < white_pieces.size(); j++)
		{

			if (i == white_pieces[j]->position)
			{
				if ((i + row_counter) % 2 == 0)
					SetConsoleTextAttribute(hConsole, 119);
				else
					SetConsoleTextAttribute(hConsole, 136);
				std::cout << "#";
				if ((i + row_counter) % 2 == 0) //changing piece color white
				{
					if (white_pieces[j]->is_targeted)
						SetConsoleTextAttribute(hConsole, 124);
					else
						SetConsoleTextAttribute(hConsole, 112);
				}
				else //changing piece color black
				{
					if (white_pieces[j]->is_targeted)
						SetConsoleTextAttribute(hConsole, 140);
					else
						SetConsoleTextAttribute(hConsole, 128);
				}
				white_pieces[j]->print();
				if ((i + row_counter) % 2 == 0)
					SetConsoleTextAttribute(hConsole, 119);
				else
					SetConsoleTextAttribute(hConsole, 136);
				std::cout << "#";
				check = true;
			}
		}
		for (int j=0; j<black_pieces.size();j++)
		{
			if (i == black_pieces[j]->position)
			{
				if ((i + row_counter) % 2 == 0)
					SetConsoleTextAttribute(hConsole, 119);
				else
					SetConsoleTextAttribute(hConsole, 136);
				std::cout << "#";
				if ((i + row_counter) % 2 == 0) //changing piece color white
				{
					if (black_pieces[j]->is_targeted)
						SetConsoleTextAttribute(hConsole, 124);
					else
						SetConsoleTextAttribute(hConsole, 112);
				}
				else //changing piece color black
				{
					if (black_pieces[j]->is_targeted) //changes for selected
						SetConsoleTextAttribute(hConsole, 140);
					else
						SetConsoleTextAttribute(hConsole, 128);
				}
				black_pieces[j]->print();
				if ((i + row_counter) % 2 == 0)
					SetConsoleTextAttribute(hConsole, 119);
				else
					SetConsoleTextAttribute(hConsole, 136);
				std::cout << "#";
				check = true;
			}
		}
		if (check) //if piece was there dont output ###
		{
			check = false;
			continue;
		}
		bool skip = false;
		for (int k = 0; k < possible_moves.size(); k++) //highlighting possible moves
		{
			if (i == possible_moves[k]->move_position)
			{
				if ((i + row_counter) % 2 == 0)
					SetConsoleTextAttribute(hConsole, 119);
				else
					SetConsoleTextAttribute(hConsole, 136);
				std::cout << "#";
				if ((i + row_counter) % 2 == 0)
					SetConsoleTextAttribute(hConsole, 122);
				else
					SetConsoleTextAttribute(hConsole, 138);
				selected_piece->print();
				if ((i + row_counter) % 2 == 0)
					SetConsoleTextAttribute(hConsole, 119);
				else
					SetConsoleTextAttribute(hConsole, 136);
				std::cout << "#";
				skip = true;
			}
		}
		if (skip)
			continue;
		std::cout << output_board[i];	
	}
	SetConsoleTextAttribute(hConsole, 15);
	std::cout << std::endl;
	if (white_board)
		std::cout << "   A  B  C  D  E  F  G  H\n";
	else
		std::cout << "   H  G  F  E  D  C  B  A\n";
	if (white_king->is_in_check)
	{
		std::cout << std::endl << "White King is in Check!\n";
	}
	if (black_king->is_in_check)
	{
		std::cout << std::endl << "Black King is in Check!\n";
	}
}

void board::load_pieces()
{
	
	for (int i = 0; i < 8; i++)
	{
		white_pieces.push_back(new pawn(i,0,81+i)); //white pawns
		black_pieces.push_back(new pawn(i,1,31+i)); //black pawns
		if (i < 2)
		{
			white_pieces.push_back(new knight(i,0,92+(5*i)));
			black_pieces.push_back(new knight(i,1,22+(5*i)));
			white_pieces.push_back(new bishop(i,0,93+(3*i)));
			black_pieces.push_back(new bishop(i,1,23+(3*i)));
			white_pieces.push_back(new rook(i,0,91+(7*i)));
			black_pieces.push_back(new rook(i, 1, 21+(7*i)));
		}
		if (i < 1)
		{
			white_pieces.push_back(new queen(i,0,95) );
			black_pieces.push_back(new queen(i,1,25));
		}
	}
	white_king = new king(0, 0, 94);
	white_pieces.push_back(white_king);
	black_king = new king(0, 1, 24);
	black_pieces.push_back(black_king);
	for (int i = 0; i < 120; i++)
	{
		char row = static_cast<char>(47 + (i / 10));
		
		if (i >= 21 && i <= 98)
			output_board[i] = "###";
		
		if ((i+1) % 10 == 0)
			output_board[i] = "\n";
		if (i % 10 == 0)
			output_board[i] = std::to_string(9-(i/10-1))+" ";
		if (i <20 || i>98)
			output_board[i] = "";
		
	}
}

void board::reverse_board()
{
	for (int i = 0; i < 120; i++)
	{
		if (output_board[i] == "1 ")
			output_board[i] = "8 ";
		else if (output_board[i] == "2 ")
			output_board[i] = "7 ";
		else if (output_board[i] == "3 ")
			output_board[i] = "6 ";
		else if (output_board[i] == "4 ")
			output_board[i] = "5 ";
		else if (output_board[i] == "5 ")
			output_board[i] = "4 ";
		else if (output_board[i] == "6 ")
			output_board[i] = "3 ";
		else if (output_board[i] == "7 ")
			output_board[i] = "2 ";
		else if (output_board[i] == "8 ")
			output_board[i] = "1 ";

	}
}

void board::check_castle(piece* king, std::string side)
{
	int sign = 1;
	if (side == "queen")
		sign = -1;
	if (side == "king")
		sign = 1;
	int temp = king->position;
	if (king->hasnt_moved) //castling is a bitch part 1
	{
		if (king->is_white)
		{
			for (int i = 0; i < white_pieces.size(); i++) //both loops work in general to see if any pieces are in the way
			{
				if (white_pieces[i]->position == king->position - (sign*1) || white_pieces[i]->position == king->position - (sign * 2))
				{
					goto end;
				}
			}
			for (int i = 0; i < black_pieces.size(); i++)
			{
				if (black_pieces[i]->position == king->position - (sign * 1) || black_pieces[i]->position == king->position - (sign * 2))
				{
					goto end;
				}
			}
		}
		else
		{
			for (int i = 0; i < white_pieces.size(); i++) //both loops work in general to see if any pieces are in the way
			{
				if (white_pieces[i]->position == king->position + (sign * 1) || white_pieces[i]->position == king->position + (sign * 2))
				{
					goto end;
				}
			}
			for (int i = 0; i < black_pieces.size(); i++)
			{
				if (black_pieces[i]->position == king->position + (sign * 1) || black_pieces[i]->position == king->position + (sign * 2))
				{
					goto end;
				}
			}
		}
		if (white_move) //just white stuff
		{
			for (int i = 0; i < white_pieces.size(); i++)
			{
				if (white_pieces[i]->position == 91 && white_pieces[i]->hasnt_moved&&white_pieces[i]->piece_type == 3)
				{
					check_for_check(white_king);
					if (!white_king->is_in_check)
					{
						white_king->position = white_king->position - (sign * 1);
						check_for_check(white_king);
						if (!white_king->is_in_check)
						{
							white_king->position = white_king->position - (sign * 1);
							check_for_check(white_king);
							if (!white_king->is_in_check)
							{
								if (side=="queen")
									possible_moves.push_back(new move(white_king->position, "qcastle"));
								else
									possible_moves.push_back(new move(white_king->position, "castle"));
								white_king->position += (sign * 2);
							}
						}
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < black_pieces.size(); i++)
			{
				if (black_pieces[i]->position == 98 && black_pieces[i]->hasnt_moved&&black_pieces[i]->piece_type == 3)
				{
					check_for_check(black_king);
					if (!black_king->is_in_check)
					{
						black_king->position = black_king->position + (sign * 1);
						check_for_check(black_king);
						if (!black_king->is_in_check)
						{
							black_king->position = black_king->position + (sign * 1);
							check_for_check(black_king);
							if (!black_king->is_in_check)
							{
								if (side == "queen")
									possible_moves.push_back(new move(black_king->position, "qcastle"));
								else
									possible_moves.push_back(new move(black_king->position, "castle"));
								black_king->position -= (sign * 2);
							}
						}
					}
				}
			}
		}
	}
	end:
	king->position = temp;
	king->is_in_check = false;
}

void board::make_straight_line(int increment, int size, piece* selected)
{
	bool was_found = false;
	bool target_was_found = false;
	if (selected->is_white)
	{
		for (int i = 1; i < size+1; i++)
		{
			for (int j = 0; j < white_pieces.size(); j++)
			{
				if (selected->position + (increment * i) == white_pieces[j]->position || selected->position + (increment * i) % 10 == 0 || (selected->position + (increment * i) + 1) % 10 == 0)
					was_found = true;

			}
			for (int j = 0; j < black_pieces.size(); j++)
			{
				if (selected->position + (increment * i) == black_pieces[j]->position)
					target_was_found = true;
			}
			if (target_was_found)
			{
				possible_moves.push_back(new move(selected->position + (increment * i)));
				break;
			}
			if (was_found)
				break;
			else
				possible_moves.push_back(new move(selected->position + (increment * i)));
		}
	}
	else
	{
		for (int i = 1; i < size+1; i++)
		{
			for (int j = 0; j < black_pieces.size(); j++)
			{
				if (selected->position + (increment * i) == black_pieces[j]->position || selected->position + (increment * i) % 10 == 0 || (selected->position + (increment * i) + 1) % 10 == 0)
					was_found = true;
			}
			for (int j = 0; j < white_pieces.size(); j++)
			{
				if (selected->position + (increment * i) == white_pieces[j]->position)
					target_was_found = true;
			}
			if (target_was_found)
			{
				possible_moves.push_back(new move(selected->position + (increment * i)));
				break;
			}
			if (was_found)
				break;
			else
				possible_moves.push_back(new move(selected->position + (increment * i)));
		}
	}
}


board::~board()
{
	for (int i = 0; i < white_pieces.size(); i++)
	{
		delete white_pieces[i];
	}
	for (int i = 0; i < black_pieces.size(); i++)
	{
		delete black_pieces[i];
	}
	for (int i = 0; i < possible_moves.size(); i++)
	{
		delete possible_moves[i];
	}
}







board::board(board* prev, piece* sel, move* mov)					//CANT USE SAME POINTER BECAUSE ITLL MOVE POSITION FOREVER NEED TO MAKE A NEW PIECE WITH A COPY CONSTRUCTOR
{
	two_player = false;
	if (prev->white_move)
	{
		white_move = false;
	}
	else
	{
		white_move = true;
	}
	//std::cout << "made it into constructor.\n";
	white_king = prev->white_king;
	black_king = prev->black_king;
	for (int i = 0; i < prev->white_pieces.size(); i++)
	{
		//std::cout << "going to add new white piece.\n";
		if (!prev->white_pieces[i]->has_been_taken)
		{
			white_pieces.push_back(new piece(prev->white_pieces[i]));
			if (prev->white_pieces[i] == sel)
			{
				white_pieces[white_pieces.size() - 1]->selected = true;
			}
		}
		//std::cout << "added new white piece.\n";
	}
	for (int i = 0; i < white_pieces.size(); i++)
	{
		if (white_pieces[i]->selected)
		{
			int temp = white_pieces[i]->position;
			white_pieces[i]->position = mov->move_position;
			if (white_king->is_in_check)
			{
				check_for_check(white_king);
				if (white_king->is_in_check)
				{
					white_pieces[i]->position = temp;
					std::cout << "Invalid move. White King must be taken out of check.\n";
					goto invalid_board;
				}
			}
			if (white_pieces[i]->selected&&white_pieces[i] == white_king)
			{
				check_for_check(white_king);
				if (white_king->is_in_check)
				{
					white_pieces[i]->position = temp;
					std::cout << "Cannot put own king in check!\n";
					goto invalid_board;
				}
			}
			for (int k = 0; k < black_pieces.size(); k++)
			{
				if (white_pieces[i]->position == black_pieces[k]->position)
				{
					//std::cout << "attempting to take black piece.\n";
					//take_piece(black_pieces, k);
					if (white_pieces[i]->piece_type == 0)
					{
						if (mov->pawn_attack || mov->passant_attack)
						{

						}
						else
						{
							goto invalid_board;
						}
					}
					black_pieces[k]->has_been_taken = true;
					//std::cout << "was able to take black piece.\n";
				}
			}
			if ((white_pieces[i]->piece_type == 0 && white_pieces[i]->hasnt_moved) || (white_pieces[i]->piece_type == 5 && white_pieces[i]->hasnt_moved) || (white_pieces[i]->piece_type == 3 && white_pieces[i]->hasnt_moved))
			{
				white_pieces[i]->hasnt_moved = false;
			}
			white_pieces[i]->selected = false;
		}
	}
	
	for (int i = 0; i < prev->black_pieces.size(); i++)
	{
		//std::cout << "attempting to add new black piece.\n";
		if (!prev->black_pieces[i]->has_been_taken)
		{
			black_pieces.push_back(new piece(prev->black_pieces[i]));
			if (prev->black_pieces[i] == sel)
			{
				black_pieces[black_pieces.size() - 1]->selected = true;
			}
		}
		//std::cout << "added new black piece.\n";
	}
	for (int i=0;i<black_pieces.size();i++)
	{
		if (black_pieces[i]->selected)
		{
			//std::cout << "attempting to move the selected piece.\n";
			int temp = black_pieces[i]->position;
			black_pieces[i]->position = mov->move_position;
			//std::cout << "moved selected piece.\n";
			if (black_king->is_in_check)
			{
				check_for_check(black_king);
				if (black_king->is_in_check)
				{
					black_pieces[i]->position = temp;
					std::cout << "Invalid move. Black King must be taken out of check.\n";
					goto invalid_board;
				}
			}
			//std::cout << "checking if selected is black king.\n";
			if (black_pieces[i]->selected&&black_pieces[i] == black_king)
			{
				//std::cout << "is black king.\n";
				check_for_check(black_king);
				if (black_king->is_in_check)
				{
					black_pieces[i]->position = temp;
					std::cout << "Cannot put own king in check!\n";
					goto invalid_board;
				}
			}
			//std::cout << "time to check if a piece needs to be taken.\n";
			for (int k = 0; k < white_pieces.size(); k++)
			{
				//std::cout << "was able to access white pieces.\n";
				if (black_pieces[i]->position == white_pieces[k]->position)
				{
					//std::cout << "attempting to take white piece.\n";
					//take_piece(white_pieces, k);
					if (black_pieces[i]->piece_type == 0)
					{
						if (mov->pawn_attack || mov->passant_attack)
						{

						}
						else
						{
							goto invalid_board;
						}
					}
					white_pieces[k]->has_been_taken = true;
					//std::cout << "was able to take white piece.\n";
				}
			}
			if ((black_pieces[i]->piece_type == 0 && black_pieces[i]->hasnt_moved) || (black_pieces[i]->piece_type == 5 && black_pieces[i]->hasnt_moved) || (black_pieces[i]->piece_type == 3 && black_pieces[i]->hasnt_moved))
			{
				black_pieces[i]->hasnt_moved = false;
			}
			black_pieces[i]->selected = false;
		}
		
	}
	for (int i = 0; i < 120; i++)
	{
		char row = static_cast<char>(47 + (i / 10));

		if (i >= 21 && i <= 98)
			output_board[i] = "###";

		if ((i + 1) % 10 == 0)
			output_board[i] = "\n";
		if (i % 10 == 0)
			output_board[i] = std::to_string(9 - (i / 10 - 1)) + " ";
		if (i < 20 || i>98)
			output_board[i] = "";
	}
	if (false)
	{
	invalid_board:
		is_valid = false;
	}
	//previous_board = prev;
	move_to_get_here = mov;
	current_score = get_score();
}

int board::get_score()
{
	int score = 0;
	for (int i = 0; i < white_pieces.size(); i++)
	{
		if (!white_pieces[i]->has_been_taken)
		{
			score += white_pieces[i]->value;
		}
	}
	for (int i = 0; i < black_pieces.size(); i++)
	{
		if (!black_pieces[i]->has_been_taken)
		{
			score -= black_pieces[i]->value;
		}
	}
	return score;
}

/*
move* board::find_best_move(int depth, bool white_player, int score)
{
	save_positions();
	int max_score = -9999;
	int min_score = 99999;
	int temp_score = 0;
	move* best_move = nullptr;
	update_pieces_moves();
	if (white_player)
	{
		for (int i = 0; i < white_pieces.size(); i++)
		{
			for (int j = 0; j < white_pieces[i]->possible_moves_stored.size(); j++)
			{
				temp_score=maxi(white_pieces[i]->possible_moves_stored[j], depth);
				reset_taken_pieces();
				load_positions();
				update_pieces_moves();
				if (temp_score > max_score)
				{
					max_score = temp_score;
					best_move = white_pieces[i]->possible_moves_stored[j];
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < black_pieces.size(); i++)
		{
			for (int j = 0; j < black_pieces[i]->possible_moves_stored.size(); j++)
			{
				temp_score = mini(black_pieces[i]->possible_moves_stored[j], depth);
				if (temp_score < min_score)
				{
					min_score = temp_score;
					best_move = black_pieces[i]->possible_moves_stored[j];
				}
			}
		}
	}
	return best_move;
}

int board::maxi(move* current_move, int depth)
{
	std::vector<piece*> taken_pieces;
	if (depth == 0)
	{
		int x = current_move->get_score(white_pieces, black_pieces);
		return x;
	}
	int score = -99999;
	int temp_score = 0;
	int temp = 0;
	temp = current_move->parent->position;
	current_move->parent->position = current_move->move_position;
	update_pieces_moves();
	if (current_move->parent->is_white)
	{
		for (int i = 0; i < black_pieces.size(); i++)
		{
			if (black_pieces[i]->position == current_move->parent->position)
			{
				taken_pieces.push_back(black_pieces[i]);
				black_pieces[i]->has_been_taken = true;
			}
		}
	}
	else
	{
		for (int i = 0; i < white_pieces.size(); i++)
		{
			if (white_pieces[i]->position == current_move->parent->position)
			{
				taken_pieces.push_back(white_pieces[i]);
				white_pieces[i]->has_been_taken = true;
			}
		}
	}
	if (depth > 0)
	{
		for (int i = 0; i < black_pieces.size(); i++)
		{
			for (int j = 0; j < black_pieces[i]->possible_moves_stored.size(); j++)
			{
				temp_score = mini(black_pieces[i]->possible_moves_stored[j], depth - 1);
				if (temp_score > score)
				{
					score = temp_score;
				}
			}
		}
	}
	for (int i = 0; i < taken_pieces.size(); i++)
	{
		taken_pieces[i]->has_been_taken = false;
	}
	current_move->parent->position = temp;
	return score;
}

int board::mini(move* current_move, int depth)
{
	std::vector<piece*> taken_pieces;
	if (depth == 0)
	{
		int x = current_move->get_score(white_pieces, black_pieces);
		return x;
	}
	int score = 99999;
	int temp_score = 0;
	int temp = 0;
	temp = current_move->parent->position;
	current_move->parent->position = current_move->move_position;
	update_pieces_moves();
	if (current_move->parent->is_white)
	{
		for (int i = 0; i < black_pieces.size(); i++)
		{
			if (black_pieces[i]->position == current_move->parent->position)
			{
				taken_pieces.push_back(black_pieces[i]);
				black_pieces[i]->has_been_taken = true;
			}
		}
	}
	else
	{
		for (int i = 0; i < white_pieces.size(); i++)
		{
			if (white_pieces[i]->position == current_move->parent->position)
			{
				taken_pieces.push_back(white_pieces[i]);
				white_pieces[i]->has_been_taken = true;
			}
		}
	}
	if (depth > 0)
	{
		for (int i = 0; i < white_pieces.size(); i++)
		{
			for (int j = 0; j < white_pieces[i]->possible_moves_stored.size(); j++)
			{
				temp_score = maxi(white_pieces[i]->possible_moves_stored[j], depth - 1);
				if (temp_score < score)
				{
					score = temp_score;
				}
			}
		}
	}
	for (int i = 0; i < taken_pieces.size(); i++)
	{
		taken_pieces[i]->has_been_taken = false;
	}
	current_move->parent->position = temp;
	return score;
}

void board::make_move(piece* current, move* current_move)
{
	if ((current->piece_type == 0 && current->hasnt_moved) || (current->piece_type == 5 && current->hasnt_moved) || (current->piece_type == 3 && current->hasnt_moved))
	{
		current->hasnt_moved = false;
	}
	current->position = current_move->move_position;
	if (current->is_white)
	{
		for (int i = 0; i < black_pieces.size(); i++)
		{
			if (black_pieces[i]->position == current->position)
				take_piece(black_pieces, i);
		}
	}
	else
	{
		for (int i = 0; i < white_pieces.size(); i++)
		{
			if (white_pieces[i]->position == current->position)
				take_piece(white_pieces, i);
		}
	}
}

int board::test_move(piece* current, move* current_move)
{
	int temp = current->position;
	int score = 0;
	current->position = current_move->move_position;
	if (current->is_white)
	{
		for (int i = 0; i < black_pieces.size(); i++)
		{
			if (black_pieces[i]->position == current->position)
			{
				taken = new piece(black_pieces[i]->piece_type, black_pieces[i]->value, black_pieces[i]->num_of_piece, black_pieces[i]->color, black_pieces[i]->position,black_pieces[i]->hasnt_moved, black_pieces[i]->just_jumped);
				take_piece(black_pieces, i);
			}
		}
	}
	else
	{
		for (int i = 0; i < white_pieces.size(); i++)
		{
			if (white_pieces[i]->position == current->position)
			{
				taken = new piece(white_pieces[i]->piece_type, white_pieces[i]->value, white_pieces[i]->num_of_piece, white_pieces[i]->color, white_pieces[i]->position, white_pieces[i]->hasnt_moved,white_pieces[i]->just_jumped);
				take_piece(white_pieces, i);
			}
		}
	}
	if (taken == nullptr)
		goto exit;
	if (taken->is_white&&taken!=nullptr)
	{
		//std::cout << "should have put piece back\n";
		white_pieces.push_back(taken);
	}
	else if(taken != nullptr)
	{
		black_pieces.push_back(taken);
	}
	exit:
	score = get_score();
	current->position = temp;
	return score;
}

board& board::operator=(board& board_)
{
	for (int i = 0; i < white_pieces.size(); i++)
	{
		*white_pieces[i] = *board_.white_pieces[i];
	}
	for (int i = 0; i < white_pieces.size(); i++)
	{
		*black_pieces[i] = *board_.black_pieces[i];
	}
	return *this;
}

int board::get_score()
{
	int temp_score = 0;
	for (int i = 0; i < white_pieces.size(); i++)
	{
		if (!white_pieces[i]->has_been_taken)
		temp_score += white_pieces[i]->value;
	}
	for (int i = 0; i < black_pieces.size(); i++)
	{
		if (!black_pieces[i]->has_been_taken)
		temp_score -= black_pieces[i]->value;
	}
	return temp_score;
}

void board::save_positions()
{
	white_positions.clear();
	black_positions.clear();
	saved_whites.clear();
	saved_blacks.clear();
	//std::cout << "Saved:\n\nWhite:\n";
	for (int i = 0; i < white_pieces.size(); i++)
	{
		saved_whites.push_back(white_pieces[i]);
		white_positions.push_back(white_pieces[i]->position);
		//std::cout << white_pieces[i]->type_name << " -> " << white_pieces[i]->position << std::endl;
	}
	//std::cout << "\nBlack:\n";
	for (int i = 0; i < black_pieces.size(); i++)
	{
		saved_blacks.push_back(black_pieces[i]);
		black_positions.push_back(black_pieces[i]->position);
		//std::cout << black_pieces[i]->type_name << " -> " << black_pieces[i]->position << std::endl;
	}
	//system("PAUSE");
}

void board::load_positions()
{
	
	//std::cout << "Loaded\n\nWhite:\n";
	for (int i=0; i<white_pieces.size(); i++)
	{
		white_pieces[i]->position = white_positions[i];
		//std::cout << white_pieces[i]->type_name << " -> " << white_pieces[i]->position << std::endl;
	}
	for (int i=0; i<black_pieces.size(); i++)
	{
		black_pieces[i]->position = black_positions[i];
		//std::cout << black_pieces[i]->type_name << " -> " << black_pieces[i]->position << std::endl;
	}
	//system("PAUSE");
}

void board::sort_pieces()
{
	/*std::vector<piece*> temp, holding;
	for (int i = 0; i < white_pieces.size(); i++)
	{
		temp.push_back(white_pieces[i]);
	}
	white_pieces.clear();
	int x = 0;
	int y = 0;
	int i = 0, j = 0;
	while (temp.size() > 0)
	{
		size_t f = temp.size();
		i = 0;
		j = 0;
		for (i=0; i < f; i++)
		{
			if (temp[i]->piece_type == x)
			{
				holding.push_back(temp[i]);
			}
		}
		while (white_pieces.size() != holding.size())
		{
			for (j = 0; j < holding.size(); j++)
			{
				if (holding[j]->num_of_piece == y&&holding[j]->piece_type==x)
				{
					white_pieces.push_back(holding[j]);
					y++;
				}
			}
		}
		x++;
		y = 0;
		if (x == 6)
			break;
	}
	temp.clear();
	holding.clear();
	for (int i = 0; i < black_pieces.size(); i++)
	{
		temp.push_back(black_pieces[i]);
	}
	black_pieces.clear();
	x = 0; y = 0; i = 0; j = 0;
	while (temp.size() > 0)
	{
		size_t f = temp.size();
		i = 0;
		j = 0;
		for (i = 0; i < f; i++)
		{
			if (temp[i]->piece_type == x)
			{
				holding.push_back(temp[i]);
			}
		}
		while (black_pieces.size() != holding.size())
		{
			for (j = 0; j < holding.size(); j++)
			{
				if (holding[j]->num_of_piece == y && holding[j]->piece_type == x)
				{
					black_pieces.push_back(holding[j]);
					y++;
				}
			}
		}
		x++;
		y = 0;
		if (x == 6)
			break;
	}
	temp.clear();
	holding.clear();
}

void board::swap_pieces(piece* p1, piece* p2)
{
	piece temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void board::reset_taken_pieces()
{
	for (int i = 0; i < white_pieces.size(); i++)
	{
		white_pieces[i]->has_been_taken = true;
	}
}

*/
/*
input A3
static cast A to int and subtract 65
multiply (3-1) by 8
add together and should be pos 16
*/

/*
make left side of output board be i/11-2
do ascii for bottom letters depending on i
*/

/*
class moves
has int position
bools such as castling_move and maybe en pasante
vector of pointers instead of possible moves
*/



/*
make best move (int depth, bool maximizing_player)
{
for black_pieces
{
clear moves
get moves
check moves
best_move=minimax
pushback best move
clear possible moves
}
for vector of best moves
{
max score =-99999
if vector of best moves [i] > max score
max score = vector of best moves
}
for vector of best moves
{
if best moves [i] == max score
make move (black_pieces[i], best_moves[i])
}
}

minimax (piece* selection, int depth, int alpha, int beta, bool maximizing_player)
{
if (maximizing player)
{
int max eval = -99999
for possible moves
{
eval = minimax(child, depth - 1, alpha, beta, false)
			maxEval = max(maxEval, eval)
			alpha = max(alpha, eval)
			if beta <= alpha
				break
		return maxEval
}
}
}

make move (piece* selection, move* move_made)
{

}

*/

/*
minimax(vector of pieces v1, depth, alpha, beta, maximizing player)
{
	for (int i<0; i<v1.size(); i++)
	{
		
	}
}
check all of black pieces
check each move
give that move a value
check all white pieces
check each move


board::get_score()


AI class
board* current_board 
generate_possible_boards(int depth)

	puts possible boards into vector
	goes through vectors and gets scores


*/


/*
so maybe make a vector of moves with first move, second move, and third move
calculate score of just third move
if score is less than max score get rid of those moves
else push back those moves i think
return the best move to the AI and AI will then make that move
can maybe still do alpha beta pruning hopefully








kk
so
recursively go through the 3 moves
then calculate score
so basically
black move
white response
black response 1
calculate score
black response 2
calculate score
but once we break out of that need to calculate scores of white moves where we take max of black responses
and then take min of white responses and that equals the black move score and move
now just need to track moves somehow
can probably just keep what im doing with vectors and pushback when score is updated

so maybe like

move get best move(depth, white)
{
	if (depth == 0)
		return get_score()
	for (int i=0; i <whitepiecs; i++)
		for (int j=0; j<possible moves stored; j++)
			make move(whitepiece, possible move stored)
			best move = get best move (depth-1, !white)
}






what if

get best movee
generate first level of moves
put those into mini or max with depth
mini or max recursively call get best move





AI has vectors of boards and constructs them using current board
1st vector will be of first moves where we pass in current board, currently selected piece, and the move it needs to make
the constructor for the board will then put all the pieces where they should be, make the move, and then take pieces if necessary
this board will then be pushed back into vector
then go again but make each board in 1st vector the current board to build from
keep doing this
as well as a pointer to the previous board and move that was made so that once we know which 3rd board was the best we can follow back to the original board and what move was made
	on the first board in order to get there.




need to fix how ai takes pieces
STILL NEED TO FIX MEMORY LEAK WITH FIRST MOVE BOARDS WITHOUT DELETING CURRENT BOARD
*/
