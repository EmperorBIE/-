#include<iostream>
#include<stdio.h>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<vector>
#include<queue>
#include<string>
#include<stack>
#define MAXN 10005

using namespace std;

void (*fun[6])(int, int);
class BASE;
class BLOCK;
class ORDER {
public:
	int kind, a, b;
	friend istream& operator>>(istream& in, ORDER& order) {
		string str;
		in >> str;
		if (str == "q") {
			order.kind = 0;
		}
		else if (str == "mv") {
			cin >> order.a >> str >> order.b;
			if (str == "on") {
				order.kind = 1;
			}
			else order.kind = 2;
		}
		else if (str == "st") {
			cin >> order.a >> str >> order.b;
			if (str == "on") {
				order.kind = 3;
			}
			else order.kind = 4;
		}
		else {
			cin >> order.a >> str >> order.b;
			order.kind = 5;
		}
		return in;
	}
};

class BLOCK {
public:
	int num;  //这个积木的编号
	int now;  //现在位于第几列
	BLOCK& operator=(BLOCK& block) {
		num = block.num;
		now = block.now;
		return *this;
	}
};

stack<BLOCK, vector<BLOCK> > s[25];
BLOCK block[25];	//用于作为外部数据记录
ORDER order[10005];

void fun1(int a, int b) {
	//恢复a、b之上的所有木块，把a放到b上
//	cout << "move " << a << " on " << b << endl;
	BLOCK tmp[25];
	int cnt = 0;
	while ((!s[block[a].now].empty()) && s[block[a].now].top().num != a) {
		//把第a块积木上面的积木取下来
		tmp[cnt] = s[block[a].now].top();
		block[tmp[cnt].num].now = block[tmp[cnt].num].num; //修改记录信息
		s[block[a].now].pop();
		cnt++;
	}
	for (int i = 0; i < cnt; ++i) {
		//把刚才取出来的积木归位
		tmp[i].now = tmp[i].num;
		s[tmp[i].now].push(tmp[i]);
	}
	cnt = 0;
	while ((!s[block[b].now].empty()) && s[block[b].now].top().num != b) {
		//把第b块积木上面的积木取下来
		tmp[cnt] = s[block[b].now].top();
		block[tmp[cnt].num].now = block[tmp[cnt].num].num; //修改记录信息
		s[block[b].now].pop();
		cnt++;
	}
	for (int i = 0; i < cnt; ++i) {
		//把刚才取出来的积木归位
		tmp[i].now = tmp[i].num;
		s[tmp[i].now].push(tmp[i]);
	}
	s[block[a].now].pop(); //把a木块取出
	block[a].now = block[b].now;   //更新位置
	s[block[b].now].push(block[a]);	 //把a木块放到b木块上面
}
void fun2(int a, int b) {
//	cout << "move " << a << " over " << b << endl;
	BLOCK tmp[25];
	int cnt = 0;
	while ((!s[block[a].now].empty())&&s[block[a].now].top().num != a) {
		//把第a块积木上面的积木取下来
		tmp[cnt] = s[block[a].now].top();
		block[tmp[cnt].num].now = block[tmp[cnt].num].num; //修改记录信息
		s[block[a].now].pop();
		cnt++;
	}
	for (int i = 0; i < cnt; ++i) {
		//把刚才取出来的积木归位
		tmp[i].now = tmp[i].num;
		s[tmp[i].now].push(tmp[i]);
	}
	s[block[a].now].pop(); //把a木块取出
	block[a].now = block[b].now;  //更新位置
	s[block[b].now].push(block[a]);	 //把a木块放到b木块上面
}
void fun3(int a, int b) {
//	cout << "set " << a << " on " << b << endl;
	BLOCK tmp[25], tmpb[25];
	int cnta = 0, cntb = 0;
	while ((!s[block[a].now].empty()) && s[block[a].now].top().num != a) {
		//把第a块积木上面的积木取下来
		tmp[cnta] = s[block[a].now].top();
		tmp[cnta].now = block[b].now;
		block[tmp[cnta].num].now = block[b].now; //修改记录信息
		s[block[a].now].pop();
		cnta++;
	}
	tmp[cnta] = s[block[a].now].top();
	tmp[cnta].now = block[b].now;
	s[block[a].now].pop();	   //把第a块也取下来
	block[a].now = block[b].now;
	cnta++;

	while ((!s[block[b].now].empty()) && s[block[b].now].top().num != b) {
		//把第b块积木上面的积木取下来
		tmpb[cntb] = s[block[b].now].top();
		block[tmpb[cntb].num].now = block[tmpb[cntb].num].num; //修改记录信息
		s[block[b].now].pop();
		cntb++;
	}
	for (int i = 0; i < cntb; ++i) {
		//把刚才取出来的积木归位
		tmpb[i].now = tmpb[i].num;
		s[tmpb[i].now].push(tmpb[i]);
	}
	for (int i = cnta - 1; i >= 0; --i) {
		//把刚才取出来的所有木块放在b上面
		s[block[b].now].push(tmp[i]);
	}
}
void fun4(int a, int b) {
//	cout << "set " << a << " over " << b << endl;
	BLOCK tmp[25];
	int cnta = 0;
	while ((!s[block[a].now].empty()) && s[block[a].now].top().num != a) {
		//把第a块积木上面的积木取下来
		tmp[cnta] = s[block[a].now].top();
		tmp[cnta].now = block[b].now;
		block[tmp[cnta].num].now = block[b].now; //修改记录信息
		s[block[a].now].pop();
		cnta++;
	}
	tmp[cnta] = s[block[a].now].top();
	tmp[cnta].now = block[b].now;
	s[block[a].now].pop();	   //把第a块也取下来	
	block[a].now = block[b].now;
	cnta++;

//	cout << "第" << b << "块木块现在所在的位置：" << s[block[b].now].top().now << endl;

	for (int i = cnta - 1; i >= 0; --i) {
		//把刚才取出来的所有木块放在b上面
		s[block[b].now].push(tmp[i]);
	}
}
void fun5(int a, int b) {
//	cout << "exchange " << a << " and " << b << endl;
//	swap(s[block[a].now], s[block[b].now]);
	int s1 = block[a].now, s2 = block[b].now;
	int cnta = 0, cntb = 0;
	BLOCK tmp_s1[25];
	BLOCK tmp_s2[25];
	while (!s[s1].empty()) {
		tmp_s1[cnta] = s[s1].top();
		tmp_s1[cnta].now = s2;
		block[tmp_s1[cnta].num].now = s2;
		s[s1].pop();
		cnta++;
	}
	while (!s[s2].empty()) {
		tmp_s2[cntb] = s[s2].top();
		tmp_s2[cntb].now = s1;
		block[tmp_s2[cntb].num].now = s1;
		s[s2].pop();
		cntb++;
	}
	for (int i = cnta - 1; i >= 0; --i) {
		s[s2].push(block[tmp_s1[i].num]);
	}
	for (int i = cntb - 1; i >= 0; --i) {
		s[s1].push(block[tmp_s2[i].num]);
	}
}

