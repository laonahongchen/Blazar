void getnex(char *s, int *nex)
{
	int n = strlen(s + 1);
	for(int j = 0, i = 2; i <= n; i++)
	{
		while(j && s[j + 1] != s[i])
			j = nex[j];
		if(s[i] == s[j + 1])
			j++;
		nex[i] = j;
	}
}
int main()
{
	const int N = 1e6 + 10; 
	static char s[N];
	static int nex[N];
	scanf("%s", s + 1);
	getnex(s, nex);
}



