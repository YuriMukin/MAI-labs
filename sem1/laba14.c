#include <stdio.h>

int main() {
	int n, t, l, k, o;
	int arr[9][9];
	printf("enter rank ");
	while (scanf("%d", &n) != EOF) {
		if (n <= 7 && n > 0) {
			l = 1; t = 0;
			for (int i = 1; i <= n; i++) {
				for (int j = 1; j <= n; j++)
					scanf("%d", &arr[i][j]);
			}
			printf("initial matrix\n");
			for (int i = 1; i <= n; i++) {
				printf("\n");
				for (int j = 1; j <= n; j++)
					printf("%3d ", arr[i][j]);
			}
			printf("\n");
			o = n * 2 - 1;
			printf("deployed matrix: ");
			for (int u = 1; u <= o; u++) {
				if (u % 2 != 0) {
					k = n - t;
					for (int i = 1; i <= k; i++)
						printf("%d ", arr[k - i + 1][i]);
					t += 1;
				}
				if (u % 2 == 0) {
					for (int j = 1; j <= n - l; j++)
						printf("%d ", arr[j + l][n - j + 1]);
					l += 1;
				}
			}
		}
		else printf("this value can't be accepted");
		printf("\nenter rank ");
	}
	printf("\n");
}