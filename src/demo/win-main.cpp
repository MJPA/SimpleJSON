/*
 * win-main.cpp
 * Copyright (C) 2010 Mike Anchor <mikea@mjpa.co.uk>
 *
 * Part of the MJPA JSON Library Demo - http://mjpa.co.uk/blog/view/A-simple-C-JSON-library/
 *
 * License: http://mjpa.co.uk/licenses/GPLv2/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <windows.h>
#include "..\..\vs2008\resource.h"
#include "..\JSON.h"
#include "functions.h"

// Handle to the window
static HWND hDlg = NULL;

// A function to display output
void print_out(const wchar_t *output)
{
	if (hDlg != NULL)
	{
		size_t size = GetWindowTextLength(GetDlgItem(hDlg, IDC_OUTPUT)) + 1 + wcslen(output);
		wchar_t *current = new wchar_t[size];
		GetWindowText(GetDlgItem(hDlg, IDC_OUTPUT), current, size);
		wcscat_s(current, size, output);
		SetWindowText(GetDlgItem(hDlg, IDC_OUTPUT), current);
	}
}

// Dialog proc for the Windows window
int CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_INITDIALOG:
			hDlg = hWnd;
			break;

		case WM_CLOSE:
			EndDialog(hWnd, 0);
			break;

		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		case WM_COMMAND:
		{
			if (HIWORD(wParam) != BN_CLICKED)
				break;

			SetWindowText(GetDlgItem(hWnd, IDC_OUTPUT), L"");

			switch (LOWORD(wParam))
			{
				case IDC_VERIFY:
				case IDC_ECHO:
				{
					int size = GetWindowTextLength(GetDlgItem(hWnd, IDC_INPUT));
					wchar_t* text = new wchar_t[size + 1];
					GetWindowText(GetDlgItem(hWnd, IDC_INPUT), text, size + 1);

					JSONValue *value = JSON::Parse(text);

					if (value == NULL)
					{
						SetWindowText(GetDlgItem(hWnd, IDC_OUTPUT), L"The JSON text *is not* valid");
					}
					else
					{
						if (LOWORD(wParam) == IDC_ECHO)
							SetWindowText(GetDlgItem(hWnd, IDC_OUTPUT), value->Stringify().c_str());
						else
							SetWindowText(GetDlgItem(hWnd, IDC_OUTPUT), L"The JSON text *is* valid");
						delete value;
					}

					delete text;
					break;
				}

				case IDC_EX1:
					extern wchar_t *EXAMPLE;
					SetWindowText(GetDlgItem(hDlg, IDC_INPUT), EXAMPLE);
					example1();
					break;

				case IDC_EX2:
					SetWindowText(GetDlgItem(hDlg, IDC_INPUT), L"Example 2:\r\n\r\nKey 'test_string' has a value 'hello world'\r\nKey 'sample_array' is an array of 10 random numbers");
					example2();
					break;

				case IDC_TESTCASES:
					SetWindowText(GetDlgItem(hWnd, IDC_INPUT), L"");
					run_tests();
					break;
			}

			break;
		}
	}

	return 0;
}

// Windows entry point
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	wchar_t progdir[_MAX_PATH + 1];
	progdir[GetModuleFileName(hInstance, progdir, _MAX_PATH + 1)] = 0;
	wchar_t *last_slash = wcsrchr(progdir, L'\\');
	if (last_slash) *(++last_slash) = 0;
	SetCurrentDirectory(progdir);
	
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_JSONDEMO), NULL, DialogProc);
	return 0;
}
