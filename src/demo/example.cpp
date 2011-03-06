/*
 * File demo/example.cpp part of the SimpleJSON Library Demo - http://mjpa.in/json
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
#include <sstream>
#include <time.h>
#include "../JSON.h"
#include "functions.h"

using namespace std;

// Just some sample JSON text, feel free to change but could break demo
const wchar_t* EXAMPLE = L"\
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
