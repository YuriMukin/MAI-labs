#include <stdio.h>
#include <math.h>
int main() {
	int nu, max, a, b, c, k, ep;
	printf("enter number ");
	while (scanf("%d",nu)!=EOF) {
		nu = abs(nu); max = -1;
		if (nu < 100) printf("number contains less than three digits\n");
		else {
			while (nu > 99) {
				a = nu % 10; b = (nu % 100) / 10; c = (nu % 1000) / 100; nu = nu / 10;
				k = a + b + c;
				if (k > max) { max = k; ep = c * 100 + b * 10 + a; }
			}
			printf("%d\n", ep);
		}
		printf("enter number ");
	}
	printf("\n");
}