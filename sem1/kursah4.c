#include <stdio.h>
#include <math.h>

double func_1(double x) {
	return (log(x) - x + 1.8);
}

double func_2(double x) {
	double r = 1, d = 3;
	double a = r / d;
	return (x*tan(x) - a);
}

double funcit_1(double x) {
	return (log(x) + 1.8);
}

double funcit_2(double x) {
	double a = 3 * tan(x);
	printf("%f", 1 / a);
	return (1 / a);
}

double funcit_1der(double x) {
	return (1 / x);
}

double funcit_2der(double x) {
	double a = 3 * cos(x)*cos(x)*tan(x)*tan(x);
	return (-1 / a);
}

double func_1der(double x) {
	return ((1 / x) - 1);
}

double func_2der(double x) {
	double a = cos(x)*cos(x);
	return (tan(x) + x / a);
}

double func_1der2(double x) {
	return (-1 / (x*x));
}

double func_2der2(double x) {
	double a = cos(x)*cos(x)*cos(x);  double b = cos(x)*cos(x);
	return ((2 * x*sin(x)) / a + 2 / b);
}


double calcDif(double a, double b, double(*D)(double)) {
	double eps = 0.0000001;
	while (fabs(b - a) > eps) {
		double mid = (a + b) / 2.0;
		if (D(mid)*D(a) > 0.0)
			a = mid;
		else if (D(mid)*D(b) > 0.0)
			b = mid;
	}
	return ((a + b) / 2.0);
}

double calcIt(double a, double b, double(*I)(double), double(*I2)(double)) {
	double eps = 0.0000001;
	double x = (a + b) / 2.0;
	if (fabs(I2(x)) < 1) {
		while (fabs(I(x) - x) > eps)
			x = I(x);
		return (I(x));
	}
	else return (0);
}

double calcNu(double a, double b, double(*N)(double), double(*N2)(double), double(*N3)(double)) {
	double eps = 0.0000001;
	double x = (a + b) / 2.0;
	while (fabs((x - N(x) / N2(x)) - x) > eps)
		x = x - N(x) / N2(x);
	return (x - N(x) / N2(x));
}

int main() {
	double diff, it, nu, A = 2.0, B = 3, C = 0.2, D = 1.0;
	printf("  if program return 0, then method doesn't work\n____________________________________________________\n|    function     | dihtomy | iterations |  Newton |\n|_________________|_________|____________|_________|\n");
	printf("|log(x) - x + 1.8 | %8lf| %11lf| %7lf|\n|_________________|_________|____________|_________|\n", calcDif(A, B, func_1), calcIt(A, B, funcit_1, funcit_1der), calcNu(A, B, func_1, func_1der, func_1der2));
	printf("|x*tan(x) - 1/3   | %8lf| %11lf| %7lf|\n|_________________|_________|____________|_________|\n", calcDif(C, D, func_2), calcIt(C, D, funcit_2, funcit_2der), calcNu(C, D, func_2, func_2der, func_2der2));
}