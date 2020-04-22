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
#include<sstream>

using namespace std;

string words[100];
string res[100];
int n, maxLen;	   //�ִ�����������п��
int Left;		   //��ʾ���һ��ȱ�ټ���
int cnt=0;

int main(void) {
	ostringstream ss;
	ss.setf(ios::left);
	while (cin >> n >> maxLen) {
		for (int i = 0; i < n; ++i) {
			cin >> words[i];
		}
		sort(words, words + n);
		int wide = 0;
		for (int i = 0; i < n; ++i) {
			if (words[i].length() > wide) wide = words[i].length();
		}
		int columNum = maxLen / (wide + 2);
		if (maxLen % (wide + 2) >= wide) {
			columNum++;
		}
		int Line = ceil((float)n / columNum); //������
		Left = Line * columNum - n; //�����һ�п��ø���

		ss.clear();
		ss.str("");
		for (int i = 0; i < maxLen; ++i) ss << "-";
		res[cnt++] = ss.str();
		for (int i = 0; i < Line; ++i) {
			//��ӡ���
			ss.clear();
			ss.str("");
			for (int j = 0; j < columNum - Left; ++j) {
				if (i != Line - 1 && j != columNum - 1) {
					//���û�����һ��
					ss.width(wide + 2);
					ss << words[i + Line * j];
				}
				else if (i == Line - 1 && j != columNum - Left - 1) {
					ss.width(wide + 2);
					ss << words[i + Line * j];
				}
				else ss << words[i + Line * j];
			}
			if (i != Line - 1) {
				for (int j = columNum - Left; j < columNum; ++j) {
					if (j != columNum - 1) {
						//���û�����һ��
						ss.width(wide + 2);
						ss << words[i + Line * (columNum - Left) + (Line - 1) * (j - columNum + Left)];
					}
					else ss << words[i + Line * (columNum - Left) + (Line - 1) * (j - columNum + Left)];
				}
			}
			res[cnt++] = ss.str();
		}
	}
	for (int i = 0; i < cnt; ++i) {
		cout << res[i] << endl;
	}
}