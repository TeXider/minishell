#include <stdio.h>

int main(int argc, char **argv)
{
    printf("%d\n", argc - 1);
	for (size_t i = 0; argv[i + 1]; i++)
		printf("%s\n", argv[i + 1]);
	
}