# include "lem_in.h"

int main(void)
{
	t_anthill	*anthill;

	anthill = init_anthill();
	parse(anthill);
	printf("ants = %d\n", anthill->num_ants);
	printf("start\n");
	return (0);
}