/*
 * File JSON.h part of the SimpleJSON Library - http://mjpa.in/json
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

#ifndef _JSON_H_
#define _JSON_H_

#include <vector>
#include <string>
#include <map>
#include <cstring>
#include <cstdlib>
#include <cwctype>

static inline bool simplejson_isnan(double x) {
	return x != x;
}
static inline bool simplejson_isinf(double x) {
	return !simplejson_isnan(x) && simplejson_isnan(x - x);
}


static inline int simplejson_ncasecmp(const char *s1, const char *s2, size_t n) {
	int lc1 = 0;
	int lc2 = 0;

	while (n--) {
		lc1 = towlower(*s1);
		lc2 = towlower(*s2);

		if (lc1 != lc2)
			return (lc1 - lc2);

		if (!lc1)
			return 0;

		++s1;
		++s2;
	}

	return 0;
}

// Simple function to check a string 's' has at least 'n' characters
static inline bool simplejson_nlen(const char *s, size_t n) {
	if (s == 0)
		return false;

	const char *save = s;
	while (n-- > 0) {
		if (*(save++) == 0)
			return false;
	}

	return true;
}

// Custom types
class JSONValue;
typedef std::vector<JSONValue*> JSONArray;
typedef std::map<std::string, JSONValue*> JSONObject;

#include "../json/JSONValue.h"

class JSON {
	friend class JSONValue;

public:
	static JSONValue* ParseFromFile(std::string filename);
	static JSONValue* Parse(const char *data);
	static std::string Stringify(const JSONValue *value);
protected:
	static bool SkipWhitespace(const char **data);
	static bool ExtractString(const char **data, std::string &str);
	static double ParseInt(const char **data);
	static double ParseDecimal(const char **data);
private:
	JSON();
};

#endif
