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
#include <sstream>
#include "varobject.h"

using namespace std;

namespace var {

#define OPTERROR(l, r) \
	do{ cerr << "error " << __func__ << " (" << (l).Type << ", " << (r).Type << ")" << endl; }while(0)
#define OPTERRORS(l) \
	do{ cerr << "error " << __func__ << " (" << (l).Type << ")" << endl; }while(0)

/* + */
VarObject operator+(const VarObject &left, const VarObject &right) {
	VarObject tmp;
	switch(left.Type) {
	case TNull:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TBool:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool + right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool + right.Integer;
			break;
		case TFloat:
			tmp.Type = TFloat;
			tmp.Float = (double) left.Bool + right.Float;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TInteger:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer + right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer + right.Integer;
			break;
		case TFloat:
			tmp.Type = TFloat;
			tmp.Float = (double) left.Integer + right.Float;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TFloat:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TFloat;
			tmp.Float = (double) left.Float + right.Bool;
			break;
		case TInteger:
			tmp.Type = TFloat;
			tmp.Float = (double) left.Float + right.Integer;
			break;
		case TFloat:
			tmp.Type = TFloat;
			tmp.Float = (double) left.Float + right.Float;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TString:
	{
		switch(right.Type) {
		case TString:
			tmp.Type = TString;
			tmp.String = left.String + right.String;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TList:
	{
		switch(right.Type) {
		case TList:
			tmp.Type = TList;
			tmp.List.insert(tmp.List.end(), left.List.begin(), left.List.end());
			tmp.List.insert(tmp.List.end(), right.List.begin(), right.List.end());
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TDict:
		OPTERROR(left, right);
		throw;
	}
	return tmp;
}

/* - */
VarObject operator-(const VarObject &left, const VarObject &right) {
	VarObject tmp;
	switch(left.Type) {
	case TNull:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TBool:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool - right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool - right.Integer;
			break;
		case TFloat:
			tmp.Type = TFloat;
			tmp.Float = (double) left.Bool - right.Float;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TInteger:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer - right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer - right.Integer;
			break;
		case TFloat:
			tmp.Type = TFloat;
			tmp.Float = (double) left.Integer - right.Float;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TFloat:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TFloat;
			tmp.Float = (double) left.Float - right.Bool;
			break;
		case TInteger:
			tmp.Type = TFloat;
			tmp.Float = (double) left.Float - right.Integer;
			break;
		case TFloat:
			tmp.Type = TFloat;
			tmp.Float = (double) left.Float - right.Float;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TString:
		OPTERROR(left, right);
		throw;
		return tmp;
	case TList:
		OPTERROR(left, right);
		throw;
		return tmp;
	case TDict:
		OPTERROR(left, right);
		throw ErrorType;
	}
	return tmp;
}

/* * */
VarObject operator*(const VarObject &left, const VarObject &right) {
	VarObject tmp;
	switch(left.Type) {
	case TNull:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TBool:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool * right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool * right.Integer;
			break;
		case TFloat:
			tmp.Type = TFloat;
			tmp.Float = (double) left.Bool * right.Float;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TInteger:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer * right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer * right.Integer;
			break;
		case TFloat:
			tmp.Type = TFloat;
			tmp.Float = (double) left.Integer * right.Float;
			break;
		case TString:
			tmp.Type = TString;
			for(long long i = 0; i < left.Integer; i++) {
				tmp.String += right.String;
			}
			break;
		case TList:
			tmp.Type = TList;
			for(long long i = 0; i < left.Integer; i++) {
				tmp.List.insert(tmp.List.end(), right.List.begin(), right.List.end());
			}
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TFloat:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TFloat;
			tmp.Float = (double) left.Float * right.Bool;
			break;
		case TInteger:
			tmp.Type = TFloat;
			tmp.Float = (double) left.Float * right.Integer;
			break;
		case TFloat:
			tmp.Type = TFloat;
			tmp.Float = (double) left.Float * right.Float;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TString:
	{
		if(right.Type == TInteger) {
			tmp.Type = TString;
			for(long long i = 0; i < right.Integer; i++) {
				tmp.String += left.String;
			}
		}else{
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TList:
	{
		if(right.Type == TInteger) {
			tmp.Type = TList;
			for(long long i = 0; i < right.Integer; i++) {
				tmp.List.insert(tmp.List.end(), left.List.begin(), left.List.end());
			}
		}else{
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TDict:
		OPTERROR(left, right);
		throw ErrorType;
	}
	return tmp;
}

/* / */
VarObject operator/(const VarObject &left, const VarObject &right) {
	VarObject tmp;
	switch(left.Type) {
	case TNull:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TBool:
	{
		switch(right.Type) {
		case TBool:
			if(!right.Bool)
				throw ZeroDivisor;
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool / right.Bool;
			break;
		case TInteger:
			if(right.Integer == 0)
				throw ZeroDivisor;
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool / right.Integer;
			break;
		case TFloat:
			if(right.Float == 0.0)
				throw ZeroDivisor;
			tmp.Type = TFloat;
			tmp.Float = (double) left.Bool / right.Float;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TInteger:
	{
		switch(right.Type) {
		case TBool:
			if(!right.Bool)
				throw ZeroDivisor;
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer / right.Bool;
			break;
		case TInteger:
			if(right.Integer == 0)
				throw ZeroDivisor;
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer / right.Integer;
			break;
		case TFloat:
			if(right.Float == 0.0)
				throw ZeroDivisor;
			tmp.Type = TFloat;
			tmp.Float = (double) left.Integer / right.Float;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TFloat:
	{
		switch(right.Type) {
		case TBool:
			if(!right.Bool)
				throw ZeroDivisor;
			tmp.Type = TFloat;
			tmp.Float = (double) left.Float / right.Bool;
			break;
		case TInteger:
			if(right.Integer == 0)
				throw ZeroDivisor;
			tmp.Type = TFloat;
			tmp.Float = (double) left.Float / right.Integer;
			break;
		case TFloat:
			if(right.Float == 0.0)
				throw ZeroDivisor;
			tmp.Type = TFloat;
			tmp.Float = (double) left.Float / right.Float;
			break;
		default:
			OPTERROR(left, right);
			throw;
		}
		return tmp;
	}
	case TString:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TList:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TDict:
		OPTERROR(left, right);
		throw ErrorType;
	}
	return tmp;
}

/* & */
VarObject operator&(const VarObject &left, const VarObject &right) {
	VarObject tmp;
	switch(left.Type) {
	case TNull:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TBool:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool & right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool & right.Integer;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TInteger:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer & right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer & right.Integer;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TFloat:
		OPTERROR(left, right);
		throw;
		return tmp;
	case TString:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TList:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TDict:
		OPTERROR(left, right);
		throw ErrorType;
	}
	return tmp;
}

/* | */
VarObject operator|(const VarObject &left, const VarObject &right) {
	VarObject tmp;
	switch(left.Type) {
	case TNull:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TBool:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool | right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool | right.Integer;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TInteger:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer | right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer | right.Integer;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TFloat:
		OPTERROR(left, right);
		throw;
		return tmp;
	case TString:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TList:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TDict:
		OPTERROR(left, right);
		throw ErrorType;
	}
	return tmp;
}

/* ^ */
VarObject operator^(const VarObject &left, const VarObject &right) {
	VarObject tmp;
	switch(left.Type) {
	case TNull:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TBool:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool ^ right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool ^ right.Integer;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TInteger:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer ^ right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer ^ right.Integer;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TFloat:
		OPTERROR(left, right);
		throw;
		return tmp;
	case TString:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TList:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TDict:
		OPTERROR(left, right);
		throw ErrorType;
	}
	return tmp;
}

/* % */
VarObject operator%(const VarObject &left, const VarObject &right) {
	VarObject tmp;
	switch(left.Type) {
	case TNull:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TBool:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool % right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool % right.Integer;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TInteger:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer % right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer % right.Integer;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TFloat:
		OPTERROR(left, right);
		throw;
		return tmp;
	case TString:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TList:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TDict:
		OPTERROR(left, right);
		throw ErrorType;
	}
	return tmp;
}

/* << */
VarObject operator<<(const VarObject &left, const VarObject &right) {
	VarObject tmp;
	switch(left.Type) {
	case TNull:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TBool:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool << right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool << right.Integer;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TInteger:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer << right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer << right.Integer;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TFloat:
		OPTERROR(left, right);
		throw;
		return tmp;
	case TString:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TList:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TDict:
		OPTERROR(left, right);
		throw ErrorType;
	}
	return tmp;
}

/* >> */
VarObject operator>>(const VarObject &left, const VarObject &right) {
	VarObject tmp;
	switch(left.Type) {
	case TNull:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TBool:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool >> right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Bool >> right.Integer;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TInteger:
	{
		switch(right.Type) {
		case TBool:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer >> right.Bool;
			break;
		case TInteger:
			tmp.Type = TInteger;
			tmp.Integer = (long long) left.Integer >> right.Integer;
			break;
		default:
			OPTERROR(left, right);
			throw ErrorType;
		}
		return tmp;
	}
	case TFloat:
		OPTERROR(left, right);
		throw;
		return tmp;
	case TString:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TList:
		OPTERROR(left, right);
		throw ErrorType;
		return tmp;
	case TDict:
		OPTERROR(left, right);
		throw ErrorType;
	}
	return tmp;
}

/* == */
bool operator==(const VarObject &left, const VarObject &right) {
	VarObject tmp;
	switch(left.Type) {
	case TNull:
	{
		switch(right.Type) {
		case TNull:
			return true;
		default:
			return false;
		}
	}
	case TBool:
	{
		switch(right.Type) {
		case TBool:
			return left.Bool == right.Bool;
		case TInteger:
			return left.Bool == right.Integer;
		case TFloat:
			return left.Bool == right.Float;
		default:
			return false;
		}
	}
	case TInteger:
	{
		switch(right.Type) {
		case TBool:
			return left.Integer == right.Bool;
		case TInteger:
			return left.Integer == right.Integer;
		case TFloat:
			return left.Integer == right.Float;
		default:
			return false;
		}
	}
	case TFloat:
	{
		switch(right.Type) {
		case TBool:
			return left.Float == right.Bool;
		case TInteger:
			return left.Float == right.Integer;
		case TFloat:
			return left.Float == right.Float;
		default:
			return false;
		}
	}
	case TString:
	{
		switch(right.Type) {
		case TString:
			return left.String == right.String;
		default:
			return false;
		}
	}
	case TList:
	{
		switch(right.Type) {
		case TList:
			return (left.List == right.List);
#if 0
		{
			size_t llen = left.List.size();
			size_t rlen = right.List.size();
			if(llen != rlen)
				return false;
			for(size_t i = 0; i < llen; i++) {
				if(left.List[i] != right.List[i]) {
					return false;
				}
			}
			return true;
		}
#endif
		default:
			return false;
		}
	}
	case TDict:
	{
		switch(right.Type) {
		case TDict:
			return (left.Dict == right.Dict);
		default:
			return false;
		}
	}
	}
}

/* < */
bool operator<(const VarObject &left, const VarObject &right) {
	VarObject tmp;
	switch(left.Type) {
	case TNull:
	{
		switch(right.Type) {
		case TNull:
			return false;
		default:
			return true;
		}
	}
	case TBool:
	{
		switch(right.Type) {
		case TNull:
			return false;
		case TBool:
			return left.Bool < right.Bool;
		case TInteger:
			return left.Bool < right.Integer;
		case TFloat:
			return left.Bool < right.Float;
		default:
			return true;
		}
	}
	case TInteger:
	{
		switch(right.Type) {
		case TNull:
			return false;
		case TBool:
			return left.Integer < right.Bool;
		case TInteger:
			return left.Integer < right.Integer;
		case TFloat:
			return left.Integer < right.Float;
		default:
			return true;
		}
	}
	case TFloat:
	{
		switch(right.Type) {
		case TNull:
			return false;
		case TBool:
			return left.Float < right.Bool;
		case TInteger:
			return left.Float < right.Integer;
		case TFloat:
			return left.Float < right.Float;
		default:
			return true;
		}
	}
	case TString:
	{
		switch(right.Type) {
		case TString:
			return left.String < right.String;
		default:
			return false;
		}
	}
	case TList:
	{
		switch(right.Type) {
		case TList:
			return (left.List < right.List);
		case TString:
			return true;
		default:
			return false;
		}
	}
	case TDict:
	{
		switch(right.Type) {
		case TDict:
			return (left.Dict < right.Dict);
		case TList:
		case TString:
			return true;
		default:
			return false;
		}
	}
	}
}

/* + */
VarObject operator+(const VarObject &l, long long r) {
	return l + VarObject(r);
}
VarObject operator+(const VarObject &l, int r) {
	return l + VarObject(r);
}
VarObject operator+(const VarObject &l, double r) {
	return l + VarObject(r);
}
VarObject operator+(const VarObject &l, bool r) {
	return l + VarObject(r);
}
VarObject operator+(const VarObject &l, string &r) {
	return l + VarObject(r);
}
VarObject operator+(const VarObject &l, const char *r) {
	return l + VarObject(r);
}
VarObject operator+(const VarObject &l, vector<VarObject> &r) {
	return l + VarObject(r);
}
VarObject operator+(long long l, const VarObject &r) {
	return VarObject(l) + r;
}
VarObject operator+(int l, const VarObject &r) {
	return VarObject(l) + r;
}
VarObject operator+(double l, const VarObject &r) {
	return VarObject(l) + r;
}
VarObject operator+(bool l, const VarObject &r) {
	return VarObject(l) + r;
}
VarObject operator+(string &l, const VarObject &r) {
	return VarObject(l) + r;
}
VarObject operator+(const char *l, const VarObject &r) {
	return VarObject(l) + r;
}
VarObject operator+(vector<VarObject> &l, const VarObject &r) {
	return VarObject(l) + r;
}

/* - */
VarObject operator-(const VarObject &l, long long r) {
	return l - VarObject(r);
}
VarObject operator-(const VarObject &l, int r) {
	return l - VarObject(r);
}
VarObject operator-(const VarObject &l, double r) {
	return l - VarObject(r);
}
VarObject operator-(const VarObject &l, bool r) {
	return l - VarObject(r);
}
VarObject operator-(long long l, const VarObject &r) {
	return VarObject(l) - r;
}
VarObject operator-(int l, const VarObject &r) {
	return VarObject(l) - r;
}
VarObject operator-(double l, const VarObject &r) {
	return VarObject(l) - r;
}
VarObject operator-(bool l, const VarObject &r) {
	return VarObject(l) - r;
}

/* * */
VarObject operator*(const VarObject &l, long long r) {
	return l * VarObject(r);
}
VarObject operator*(const VarObject &l, int r) {
	return l * VarObject(r);
}
VarObject operator*(const VarObject &l, double r) {
	return l * VarObject(r);
}
VarObject operator*(const VarObject &l, bool r) {
	return l * VarObject(r);
}
VarObject operator*(long long l, const VarObject &r) {
	return VarObject(l) * r;
}
VarObject operator*(int l, const VarObject &r) {
	return VarObject(l) * r;
}
VarObject operator*(double l, const VarObject &r) {
	return VarObject(l) * r;
}
VarObject operator*(bool l, const VarObject &r) {
	return VarObject(l) * r;
}

/* / */
VarObject operator/(const VarObject &l, long long r) {
	return l / VarObject(r);
}
VarObject operator/(const VarObject &l, int r) {
	return l / VarObject(r);
}
VarObject operator/(const VarObject &l, double r) {
	return l / VarObject(r);
}
VarObject operator/(const VarObject &l, bool r) {
	return l / VarObject(r);
}
VarObject operator/(long long l, const VarObject &r) {
	return VarObject(l) / r;
}
VarObject operator/(int l, const VarObject &r) {
	return VarObject(l) / r;
}
VarObject operator/(double l, const VarObject &r) {
	return VarObject(l) / r;
}
VarObject operator/(bool l, const VarObject &r) {
	return VarObject(l) / r;
}

/* < */
bool operator<(const VarObject &l, long long r) {
	return l < VarObject(r);
}
bool operator<(const VarObject &l, int r) {
	return l < VarObject(r);
}
bool operator<(const VarObject &l, double r) {
	return l < VarObject(r);
}
bool operator<(const VarObject &l, bool r) {
	return l < VarObject(r);
}
bool operator<(const VarObject &l, string &r) {
	return l < VarObject(r);
}
bool operator<(const VarObject &l, const char *r) {
	return l < VarObject(r);
}
bool operator<(const VarObject &l, vector<VarObject> &r) {
	return l < VarObject(r);
}
bool operator<(long long l, const VarObject &r) {
	return VarObject(l) < r;
}
bool operator<(int l, const VarObject &r) {
	return VarObject(l) < r;
}
bool operator<(double l, const VarObject &r) {
	return VarObject(l) < r;
}
bool operator<(bool l, const VarObject &r) {
	return VarObject(l) < r;
}
bool operator<(string &l, const VarObject &r) {
	return VarObject(l) < r;
}
bool operator<(const char *l, const VarObject &r) {
	return VarObject(l) < r;
}
bool operator<(vector<VarObject> &l, const VarObject &r) {
	return VarObject(l) < r;
}

/* > */
bool operator>(const VarObject &l, const VarObject &r) {
	return r < l;
}
bool operator>(const VarObject &l, long long r) {
	return l > VarObject(r);
}
bool operator>(const VarObject &l, int r) {
	return l > VarObject(r);
}
bool operator>(const VarObject &l, double r) {
	return l > VarObject(r);
}
bool operator>(const VarObject &l, bool r) {
	return l > VarObject(r);
}
bool operator>(const VarObject &l, string &r) {
	return l > VarObject(r);
}
bool operator>(const VarObject &l, const char *r) {
	return l > VarObject(r);
}
bool operator>(const VarObject &l, vector<VarObject> &r) {
	return l > VarObject(r);
}
bool operator>(long long l, const VarObject &r) {
	return VarObject(l) > r;
}
bool operator>(int l, const VarObject &r) {
	return VarObject(l) > r;
}
bool operator>(double l, const VarObject &r) {
	return VarObject(l) < r;
}
bool operator>(bool l, const VarObject &r) {
	return VarObject(l) < r;
}
bool operator>(string &l, const VarObject &r) {
	return VarObject(l) > r;
}
bool operator>(const char *l, const VarObject &r) {
	return VarObject(l) > r;
}
bool operator>(vector<VarObject> &l, const VarObject &r) {
	return VarObject(l) > r;
}

/* <= */
bool operator<=(const VarObject &l, const VarObject &r) {
	if(l == r) {
		return true;
	}
	return l < r;
}
bool operator<=(const VarObject &l, long long r) {
	return l <= VarObject(r);
}
bool operator<=(const VarObject &l, int r) {
	return l <= VarObject(r);
}
bool operator<=(const VarObject &l, double r) {
	return l <= VarObject(r);
}
bool operator<=(const VarObject &l, bool r) {
	return l <= VarObject(r);
}
bool operator<=(const VarObject &l, string &r) {
	return l <= VarObject(r);
}
bool operator<=(const VarObject &l, const char *r) {
	return l <= VarObject(r);
}
bool operator<=(const VarObject &l, vector<VarObject> &r) {
	return l <= VarObject(r);
}
bool operator<=(long long l, const VarObject &r) {
	return VarObject(l) <= r;
}
bool operator<=(int l, const VarObject &r) {
	return VarObject(l) <= r;
}
bool operator<=(double l, const VarObject &r) {
	return VarObject(l) <= r;
}
bool operator<=(bool l, const VarObject &r) {
	return VarObject(l) <= r;
}
bool operator<=(string &l, const VarObject &r) {
	return VarObject(l) <= r;
}
bool operator<=(const char *l, const VarObject &r) {
	return VarObject(l) <= r;
}
bool operator<=(vector<VarObject> &l, const VarObject &r) {
	return VarObject(l) <= r;
}

/* >= */
bool operator>=(const VarObject &l, const VarObject &r) {
	if(l == r) {
		return true;
	}
	return r < l;
}
bool operator>=(const VarObject &l, long long r) {
	return l >= VarObject(r);
}
bool operator>=(const VarObject &l, int r) {
	return l >= VarObject(r);
}
bool operator>=(const VarObject &l, double r) {
	return l >= VarObject(r);
}
bool operator>=(const VarObject &l, bool r) {
	return l >= VarObject(r);
}
bool operator>=(const VarObject &l, string &r) {
	return l >= VarObject(r);
}
bool operator>=(const VarObject &l, const char *r) {
	return l >= VarObject(r);
}
bool operator>=(const VarObject &l, vector<VarObject> &r) {
	return l >= VarObject(r);
}
bool operator>=(long long l, const VarObject &r) {
	return VarObject(l) >= r;
}
bool operator>=(int l, const VarObject &r) {
	return VarObject(l) >= r;
}
bool operator>=(double l, const VarObject &r) {
	return VarObject(l) >= r;
}
bool operator>=(bool l, const VarObject &r) {
	return VarObject(l) >= r;
}
bool operator>=(string &l, const VarObject &r) {
	return VarObject(l) >= r;
}
bool operator>=(const char *l, const VarObject &r) {
	return VarObject(l) >= r;
}
bool operator>=(vector<VarObject> &l, const VarObject &r) {
	return VarObject(l) >= r;
}

/* == */
bool operator==(const VarObject &l, long long r) {
	return l == VarObject(r);
}
bool operator==(const VarObject &l, int r) {
	return l == VarObject(r);
}
bool operator==(const VarObject &l, double r) {
	return l == VarObject(r);
}
bool operator==(const VarObject &l, bool r) {
	return l == VarObject(r);
}
bool operator==(const VarObject &l, string &r) {
	return l == VarObject(r);
}
bool operator==(const VarObject &l, const char *r) {
	return l == VarObject(r);
}
bool operator==(const VarObject &l, vector<VarObject> &r) {
	return l == VarObject(r);
}
bool operator==(long long l, const VarObject &r) {
	return VarObject(l) == r;
}
bool operator==(int l, const VarObject &r) {
	return VarObject(l) == r;
}
bool operator==(double l, const VarObject &r) {
	return VarObject(l) == r;
}
bool operator==(bool l, const VarObject &r) {
	return VarObject(l) == r;
}
bool operator==(string &l, const VarObject &r) {
	return VarObject(l) == r;
}
bool operator==(const char *l, const VarObject &r) {
	return VarObject(l) == r;
}
bool operator==(vector<VarObject> &l, const VarObject &r) {
	return VarObject(l) == r;
}

/* != */
bool operator!=(const VarObject &left, const VarObject &right) {
	return !(left == right);
}
bool operator!=(const VarObject &l, long long r) {
	return l != VarObject(r);
}
bool operator!=(const VarObject &l, int r) {
	return l != VarObject(r);
}
bool operator!=(const VarObject &l, double r) {
	return l != VarObject(r);
}
bool operator!=(const VarObject &l, bool r) {
	return l != VarObject(r);
}
bool operator!=(const VarObject &l, string &r) {
	return l != VarObject(r);
}
bool operator!=(const VarObject &l, const char *r) {
	return l != VarObject(r);
}
bool operator!=(const VarObject &l, vector<VarObject> &r) {
	return l != VarObject(r);
}
bool operator!=(long long l, const VarObject &r) {
	return VarObject(l) != r;
}
bool operator!=(int l, const VarObject &r) {
	return VarObject(l) != r;
}
bool operator!=(double l, const VarObject &r) {
	return VarObject(l) != r;
}
bool operator!=(bool l, const VarObject &r) {
	return VarObject(l) != r;
}
bool operator!=(string &l, const VarObject &r) {
	return VarObject(l) != r;
}
bool operator!=(const char *l, const VarObject &r) {
	return VarObject(l) != r;
}
bool operator!=(vector<VarObject> &l, const VarObject &r) {
	return VarObject(l) != r;
}

/* & */
VarObject operator&(const VarObject &l, long long r) {
	return l & VarObject(r);
}
VarObject operator&(const VarObject &l, int r) {
	return l & VarObject(r);
}
VarObject operator&(const VarObject &l, bool r) {
	return l & VarObject(r);
}
VarObject operator&(long long l, const VarObject &r) {
	return VarObject(l) & r;
}
VarObject operator&(int l, const VarObject &r) {
	return VarObject(l) & r;
}
VarObject operator&(bool l, const VarObject &r) {
	return VarObject(l) & r;
}

/* | */
VarObject operator|(const VarObject &l, long long r) {
	return l | VarObject(r);
}
VarObject operator|(const VarObject &l, int r) {
	return l | VarObject(r);
}
VarObject operator|(const VarObject &l, bool r) {
	return l | VarObject(r);
}
VarObject operator|(long long l, const VarObject &r) {
	return VarObject(l) | r;
}
VarObject operator|(int l, const VarObject &r) {
	return VarObject(l) | r;
}
VarObject operator|(bool l, const VarObject &r) {
	return VarObject(l) | r;
}

/* ^ */
VarObject operator^(const VarObject &l, long long r) {
	return l ^ VarObject(r);
}
VarObject operator^(const VarObject &l, int r) {
	return l ^ VarObject(r);
}
VarObject operator^(const VarObject &l, bool r) {
	return l ^ VarObject(r);
}
VarObject operator^(long long l, const VarObject &r) {
	return VarObject(l) ^ r;
}
VarObject operator^(int l, const VarObject &r) {
	return VarObject(l) ^ r;
}
VarObject operator^(bool l, const VarObject &r) {
	return VarObject(l) ^ r;
}

/* % */
VarObject operator%(const VarObject &l, long long r) {
	return l % VarObject(r);
}
VarObject operator%(const VarObject &l, int r) {
	return l % VarObject(r);
}
VarObject operator%(const VarObject &l, bool r) {
	return l % VarObject(r);
}
VarObject operator%(long long l, const VarObject &r) {
	return VarObject(l) % r;
}
VarObject operator%(int l, const VarObject &r) {
	return VarObject(l) % r;
}
VarObject operator%(bool l, const VarObject &r) {
	return VarObject(l) % r;
}

/* << */
VarObject operator<<(const VarObject &l, long long r) {
	return l << VarObject(r);
}
VarObject operator<<(const VarObject &l, int r) {
	return l << VarObject(r);
}
VarObject operator<<(const VarObject &l, bool r) {
	return l << VarObject(r);
}
VarObject operator<<(long long l, const VarObject &r) {
	return VarObject(l) << r;
}
VarObject operator<<(int l, const VarObject &r) {
	return VarObject(l) << r;
}
VarObject operator<<(bool l, const VarObject &r) {
	return VarObject(l) << r;
}

/* >> */
VarObject operator>>(const VarObject &l, long long r) {
	return l >> VarObject(r);
}
VarObject operator>>(const VarObject &l, int r) {
	return l >> VarObject(r);
}
VarObject operator>>(const VarObject &l, bool r) {
	return l >> VarObject(r);
}
VarObject operator>>(long long l, const VarObject &r) {
	return VarObject(l) >> r;
}
VarObject operator>>(int l, const VarObject &r){
	return VarObject(l) >> r;
}
VarObject operator>>(bool l, const VarObject &r){
	return VarObject(l) >> r;
}

/* += */
const VarObject& operator+=(VarObject &l, const VarObject &r) {
	return l = l + r;
}
const VarObject& operator+=(VarObject &l, long long r) {
	return (l += VarObject(r));
}
const VarObject& operator+=(VarObject &l, int r) {
	return (l += VarObject(r));
}
const VarObject& operator+=(VarObject &l, double r) {
	return (l += VarObject(r));
}
const VarObject& operator+=(VarObject &l, bool r) {
	return (l += VarObject(r));
}
const VarObject& operator+=(VarObject &l, string &r) {
	return (l += VarObject(r));
}
const VarObject& operator+=(VarObject &l, const char *r) {
	return (l += VarObject(r));
}
const VarObject& operator+=(VarObject &l, vector<VarObject> &r) {
	return (l += VarObject(r));
}

/* -= */
const VarObject& operator-=(VarObject &l, const VarObject &r) {
	return l = l - r;
}
const VarObject& operator-=(VarObject &l, long long r) {
	return (l -= VarObject(r));
}
const VarObject& operator-=(VarObject &l, int r) {
	return (l -= VarObject(r));
}
const VarObject& operator-=(VarObject &l, double r) {
	return (l -= VarObject(r));
}
const VarObject& operator-=(VarObject &l, bool r) {
	return (l -= VarObject(r));
}

/* *= */
const VarObject& operator*=(VarObject &l, const VarObject &r) {
	return l = l * r;
}
const VarObject& operator*=(VarObject &l, long long r) {
	return (l *= VarObject(r));
}
const VarObject& operator*=(VarObject &l, int r) {
	return (l *= VarObject(r));
}
const VarObject& operator*=(VarObject &l, double r) {
	return (l *= VarObject(r));
}
const VarObject& operator*=(VarObject &l, bool r) {
	return (l *= VarObject(r));
}

/* /= */
const VarObject& operator/=(VarObject &l, const VarObject &r) {
	return l = l / r;
}
const VarObject& operator/=(VarObject &l, long long r) {
	return (l /= VarObject(r));
}
const VarObject& operator/=(VarObject &l, int r) {
	return (l /= VarObject(r));
}
const VarObject& operator/=(VarObject &l, double r) {
	return (l /= VarObject(r));
}
const VarObject& operator/=(VarObject &l, bool r) {
	return (l /= VarObject(r));
}

/* &= */
const VarObject& operator&=(VarObject &l, const VarObject &r) {
	return l = l & r;
}
const VarObject& operator&=(VarObject &l, long long r) {
	return (l &= VarObject(r));
}
const VarObject& operator&=(VarObject &l, int r) {
	return (l &= VarObject(r));
}
const VarObject& operator&=(VarObject &l, bool r) {
	return (l &= VarObject(r));
}

/* |= */
const VarObject& operator|=(VarObject &l, const VarObject &r) {
	return l = l | r;
}
const VarObject& operator|=(VarObject &l, long long r) {
	return (l |= VarObject(r));
}
const VarObject& operator|=(VarObject &l, int r) {
	return (l |= VarObject(r));
}
const VarObject& operator|=(VarObject &l, bool r) {
	return (l |= VarObject(r));
}

/* ^= */
const VarObject& operator^=(VarObject &l, const VarObject &r) {
	return l = l ^ r;
}
const VarObject& operator^=(VarObject &l, long long r) {
	return (l ^= VarObject(r));
}
const VarObject& operator^=(VarObject &l, int r) {
	return (l ^= VarObject(r));
}
const VarObject& operator^=(VarObject &l, bool r) {
	return (l ^= VarObject(r));
}

/* %= */
const VarObject& operator%=(VarObject &l, const VarObject &r) {
	return l = l % r;
}
const VarObject& operator%=(VarObject &l, long long r) {
	return (l %= VarObject(r));
}
const VarObject& operator%=(VarObject &l, int r) {
	return (l %= VarObject(r));
}
const VarObject& operator%=(VarObject &l, bool r) {
	return (l %= VarObject(r));
}

/* <<= */
const VarObject& operator<<=(VarObject &l, const VarObject &r) {
	return l = l << r;
}
const VarObject& operator<<=(VarObject &l, long long r) {
	return (l <<= VarObject(r));
}
const VarObject& operator<<=(VarObject &l, int r) {
	return (l <<= VarObject(r));
}
const VarObject& operator<<=(VarObject &l, bool r) {
	return (l <<= VarObject(r));
}

/* >>= */
const VarObject& operator>>=(VarObject &l, const VarObject &r) {
	return l = l >> r;
}
const VarObject& operator>>=(VarObject &l, long long r) {
	return (l >>= VarObject(r));
}
const VarObject& operator>>=(VarObject &l, int r) {
	return (l >>= VarObject(r));
}
const VarObject& operator>>=(VarObject &l, bool r) {
	return (l >>= VarObject(r));
}

VarObject::operator bool(void) {
	switch(Type) {
	case TNull:
		return false;
	case TBool:
		return Bool;
	case TInteger:
		return (Integer != 0);
	case TFloat:
		return (Float != 0.0);
	case TString:
		return !(String.empty() || String.length() == 0);
	case TList:
		return !(List.size() == 0);
	case TDict:
		return !(Dict.size() == 0);
	}
}

VarObject::operator long long(void) {
	return this->ToInteger();
}

VarObject::operator int(void) {
	return this->ToInteger();
}

VarObject::operator double(void) {
	return this->ToFloat();
}

VarObject::operator string(void) {
	return ToString();
}

VarObject::operator vector<VarObject>&(void) {
	if(Type != TList) {
		OPTERRORS(*this);
		throw ErrorType;
	}
	return this->List;
}

VarObject::operator map<VarObject, VarObject>&(void) {
	if(Type != TDict) {
		OPTERRORS(*this);
		throw ErrorType;
	}
	return this->Dict;
}

/* ++ -- ~ ! */
VarObject operator++(VarObject &l) {
	switch(l.Type) {
	case TInteger:
		++l.Integer;
		return l;
	default:
		OPTERRORS(l);
		throw ErrorType;
		return l;
	}
}

const VarObject operator++(VarObject &l, int __attribute__((unused)) i) {
	VarObject tmp = l;
	++l;
	return tmp;
}

VarObject operator--(VarObject &l) {
	switch(l.Type) {
	case TInteger:
		--l.Integer;
		return l;
	default:
		OPTERRORS(l);
		throw ErrorType;
		return l;
	}
}

const VarObject operator--(VarObject &l, int __attribute__((unused)) i) {
	VarObject tmp = l;
	--l;
	return tmp;
}

VarObject operator~(const VarObject &l) {
	switch(l.Type) {
	case TBool:
	{
		VarObject tmp;
		tmp.Type = TInteger;
		tmp.Integer = ~l.Bool;
		return tmp;
	}
	case TInteger:
	{
		VarObject tmp;
		tmp.Type = TInteger;
		tmp.Integer = ~l.Integer;
		return tmp;
	}
	default:
		OPTERRORS(l);
		throw ErrorType;
		return l;
	}
}

bool operator!(const VarObject &l) {
	switch(l.Type) {
	case TNull:
		return true;
	case TBool:
		return !l.Bool;
	case TInteger:
		return !l.Integer;
	case TFloat:
		return !l.Float;
	case TString:
		return !(l.String.length() != 0);
	case TList:
		return !(l.List.size() != 0);
	case TDict:
		return !(l.Dict.size() != 0);
	}
}

/* [] */
VarObject& VarObject::operator[](const VarObject &idx) {
	switch(Type) {
	case TList:
		switch(idx.Type) {
		case TBool:
			return this->List[idx.Bool];
		case TInteger:
			return this->List[idx.Integer];
		default:
			OPTERRORS(*this);
			throw ErrorType;
		}
	case TDict:
		return this->Dict[idx];
	default:
		OPTERRORS(*this);
		throw ErrorType;
	}
}

VarObject& VarObject::operator[](const long long &idx) {
	return (*this)[VarObject(idx)];
}

VarObject& VarObject::operator[](const int &idx) {
	return (*this)[VarObject(idx)];
}

VarObject& VarObject::operator[](const bool &idx) {
	return (*this)[VarObject(idx)];
}

VarObject& VarObject::operator[](const double &idx) {
	return (*this)[VarObject(idx)];
}

VarObject& VarObject::operator[](const string &idx) {
	return (*this)[VarObject(idx)];
}

VarObject& VarObject::operator[](const char *idx) {
	return (*this)[VarObject(idx)];
}

ostream& operator<<(ostream &other, const VarObject &me) {
	return me.ToStr(other);
}

ostream& operator<<(ostream &o, const __LIST_PRODUCE &me)
{
	return (o << VarObject(me));
}

}
