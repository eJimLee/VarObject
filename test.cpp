/**
 * Copyright (c) 2014, eJim Lee (lyjforpublic@gmail.com)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the eJim Lee nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL eJim Lee BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include <iostream>
#include "varobject/varobject.h"

using namespace var;

#define PINI(x) cout << #x << ": " << x << endl
#define INIT(x, v) VarObject x = v; PINI(x)
#define TEST_OP(exp) \
	do{ \
		VarObject tmp_v; \
		try { \
			tmp_v = exp; \
			cout << "Result: {" << #exp << "} = " << tmp_v << endl; \
		} \
		catch(Exception &e) { \
			cerr << "Error: exp \"" << #exp << "\" throw " << e << " exception" << endl; \
		} \
	}while(0)

#define TEST_OP_CHECK(exp, op, value) \
	do{ \
		VarObject tmp_v; \
		try { \
			tmp_v = exp; \
			bool check_result = (tmp_v op (value)); \
			if(check_result) { \
				cout << "Check: {(" << #exp << ") " << #op << " (" << #value << ")}" << endl; \
			}else{ \
				cout << "Error: {(" << #exp << ") " << #op << " (" << #value << ")} = {(" << tmp_v << ") " << #op << " (" << #value << ")}" << endl; \
			} \
		} \
		catch(Exception &e) { \
			cerr << "Error: exp \"" << #exp << "\" throw " << e << " exception" << endl; \
		} \
	}while(0)

void varobject_test(void)
{
	cout << "initial:" << endl;

	INIT(i, 23);
	INIT(i2, 5);

	INIT(d, 3.14);
	INIT(d2, 0.618);

	INIT(s, "abc");
	INIT(b, true);
	INIT(l, LIST(i, d, s, b));
	INIT(n, None);

	map<Var, Var> a;
	a["atest"] = 214;
	map<Var, Var> m;
	m[34] = 1;
	m[5.3] = 2;
	m["str1"] = 3;
	m[string("str2")] = 4;
	m[true] = 5;
	m[l] = 6;
	m[a] = 7;
	INIT(dict, m);

	cout << "pure VarObject operator: " << endl;

	/* + - * / */
	TEST_OP_CHECK(i + i2, ==, 23 + 5);
	TEST_OP_CHECK(i - i2, ==, 23 - 5);
	TEST_OP_CHECK(i * i2, ==, 23 * 5);
	TEST_OP_CHECK(i / i2, ==, 23 / 5);

	TEST_OP_CHECK(d + d2, ==, 3.14 + 0.618);
	TEST_OP_CHECK(d - d2, ==, 3.14 - 0.618);
	TEST_OP_CHECK(d * d2, ==, 3.14 * 0.618);
	TEST_OP_CHECK(d / d2, ==, 3.14 / 0.618);

	TEST_OP_CHECK(i + d, ==, 23 + 3.14);
	TEST_OP_CHECK(i - d, ==, 23 - 3.14);
	TEST_OP_CHECK(i * d, ==, 23 * 3.14);
	TEST_OP_CHECK(i / d, ==, 23 / 3.14);

	TEST_OP_CHECK(d + i, ==, 3.14 + 23);
	TEST_OP_CHECK(d - i, ==, 3.14 - 23);
	TEST_OP_CHECK(d * i, ==, 3.14 * 23);
	TEST_OP_CHECK(d / i, ==, 3.14 / 23);

	TEST_OP_CHECK(b + i, ==, true + 23);
	TEST_OP_CHECK(b - i, ==, true - 23);
	TEST_OP_CHECK(b * i, ==, true * 23);
	TEST_OP_CHECK(b / i, ==, true / 23);

	TEST_OP_CHECK(i + b, ==, 23 + true);
	TEST_OP_CHECK(i - b, ==, 23 - true);
	TEST_OP_CHECK(i * b, ==, 23 * true);
	//b = false;
	//TEST_OP(i / b);
	//b = true;
	TEST_OP_CHECK(i / b, ==, 23 / true);

	TEST_OP_CHECK(b + d, ==, true + 3.14);
	TEST_OP_CHECK(b - d, ==, true - 3.14);
	TEST_OP_CHECK(b * d, ==, true * 3.14);
	TEST_OP_CHECK(b / d, ==, true / 3.14);

	TEST_OP_CHECK(d + b, ==, 3.14 + true);
	TEST_OP_CHECK(d - b, ==, 3.14 - true);
	TEST_OP_CHECK(d * b, ==, 3.14 * true);
	//b = false;
	//TEST_OP(d / b);
	//b = true;
	TEST_OP_CHECK(d / b, ==, 3.14 / true);

	TEST_OP_CHECK(s * i2, ==, i2 * s);
	TEST_OP_CHECK(3 * s, ==, "abcabcabc");

	TEST_OP(i2 * l);
	TEST_OP_CHECK(l * i2, ==, i2 * l);


	/* > < == != */
	TEST_OP_CHECK(i > i2, ==, true);
	TEST_OP_CHECK(i >= i2, ==, true);
	TEST_OP_CHECK(i == i2, ==, false);
	TEST_OP_CHECK(i != i2, ==, true);
	TEST_OP_CHECK(i <= i2, ==, false);
	TEST_OP_CHECK(i < i2, ==, false);

	TEST_OP_CHECK(d > d2, ==, true);
	TEST_OP_CHECK(d >= d2, ==, true);
	TEST_OP_CHECK(d == d2, ==, false);
	TEST_OP_CHECK(d != d2, ==, true);
	TEST_OP_CHECK(d <= d2, ==, false);
	TEST_OP_CHECK(d < d2, ==, false);

	TEST_OP_CHECK(i > d, ==, true);
	TEST_OP_CHECK(i >= d, ==, true);
	TEST_OP_CHECK(i == d, ==, false);
	TEST_OP_CHECK(i != d, ==, true);
	TEST_OP_CHECK(i <= d, ==, false);
	TEST_OP_CHECK(i < d, ==, false);

	TEST_OP_CHECK(d > i, ==, false);
	TEST_OP_CHECK(d >= i, ==, false);
	TEST_OP_CHECK(d == i, ==, false);
	TEST_OP_CHECK(d != i, ==, true);
	TEST_OP_CHECK(d <= i, ==, true);
	TEST_OP_CHECK(d < i, ==, true);

	TEST_OP_CHECK(i > b, ==, true);
	TEST_OP_CHECK(i >= b, ==, true);
	TEST_OP_CHECK(i == b, ==, false);
	TEST_OP_CHECK(i != b, ==, true);
	TEST_OP_CHECK(i <= b, ==, false);
	TEST_OP_CHECK(i < b, ==, false);

	TEST_OP_CHECK(b > i, ==, false);
	TEST_OP_CHECK(b >= i, ==, false);
	TEST_OP_CHECK(b == i, ==, false);
	TEST_OP_CHECK(b != i, ==, true);
	TEST_OP_CHECK(b <= i, ==, true);
	TEST_OP_CHECK(b < i, ==, true);

	TEST_OP_CHECK(i > n, ==, true);
	TEST_OP_CHECK(b > n, ==, true);
	TEST_OP_CHECK(d > n, ==, true);
	TEST_OP_CHECK(s > n, ==, true);
	TEST_OP_CHECK(l > n, ==, true);

	TEST_OP_CHECK(i > b, ==, true);
	TEST_OP_CHECK(d > b, ==, true);
	TEST_OP_CHECK(s > b, ==, true);
	TEST_OP_CHECK(l > b, ==, true);

	TEST_OP_CHECK(s > i, ==, true);
	TEST_OP_CHECK(s > d, ==, true);
	TEST_OP_CHECK(l > i, ==, true);
	TEST_OP_CHECK(l > d, ==, true);
	TEST_OP_CHECK(s > l, ==, true);

	/* type transform */
	TEST_OP_CHECK((bool) n, ==, false);
	TEST_OP_CHECK((bool) i, ==, true);
	TEST_OP_CHECK((bool) d, ==, true);
	TEST_OP_CHECK((bool) b, ==, true);
	TEST_OP_CHECK((bool) s, ==, true);
	TEST_OP_CHECK((bool) l, ==, true);

	/* bit operator */
	TEST_OP_CHECK(i & 0xa, ==, 23 & 0xa);
	TEST_OP_CHECK(i | 0xa, ==, 23 | 0xa);
	TEST_OP_CHECK(i ^ 0xa, ==, 23 ^ 0xa);
	TEST_OP_CHECK(i % 0x4, ==, 23 % 0x4);
	TEST_OP_CHECK(i << 0xa, ==, 23 << 0xa);
	TEST_OP_CHECK(i >> 0x2, ==, 23 >> 0x2);

	TEST_OP_CHECK(i & b, ==, 23 & b);
	TEST_OP_CHECK(i | b, ==, 23 | b);
	TEST_OP_CHECK(i ^ b, ==, 23 ^ b);
	TEST_OP_CHECK(i % b, ==, 23 % b);
	TEST_OP_CHECK(i << b, ==, 23 << b);
	TEST_OP_CHECK(i >> b, ==, 23 >> b);

	/* ! ~ [] */
	TEST_OP_CHECK(l[2], ==, "abc");

	/* LIST */
	Var l2 = LIST(b, i, s, l, 1, 2.2, true, "kkk", LIST(i, i, i));
	TEST_OP(l2);

	/* None */
	TEST_OP_CHECK(n, == ,None);

	TEST_OP(dict);
	TEST_OP_CHECK(dict[34], ==, 1);
	TEST_OP_CHECK(dict[5.3], ==, 2);
	TEST_OP_CHECK(dict["str1"], ==, 3);
	TEST_OP_CHECK(dict["str2"], ==, 4);
	TEST_OP_CHECK(dict[true], ==, 5);
	TEST_OP_CHECK(dict[l], ==, 6);
	TEST_OP_CHECK(dict[a], ==, 7);
}

int main(void)
{
	varobject_test();
	return 0;
}
