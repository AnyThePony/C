// FREE WEEKEND Malloc

#include <stdio.h>
#include <stdlib.h>

void mem_alloc(char ***p, int *i);
void mem_dealloc(char ***p, int *i);
void print_help();

int main() {
	char **p, s[64];
	int arr_size = 1000;
	int i = -1;

	if ((p = (char**) malloc(arr_size*sizeof(char*))) == NULL) {
		printf("Allocation failed");
		exit(1);
	}

print_help();

	while(scanf("%1s", s)) {
		if(i+1 == arr_size) {
			printf("\n");
			mem_dealloc(&p, &i);
		}

		switch(s[0]) {
			case 'a': mem_alloc(&p, &i); break;
			case 'd':
			case 'f': mem_dealloc(&p, &i); break;
			case 'h': print_help(); break;
			case 'q':
			case 'e':
			case 'k': return 0;
			default: printf("Wrong command\n\n"); fflush(stdin); break;
		}
	}
	return 0;
}

void mem_alloc(char ***p, int *i) {
	unsigned int n = 0;

	printf("Enter number of MiB you want to allocate (1 to 4095)\n");
		if(!scanf("%d", &n))
			fflush(stdin);

		if(n > 4095 || n <= 0) {
			printf("Wrong value\n\n");
			return;
		}

	if(( *(*p+(++(*i))) = (char*) malloc(n << 10 << 10) ) == NULL) {
		printf("Allocation failed\n\n");
		(*i)--;
		return;
	}
	printf("%d MiB allocated into an array[%d] at address \t%p -> %p\n\n", n, *i, *p+*i, *(*p+*i));
}

void mem_dealloc(char ***p, int *i) {
	if(*i < 0) {
		printf("no memory allocated\n\n");
		return;
	}

	for( ; (*i) >= 0; (*i)--) {
		free(*(*p+*i));
		printf("freed arr[%d]\t%p\n", *i, (*p+*i));
	}
	putchar('\n');
}

void print_help() {
	printf("available commands: \n\th - this manual\n");
	printf("\ta - alloc memory\n");
	printf("\tf, d - free allocated memory\n");
	printf("\te, q, k - exit\n\n");
}