void init(int n) {
	for (int i = 0; i < n; ++i) {
		block[i].num = block[i].now = i;
		s[i].push(block[i]);
	}
	fun[1] = fun1;
	fun[2] = fun2;
	fun[3] = fun3;
	fun[4] = fun4;
	fun[5] = fun5;
}

void print(int n) {
	BLOCK tmp[25];
	for (int i = 0; i < n; ++i) {
		int cnt = 0;
		while (s[i].size() != 0) {
			tmp[cnt++] = s[i].top();
			s[i].pop();
		}
		cout << i << ":";
		for (int j = cnt - 1; j >= 0; --j) {
			cout << " " << tmp[j].num;
		}
		cout << endl;
	}
}

int main(void) {
	int n;
	cin >> n;
	init(n);
	int cnt = 0;
	while (cin >> order[cnt]) {
//		cout << "order[" << cnt << "]: kind=" << order[cnt].kind << endl;
		if (order[cnt].kind == 0) break;
		cnt++;
	}
//	cout << "输入完成" << endl;
//	print(n);
//	cout << endl;
	for (int i = 0; i < cnt; ++i) {
		if (order[i].a == order[i].b) continue;
		if (block[order[i].a].now == block[order[i].b].now) continue;
		fun[order[i].kind](order[i].a, order[i].b);
//		print(n);
	}
	print(n);
}