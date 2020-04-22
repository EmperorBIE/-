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

int main(void) {
	queue<int, vector<int>> v[10];
	v[0].push(1);
	v[0].push(2);
	cout << v[0].front() << endl;
	v[0].pop();
	
}