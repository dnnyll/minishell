/* **************************************************************************** */
/*                                                                              */
/*                                                                              */
/*                                                                              */
/*                           DEAD INSIDE                                        */
/*                                                                              */
/*                                                                              */
/*                                       MROSSET & DANIEFE2                     */
/*                                                                              */
/*                                                                              */
/* **************************************************************************** */

#include "minishell.h"

//	function to free char ** arrays

void	free_char_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
