#include <bits/stdc++.h>
using namespace std;
const int N = 2e6+10;
int n, p[N];
char s[N], st[N];

int manacher(char *s, int n){
	int pos, mx = 0, res = 0;
	for(int i = 1; i <= n; i++){
		if(mx > i)
			p[i] = min(p[pos * 2 - i], mx - i);
		else
			p[i] = 1;
		while(s[i + p[i]] == s[i - p[i]])
			p[i]++;
		if(p[i] + i - 1 > mx){
			mx = p[i] + i - 1;
			pos = i;
		}
		res = max(p[i], res);
	}
	return res - 1;
}

int main(){
	int tim = 0;
	while(1){
		scanf("%s", s + 1);
		if(s[1] == 'E')
			break;
		int n = strlen(s + 1);
		st[1] = '$';//开头另外加一个字符，防止无限延长
		st[2] = '#';
		for(int i = 1; i <= n; i++){
			int t = (i + 1) << 1;
			st[t - 1] = s[i];
			st[t] = '#';
		}
		tim++;
		printf("Case %d: %d\n", tim, manacher(st, (n + 1) << 1));
	}
}

