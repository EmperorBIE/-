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

using namespace std;
typedef unsigned long long ll;

ll res[10005];

int main(void) {
	set<ll> s;
	set<ll>::iterator iter;
	int tot = 0;
	res[0] = 1;
	s.insert(res[0]);
	iter = s.begin();
	while (tot < 10001) {
		res[tot] = *iter;
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