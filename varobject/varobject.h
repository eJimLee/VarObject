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
#ifndef __VAROBJECT_H__
#define __VAROBJECT_H__

#include <vector>
#include <string>

#include "vartype.h"

namespace var {

using namespace std;

class VarObject {
public:
	/* initial */
	VarObject(void);
	VarObject(long long i);
	VarObject(int i);
	VarObject(double f);
	VarObject(bool b);
	VarObject(string s);
	VarObject(const char *s);
	VarObject(const vector<VarObject> &l);
	VarObject(VarType t);

public:
	VarType GetType(void);

public:
	/* cout << obj */
	friend ostream& operator<<(ostream &other, const VarObject &me);
	/* type transform */
	operator bool(void);
	operator long long(void);
	operator int(void);
	operator double(void);
	operator string(void);
	operator vector<VarObject>&(void);

public:
	/* operator */
	/* assign */
	VarObject& operator=(const VarObject &src);
	VarObject& operator=(long long i);
	VarObject& operator=(int i);
	VarObject& operator=(double f);
	VarObject& operator=(bool b);
	VarObject& operator=(const string &s);
	VarObject& operator=(const char *s);
	VarObject& operator=(vector<VarObject> &list);
	VarObject& operator=(VarType t);

	/* + */
	friend VarObject operator+(const VarObject &l, const VarObject &r);
	friend VarObject operator+(const VarObject &l, long long r);
	friend VarObject operator+(const VarObject &l, int r);
	friend VarObject operator+(const VarObject &l, double r);
	friend VarObject operator+(const VarObject &l, bool r);
	friend VarObject operator+(const VarObject &l, string &r);
	friend VarObject operator+(const VarObject &l, const char *r);
	friend VarObject operator+(const VarObject &l, vector<VarObject> &r);
	friend VarObject operator+(long long l, const VarObject &r);
	friend VarObject operator+(int l, const VarObject &r);
	friend VarObject operator+(double l, const VarObject &r);
	friend VarObject operator+(bool l, const VarObject &r);
	friend VarObject operator+(string &l, const VarObject &r);
	friend VarObject operator+(const char *l, const VarObject &r);
	friend VarObject operator+(vector<VarObject> &l, const VarObject &r);

	/* - */
	friend VarObject operator-(const VarObject &l, const VarObject &r);
	friend VarObject operator-(const VarObject &l, long long r);
	friend VarObject operator-(const VarObject &l, int r);
	friend VarObject operator-(const VarObject &l, double r);
	friend VarObject operator-(const VarObject &l, bool r);
	//friend VarObject operator-(const VarObject &l, string &r);
	//friend VarObject operator-(const VarObject &l, vector<VarObject> &r);
	friend VarObject operator-(long long l, const VarObject &r);
	friend VarObject operator-(int l, const VarObject &r);
	friend VarObject operator-(double l, const VarObject &r);
	friend VarObject operator-(bool l, const VarObject &r);
	//friend VarObject operator-(string l, const VarObject &r);
	//friend VarObject operator-(vector<VarObject> &l, const VarObject &r);

	/* * */
	friend VarObject operator*(const VarObject &l, const VarObject &r);
	friend VarObject operator*(const VarObject &l, long long r);
	friend VarObject operator*(const VarObject &l, int r);
	friend VarObject operator*(const VarObject &l, double r);
	friend VarObject operator*(const VarObject &l, bool r);
	//friend VarObject operator*(const VarObject &l, string &r);
	//friend VarObject operator*(const VarObject &l, vector<VarObject> &r);
	friend VarObject operator*(long long l, const VarObject &r);
	friend VarObject operator*(int l, const VarObject &r);
	friend VarObject operator*(double l, const VarObject &r);
	friend VarObject operator*(bool l, const VarObject &r);
	//friend VarObject operator*(string l, const VarObject &r);
	//friend VarObject operator*(vector<VarObject> &l, const VarObject &r);

	/* / */
	friend VarObject operator/(const VarObject &l, const VarObject &r);
	friend VarObject operator/(const VarObject &l, long long r);
	friend VarObject operator/(const VarObject &l, int r);
	friend VarObject operator/(const VarObject &l, double r);
	friend VarObject operator/(const VarObject &l, bool r);
	//friend VarObject operator/(const VarObject &l, string &r);
	//friend VarObject operator/(const VarObject &l, vector<VarObject> &r);
	friend VarObject operator/(long long l, const VarObject &r);
	friend VarObject operator/(int l, const VarObject &r);
	friend VarObject operator/(double l, const VarObject &r);
	friend VarObject operator/(bool l, const VarObject &r);
	//friend VarObject operator/(string &l, const VarObject &r);
	//friend VarObject operator/(vector<VarObject> &l, const VarObject &r);

