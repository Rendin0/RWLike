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
	left_pos = 0;
	top_pos = 0;
	length = 10;
	width = 10;
}

GameBox::GameBox(int top_pos, int left_pos, int length, int width)
{
	this->top_pos = top_pos;
	this->left_pos = left_pos;
	this->length = length;
	this->width = width;
}

void setCursorPosition(int top_pos, int left_pos)
{
	std::cout << "\u001b[" << top_pos << ";" << left_pos << "H";
}

void GameBox::gameBoxPrint()
{
	setCursorPosition(top_pos - 1, left_pos - 1);

	draw_text(L"┌");
	for (int i = 0; i <= length + 1; i++)
	{
		draw_text(L"─");
	}
	draw_text(L"┐");
	for (int i = 1; i <= width + 1; i++)
	{
		setCursorPosition(top_pos + i - 1, left_pos - 1);
		draw_text(L"│");
		for (int i = 0; i <= length + 1; i++)
		{
			std::cout << " ";
		}
		draw_text(L"│");
	}
	setCursorPosition(top_pos + width, left_pos - 1);
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

void GameBox::movePlayer(char player, int amount, char dir)
{
	std::cout << "\u001b[1D \u001b[1D\u001b[" << amount << dir << player;
}
