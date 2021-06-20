#include <stdio.h>

int main()
{
	int min, x_min, y_min, max, x_max, y_max, n, r;
	int arr[10][10];
	printf("enter ranc: ");
	while (scanf("%d",n)!=EOF){
		if (n>0&&n<=8){
			r = 0;
			min = 234567545; max = -234567545;
			printf("enter matrix\n");
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					scanf("%d",&arr[i][j]);
			printf("your matrix:");
			for (int i = 1; i <= n; i++) {
				printf("\n");
				for (int j = 1; j <= n; j++)
					printf("%3d ", arr[i][j]);
			}
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					if (arr[i][j] > max) { max = arr[i][j]; x_max = i; y_max = j; }
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					if (arr[i][j] < min) { min = arr[i][j]; x_min = i; y_min = j; }
			printf("\nnew matrix:");
			for (int i = 1; i <= n; i++)
				r += (arr[i][y_max] * arr[x_min][i]);
					printf("%3d ", r);
		}
		else printf("this value can't be accepted");
		printf("\nenter ranc: ");
	}
	printf("\n");
}