#include "piece.h"
#include "move.h"

HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
DWORD n;

piece::piece()
{

}

piece::piece(piece* p1)
{
	type = p1->type;
	value = p1->value;
	num_of_piece = p1->num_of_piece;
	color = p1->color;
	piece_type = p1->piece_type;
	position = p1->position;
	has_been_taken = p1->has_been_taken;
	hasnt_moved = p1->hasnt_moved;
	just_jumped = p1->just_jumped;
	is_white = p1->is_white;
	is_in_check = p1->is_in_check;
	possible_moves_stored = p1->possible_moves_stored;
	selected = false;
	type_name = p1->type_name;
}

piece::piece(int type, int value_, int num, int color_, int pos, bool moved, bool jumped) : piece_type(type), value(value_), num_of_piece(num), color(color_), position(pos), hasnt_moved(moved), just_jumped(jumped)
{
	if (color == 0)
		is_white = true;
}

void piece::move_piece(int new_x, int new_y)
{
	check_move(new_x, new_y);
}

void piece::set_moves(move* move)
{
	possible_moves_stored.push_back(move);
	move->parent = this;
}

piece::piece(int num, int color_, int pos)
{
	num_of_piece = num;
	color = color_;
	position = pos;
	if (color == 0)
		is_white = true;
	else
		is_white = false;
}

bool piece::check_move(int new_x, int new_y)
{
	if (type == "Pawn")
	{

	}
	if (type == "Pawn")
	{

	}
	if (type == "Pawn")
	{

	}
	if (type == "Pawn")
	{

	}
	if (type == "Pawn")
	{

	}
	if (type == "Pawn")
	{

	}
	return true;
}

void piece::print()
{
	switch (piece_type)
	{
	case 0:
	{
		if (is_white)
		{
			wchar_t wpawn[] = L"\u2659"; //pawn
			WriteConsoleW(cons, wpawn, wcslen(wpawn), &n, NULL);
		}
		else
		{
			wchar_t bpawn[] = L"\u265F"; //pawn
			WriteConsoleW(cons, bpawn, wcslen(bpawn), &n, NULL);
		}
		break;
	}
	case 1:
	{
		if (is_white)
		{
			wchar_t wknight[] = L"\u2658"; //pawn
			WriteConsoleW(cons, wknight, wcslen(wknight), &n, NULL);
		}
		else
		{
			wchar_t bknight[] = L"\u265E"; //pawn
			WriteConsoleW(cons, bknight, wcslen(bknight), &n, NULL);
		}
		break;
	}
	case 2:
	{
		if (is_white)
		{
			wchar_t wbishop[] = L"\u2657"; //pawn
			WriteConsoleW(cons, wbishop, wcslen(wbishop), &n, NULL);
		}
		else
		{
			wchar_t bbishop[] = L"\u265D"; //pawn
			WriteConsoleW(cons, bbishop, wcslen(bbishop), &n, NULL);
		}
		break;
	}
	case 3:
	{
		if (is_white)
		{
			wchar_t wrook[] = L"\u2656"; //pawn
			WriteConsoleW(cons, wrook, wcslen(wrook), &n, NULL);
		}
		else
		{
			wchar_t brook[] = L"\u265C"; //pawn
			WriteConsoleW(cons, brook, wcslen(brook), &n, NULL);
		}
		break;
	}
	case 4:
	{
		if (is_white)
		{
			wchar_t wqueen[] = L"\u2655"; //pawn
			WriteConsoleW(cons, wqueen, wcslen(wqueen), &n, NULL);
		}
		else
		{
			wchar_t bqueen[] = L"\u265B"; //pawn
			WriteConsoleW(cons, bqueen, wcslen(bqueen), &n, NULL);
		}

		break;
	}
	case 5:
	{
		if (is_white)
		{
			wchar_t wking[] = L"\u2654"; //pawn
			WriteConsoleW(cons, wking, wcslen(wking), &n, NULL);
		}
		else
		{
			wchar_t bking[] = L"\u265A"; //pawn
			WriteConsoleW(cons, bking, wcslen(bking), &n, NULL);
		}
		break;
	}
	}
}

void pawn::print()
{
	if (is_white)
	{
		wchar_t wpawn[] = L"\u2659"; //pawn
		WriteConsoleW(cons, wpawn, wcslen(wpawn), &n, NULL);
	}
	else
	{
		wchar_t bpawn[] = L"\u265F"; //pawn
		WriteConsoleW(cons, bpawn, wcslen(bpawn), &n, NULL);
	}

}

void knight::print()
{
	if (is_white)
	{
		wchar_t wknight[] = L"\u2658"; //pawn
		WriteConsoleW(cons, wknight, wcslen(wknight), &n, NULL);
	}
	else
	{
		wchar_t bknight[] = L"\u265E"; //pawn
		WriteConsoleW(cons, bknight, wcslen(bknight), &n, NULL);
	}

}

