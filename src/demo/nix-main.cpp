/*
 * nix-main.cpp
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

#include <string>
#include <iostream>
#include <iterator>

#include "../JSON.h"
#include "functions.h"

using namespace std;

// Print out function
void print_out(const wchar_t* output)
{
	wcout << output;
	wcout.flush();
}

// Linux entry point
int main(int argc, char **argv)
{
	// Required for utf8 chars
	setlocale(LC_CTYPE, "");
	
	// The mode...
	string mode = argc != 2 ? "" : argv[1];
	
	// Verifying?
	if (mode == "-v" || mode == "-f")
	{
		// Get the stdin data
		cin >> noskipws;
		istream_iterator<char> it(cin);
		istream_iterator<char> end;
		string results(it, end);
		
		// Parse it, print if the test is good/bad
		JSONValue *value = JSON::Parse(results.c_str());
		if ((value != NULL && mode == "-v") || (value == NULL && mode == "-f"))
			wcout << L"PASS" << endl;
		else
			wcout << L"FAIL" << endl;

		if (value) delete value;
	}
	
	// Parse + echo?
	else if (mode == "-e")
	{
		// Get the stdin data
		cin >> noskipws;
		istream_iterator<char> it(cin);
		istream_iterator<char> end;
		string results(it, end);
		
		// Parse it & echo if it's valid
		JSONValue *value = NULL;
		if ((value = JSON::Parse(results.c_str())) == NULL)
			wcout << L"Code entered is *NOT* valid.";
		else
			wcout << value->Stringify();
		wcout << endl;

		if (value) delete value;
	}
	
	// Example 1?
	else if (mode == "-ex1")
	{
		example1();
	}
	
	// Example 2?
	else if (mode == "-ex2")
	{
		example2();
	}
	
	// Test cases?
	else if (mode == "-t")
	{
		run_tests();
	}
	
	// Help!
	else 
	{
		wcout << L"Usage: " << argv[0] << L" <option>" << endl;
		wcout << endl;
		wcout << L"\t-v\tVerify JSON string is *valid* via stdin" << endl;
		wcout << L"\t-f\tVerify JSON string is *invalid* via stdin" << endl;
		wcout << L"\t-e\tVerify JSON string via stdin and echo it back using Stringify()" << endl;
		wcout << L"\t-ex1\tRun example 1 - Example of how to extract data from the JSONValue object" << endl;
		wcout << L"\t-ex2\tRun example 2 - Building a JSONValue from nothing" << endl;
		wcout << L"\t-t\tRun test cases" << endl;
		wcout << endl;
		wcout << L"Only one option can be used at a time." << endl;
	}
	
	return 0;
}
