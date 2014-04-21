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

using namespace var;

stringstream& VarObject::ToStr(stringstream &s) const {
	switch(Type) {
	case TNull:
		s << "null";
		break;
	case TInteger:
		s << Integer;
		break;
	case TFloat:
		s << Float;
		break;
	case TBool:
		s << (Bool ? "True" : "False");
		break;
	case TString:
		s << String;
		break;
	case TList:
	{
		s << "[";
		size_t len = List.size();
		if(len > 0) {
			List[0].ToStr(s);
			for(size_t i = 1; i < len; i++) {
				s << ",";
				List[i].ToStr(s);
			}
		}
		s << "]";
		break;
	}
	default:
		cerr << "translate unknown type (" << Type << ") to ostream" << endl;
		throw;
	}
	return s;
}

long long VarObject::ToInteger(void) {
	switch(Type) {
	case TNull:
		return 0;
	case TBool:
		return (Bool ? 1 : 0);
	case TInteger:
		return Integer;
	case TFloat:
		return (long long) Float;
	case TString:
	{
		stringstream ss;
		long long retval;
		ss << String;
		ss >> retval;
		return retval;
	}
	case TList:
		cerr << "can't transform value from " << Type << " to long long" << endl;
		throw;
	default:
		cerr << "transform value from unknwon type (" << Type << ") to long long" << endl;
		throw;
	}
	return 0;
}

double VarObject::ToFloat(void) {
	switch(Type) {
	case TNull:
		return 0.0;
	case TBool:
		cerr << "can't transform value from " << Type << " to double" << endl;
		throw;
	case TInteger:
		return (double) Integer;
	case TFloat:
		return Float;
	case TString:
	{
		stringstream ss;
		double retval;
		ss << String;
		ss >> retval;
		return retval;
	}
	case TList:
		throw;
	default:
		cerr << "transform value from unknwon type (" << Type << ") to double" << endl;
		throw;
	}
	return 0.0;
}

string VarObject::ToString(void) {
	switch(Type) {
	case TString:
		return String;
	default:
		cerr << "can't transform value from " << Type << " to string" << endl;
		throw;
	}
	//return "";
}

void VarObject::FromInteger(long long i) {
	if(Type != TNull) {
		Clear();
	}
	Type = TInteger;
	Integer = i;
}

void VarObject::FromFloat(double d) {
	if(Type != TNull) {
		Clear();
	}
	Type = TFloat;
	Float = d;
}

void VarObject::FromBool(bool b) {
	if(Type != TNull) {
		Clear();
	}
	Type = TBool;
	Bool = b;
}

void VarObject::FromString(const string &s) {
	if(Type != TNull) {
		Clear();
	}
	Type = TString;
	String = s;
}

void VarObject::FromString(const char *s) {
	if(Type != TNull) {
		Clear();
	}
	Type = TString;
	String = s;
}

void VarObject::FromList(vector<VarObject> &list) {
	if(Type != TNull) {
		Clear();
	}
	Type = TList;
	List = list;
}
