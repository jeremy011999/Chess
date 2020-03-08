#include "board.h"
#include "piece.h"
#include "AI.h"
#define _WIN32_WINNT 0x0500

HANDLE hConsole1 = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
	system("mode 650");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	//SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	AI ai;
	ai.start();
	/*CONSOLE_FONT_INFOEX font;//CONSOLE_FONT_INFOEX is defined in some windows header
	GetCurrentConsoleFontEx(hConsole1, false, &font);//PCONSOLE_FONT_INFOEX is the same as CONSOLE_FONT_INFOEX*
	font.dwFontSize.X = 50;
	font.dwFontSize.Y = 60;
	SetCurrentConsoleFontEx(hConsole1, true, &font);
	std::cout << "hi"<< std::endl;
	HANDLE cons = GetStdHandle(STD_OUTPUT_HANDLE);
	wchar_t p[] = L"Queen: \u265A.\n";
	wchar_t white_king[] = L"\u265A";
	DWORD n;
	WriteConsoleW(cons, p, wcslen(p), &n, NULL);
	WriteConsoleW(cons, white_king, wcslen(white_king), &n, NULL);*/
	return 0;
}