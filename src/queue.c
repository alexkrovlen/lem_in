# include "lem_in.h"

int		empty_queue(t_queue *q)
{
	return (q == NULL);
}

t_queue	*pop_queue(t_queue *q)
{
	t_queue *tmp;

	if (q == NULL)
		return NULL;
	/*tmp = q;
	tmp = tmp->next;
	//free(q);
	q = tmp;*/
	tmp = q->next;
	return (tmp);
}

t_queue *new_queue(int n)
{
	t_queue *new;

	if (!(new = (t_queue *)malloc(sizeof(t_queue))))
		return (NULL);
	new->num = n;
	new->next = NULL;//printf("num = %d\n", new->num);
	return (new);
}

t_queue *push_queue(t_queue *queue, int n)
{
	t_queue *tmp;

	if (queue == NULL)
	{
		queue = new_queue(n);//printf("num2 = %d\n", queue->num);
		return (queue);
	}
	else
	{
		tmp = queue;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_queue(n);
		return (tmp);
	}
}