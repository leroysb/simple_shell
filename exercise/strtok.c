#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *input = NULL, **str;
	size_t *ptr, i = 0, size = sizeof(char);

	ptr = &size;
	printf("-> ");
	getline(&input, ptr, stdin);

	str = malloc(sizeof(input));
	while (str[i - 1] || i < 1)
	{
		if (i < 1)
		{
			str[i] = strtok(input, " ");
		}
		else
		{
			str[i] = strtok(NULL, " ");
		}
		i++;
	}
	i = 0;
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1] != NULL)
			printf(" ");
		i++;
	}
	//printf("\n");
	free(str);
	free(input);

	return (0);
}
