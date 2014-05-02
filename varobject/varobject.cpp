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
	Type = TNull;
}

VarObject::VarObject(const VarObject &o) {
	if(o.Type == TObject) {
		cerr << "VarObject::" << __func__ << "(const VarObject &o)"
			<< " not support TObject Type" << endl;
		throw InvalidArg;
	}
	Copy(o);
}

VarObject::VarObject(long long i) {
	Type = TInteger;
	Integer = i;
}
VarObject::VarObject(int i) {
	Type = TInteger;
	Integer = i;
}

VarObject::VarObject(double f) {
	Type = TFloat;
	Float = f;
}

VarObject::VarObject(bool b) {
	Type = TBool;
	Bool = b;
}

VarObject::VarObject(string s) {
	Type = TString;
	String = s;
}

VarObject::VarObject(const char *s) {
	Type = TString;
	String = s;
}

VarObject::VarObject(const VarList &l) {
	Type = TList;
	List = l;
}

VarObject::VarObject(const map<VarObject, VarObject> &d) {
	Type = TDict;
	Dict = d;
}

VarObject::VarObject(VarType t) {
	Type = t;
}

VarObject::VarObject(VarType t, string s) {
	if(t != TObject) {
		cerr << "VarObject::" << __func__ << "(VarType t, string s)"
			<< " Only support TObject Type" << endl;
		throw InvalidArg;
	}
	Type = TObject;
	String = s;
}

VarObject::VarObject(VarType t, const char *s) {
	if(t != TObject) {
		cerr << "VarObject::" << __func__ << "(VarType t, const char s)"
			<< " Only support TObject Type" << endl;
		throw InvalidArg;
	}
	Type = TObject;
	String = s;
}

VarObject::~VarObject(void) {
	Clear();
}

VarObject& VarObject::operator=(const VarObject &src) {
	if(Type != TNull) {
		Clear();
	}
	if(Type == TObject && Type != TObject) {
		cerr << "TObject variable only support to be assigned from TObject" << endl;
		throw InvalidArg;
	}
	Copy(src);
	return *this;
}

void VarObjectTypeCheck(const VarObject *o, VarType t) {
	if(o->GetType() == TObject && t != TObject) {
		cerr << "TObject variable only support to be assigned from TObject" << endl;
		throw InvalidArg;
	}
}

VarObject& VarObject::operator=(const long long &i) {
	VarObjectTypeCheck(this, TInteger);
	FromInteger(i);
	return *this;
}

VarObject& VarObject::operator=(const int &i) {
	VarObjectTypeCheck(this, TInteger);
	FromInteger(i);
	return *this;
}

VarObject& VarObject::operator=(const double &d) {
	VarObjectTypeCheck(this, TFloat);
	FromFloat(d);
	return *this;
}

VarObject& VarObject::operator=(const bool &b) {
	VarObjectTypeCheck(this, TBool);
	FromBool(b);
	return *this;
}

VarObject& VarObject::operator=(const string &s) {
	VarObjectTypeCheck(this, TString);
	FromString(s);
	return *this;
}

VarObject& VarObject::operator=(const char *s) {
	VarObjectTypeCheck(this, TString);
	FromString(s);
	return *this;
}

VarObject& VarObject::operator=(const VarList &list) {
	VarObjectTypeCheck(this, TList);
	FromList(list);
	return *this;
}

VarObject& VarObject::operator=(const map<VarObject, VarObject> &dict) {
	VarObjectTypeCheck(this, TDict);
	FromDict(dict);
	return *this;
}

VarObject& VarObject::operator=(const VarType &t) {
	VarObjectTypeCheck(this, t);
	Clear();
	Type = t;
	return *this;
}

VarType VarObject::GetType(void) const{
	return this->Type;
}

VarObject* VarObject::CopySelf(void) const {
	VarObject *new_instance = new VarObject();
	*new_instance = *this;
	return new_instance;
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
	case TObject:
		String = src.String;
		break;
	case TList:
		List = src.List;
		break;
	case TDict:
		Dict = src.Dict;
		break;
	}
	Type = src.Type;
}

void VarObject::Clear(void) {
	Integer = 0;
	Float = 0;
	Bool = false;
	String.clear();
	List.clear();
	Dict.clear();
}

}