	/* & */
	friend VarObject operator&(const VarObject &l, const VarObject &r);
	friend VarObject operator&(const VarObject &l, long long r);
	friend VarObject operator&(const VarObject &l, int r);
	friend VarObject operator&(const VarObject &l, bool r);
	//friend VarObject operator&(const VarObject &l, double r);
	//friend VarObject operator&(const VarObject &l, string &r);
	//friend VarObject operator&(const VarObject &l, vector<VarObject> &r);
	friend VarObject operator&(long long l, const VarObject &r);
	friend VarObject operator&(int l, const VarObject &r);
	friend VarObject operator&(bool l, const VarObject &r);
	//friend VarObject operator&(double l, const VarObject &r);
	//friend VarObject operator&(string &l, const VarObject &r);
	//friend VarObject operator&(vector<VarObject> &l, const VarObject &r);

	/* | */
	friend VarObject operator|(const VarObject &l, const VarObject &r);
	friend VarObject operator|(const VarObject &l, long long r);
	friend VarObject operator|(const VarObject &l, int r);
	friend VarObject operator|(const VarObject &l, bool r);
	//friend VarObject operator|(const VarObject &l, double r);
	//friend VarObject operator|(const VarObject &l, string &r);
	//friend VarObject operator|(const VarObject &l, vector<VarObject> &r);
	friend VarObject operator|(long long l, const VarObject &r);
	friend VarObject operator|(int l, const VarObject &r);
	friend VarObject operator|(bool l, const VarObject &r);
	//friend VarObject operator|(double l, const VarObject &r);
	//friend VarObject operator|(string &l, const VarObject &r);
	//friend VarObject operator|(vector<VarObject> &l, const VarObject &r);

	/* ^ */
	friend VarObject operator^(const VarObject &l, const VarObject &r);
	friend VarObject operator^(const VarObject &l, long long r);
	friend VarObject operator^(const VarObject &l, int r);
	friend VarObject operator^(const VarObject &l, bool r);
	//friend VarObject operator^(const VarObject &l, double r);
	//friend VarObject operator^(const VarObject &l, string &r);
	//friend VarObject operator^(const VarObject &l, vector<VarObject> &r);
	friend VarObject operator^(long long l, const VarObject &r);
	friend VarObject operator^(int l, const VarObject &r);
	friend VarObject operator^(bool l, const VarObject &r);
	//friend VarObject operator^(double l, const VarObject &r);
	//friend VarObject operator^(string &l, const VarObject &r);
	//friend VarObject operator^(vector<VarObject> &l, const VarObject &r);

	/* % */
	friend VarObject operator%(const VarObject &l, const VarObject &r);
	friend VarObject operator%(const VarObject &l, long long r);
	friend VarObject operator%(const VarObject &l, int r);
	friend VarObject operator%(const VarObject &l, bool r);
	//friend VarObject operator%(const VarObject &l, double r);
	//friend VarObject operator%(const VarObject &l, string &r);
	//friend VarObject operator%(const VarObject &l, vector<VarObject> &r);
	friend VarObject operator%(long long l, const VarObject &r);
	friend VarObject operator%(int l, const VarObject &r);
	friend VarObject operator%(bool l, const VarObject &r);
	//friend VarObject operator%(double l, const VarObject &r);
	//friend VarObject operator%(string &l, const VarObject &r);
	//friend VarObject operator%(vector<VarObject> &l, const VarObject &r);

	/* << */
	friend VarObject operator<<(const VarObject &l, const VarObject &r);
	friend VarObject operator<<(const VarObject &l, long long r);
	friend VarObject operator<<(const VarObject &l, int r);
	friend VarObject operator<<(const VarObject &l, bool r);
	//friend VarObject operator<<(const VarObject &l, double r);
	//friend VarObject operator<<(const VarObject &l, string &r);
	//friend VarObject operator<<(const VarObject &l, vector<VarObject> &r);
	friend VarObject operator<<(long long l, const VarObject &r);
	friend VarObject operator<<(int l, const VarObject &r);
	friend VarObject operator<<(bool l, const VarObject &r);
	//friend VarObject operator<<(double l, const VarObject &r);
	//friend VarObject operator<<(string &l, const VarObject &r);
	//friend VarObject operator<<(vector<VarObject> &l, const VarObject &r);

