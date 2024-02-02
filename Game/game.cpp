#include "game.h"


class output_swap {
	output_swap(const output_swap&) = delete;
	output_swap operator=(output_swap&) = delete;
public:
	output_swap() noexcept :
		prevCP_(::GetConsoleCP())
	{
		::SetConsoleCP(CP_WINUNICODE);
		::SetConsoleOutputCP(CP_WINUNICODE);
	} 
	~output_swap() noexcept {
		::SetConsoleCP(prevCP_);
		::SetConsoleOutputCP(prevCP_);
	}
private:
	::DWORD prevCP_;
};

void draw_text(const wchar_t* text)
{
	static ::HANDLE _out = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::DWORD written;
	::WriteConsoleW(_out, text, std::wcslen(text), &written, nullptr);
}

GameBox::GameBox()
{
	cords.X = 0;
	cords.Y = 0;
	length = 10;
	width = 10;
	player_cords.X = 0;
	player_cords.Y = 0;
}

GameBox::GameBox(int top_pos, int left_pos, int length, int width)
{
	this->cords.Y = top_pos;
	this->cords.X = left_pos;
	this->length = length;
	this->width = width;
	player_cords.X = 0;
	player_cords.Y = 0;
}

void setCursorPosition(COORD cords)
{
	std::cout << "\u001b[" << cords.Y << ";" << cords.X << "H";
}

void GameBox::gameBoxPrint()
{
	COORD tmp_cords;

	setCursorPosition(cords);

	draw_text(L"┌");
	for (int i = 0; i <= length + 1; i++)
	{
		draw_text(L"─");
	}
	draw_text(L"┐");
	for (int i = 1; i <= width + 1; i++)
	{
		tmp_cords.Y = cords.Y + i - 1;
		tmp_cords.Y = cords.X - 1;
		setCursorPosition(tmp_cords);
		draw_text(L"│");
		for (int i = 0; i <= length + 1; i++)
		{
			std::cout << " ";
		}
		draw_text(L"│");
	}

	tmp_cords.X = cords.X - 1;
	tmp_cords.Y = cords.Y + width;
	setCursorPosition(tmp_cords);
	draw_text(L"└");
	for (int i = 0; i <= length + 1; i++)
	{
		draw_text(L"─");
	}
	draw_text(L"┘");
}

void hideCursor()
{
	std::cout << "\u001b[?25l";
}

void GameBox::movePlayer(char player, int amount, char dir, int dir_int, int dir_mod)
{
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	TCHAR tch = ' ';
	LPTSTR lpt = &tch;
	DWORD dw = 1;
	LPDWORD lpdword = &dw;

	player_cords.X += (!dir_int * dir_mod);
	player_cords.X += (dir_int * dir_mod);

	ReadConsoleOutputCharacter(hCon, lpt, 1, player_cords, lpdword);

	std::cout << lpt;

	std::cout << "\u001b[1D \u001b[1D\u001b[" << amount << dir << player;
}

COORD GameBox::getPlayerCords()
{
	return player_cords;
}

GameBox& GameBox::setPlayerPosition(COORD cords)
{
	player_cords = cords;
	return *this;
}
