#include<stdio.h>
#include<math.h>

double left, right;
double x1, x2;

void cal1(int h, double x1, double(*funp)());
void cal2(int h, double x2, double(*funp)());
double fun(double x1, double x2);
double funx1(double x1, double x2);
double funx2(double x1, double x2);
double half1(double left, double right, double e1);
double half2(double left, double right, double e1);


void main()
{
	double e, e1, x;
	double(*funp)();
	int end;
	funp = fun;
	e = 0.01;
	e1 = 0.0001;
	x1 = 1; x2 = 1;
	x = 0;
	while (fabs(x - x2)>e)
	{
		x = x1;
		left = right = 0;
		cal1(1, x1, funp);
		x1 = half1(left, right, e1);
		if (fabs(x - x1)<e)
			break;
		else
		{
			x = x2;
			left = right = 0;
			cal2(1, x2, funp);
			x2 = half2(left, right, e1);
		}

	}
	printf("f(%f,%f)=%f\n", x1, x2, fun(x1, x2));

	printf("Input the end num:");
	scanf("%d", &end);
}




/*find the search range*/
void cal1(int h, double x1, double(*funp)())
{
	double a1, a2, a3, y1, y2, y3;
	a1 = x1;
	y1 = (*funp)(a1, x2);
	a2 = a1 + h;
	y2 = (*funp)(a2, x2);

	if ((funx1(a1, x2)*funx1(a2, x2))>0)
	{
		if ((y1<y2))
		{
			h = h * (-1);
			a2 = a1 + (double)h;
			y2 = (*funp)(a2, x2);
		}
		a3 = a2 + (double)h;
		y3 = (*funp)(a3, x2);

		while ((y1>y2) && (y2>y3))
		{
			h = h * 2;
			a1 = a2;
			a2 = a3;
			a3 = a2 + (double)h;
			y1 = y2;
			y2 = y3;
			y3 = (*funp)(a3, x2);

		}

		if (a1>a3)
		{
			a2 = a1;
			a1 = a3;
			a3 = a2;
		}
	}
	else
		a3 = a2;
	left = a1;
	right = a3;

}


void cal2(int h, double x2, double(*funp)())
{
	double a1, a2, a3, y1, y2, y3;
	a1 = x2;
	y1 = (*funp)(x1, a1);
	a2 = a1 + h;
	y2 = (*funp)(x1, a2);

	if ((funx2(x1, a1)*funx2(x1, a2))>0)
	{
		if (y1<y2)
		{
			h = h * (-1);
			a2 = a1 + (double)h;
			y2 = (*funp)(x1, a2);
		}
		a3 = a2 + (double)h;
		y3 = (*funp)(x1, a3);

		while ((y1>y2) && (y2>y3))
		{
			h = h * 2;
			a1 = a2;
			a2 = a3;
			a3 = a2 + (double)h;
			y1 = y2;
			y2 = y3;
			y3 = (*funp)(x1, a3);
		}

		if (a1>a3)
		{
			a2 = a1;
			a1 = a3;
			a3 = a2;
		}
	}
	else
		a3 = a2;
	left = a1;
	right = a3;
}
/*find the minmum value using binary search*/
double half1(double left, double right, double e1)
{
	double m, a, b;
	a = left;
	b = right;
	m = (a + b) / 2;
	x1 = m;
	while (fabs(funx1(x1, x2))>e1)
	{
		if (funx1(x1, x2)>0)
			b = m;
		if (funx1(x1, x2)<0)
			a = m;
		m = (a + b) / 2;
		x1 = m;
	}
	return m;
}

double half2(double left, double right, double e1)
{
	double m, a, b;
	a = left;
	b = right;
	m = (a + b) / 2;
	x2 = m;
	while (fabs(funx2(x1, x2))>e1)
	{
		if (funx2(x1, x2)>0)
			b = m;
		if (funx2(x1, x2)<0)
			a = m;
		m = (a + b) / 2;
		x2 = m;
	}
	return m;
}

//target function
double fun(double x1, double x2)
{
	double result;
	result = x1 * x1 + 2 * x2*x2 - 2 * x1*x2 - 4 * x1;
	return result;
}

//take derivatives of x1
double funx1(double x1, double x2)
{
	return 2 * x1 - 2 * x2 - 4;
}

//take derivatives of x2
double funx2(double x1, double x2)
{
	return 4 * x2 - 2 * x1;
}
