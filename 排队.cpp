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
#include<map>

using namespace std;

int g, n, k, Case, cnt;	 //cnt记录共有多少组团伙
string str;
vector<queue<string>> Q;
map<string, int> people; //people[str]表示名字为str的人所属的队伍编号
string out[1000][1000];  //out[i][j]表示第i组输出的第j个输出队列
int team[10005]; 	     //team[i]表示第编号为i的组在队列Q中的位置
int now;                 //用于Q[now]表示现在考察第now个队列
int Time;			     //用于out[Time]表示现在考察第Time行的输出
int Num[1000];           //Num[i]用于记录第i组输出out[i]共有多少行 

void enqueue(string& name) {
	if (people.find(name) != people.end()) {
		//如果这个人是孤儿
//		cout << name << "是孤儿，他在第" << cnt << "组" << endl;
		people[name] = cnt++;
		team[people[name]] = Q.size();
		Q.push_back(queue<string>());
		Q[team[people[name]]].push(name);
	}
	if (team[people[name]] != -1) {
		//如果之前有跟他同组的人进队了
		Q[team[people[name]]].push(name);
	}
	else {
		team[people[name]] = Q.size();
		Q.push_back(queue<string>());
		Q[team[people[name]]].push(name);
	}
}

void print() {
	cout << endl;
	if (Q.size() <= now) {
		cout << "队中无人" << endl;
	}
	for (int i = now; i < Q.size(); ++i) {	
		queue<string> tmp;
		while (!Q[i].empty()) {
			cout << Q[i].front() << " ";
			tmp.push(Q[i].front());
			Q[i].pop();
		}
		Q[i] = tmp;
		cout << endl;
	}
	cout << endl;
}

void dequeue() {
	if (Q.size() <= now) return;
	while (Q[now].empty()) {
		now++;
		if (Q.size() == now) return;
	}
	out[Case][Time] = Q[now].front();
	Q[now].pop();
	if (Q[now].empty()) { 
		team[people[out[Case][Time]]] = -1;
		now++;
	}
	Time++;
}

void deqteam(string& name) {
	if (people.find(name) != people.end() || team[people[name]] == -1) return;
	while (!Q[team[people[name]]].empty()) {
		if (out[Case][Time] == "") {
			out[Case][Time] = Q[team[people[name]]].front();
			Q[team[people[name]]].pop();
		}
		else {
			out[Case][Time] += " ";
			out[Case][Time] += Q[team[people[name]]].front();
			Q[team[people[name]]].pop();
		}
	}
	team[people[name]] = -1;
	Time++;
}

void init() {
	memset(team, -1, sizeof(int));
	Q.clear();
	people.clear();
	Time = 0;
	now = 0;
	cnt = 0;
}

int main(void) {
	while (1) {
		cin >> g;
		if (g == 0) break;
		init();
		for (int i = 0; i < g; ++i) {
			cin >> k;
			for (int j = 0; j < k; ++j) {
				cin >> str;
				people[str] = cnt;
			}
			cnt++;
		}
		while (cin >> str) {
			if (str == "enqueue") {
				cin >> str;
				enqueue(str);
			}
			else if (str == "deqteam") {
				cin >> str;
				deqteam(str);
			}
			else if (str == "dequeue") {
				dequeue();
			}
			else break;
			print();
		}
		Num[Case++] = Time;
	}
	for (int i = 0; i < Case; ++i) {
		cout << "Case #" << i + 1 << ":" << endl;
		for (int j = 0; j < Num[j]; ++j) {
			cout << out[i][j] << endl;
		}
	}
}