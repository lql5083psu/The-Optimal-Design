#include<stdio.h>
#include<math.h>

double left, right;
double x, y;
int M;
double d[2], A[2][2];

void cal(double h, double x);
double fun(double x, double y);
double funx(double x, double y);
double funy(double x, double y);
double funxx(double x, double y);
double funxy(double x, double y);
double funa0(double x, double y, double a);
double gold(double left, double right, double e1);

int main()
{

	int k, N, count, end;
	double e, e1, x0, a, x1, y1, m, n, p, cx, cy;
	double B[2][2], C[2][2];

	e = 0.001;
	e1 = 0.0001;
	x = -2.5; y = 4.25;
	x0 = 0;
	N = 5;
	count = 0;

	printf("Choose the method you want to use:\n1.Gradient Descent Method\n2.Damping Newton's method\n3.Conjugate Gradient Method\n4.DFP Method\n");
	scanf_s("%d", &M);

	switch (M)
	{
	case 1:
		while (fabs(x - x0) > e)
		{
			x0 = x;
			left = right = 0;
			cal(1, 2);
			a = gold(left, right, e1);
			x1 = x - a * funx(x, y);
			y1 = y - a * funy(x, y);
			x = x1;
			y = y1;
			count++;
		}
		break;
	case 2:
		while (fabs(x - x0) > e)
		{
			x0 = x;
			left = right = 0;
			cal(1, 0);
			a = gold(left, right, e1);
			p = 1 / (4 * funxx(x, y) - funxy(x, y)*funxy(x, y));
			m = p * (4 * funx(x, y) - funxy(x, y)*funy(x, y));
			n = p * (funxx(x, y)*funy(x, y) - funxy(x, y)*funx(x, y));
			x1 = x - a * m;
			y1 = y - a * n;
			x = x1;
			y = y1;
			count++;
		}
		break;
	case 3:
		while (fabs(x - x0) > e)
		{
			k = 1;
			d[0] = funx(x, y);
			d[1] = funy(x, y);
			while ((k < N) && (fabs(x - x0) > e))
			{
				x0 = x;
				left = right = 0;
				cal(1, 2);
				a = gold(left, right, e1);
				x1 = x - a * d[0];
				y1 = y - a * d[1];
				p = (funx(x1, y1)*funx(x1, y1) + funy(x1, y1)*funy(x1, y1)) / (funx(x, y)*funx(x, y) + funy(x, y)*funy(x, y));
				d[0] = -funx(x1, y1) + p * d[0];
				d[1] = -funy(x1, y1) + p * d[1];
				x = x1;
				y = y1;
				k++;
				count++;
			}
		}
		break;
	case 4:
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
				m = A[0][0] * funx(x, y) + A[0][1] * funy(x, y);
				n = A[1][0] * funx(x, y) + A[1][1] * funy(x, y);
				x1 = x - a * m;
				y1 = y - a * n;
				cx = funx(x1, y1) - funx(x, y);
				cy = funy(x1, y1) - funy(x, y);
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
				count++;
			}
		}
		break;
	}

	printf("f(%f,%f)=%f\n", x, y, fun(x, y));
	printf("The interation number is %d\n", count);

	printf("Input an integer num:");
	scanf_s("%d", &end);

	return 0;

}


/*?????*/
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


/*?????*/
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



/*define the function*/
double fun(double x, double y)
{
	double result;
	result = x * x*x*x - 2 * x*x*y - 2 * x*y + x * x + 2 * y*y + 4.5*x - 4 * y + 4;
	return result;
}

double funx(double x, double y)
{
	return 4 * x*x*x - 4 * x*y - 2 * y + 2 * x + 4.5;
}

double funy(double x, double y)
{
	return 4 * y - 2 * x*x - 2 * x - 4;
}

double funxx(double x, double y)
{
	return 12 * x*x - 4 * y + 2 * x;
}

double funxy(double x, double y)
{
	return -4 * x - 2;
}
double funa0(double x, double y, double a)
{
	double a0, x1, y1, p, m, n;
	switch (M)
	{
	case 1:
		a0 = a;
		x1 = x - a0 * funx(x, y);
		y1 = y - a0 * funy(x, y);
		break;
	case 2:
		p = 1 / (4 * funxx(x, y) - funxy(x, y)*funxy(x, y));
		m = p * (4 * funx(x, y) - funxy(x, y)*funy(x, y));
		n = p * (funxx(x, y)*funy(x, y) - funxy(x, y)*funx(x, y));
		x1 = x - a * m;
		y1 = y - a * n;
		break;
	case 3:
		x1 = x - a * d[0];
		y1 = y - a * d[1];
		break;
	case 4:
		m = A[0][0] * funx(x, y) + A[0][1] * funy(x, y);
		n = A[1][0] * funx(x, y) + A[1][1] * funy(x, y);
		x1 = x - a * m;
		y1 = y - a * n;
		break;
	}
	return fun(x1, y1);
}