	/* >> */
	friend VarObject operator>>(const VarObject &l, const VarObject &r);
	friend VarObject operator>>(const VarObject &l, long long r);
	friend VarObject operator>>(const VarObject &l, int r);
	friend VarObject operator>>(const VarObject &l, bool r);
	//friend VarObject operator>>(const VarObject &l, double r);
	//friend VarObject operator>>(const VarObject &l, string &r);
	//friend VarObject operator>>(const VarObject &l, vector<VarObject> &r);
	friend VarObject operator>>(long long l, const VarObject &r);
	friend VarObject operator>>(int l, const VarObject &r);
	friend VarObject operator>>(bool l, const VarObject &r);
	//friend VarObject operator>>(double l, const VarObject &r);
	//friend VarObject operator>>(string &l, const VarObject &r);
	//friend VarObject operator>>(vector<VarObject> &l, const VarObject &r);

	/* < */
	friend bool operator<(const VarObject &l, const VarObject &r);
	friend bool operator<(const VarObject &l, long long r);
	friend bool operator<(const VarObject &l, int r);
	friend bool operator<(const VarObject &l, double r);
	friend bool operator<(const VarObject &l, bool r);
	friend bool operator<(const VarObject &l, string &r);
	friend bool operator<(const VarObject &l, const char *r);
	friend bool operator<(const VarObject &l, vector<VarObject> &r);
	friend bool operator<(long long l, const VarObject &r);
	friend bool operator<(int l, const VarObject &r);
	friend bool operator<(double l, const VarObject &r);
	friend bool operator<(bool l, const VarObject &r);
	friend bool operator<(string &l, const VarObject &r);
	friend bool operator<(const char *l, const VarObject &r);
	friend bool operator<(vector<VarObject> &l, const VarObject &r);

	/* > */
	friend bool operator>(const VarObject &l, const VarObject &r);
	friend bool operator>(const VarObject &l, long long r);
	friend bool operator>(const VarObject &l, int r);
	friend bool operator>(const VarObject &l, double r);
	friend bool operator>(const VarObject &l, bool r);
	friend bool operator>(const VarObject &l, string &r);
	friend bool operator>(const VarObject &l, const char *r);
	friend bool operator>(const VarObject &l, vector<VarObject> &r);
	friend bool operator>(long long l, const VarObject &r);
	friend bool operator>(int l, const VarObject &r);
	friend bool operator>(double l, const VarObject &r);
	friend bool operator>(bool l, const VarObject &r);
	friend bool operator>(string &l, const VarObject &r);
	friend bool operator>(const char *l, const VarObject &r);
	friend bool operator>(vector<VarObject> &l, const VarObject &r);

	/* <= */
	friend bool operator<=(const VarObject &l, const VarObject &r);
	friend bool operator<=(const VarObject &l, long long r);
	friend bool operator<=(const VarObject &l, int r);
	friend bool operator<=(const VarObject &l, double r);
	friend bool operator<=(const VarObject &l, bool r);
	friend bool operator<=(const VarObject &l, string &r);
	friend bool operator<=(const VarObject &l, const char *r);
	friend bool operator<=(const VarObject &l, vector<VarObject> &r);
	friend bool operator<=(long long l, const VarObject &r);
	friend bool operator<=(int l, const VarObject &r);
	friend bool operator<=(double l, const VarObject &r);
	friend bool operator<=(bool l, const VarObject &r);
	friend bool operator<=(string &l, const VarObject &r);
	friend bool operator<=(const char *l, const VarObject &r);
	friend bool operator<=(vector<VarObject> &l, const VarObject &r);

	/* >= */
	friend bool operator>=(const VarObject &l, const VarObject &r);
	friend bool operator>=(const VarObject &l, long long r);
	friend bool operator>=(const VarObject &l, int r);
	friend bool operator>=(const VarObject &l, double r);
	friend bool operator>=(const VarObject &l, bool r);
	friend bool operator>=(const VarObject &l, string &r);
	friend bool operator>=(const VarObject &l, const char *r);
	friend bool operator>=(const VarObject &l, vector<VarObject> &r);
	friend bool operator>=(long long l, const VarObject &r);
	friend bool operator>=(int l, const VarObject &r);
	friend bool operator>=(double l, const VarObject &r);
	friend bool operator>=(bool l, const VarObject &r);
	friend bool operator>=(string &l, const VarObject &r);
	friend bool operator>=(const char *l, const VarObject &r);
	friend bool operator>=(vector<VarObject> &l, const VarObject &r);

