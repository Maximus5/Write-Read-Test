﻿#include <windows.h>
#include <stdio.h>
#include <crtdbg.h>

void main()
{
	_ASSERTE(FALSE);
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi = {};
	GetConsoleScreenBufferInfo(hOut, &csbi);
	CHAR_INFO chr_before[3] = {}, chr_after[3] = {};
	COORD cr0 = {}, crSize = {3,1};
	SMALL_RECT rcRead = {csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y, csbi.dwCursorPosition.X+2, csbi.dwCursorPosition.Y};
	wchar_t szData[] = {L"世 "}; // 2 wchar_t
	DWORD nWritten = 0;
	GetConsoleScreenBufferInfo(hOut, &csbi);
	// before
	SMALL_RECT r = rcRead;
	ReadConsoleOutputW(hOut, chr_before, crSize, cr0, &r);
	// write CJK+space
	WriteConsoleW(hOut, szData, 2, &nWritten, NULL);
	// after
	r = rcRead;
	ReadConsoleOutputW(hOut, chr_after, crSize, cr0, &r);
	// show data
	wchar_t szInfo[512];
	swprintf_s(szInfo, L"\nReading Rect: {%i,%i}-{%i,%i}\n"
		L"Before: {'%c' U+%X 0x%04X} {'%c' U+%X 0x%04X} {'%c' U+%X 0x%04X}\n"
		L"After:  {'%c' U+%X 0x%04X} {'%c' U+%X 0x%04X} {'%c' U+%X 0x%04X}\n",
		rcRead.Left, rcRead.Top, rcRead.Right, rcRead.Bottom,
		chr_before[0].Char.UnicodeChar, chr_before[0].Char.UnicodeChar, chr_before[0].Attributes,
		chr_before[1].Char.UnicodeChar, chr_before[1].Char.UnicodeChar, chr_before[1].Attributes,
		chr_before[2].Char.UnicodeChar, chr_before[2].Char.UnicodeChar, chr_before[2].Attributes,
		chr_after[0].Char.UnicodeChar, chr_after[0].Char.UnicodeChar, chr_after[0].Attributes,
		chr_after[1].Char.UnicodeChar, chr_after[1].Char.UnicodeChar, chr_after[1].Attributes,
		chr_after[2].Char.UnicodeChar, chr_after[2].Char.UnicodeChar, chr_after[2].Attributes
		);
	DWORD nLen = wcslen(szInfo);
	WriteConsoleW(hOut, szInfo, nLen, &nLen, NULL);
}