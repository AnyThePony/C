#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DBG 0
#define DBG_LOG 0

// for(i=n; i>0; i--)
// for(i=n; i--; )

float f_mmove(unsigned command_id);
float f_memset(unsigned command_id);
void print_help();

int main() {
	unsigned cmd_id;
	float t;
	char s[64];

	print_help();

	while(scanf("%1s", s)) {
		switch(*s) {
			case 'm':
				if ( !(scanf("%u", &cmd_id) && cmd_id <= 4) ) {
						fflush(stdin);
						printf("Wrong command id\n\n");
						break;
				}
				if (t = f_mmove(cmd_id))
					printf("Command execution time: %.3f\n", t);
				printf("\n");
				break;

			case 's':
					if ( !(scanf("%u", &cmd_id) && cmd_id <= 2) ) {
						fflush(stdin);
						printf("Wrong command id\n");
						break;
				}
				if (t = f_memset(cmd_id))
					printf("Command execution time: %.3f\n", t);
				printf("\n");
				break;

			case 'h':
				print_help();
				break;
			case 'e':
			case 'q':
			case 'k': return 0;
			default: printf("Wrong command\n\n"); fflush(stdin); break;
		}
	}

	return 0;
}

float f_mmove(unsigned c) {
	unsigned i, j, n;
	clock_t t;
	char *str;

	printf("Enter Number of symbols (100k+ may take longer to process)\n");
	if(!scanf("%d", &n)) {
			printf("Wrong value\n");
			fflush(stdin);
			return 0;
	}

	if((str = (char*) malloc(n+1)) == NULL) {
		printf("Allocation failed\n");
		return 0;
	}

	for(i = 0; i < n; i++)
		memset(str+i, 'a'+i%26, 1);
	memset(str+n, '\0', 1);

	if (n < 64)
		printf("\"%s\"\n", str);
	else
		printf("String is too long for printing\n");

	printf("Processing...\n");

	switch(c) {
			// memmove
		case 0:
			t = clock(); /* ------- TIMER ------- */
			for(i = n; i-- ; ) {
				memmove(str, str+1, i+1);
#if DBG_LOG
				if(i < 12)
					printf("%s\n", str);
#endif
			}
			t = clock() - t;	/* ------- END TIMER ------- */
			printf("...Memmove completed\n");
			break;

			// memmove & strlen
		case 1:
			t = clock(); /* ------- TIMER ------- */
			for(i = n; i-- ; ) {
				memmove(str, str+1, strlen(str));
#if DBG_LOG
				if(i < 12)
					printf("%s\n", str);
#endif
			}
			t = clock() - t;	/* ------- END TIMER ------- */
			printf("...Memmove + strlen completed\n");
			break;

			// tmp strncpy
		case 2:
			t = clock(); /* ------- TIMER ------- */
			for(i = n; i ; ) {
				strncpy(str, str+1, i--);
#if DBG_LOG
				if(i < 12)
					printf("%s\n", str);
#endif
			}
			t = clock() - t;	/* ------- END TIMER ------- */
			printf("...Strncpy completed\n");
			break;

			// pointre v style prednasky
		case 3:
			t = clock(); /* ------- TIMER ------- */
			for(i = n; i-- ; ) {
					for(j = 0; j < i; j++)
						*(str+j) = *(str+j+1);
					*(str+i) = '\0';
#if DBG_LOG
				if(i < 12)
					printf("%s\n", str);
#endif
			}
			t = clock() - t;	/* ------- END TIMER ------- */
			printf("...Operation with pointers completed\n");
			break;

// memmove drevorubac
		case 4:
			t = clock(); /* ------- TIMER ------- */
			for(i = n; i-- ; ) {
					for(j = 0; j < i; j++)
						memmove(str+j, str+j+1, 1);
					*(str+i) = '\0';
#if DBG_LOG
				if(i < 12)
					printf("%s\n", str);
#endif
			}
			t = clock() - t;	/* ------- END TIMER ------- */
			printf("...Memmove drevorubac completed\n");
			break;

		default: return 0;
	}

#if DBG && DBG_LOG > 1
	if(strlen(str) < 64)
		printf("\"%s\"\n", str);
	else
		printf("String is too long for printing\n");
#endif

	free(str);
	return ((float)t)/CLOCKS_PER_SEC;
}

float f_memset(unsigned c) {
	unsigned i, n;
	clock_t t;
	char *str;

	printf("Enter Number of MiB you want to allocate (recommended few hundreds e.g. 500)\n");

	if(!scanf("%d", &n)) {
			printf("Wrong value\n");
			fflush(stdin);
			return 0;
	}

	if(n > 4095 || n <= 0) {
		printf("Wrong value\n");
		return 0;
	}

	n <<= 20;

	if((str = (char*) malloc(n+1)) == NULL) {
		printf("Allocation failed\n");
		return 0;
	}

	printf("Processing...\n");
	switch(c) {
		case 0:
			t = clock();	/* ------- END TIMER ------- */
				memset(str, 'a', n);
				memset(str+n, '\0', 1);
			t = clock() - t;	/* ------- TIMER ------- */
			printf("...Memset completed\n");
			break;

		case 1:
			t = clock();	/* ------- END TIMER ------- */
				for(i = 0; i < n; i++)
					*(str+i) = 'a';
				*(str+n) = '\0';
			t = clock() - t;	/* ------- TIMER ------- */
			printf("...Operation with pointers completed\n");
			break;
		default: break;

		case 2:
			t = clock();	/* ------- END TIMER ------- */
				for(i = 0; i < n; i++)
					memset(str+i, 'a', 1);
				memset(str+n, '\0', 1);
			t = clock() - t;	/* ------- TIMER ------- */
			printf("...Memset drevorubac completed\n");
			break;
	}
#if DBG
	printf("strlen: %u\n", strlen(str));
#endif
	free(str);
	return ((float)t)/CLOCKS_PER_SEC;
}

void print_help() {
	printf("available commands: \n\th - this manual\n");
	printf("\n\tm - will generate string of N symbols and delete the first one N-times\n\t   0 - memmove \n\t   1 - memmove & strlen\n\t   2 - strncpy \n\t   3 - pointers\n\t   4 - memmove drevorubac\n");
	printf("\n\ts - will generate string of N * 2^20 characters\n\t   0 - memset \n\t   1 - pointers \n\t   2 - memset drevorubac\n");
	printf("\n\te, q, k - exit\n\n");
}