	/* == */
	friend bool operator==(const VarObject &l, const VarObject &r);
	friend bool operator==(const VarObject &l, long long r);
	friend bool operator==(const VarObject &l, int r);
	friend bool operator==(const VarObject &l, double r);
	friend bool operator==(const VarObject &l, bool r);
	friend bool operator==(const VarObject &l, string &r);
	friend bool operator==(const VarObject &l, const char *r);
	friend bool operator==(const VarObject &l, vector<VarObject> &r);
	friend bool operator==(long long l, const VarObject &r);
	friend bool operator==(int l, const VarObject &r);
	friend bool operator==(double l, const VarObject &r);
	friend bool operator==(bool l, const VarObject &r);
	friend bool operator==(string &l, const VarObject &r);
	friend bool operator==(const char *l, const VarObject &r);
	friend bool operator==(vector<VarObject> &l, const VarObject &r);

	/* != */
	friend bool operator!=(const VarObject &l, const VarObject &r);
	friend bool operator!=(const VarObject &l, long long r);
	friend bool operator!=(const VarObject &l, int r);
	friend bool operator!=(const VarObject &l, double r);
	friend bool operator!=(const VarObject &l, bool r);
	friend bool operator!=(const VarObject &l, string &r);
	friend bool operator!=(const VarObject &l, const char *r);
	friend bool operator!=(const VarObject &l, vector<VarObject> &r);
	friend bool operator!=(long long l, const VarObject &r);
	friend bool operator!=(int l, const VarObject &r);
	friend bool operator!=(double l, const VarObject &r);
	friend bool operator!=(bool l, const VarObject &r);
	friend bool operator!=(string &l, const VarObject &r);
	friend bool operator!=(const char *l, const VarObject &r);
	friend bool operator!=(vector<VarObject> &l, const VarObject &r);

	/* ++ -- ~ ! */
	friend VarObject operator++(VarObject &l);
	friend const VarObject operator++(VarObject &l, int i);
	friend VarObject operator--(VarObject &l);
	friend const VarObject operator--(VarObject &l, int i);
	friend VarObject operator~(const VarObject &l);
	friend bool operator!(const VarObject &l);

	/* [] */
	VarObject operator[](size_t idx);
	VarObject operator[](long long idx);
	VarObject operator[](int idx);
	VarObject operator[](const VarObject &idx);

protected:
	VarType Type;
	union {
		long long Integer;
		double Float;
		bool Bool;
	};
	string String;
	vector<VarObject> List;

private:
	void Copy(const VarObject &src);
	void Clear(void);
	stringstream& ToStr(stringstream &s) const;

private:
	long long ToInteger(void);
	double    ToFloat(void);
	bool      ToBool(void);
	string    ToString(void);
	void FromInteger(long long i);
	void FromFloat(double d);
	void FromBool(bool b);
	void FromString(const string &s);
	void FromString(const char *s);
	void FromList(vector<VarObject> &list);
};

/* some helper */
class __LIST_PRODUCE : public vector<VarObject> {
public:
	__LIST_PRODUCE& operator,(const VarObject &r) {
		this->push_back(r);
		return *this;
	}
	__LIST_PRODUCE& operator,(const long long &r) {
		this->push_back(VarObject(r));
		return *this;
	}
	__LIST_PRODUCE& operator,(const int &r) {
		this->push_back(VarObject(r));
		return *this;
	}
	__LIST_PRODUCE& operator,(const double &r) {
		this->push_back(VarObject(r));
		return *this;
	}
	__LIST_PRODUCE& operator,(const string &r) {
		this->push_back(VarObject(r));
		return *this;
	}
	__LIST_PRODUCE& operator,(const char *r) {
		this->push_back(VarObject(r));
		return *this;
	}
	__LIST_PRODUCE& operator,(const vector<VarObject> &r) {
		this->push_back(VarObject(r));
		return *this;
	}
	friend ostream& operator<<(ostream &o, const __LIST_PRODUCE &me);
};
/* support nested macro LIST for 5 times */
#define ____LIST(...) (__LIST_PRODUCE(), ##__VA_ARGS__)
#define ___LIST(...) ____LIST(__VA_ARGS__)
#define __LIST(...) ___LIST(__VA_ARGS__)
#define _LIST(...) __LIST(__VA_ARGS__)
#define LIST(...) _LIST(__VA_ARGS__)

typedef VarObject Var;

class __None : public VarObject {
public:
	__None(void) : VarObject(TNull) {}
};
#define None (__None())

}

#endif
