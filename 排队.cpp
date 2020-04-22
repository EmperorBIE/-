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

int g, n, k, Case, cnt;	 //cnt��¼���ж������Ż�
string str;
vector<queue<string>> Q;
map<string, int> people; //people[str]��ʾ����Ϊstr���������Ķ�����
string out[1000][1000];  //out[i][j]��ʾ��i������ĵ�j���������
int team[10005]; 	     //team[i]��ʾ�ڱ��Ϊi�����ڶ���Q�е�λ��
int now;                 //����Q[now]��ʾ���ڿ����now������
int Time;			     //����out[Time]��ʾ���ڿ����Time�е����
int Num[1000];           //Num[i]���ڼ�¼��i�����out[i]���ж����� 

void enqueue(string& name) {
	if (people.find(name) != people.end()) {
		//���������ǹ¶�
//		cout << name << "�ǹ¶������ڵ�" << cnt << "��" << endl;
		people[name] = cnt++;
		team[people[name]] = Q.size();
		Q.push_back(queue<string>());
		Q[team[people[name]]].push(name);
	}
	if (team[people[name]] != -1) {
		//���֮ǰ�и���ͬ����˽�����
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
		cout << "��������" << endl;
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