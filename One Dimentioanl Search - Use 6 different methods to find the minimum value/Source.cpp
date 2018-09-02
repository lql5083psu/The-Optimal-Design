#include<stdio.h>
#include<math.h>

double gold(double a, double b, double e);           //Golden Section Method 
double newdon(double a, double b, double e);          //Newton's Method
double twointerp(double a, double b, double e);       //Quadratic interpolation 
double threeinterp(double a, double b, double e);      //Cubic interpolation 
double cut(double a, double b, double e);              //Line Search Method
double half(double a, double b, double e);             //Bisection Method 


double fun(double x);
double fun1(double x);
double fun2(double x);
double fun3(double x);

void main()
{
	double a, b;
	double e, val, y;
	int end, n;
	e = 0.001;
	a = 3;
	b = 5;

	printf("Choose the method you want to use:\n1.Golden Section Search\n2.Newton's Method\n3.Quadratic Interpolation Method\n4.Cubic Interpolation Method\n5.Line search Method\n6.Bisection Method\n");
	scanf_s("%d", &n);


	switch (n)
	{
	case 1:
		y = gold(a, b, e);
		break;
	case 2:
		y = newdon(a, b, e);
		break;
	case 3:
		y = twointerp(a, b, e);
		break;
	case 4:
		y = threeinterp(a, b, e);
		break;
	case 5:
		y = cut(a, b, e);
		break;
	case 6:
		y = half(a, b, e);
		break;
	}


	val = fun(y);
	printf("The answer is f(%f)=%f\n", y, val);
	printf("Input any integer num:");
	scanf_s("%d", &end);
}



/*Golden Section Search*/
double gold(double a, double b, double e)
{
	double w = 0.618;
	double a1, a2, y1, y2;

	a1 = b - w * (b - a);
	a2 = a + w * (b - a);
	y1 = fun(a1);
	y2 = fun(a2);

	while ((fabs((b - a) / b) > e) && (fabs((y2 - y1) / y2) > e))
	{
		if (y1 >= y2)
		{
			a = a1;
			a1 = a2;
			y1 = y2;
			a2 = a + w * (b - a);
			y2 = fun(a2);
		}
		else
		{
			b = a2;
			a2 = a1;
			y2 = y1;
			a1 = b - w * (b - a);
			y1 = fun(a1);
		}
	}

	a1 = 0.5*(a + b);
	return a1;
}

/*Newton's Method*/
double newdon(double a, double b, double e)
{
	double a1, y;
	a1 = b;
	y = fun1(a1);
	while (fabs(y) >= e)
	{
		a1 = a1 - fun1(a1) / fun2(a1);
		y = fun1(a1);
	}

	return a1;
}

/*Quadratic interpolation*/
double twointerp(double a, double b, double e)
{
	double a1, a2, a3, y1, y2, y3, c1, c2, p, yp;

	a1 = a;
	a2 = 2 * (a + b) / 5;
	a3 = b;
	y1 = fun(a1);
	y2 = fun(a2);
	y3 = fun(a3);
	c1 = (y3 - y1) / (a3 - a1);
	c2 = ((y2 - y1) / (a2 - a1) - c1) / (a2 - a3);
	p = 0.5*(a1 + a3 - c1 / c2);
	yp = fun(p);

	while (fun1(p) > e)
	{
		if (y2 > yp)
		{
			if (p > a2)
			{
				a1 = a2;
				y1 = y2;
				a2 = p;
				y2 = yp;
			}
			else
			{
				a3 = a2;
				y3 = y2;
				a2 = p;
				y2 = yp;
			}

		}
		else
		{
			if (p > a2)
			{
				a3 = p;
				y3 = yp;
			}
			else
			{
				a1 = p;
				y1 = yp;
			}
		}
		c1 = (y3 - y1) / (a3 - a1);
		c2 = ((y2 - y1) / (a2 - a1) - c1) / (a2 - a3);
		p = 0.5*(a1 + a3 - c1 / c2);
		yp = fun(p);
	}
	return p;

}

/*Cubic interpolation*/
double threeinterp(double a, double b, double e)
{
	double u, v, s, z, w, k;

	do
	{
		u = fun1(b);
		v = fun1(a);
		s = 3 * (fun(b) - fun(a)) / (b - a);
		z = s - u - v;
		w = sqrt(z*z - u * v);
		k = a + (b - a)*(1 - (u + w + z) / (u - v + 2 * w));

		if (fun1(k) > 0)
			b = k;
		else
			a = k;
	} while (fabs(fun1(k)) > e);

	return k;

}

/*Line Search Method*/
double cut(double a, double b, double e)
{
	double z, y2, y1, k;

	z = (a*fun(b) - b * fun(a)) / (fun(b) - fun(a));
	y2 = fun3(a);
	y1 = fun2(a);

	if ((y2*y1) > 0)
		k = b;
	else
		k = a;
	while (fabs(fun1(z)) > e)
		z = z - (k - z)*fun1(z) / (fun1(k) - fun1(z));

	return z;
}

/*Bisection method*/
double half(double a, double b, double e)
{
	double m;
	m = (a + b) / 2;

	while (fabs(fun1(m)) > e)
	{
		if (fun1(m) > 0)
			b = m;
		if (fun1(m) < 0)
			a = m;
		m = (a + b) / 2;
	}

	return m;
}



//target function 
double fun(double x)
{
	return x * x*x*x - 4 * x*x*x - 6 * x*x - 16 * x + 4;
}

//derivative of x 
double fun1(double x)
{
	return 4 * x*x*x - 12 * x*x - 12 * x - 16;
}

//2nd derivative of x
double fun2(double x)
{
	return 12 * x*x - 24 * x - 12;
}

//3rd derivative of x
double fun3(double x)
{
	return 24 * x - 24;
}
