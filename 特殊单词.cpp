#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>

using namespace std;

class WORD;
vector<WORD> v;
vector<string> res;

class WORD {
public:
	string str;
	string _str;
	bool checked;
	WORD(const string& s) :str(s),_str(s),checked(0) {
		for (int i = 0; i < _str.length(); ++i) {
			if (_str[i] >= 'a' && _str[i] <= 'z') {
				_str[i] += 'A' - 'a';
			}
		}
		sort(_str.begin(), _str.end());
	}
	bool operator==(WORD& w) {
		return _str == w._str && str != w.str;
	}
};

int main(void) {
	string str;
	while (cin >> str) {
		if (str == "#") break;
		WORD w(str);
		v.push_back(w);
	}
	for (int i = 0; i < v.size(); ++i) {
		if (!v[i].checked) {
			bool found = false;
			for (int j = i + 1; j < v.size(); ++j) {
				if (v[i] == v[j] && !v[j].checked) {
					v[j].checked = true;
					found = true;
				}
			}
			if (found) res.push_back(v[i].str);
			v[i].checked = true;
		}
	}
	sort(res.begin(), res.end());
	for (int i = 0; i < res.size(); ++i) {
		cout << res[i] << endl;
	}
}