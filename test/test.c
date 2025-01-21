#include <stdio.h>
#include <stdlib.h>

extern char	**environ;

int	data0;
int	data1 = 10;

int	main(int argc, char *argv[])
{
	(void)argc;
	char	c;

	printf("environ: \t%p\n", environ);
	printf("argv: \t%p\n", argv);
	printf("stack: \t%p\n", &c);

	printf("bss: \t%p\n", &data0);
	printf("data: \t%p\n", &data1);


	return (EXIT_SUCCESS);
}
