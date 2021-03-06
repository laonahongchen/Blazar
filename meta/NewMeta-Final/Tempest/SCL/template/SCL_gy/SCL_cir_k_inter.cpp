#include<cstring>
#include<cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
double pi = acos(-1.0), eps = 1e-12;
double sqr(const double & a) {return a * a;}
double ans[1111];
int sign(const double & a) {return a > eps?1:a < -eps?-1:0;}
int n, cnt;
struct couple
{
	double x, y;
	couple(){}
	couple(const double & _x, const double & _y) : x(_x), y(_y){}
	void scan() {scanf("%lf%lf", &x, &y);}
	double sqrlen() {return sqr(x) + sqr(y);}
	double len() {return sqrt(sqrlen());}
	couple rev() {return couple(y, -x);}
	couple zoom(const double & d) {double lambda = d / len(); return couple(lambda * x, lambda * y);}
} dvd;
double atan2(const couple & x) {return atan2(x.y, x.x);}
couple operator - (const couple & a, const couple & b)
{
	return couple(a.x - b.x, a.y - b.y);
}
couple operator + (const couple & a, const couple & b)
{
	return couple(a.x + b.x, a.y + b.y);
}
double operator * (const couple & a, const couple & b)
{
	return a.x * b.y - a.y * b.x;
}
couple operator * (const double & a, const couple & b)
{
	return couple(a * b.x, a * b.y);
}
struct circle
{
	double r; couple o;
	circle(){}
	void scan() {o.scan(); scanf("%lf", &r);}
} cir[1111];
struct arc
{
	double theta;
	int delta;
	couple p;
	arc(const double & _theta, const couple & _p, int _d) :theta(_theta), p(_p), delta(_d){}
};
bool operator < (const arc & a, const arc & b) {return a.theta < b.theta;}
vector<arc> vec;
void psh(const double t1, const couple p1, const double t2, const couple p2)
{
	if(t1 < t2)
	{
		vec.push_back(arc(t1, p1, 1));
		vec.push_back(arc(t2, p2, -1));
	}else
	{
		vec.push_back(arc(t1, p1, 1));
		vec.push_back(arc(pi, dvd, -1));
		vec.push_back(arc(-pi, dvd, 1));
		vec.push_back(arc(t2, p2, -1));
	}
}
int main()
{
	freopen("cirut.in", "r", stdin);

	scanf("%d", &n);
	for(int i = 1; i <= n; i++) cir[i].scan(), ans[i] = 0;
	for(int i = 1; i <= n; i++)
	{
		vec.clear();
		dvd = cir[i].o - couple(cir[i].r, 0);
		vec.push_back(arc(-pi, dvd, 1));
		for(int j = 1; j <= n; j++) if(j != i)
		{
			double d = (cir[j].o - cir[i].o).sqrlen();
			if(d <= sqr(cir[j].r - cir[i].r))
			{
				if(cir[i].r < cir[j].r)
					psh(-pi, dvd, pi, dvd);
			}else if(d < sqr(cir[j].r + cir[i].r))
			{
				double lambda = 0.5 * (1 + (sqr(cir[i].r) - sqr(cir[j].r))/d);
				couple cp = cir[i].o + lambda * (cir[j].o - cir[i].o);
				couple frm = cp + (cir[j].o - cir[i].o).rev().zoom(sqrt(sqr(cir[i].r) - (cp - cir[i].o).sqrlen()));
				couple to = cp - (cir[j].o - cir[i].o).rev().zoom(sqrt(sqr(cir[i].r) - (cp - cir[i].o).sqrlen()));
				psh(atan2(frm - cir[i].o), frm, atan2(to - cir[i].o), to);
			}
		}
		sort(vec.begin() + 1, vec.end());
		vec.push_back(arc(pi, dvd, -1));
		cnt = 0;
		for(int j = 0; j + 1 < vec.size(); j++)
		{
			cnt += vec[j].delta;
			double theta = vec[j + 1].theta - vec[j].theta;
			ans[cnt] += sqr(cir[i].r) * (theta - sin(theta)) * 0.5;
			ans[cnt] += vec[j].p * vec[j + 1].p * 0.5;
		}
	}
	ans[n + 1] = 0;
	for(int i = 1; i <= n; i++) printf("[%d] = %.3lf\n", i, ans[i] - ans[i + 1]);
	fclose(stdin);
	return 0;
}
