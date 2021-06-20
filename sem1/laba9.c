#include <stdio.h>
#include <math.h>

int main() {
	int i, j, l, i1, j1, l1, k, o, z, z1, min, max, min1, max1, m, m1;
	double d1, d2;
	scanf("%d %d %d", &i, &j, &l);
	z = -10;
	z1 = -20;
	o = 0;
	k = 0;
	while ((o < 50) && (k != 1)) {
		m = (z - i)*(z - i) + (z - j)*(z - j);
		m1 = (z1 - i)*(z1 - i) + (z1 - j)*(z1 - j);
		d1 = sqrt(m);
		d2 = sqrt(m1);
		if ((d1 <= 10) && (d2 <= 10))
			k = 1;
		else {
			i1 = i; j1 = j; l1 = l;
			if ((((47 * j1) % 30 + 30) % 30) < (((47 * l1) % 30 + 30) % 30))
				min = ((47 * j1) % 30 + 30) % 30;
			else
				min = ((47 * l1) % 30 + 30) % 30;
			if ((((47 * i1) % 25 + 25) % 25) < min)
				max = min;
			else
				max = ((47 * i1) % 25 + 25) % 25;
			i = max - (o % 15 + 15) % 15;
			if ((((47 * i1) % 25 + 25) % 25) > (((47 * j1) % 25 + 25) % 25))
				max1 = ((47 * i1) % 25 + 25) % 25;
			else
				max1 = ((47 * j1) % 25 + 25) % 25;
			if ((((47 * l1) % 30 + 30) % 30) > max1)
				min1 = max1;
			else
				min1 = ((47 * l1) % 30 + 30) % 30;
			j = min1 + (o % 5 + 5) % 5;
			l = ((47 * i1*l1*j1) % 25 + 25) % 25 + (o % 5 + 5) % 5;
			printf("i=%d j=%d step=%d l=%d k=%d\n", i, j, o + 1, l, o);
			o++;
		}
	}
	if (k == 1)
		printf("include i=%d j=%d step=%d l=%d k=%d\n", i, j, o + 1, l, o);
	else
		printf("not include i=%d j=%d l=%d k=%d\n", i, j, l, o);
}