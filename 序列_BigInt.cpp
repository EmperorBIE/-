#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
#include<stack>
#include<set>

/******************************************************************/
/*            报错：invalid operator 不知道为什么                 */
/******************************************************************/
using namespace std;
typedef unsigned long long ll;

class BigInt {
public:
	ll part[4];			//每个part存储16位数，超过则进位
	BigInt& operator=(int n) {
		part[0] = part[1] = part[2] = 0;
		part[3] = n;
		return *this;
	}
	BigInt& operator=(const BigInt& n) {
		part[0] = n.part[0];
		part[1] = n.part[1];
		part[2] = n.part[2];
		part[3] = n.part[3];
		return *this;
	}
	BigInt operator*(int n) {
		BigInt res = *this;
		res.part[0] *= n;
		res.part[1] *= n;
		res.part[2] *= n;
		res.part[3] *= n;
		for (int i = 3; i > 0; --i) {
			if (res.part[i] / (ll)1e16 != 0) {
//				cout << "第" << i << "位超过1e16" << endl;
				res.part[i - 1] += res.part[i] / (ll)1e16;
				res.part[i] %= (ll)1e16;
//				cout << "完成向第" << i - 1 << "位的进位" << endl;
			}
		}
		return res;
	}
	friend ostream& operator<<(ostream& out, BigInt& n) {
		bool _start = false;
		for (int i = 0; i < 4; ++i) {
			if (!_start && n.part[i] != 0) {
//				cout << "从第" << i << "位开始输出" << endl;
				_start = true;
				cout << n.part[i];
			}
			else if (_start) {
				cout.fill('0');
				cout.width(16);
				cout << n.part[i];
			}
		}
		return out;
	}
	BigInt() {
		part[0] = part[1] = part[2] = 0;
	}
	BigInt(const BigInt& n) {
		for (int i = 0; i < 4; ++i) {
			part[i] = n.part[i];
		}
	}
	bool operator>(const BigInt& n) const {
		if (*this == n) return false;
		for (int i = 0; i < 4; ++i) {
			if (part[i] > n.part[i]) return true;
		}
		return false;
	}
	bool operator==(const BigInt& n) const {
		for (int i = 0; i < 4; ++i) {
			if (part[i] != n.part[i]) return false;
		}
		return true;
	}
	bool operator!=(const BigInt& n) const {
		return *this == n ? false : true;
	}
	bool operator<(const BigInt& n) const {
		if (*this == n) return false;
		for (int i = 0; i < 4; ++i) {
			if (part[i] < n.part[i]) return true;
		}
		return false;
	}
};
/*
struct cmp {
	bool operator()(const BigInt& a, const BigInt& b) const {
		if (a == b) {
			BigInt aa = a, bb = b;
			cout << aa << "和" << bb << "相等" << endl;
			return false;
		}
		return a < b;
	}
}; */

BigInt res[10005];

int main(void) {
	set<BigInt> s;
	set<BigInt>::iterator iter;
	int tot = 0;
	res[0] = res[1] = res[2] = 1;
	s.insert(res[0]);
	iter = s.begin();

	while (tot < 10001) {
		res[tot] = *iter;
		cout << "第" << tot << "次计算，当前值：" << res[tot] << endl;
		s.insert(res[tot] * 2);
		s.insert(res[tot] * 3);
		s.insert(res[tot] * 5);
		iter++;
		tot++;
	}	  

	int n;
	while (cin >> n) {
		cout << res[n - 1] << endl;
	}
}