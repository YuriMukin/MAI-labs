#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num, nm, nu, sost, k, ck, p;
	char s, ps;
	num = 0; nu = 0; nm = 0; sost = 0; k = 0; ps = '\n'; ck = 1; p = 0;
	while (sost != 9) {
		s = getchar();
		switch (sost) {
		case 0: if ((s<'0' || s>'9') && s != '-' && s != EOF && p != 1) { printf("%c", s); ps = s; }
				else if (s == '-' && (ps == ' ' || ps == ',' || ps == '\t' || ps == '\n')) { p = 1; ps = s; }
				else if (ps == '-'&&s >= '0'&&s <= '9'&&s != EOF && p == 1) { p = 0; sost = 1; ck = -1; num = (int)(s - '0'); }
				else if (p != 0 && s != EOF && (s<'0' || s>'9')) { printf("-%c", s); ps = s; p = 0;}
				else if (p != 0 && s == EOF && (s<'0' || s>'9')) { printf("-%c", s); ps = s; p = 0; sost = 9; }
				else if ((ps == ' ' || ps == ',' || ps == '\t' || ps == '\n') && s != EOF) { sost = 1; ps = s; num = (int)(ps - '0'); }
				else if (s == EOF) sost = 9;
				else { printf("%c", s); ps = s; }
				break;
		case 1: if (s >= '0'&&s <= '9'&&s != EOF) { nm = (int)(s - '0'); num = num * 10 + nm;  }
				else
			if (s == EOF) { sost = 9; printf("%d%c", num*ck, s); num = 0; ck = 1; }
			else
				if (s == 'C') { sost = 2; ps = s; num = num * ck; ck = 1; }
				else { sost = 0; printf("%d%c", num*ck, s); num = 0; ps = s; ck = 1; }
				break;
		case 2: if ((s == ' ' || s == ',' || s == '\t' || s == '\n') && s != EOF) { num = num * 1.8 + 32; printf("%dF%c", num, s); sost = 0; num = 0; ps = s; }
				else
			if (s == EOF) { sost = 9; num = num * 1.8 + 32; printf("%dF%c", num, s); num = 0; ps = s; }
			else { printf("%d%c%c", num, ps, s); sost = 0; num = 0; ps = s; }
				break;
		}
	}
}