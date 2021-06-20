#include <stdio.h>
#include <math.h>


long long fok(long long h) {
	long long fk = 1;
	for (int u = 1; u <= h; u++)
		fk *= u;
	return fk;
}
double funk(double y) {
	long double fu = powl(3, y);
	return fu;
}
int main() {
	double tel, ep, steps, value;
	int n, z;
	printf("enter pace: ");
	scanf("%d", &n);
	const double a = 0; const double b = 1;
	ep = 1.0; value = 0.0;
	while (1 + (ep / 2.0) > 1) ep = ep / 2.0;
	printf("accurate to %.20lf\nwitch corrective value K=0\n", ep);
	steps = (b - a) / n;
	printf("             function 3^x  value table               \n");
	printf("_____________________________________________________\n");
	printf("|  x   |       func        |        tel        |step|\n");
	printf("|______|___________________|___________________|____|\n");
	for (int j = 1; j <= n; j++) {
		tel = 1; z = 1;
		for (int i = 1; i <= 99; i++)
			if (ep >= fabs(pow(log(3), i) / fok(i)*pow(value, i))) break;
			else { tel += (pow(log(3), i) / fok(i)*pow(value, i)); z++; }
		if (z<10) printf("| %.2lf | %.15lf | %.15lf | 0%d |\n", value, funk(value), tel, z);
		else printf("| %.2lf | %.15lf | %.15lf | %d |\n", value, funk(value), tel, z);
		value += steps;
	}
	printf("|______|___________________|___________________|____|\n");
}