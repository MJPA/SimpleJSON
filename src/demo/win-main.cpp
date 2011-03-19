/*
 * File demo/win-main.cpp part of the SimpleJSON Library Demo - http://mjpa.in/json
 * 
 * Copyright (C) 2010 Mike Anchor
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
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
					extern const wchar_t *EXAMPLE;
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
