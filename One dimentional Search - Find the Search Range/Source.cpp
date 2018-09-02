#include<stdio.h>
void cal(int h, int a);
int fun(int x);
int main()
{
	int h0, a, end;
	printf("Input a and h:\n");
	scanf_s("%d %d", &a, &h0);

	cal(h0, a);

	printf("Input any integer num:");
	scanf_s("%d", &end);
	return(0);
}

void cal(int h, int a)
{
	int a1, a2, a3, y1, y2, y3;
	a1 = a;
	y1 = fun(a1);
	a2 = a1 + h;
	y2 = fun(a2);
	if (y1 < y2)
	{
		h = h * (-1);
		a2 = a1 + h;
		y2 = fun(a2);
	}
	a3 = a2 + h;
	y3 = fun(a3);

	while ((y1 > y2) && (y2 > y3))
	{
		h = h * 2;
		a1 = a2;
		a2 = a3;
		a3 = a2 + h;
		y1 = y2;
		y2 = y3;
		y3 = fun(a3);
	}

	if (a1 > a3)
	{
		a2 = a1;
		a1 = a3;
		a3 = a2;
	}
	printf("The space is between %d and %d\n", a1, a3);
}

int fun(int x)
{
	return x * x - 10 * x + 20;
}