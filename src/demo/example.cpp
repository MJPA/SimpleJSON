/*
 * example.cpp
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
#include <sstream>
#include <time.h>
#include "../JSON.h"
#include "functions.h"

using namespace std;

// Just some sample JSON text, feel free to change but could break demo
wchar_t* EXAMPLE = L"\
{ \
	\"string_name\" : \"string\tvalue and a \\\"quote\\\" and a unicode char \\u00BE and a c:\\\\path\\\\ or a \\/unix\\/path\\/ :D\", \
	\"bool_name\" : true, \
	\"bool_second\" : FaLsE, \
	\"null_name\" : nULl, \
	\"negative\" : -34.276, \
	\"sub_object\" : { \
						\"foo\" : \"abc\", \
						 \"bar\" : 1.35e2, \
						 \"blah\" : { \"a\" : \"A\", \"b\" : \"B\", \"c\" : \"C\" } \
					}, \
	\"array_letters\" : [ \"a\", \"b\", \"c\", [ 1, 2, 3  ]  ] \
}    ";

// Example 1
void example1()
{
	// Parse example data
	JSONValue *value = JSON::Parse(EXAMPLE);
		
	// Did it go wrong?
	if (value == NULL)
	{
		print_out(L"Example code failed to parse, did you change it?\r\n");
	}
	else
	{
		// Retrieve the main object
		JSONObject root;
		if (value->IsObject() == false)
		{
			print_out(L"The root element is not an object, did you change the example?\r\n");
		}
		else
		{
			root = value->AsObject();
			
			// Retrieving a string
			if (root.find(L"string_name") != root.end() && root[L"string_name"]->IsString())
			{
				print_out(L"string_name:\r\n");
				print_out(L"------------\r\n");
				print_out(root[L"string_name"]->AsString().c_str());
				print_out(L"\r\n\r\n");
			}
		
			// Retrieving a boolean
			if (root.find(L"bool_second") != root.end() && root[L"bool_second"]->IsBool())
			{
				print_out(L"bool_second:\r\n");
				print_out(L"------------\r\n");
				print_out(root[L"bool_second"]->AsBool() ? L"it's true!" : L"it's false!");
				print_out(L"\r\n\r\n");
			}
			
			// Retrieving an array
			if (root.find(L"array_letters") != root.end() && root[L"array_letters"]->IsArray())
			{
				JSONArray array = root[L"array_letters"]->AsArray();
				print_out(L"array_letters:\r\n");
				print_out(L"--------------\r\n");
				for (unsigned int i = 0; i < array.size(); i++)
				{
					wstringstream output;
					output << L"[" << i << L"] => " << array[i]->Stringify() << L"\r\n";
					print_out(output.str().c_str());
				}
				print_out(L"\r\n");
			}
			
			// Retrieving nested object
			if (root.find(L"sub_object") != root.end() && root[L"sub_object"]->IsObject())
			{
				print_out(L"sub_object:\r\n");
				print_out(L"-----------\r\n");
				print_out(root[L"sub_object"]->Stringify().c_str());
				print_out(L"\r\n\r\n");
			}
		}

		delete value;
	}
}

// Example 2
void example2()
{
	JSONObject root;
		
	// Adding a string
	root[L"test_string"] = new JSONValue(L"hello world");
		
	// Create a random integer array
	JSONArray array;
	srand((unsigned)time(0));
	for (int i = 0; i < 10; i++)
		array.push_back(new JSONValue((double)(rand() % 100)));
	root[L"sample_array"] = new JSONValue(array);
		
	// Create a value
	JSONValue *value = new JSONValue(root);
		
	// Print it
	print_out(value->Stringify().c_str());

	// Clean up
	delete value;
}
