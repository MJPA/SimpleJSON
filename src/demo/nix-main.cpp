/*
 * File demo/nix-main.cpp part of the SimpleJSON Library Demo - http://mjpa.in/json
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