void bishop::print()
{
	if (is_white)
	{
		wchar_t wbishop[] = L"\u2657"; //pawn
		WriteConsoleW(cons, wbishop, wcslen(wbishop), &n, NULL);
	}
	else
	{
		wchar_t bbishop[] = L"\u265D"; //pawn
		WriteConsoleW(cons, bbishop, wcslen(bbishop), &n, NULL);
	}

}

void rook::print()
{
	if (is_white)
	{
		wchar_t wrook[] = L"\u2656"; //pawn
		WriteConsoleW(cons, wrook, wcslen(wrook), &n, NULL);
	}
	else
	{
		wchar_t brook[] = L"\u265C"; //pawn
		WriteConsoleW(cons, brook, wcslen(brook), &n, NULL);
	}

}

void queen::print()
{
	if (is_white)
	{
		wchar_t wqueen[] = L"\u2655"; //pawn
		WriteConsoleW(cons, wqueen, wcslen(wqueen), &n, NULL);
	}
	else
	{
		wchar_t bqueen[] = L"\u265B"; //pawn
		WriteConsoleW(cons, bqueen, wcslen(bqueen), &n, NULL);
	}

}

void king::print()
{
	if (is_white)
	{
		wchar_t wking[] = L"\u2654"; //pawn
		WriteConsoleW(cons, wking, wcslen(wking), &n, NULL);
	}
	else
	{
		wchar_t bking[] = L"\u265A"; //pawn
		WriteConsoleW(cons, bking, wcslen(bking), &n, NULL);
	}

}

pawn::pawn(int num, int color_, int pos) :piece(num, color_, pos)
{
	piece_type = 0;
	value = 1;
	type_name = "pawn";
}

knight::knight(int num, int color_, int pos) :piece(num, color_, pos)
{
	piece_type = 1;
	value = 3;
	type_name = "knight";
}

bishop::bishop(int num, int color_, int pos) : piece(num, color_, pos)
{
	piece_type = 2;
	value = 3;
	type_name = "bishop";
}

rook::rook(int num, int color_, int pos) : piece(num, color_, pos)
{
	piece_type = 3;
	value = 5;
	type_name = "rook";
	hasnt_moved = false;
}

queen::queen(int num, int color_, int pos) : piece(num, color_, pos)
{
	piece_type = 4;
	value = 9;
	type_name = "queen";
}

king::king(int num, int color_, int pos) : piece(num, color_, pos)
{
	piece_type = 5;
	is_in_check = false;
	hasnt_moved = true;
	type_name = "king";
	value = 1000;
}

std::vector<int> piece::display_moves()
{
	std::vector<int> v1;
	return v1;
}

std::vector<int> pawn::display_moves()
{
	std::vector<int> v1;
	return v1;
}

std::vector<int> knight::display_moves()
{
	std::vector<int> v1;
	v1.push_back(position + 12);
	v1.push_back(position - 12);
	v1.push_back(position - 19);
	v1.push_back(position - 21);
	v1.push_back(position + 19);
	v1.push_back(position + 21);
	v1.push_back(position - 8);
	v1.push_back(position + 8);
	return v1;
}

std::vector<int> bishop::display_moves()
{
	int pos;
	std::vector<int> v1;
	for (int i = 0; i < 7; i++)
	{
		if (position + (11 * i) > 98 || (position + (11 * i) + 1) % 10 == 0)
			break;
		else
			v1.push_back(position + (11 * i));
	}
	for (int i = 0; i < 7; i++)
	{
		if (position + (11 * i) > 98 || (position + (11 * i) + 1) % 10 == 0)
			break;
		else
			v1.push_back(position + (11 * i));
	}
	for (int i = 0; i < 7; i++)
	{
		if (position + (11 * i) > 98 || (position + (11 * i) + 1) % 10 == 0)
			break;
		else
			v1.push_back(position + (11 * i));
	}
	for (int i = 0; i < 7; i++)
	{
		if (position + (11 * i) > 98 || (position + (11 * i) + 1) % 10 == 0)
			break;
		else
			v1.push_back(position + (11 * i));
	}
	return v1;
}

std::vector<int> rook::display_moves()
{
	std::vector<int> v1;
	return v1;
}

std::vector<int> queen::display_moves()
{
	std::vector<int> v1;
	return v1;
}

std::vector<int> king::display_moves()
{
	std::vector<int> v1;
	return v1;
}

bool piece::operator>(piece* p1)
{
	if (piece_type != p1->piece_type)
		return piece_type > p1->piece_type;
	else
		return num_of_piece > p1->num_of_piece;
}

bool piece::operator<(piece* p1)
{
	if (piece_type != p1->piece_type)
		return piece_type < p1->piece_type;
	else
		return num_of_piece < p1->num_of_piece;
}

piece::~piece()
{
	for (int i = 0; i < possible_moves_stored.size(); i++)
	{
		delete possible_moves_stored[i];
	}
}
