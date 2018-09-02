#include<stdio.h>
#include<math.h>

double left, right;
double x, y, r;
double A[2][2];

void dfs();                                           //variable metric method for unconstrained optimization
void cal(double h, double x);                          //search range 
double fun(double x, double y);                         //target function
double penalty(double x, double y, double r);            //penalty function
double funx(double x, double y, double r);                //derivative of x
double funy(double x, double y, double r);                //derivative of y
double funa0(double x, double y, double a);               //iterative function
double gold(double left, double right, double e1);         //golden section method 

int main()
{
	int end;
	double xx, yy;
	x = 10; y = 9;                                         //intialize x, y 
	r = 1;                                                //initial value of penalty is 1 
	xx = x;
	yy = y;
	dfs();


	while (sqrt((xx - x)*(xx - x) + (yy - y)*(yy - y)) > 0.001)       //如果结果靠近目标值则停止计算 
	{
		xx = x;
		yy = y;
		dfs();
	}

	printf("f(%f,%f)=%f\n", x, y, fun(x, y));

	printf("Input any integer num:");
	scanf_s("%d", &end);

	return 0;

}

//variable metric method for unconstrained optimization
void dfs()
{

	int k, N;
	double e, e1, x0, a, x1, y1, m, n, p, cx, cy;
	double B[2][2], C[2][2];

	e = 0.001;
	e1 = 0.0001;

	x0 = 0;
	N = 10;


	while (fabs(x - x0) > e)
	{
		A[0][0] = 1;
		A[0][1] = 0;
		A[1][0] = 0;
		A[1][1] = 1;
		k = 1;
		while ((k <= N) && (fabs(x - x0) > e))
		{
			x0 = x;
			left = right = 0;
			cal(1, 2);
			a = gold(left, right, e1);
			m = A[0][0] * funx(x, y, r) + A[0][1] * funy(x, y, r);
			n = A[1][0] * funx(x, y, r) + A[1][1] * funy(x, y, r);
			x1 = x - a * m;
			y1 = y - a * n;
			cx = funx(x1, y1, r) - funx(x, y, r);
			cy = funy(x1, y1, r) - funy(x, y, r);
			x = x1;
			y = y1;

			p = x * cx + y * cy;
			B[0][0] = x * x / p;
			B[0][1] = x * y / p;
			B[1][0] = y * x / p;
			B[1][1] = y * y / p;

			p = (cx*A[0][0] + cy * A[1][0])*cx + (cx*A[0][1] + cy * A[1][1])*cy;
			C[0][0] = ((A[0][0] * x*x + A[0][1] * y*x)*A[0][0] + (A[0][0] * x*y + A[0][1] * y*y)*A[1][0]) / p;
			C[0][1] = ((A[0][0] * x*x + A[0][1] * y*x)*A[0][1] + (A[0][0] * x*y + A[0][1] * y*y)*A[1][1]) / p;
			C[1][0] = ((A[1][0] * x*x + A[1][1] * y*x)*A[0][0] + (A[1][0] * x*y + A[1][1] * y*y)*A[1][0]) / p;
			C[1][1] = ((A[1][0] * x*x + A[1][1] * y*x)*A[0][1] + (A[1][0] * x*y + A[1][1] * y*y)*A[1][1]) / p;

			A[0][0] = A[0][0] + B[0][0] - C[0][0];
			A[0][1] = A[0][1] + B[0][1] - C[0][1];
			A[1][0] = A[1][0] + B[1][0] - C[1][0];
			A[1][1] = A[1][1] + B[1][1] - C[1][1];
			k++;
		}
		r = r * 2;
	}
}

//find the search range
void cal(double h, double a)
{
	double a1, a2, a3, y1, y2, y3;
	a1 = a;
	y1 = funa0(x, y, a1);
	a2 = a1 + h;
	y2 = funa0(x, y, a2);

	if (y1 < y2)
	{
		h = h * (-1);
		a2 = a1 + h;
		y2 = funa0(x, y, a2);
	}
	a3 = a2 + h;
	y3 = funa0(x, y, a3);

	while ((y1 > y2) && (y2 > y3))
	{
		h = h + h;
		a1 = a2;
		a2 = a3;
		a3 = a2 + h;
		y1 = y2;
		y2 = y3;
		y3 = funa0(x, y, a3);

	}

	if (a1 > a3)
	{
		a2 = a1;
		a1 = a3;
		a3 = a2;
	}

	left = a1;
	right = a3;
}


//golden section method 
double gold(double left, double right, double e1)
{
	double w = 0.618;
	double a1, a2, y1, y2, a, b;

	a = left;
	b = right;
	a1 = b - w * (b - a);
	a2 = a + w * (b - a);
	y1 = funa0(x, y, a1);
	y2 = funa0(x, y, a2);

	while ((fabs((b - a) / b) > e1) && (fabs((y2 - y1) / y1) > e1))
	{
		if (y1 >= y2)
		{
			a = a1;
			a1 = a2;
			y1 = y2;
			a2 = a + w * (b - a);
			y2 = funa0(x, y, a2);
		}
		else
		{
			b = a2;
			a2 = a1;
			y2 = y1;
			a1 = b - w * (b - a);
			y1 = funa0(x, y, a1);
		}
	}

	a1 = 0.5*(a + b);
	return a1;
}



//penalty function
double penalty(double x, double y, double r)
{
	double result;
	result = fun(x, y);
	if ((1 - x) > 0.01)
		result = result + r * (x - 1)*(x - 1);                  //x>=1,y>=x+6
	if ((x + 6 - y) > 0.01)
		result = result + r * (y - x - 6)*(y - x - 6);
	return result;
}

//target function 
double fun(double x, double y)
{
	double result;
	result = x * x + y * y;
	return result;
}

//derivative of x
double funx(double x, double y, double r)
{
	double result;
	result = 2 * x;
	if ((1 - x) > 0.01)
		result = result + 2 * r*(x - 1);
	if ((x + 6 - y) > 0.01)
		result = result - 2 * r*(y - x - 6);

	return result;
}

//derivative of y
double funy(double x, double y, double r)
{
	double result;
	result = 2 * y;
	if ((x + 6 - y) > 0.01)
		result = result + 2 * r*(y - x - 6);

	return result;
}

//iterative function 
double funa0(double x, double y, double a)
{
	double x1, y1, m, n;
	m = A[0][0] * funx(x, y, r) + A[0][1] * funy(x, y, r);
	n = A[1][0] * funx(x, y, r) + A[1][1] * funy(x, y, r);
	x1 = x - a * m;
	y1 = y - a * n;
	return penalty(x1, y1, r);
}
