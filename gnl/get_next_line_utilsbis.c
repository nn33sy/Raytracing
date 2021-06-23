#include "get_next_line.h"

void	get_next_line_two(t_list *ptn, t_list *list)
{
	if (ptn->prec != NULL)
		ptn->prec->next = ptn->next;
	if (ptn->next != NULL)
		ptn->next->prec = ptn->prec;
	if (list == ptn)
	{
		if (ptn->next == 0)
			list = ptn->prec;
		else
			list = ptn->next;
	}
}
