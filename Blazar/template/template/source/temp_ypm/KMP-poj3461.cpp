#include <cstdio>
#include <cstring>
using namespace std;
const int N = 1e6+10;
int n1, n2, fail[N];
char s1[N], s2[N];

int main(){
	int T = 0;
	scanf("%d", &T);
	while(T--){
		scanf("%s%s",s1 + 1,s2 + 1);
		n1 = strlen(s1 + 1);
		n2 = strlen(s2 + 1);
		for(int j = 0,i = 2; i <= n1; i++){//求fail指针
			while(j && s1[j + 1] != s1[i])
				j = fail[j];
			if(s1[i] == s1[j + 1])
				j++;
			fail[i] = j;
		}
		int ans = 0;
		for(int j = 0,i = 1; i <= n2; i++){
			while(j && s2[i] != s1[j + 1])
				j = fail[j];
			if(s2[i] == s1[j + 1])
				j++;
			if(j == n1){
				ans++;
				j = fail[j];
			}
		}
		printf("%d\n", ans);
	}
}



