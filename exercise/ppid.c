#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int ppid = getppid();

	printf("%d\n", ppid);
	return (0);
}
