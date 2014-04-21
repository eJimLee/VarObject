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

namespace var {

VarObject::VarObject(void) {
	Clear();
	Type = TNull;
}

VarObject::VarObject(long long i) {
	Clear();
	Type = TInteger;
	Integer = i;
}

VarObject::VarObject(int i) {
	Clear();
	Type = TInteger;
	Integer = i;
}

VarObject::VarObject(double f) {
	Clear();
	Type = TFloat;
	Float = f;
}

VarObject::VarObject(bool b) {
	Clear();
	Type = TBool;
	Bool = b;
}

VarObject::VarObject(string s) {
	Clear();
	Type = TString;
	String = s;
}

VarObject::VarObject(const char *s) {
	Clear();
	Type = TString;
	String = s;
}

VarObject::VarObject(const vector<VarObject> &l) {
	Clear();
	Type = TList;
	List = l;
}

VarObject::VarObject(VarType t) {
	Clear();
	Type = t;
}

VarObject& VarObject::operator=(const VarObject &src) {
	if(Type != TNull) {
		Clear();
	}
	Copy(src);
	return *this;
}

VarObject& VarObject::operator=(long long i) {
	FromInteger(i);
	return *this;
}

VarObject& VarObject::operator=(int i) {
	FromInteger(i);
	return *this;
}

VarObject& VarObject::operator=(double d) {
	FromFloat(d);
	return *this;
}

VarObject& VarObject::operator=(bool b) {
	FromBool(b);
	return *this;
}

VarObject& VarObject::operator=(const string &s) {
	FromString(s);
	return *this;
}

VarObject& VarObject::operator=(const char *s) {
	FromString(s);
	return *this;
}

VarObject& VarObject::operator=(vector<VarObject> &list) {
	FromList(list);
	return *this;
}

VarType VarObject::GetType(void) {
	return this->Type;
}

void VarObject::Copy(const VarObject &src) {
	switch(src.Type) {
	case TNull:
		break;
	case TBool:
		Bool = false;
		break;
	case TInteger:
		Integer = src.Integer;
		break;
	case TFloat:
		Float = src.Float;
		break;
	case TString:
		String = src.String;
		break;
	case TList:
		List = src.List;
		break;
	default:
		cerr << "copy value from unknwon type (" << Type << ")" << endl;
		throw;
	}
	Type = src.Type;
}

void VarObject::Clear(void) {
	Integer = 0;
	Float = 0;
	Bool = false;
	String.clear();
	List.clear();
}

}
