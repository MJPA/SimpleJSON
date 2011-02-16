/*
 * File demo/testcases.cpp part of the SimpleJSON Library Demo - http://mjpa.in/json
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

/*
 * Test cases converted from http://testsuites.opera.com/JSON/runner.htm
 */

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include "../JSON.h"
#include "functions.h"

// Set to the width of the description column
#define DESC_LENGTH	50

using namespace std;

// Helper to do a quick parse check
bool parse_check(wstring str)
{
	JSONValue *v = JSON::Parse(str.c_str());
	if (v)
	{
		delete v;
		return true;
	}
	else
		return false;
}

// Helper to get a files contents
bool get_file(string filename, wstring &description, wstring &data)
{
	wifstream in(filename.c_str());
	if (in.is_open() == false)
		return false;

	getline(in, description);
	if (description.length() > DESC_LENGTH)
		description.resize(DESC_LENGTH);
	
	wstring line;
	data = L"";
	while (getline(in, line))
	{
		data += line;
		if (!in.eof()) data += L"\n";
	}
	return true;
}

// Run a pass / fail test
void run_test_type(bool type)
{
	int test = 0;
	wstring data = L"", name = L"";
	ostringstream stream;
	wostringstream wstream;

	while (true)
	{
		stream.str("");
		stream << "test_cases/" << (type ? "pass" : "fail") << (++test) << ".json";
		if (get_file(stream.str(), name, data) == false) break;
		
		print_out(L"| ");
		
		wstream.str(L"");
		wstream.setf(ios_base::left, ios_base::adjustfield);
		wstream << setw(DESC_LENGTH) << name;
		print_out(wstream.str().c_str());
		
		print_out(L" | ");
		print_out(parse_check(data) != type ? L"failed" : L"passed");
		print_out(L" |\r\n");
	}
}

// Tests to run
void run_tests()
{
	wstring vert_sep = wstring(L"+-") + wstring(DESC_LENGTH, L'-') + wstring(L"-+--------+\r\n");
	
	print_out(vert_sep.c_str());
	
	wstring header = wstring(L"| Test case") + wstring(DESC_LENGTH - 9, L' ') + wstring(L" | Result |\r\n");
	print_out(header.c_str());
	
	print_out(vert_sep.c_str());
	
	run_test_type(true);
	run_test_type(false);
	
	// Static test for a very precise decimal number
	double decimal = 40.9358215191158457340974;
	JSONValue *json_value = JSON::Parse("40.9358215191158457340974");
	wstring test_output = wstring(L"| Very precise decimal number") + wstring(DESC_LENGTH - 27, L' ') + wstring(L" | ");
	if (json_value && json_value->IsNumber() && json_value->AsNumber() == decimal)
	{
		test_output += wstring(L"passed |\r\n");
		delete json_value;
	}
	else
	{
		test_output += wstring(L"failed |\r\n");
	}
	print_out(test_output.c_str());
	
	// Static test for a decimal number with leading zeros
	decimal = 1.00034985734000;
	json_value = JSON::Parse("1.00034985734000");
	test_output = wstring(L"| Decimal number with leading zeros") + wstring(DESC_LENGTH - 33, L' ') + wstring(L" | ");
	if (json_value && json_value->IsNumber() && json_value->AsNumber() == decimal)
	{
		test_output += wstring(L"passed |\r\n");
	}
	else
	{
		test_output += wstring(L"failed |\r\n");
	}
	print_out(test_output.c_str());
	
	print_out(vert_sep.c_str());
}
