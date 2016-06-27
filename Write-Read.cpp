#include <windows.h>
#include <stdio.h>
#include <crtdbg.h>

wchar_t wc(const CHAR_INFO& c)
{
	return c.Char.UnicodeChar ? c.Char.UnicodeChar : L' ';
}

void main()
{
	_ASSERTE(FALSE);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi = {};
	GetConsoleScreenBufferInfo(hOut, &csbi);
	CHAR_INFO chr_before[4] = {}, chr_after[4] = {};
	COORD cr0 = {}, crSize = {4,1};
	SMALL_RECT rcRead = {csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y, csbi.dwCursorPosition.X+3, csbi.dwCursorPosition.Y};
	wchar_t szData[] = {L"世12"}; // 3 wchar_t
	wchar_t szASCII[80] = L"012345678901234567890123456789012345678901234567890123456789012345678901234567\n";
	wchar_t szCJK[80] = L"世界中のあらゆる情報を検索するためのツールを提供しています。さまざまな検索機能 を活用して、お探しの情報を見つけてください。さまざまな検索機能 を活用して、\n";
	DWORD nWritten = 0;
	GetConsoleScreenBufferInfo(hOut, &csbi);
	// before
	SMALL_RECT r = rcRead;
	ReadConsoleOutputW(hOut, chr_before, crSize, cr0, &r);
	// write CJK+space
	WriteConsoleW(hOut, szData, 3, &nWritten, NULL);
	// after
	r = rcRead;
	ReadConsoleOutputW(hOut, chr_after, crSize, cr0, &r);
	// show data
	wchar_t szInfo[512];
	swprintf_s(szInfo, L"\nReading Rect: {%i,%i}-{%i,%i}\n"
		L"Before: {'%c' U+%X x%02X} {'%c' U+%X x%02X} {'%c' U+%X x%02X} {'%c' U+%X x%02X}\n"
		L"After:  {'%c' U+%X x%02X} {'%c' U+%X x%02X} {'%c' U+%X x%02X} {'%c' U+%X x%02X}\n",
		rcRead.Left, rcRead.Top, rcRead.Right, rcRead.Bottom,
		wc(chr_before[0]), chr_before[0].Char.UnicodeChar, chr_before[0].Attributes,
		wc(chr_before[1]), chr_before[1].Char.UnicodeChar, chr_before[1].Attributes,
		wc(chr_before[2]), chr_before[2].Char.UnicodeChar, chr_before[2].Attributes,
		wc(chr_before[3]), chr_before[3].Char.UnicodeChar, chr_before[3].Attributes,
		wc(chr_after[0]), chr_after[0].Char.UnicodeChar, chr_after[0].Attributes,
		wc(chr_after[1]), chr_after[1].Char.UnicodeChar, chr_after[1].Attributes,
		wc(chr_after[2]), chr_after[2].Char.UnicodeChar, chr_after[2].Attributes,
		wc(chr_after[3]), chr_after[3].Char.UnicodeChar, chr_after[3].Attributes
		);
	DWORD nLen = wcslen(szInfo);
	WriteConsoleW(hOut, szInfo, nLen, &nLen, NULL);
	// At last, we print 78 single-width and 78 CJK characters
	WriteConsoleW(hOut, szASCII, wcslen(szASCII), &nLen, NULL);
	WriteConsoleW(hOut, szCJK, wcslen(szCJK), &nLen, NULL);
}
