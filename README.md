VarObject
=========

Provides a variable class with weak type.

1. Support Base Type:
--------------------
		a) long long     (TInteger)
		b) double        (TFloat)
		c) bool          (TBool)
		d) string        (TString)
		e) vector<Var>   (TList)
		f) map<Var, Var> (TDict)

2. Overview:
--------------------
### 2.1 Structure:
		namespace var {
			class VarObject
			typedef VarObject -> Var

			enum VarType {
				TInteger, TFloat, TBool, TString, TList, TDict
			}
		}

### 2.2 Overload operator:
support all valid operator overload, eg:

		TInteger: + - * / & | ^ ~ ! >> << ...
		TList: + * ! +=
		...

### 2.3 Support type transform:
		var::Var a = 3;
		int b = a;
		std::cout << b << std::endl; // 3

### 2.4 Support List helper
		var::Var a = LIST(2, "abc", true);
		std::cout << a << std::endl; // [2, abc, true]

3. More example:
--------------------
reference test.cpp for more detail.
there are some simple example:

		using namespace var;
		int main(void) {
			Var a = 2, b = "abc", c = true, d = 3.4;
			Var dict(TDict);
			dict[a] = 1; dict[b] = 2;
			dict[c] = 3; dict[d] = 4;

			Var e;
			e = a;    cout << e << endl; // 2
			e = b;    cout << e << endl; // abc
			e = c;    cout << e << endl; // true
			e = d;    cout << e << endl; // 3.4
			e = dict; cout << e << endl; // {2:1,abc:2,true:3,3.4:4}

			if(a < 3) {
				cout << "a < 3" << endl; // a < 3
			}
			if(b < "abcd") {
				cout << "b < \"abcd\"" << endl; // b < "abcd"
			}

			return 0;
		}
