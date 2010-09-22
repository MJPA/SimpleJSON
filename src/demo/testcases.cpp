/*
 * testcases.cpp
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
	
	print_out(vert_sep.c_str());
}
