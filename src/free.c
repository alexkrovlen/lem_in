# include "lem_in.h"

void  ft_free_split(char **str, int j)
{
	while (--j != -1)
		free(str[j]);
	free(str);
}