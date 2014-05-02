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

ostream& VarObject::ToStr(ostream &o) const {
	switch(Type) {
	case TNull:
		o << "null";
		break;
	case TInteger:
		o << Integer;
		break;
	case TFloat:
		o << Float;
		break;
	case TBool:
		o << (Bool ? "True" : "False");
		break;
	case TString:
		o << String;
		break;
	case TObject:
		o << "Object(" << String << ")";
		break;
	case TList:
	{
		o << "[";
		size_t len = List.size();
		if(len > 0) {
			List[0]->ToStr(o);
			for(size_t i = 1; i < len; i++) {
				o << ",";
				List[i]->ToStr(o);
			}
		}
		o << "]";
		break;
	}
	case TDict:
	{
		o << "{";
		map<VarObject, VarObject>::const_iterator it = Dict.begin();
		it->first.ToStr(o);
		o << ":";
		it->second.ToStr(o);
		it++;
		for(; it != Dict.end(); it++) {
			o << ",";
			it->first.ToStr(o);
			o << ":";
			it->second.ToStr(o);
		}
		o << "}";
		break;
	}
	}
	return o;
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
	default:
		cerr << "transform value from unknwon type (" << Type << ") to long long" << endl;
		throw ErrorType;
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
	default:
		cerr << "transform value from unknwon type (" << Type << ") to double" << endl;
		throw ErrorType;
	}
	return 0.0;
}

string VarObject::ToString(void) {
	switch(Type) {
	case TString:
		return String;
	default:
		cerr << "can't transform value from " << Type << " to string" << endl;
		throw ErrorType;
	}
	//return "";
}

void VarObject::FromInteger(const long long &i) {
	if(Type != TNull) {
		Clear();
	}
	Type = TInteger;
	Integer = i;
}

void VarObject::FromFloat(const double &d) {
	if(Type != TNull) {
		Clear();
	}
	Type = TFloat;
	Float = d;
}

void VarObject::FromBool(const bool &b) {
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

void VarObject::FromList(const VarList &list) {
	if(Type != TNull) {
		Clear();
	}
	Type = TList;
	List = list;
}

void VarObject::FromDict(const map<VarObject, VarObject> &dict) {
	if(Type != TNull) {
		Clear();
	}
	Type = TDict;
	Dict = dict;
}
