//a点绕Ob向量，逆时针旋转弧度angle, sin(angle),cos(angle)先求出来，减少精度问题。
point e1,e2,e3; point Rotate( point a, point b, double angle ){
	b.std();//单位化，注意b不能为（0，0，0）
	e3=b; double lens=a*e3;//dot(a,e3)
	e1=a -  e3*lens; if (e1.len()>(1e-8)) e1.std(); else return a;
	e2=e1/e3; //det(e1,e3)
	double x1,y1,x,y;	y1=a*e1; x1=a*e2;	
	x=x1*cos(angle) - y1*sin(angle);	y=x1*sin(angle) + y1*cos(angle);
	return e3*lens + e1*y + e2*x; }
