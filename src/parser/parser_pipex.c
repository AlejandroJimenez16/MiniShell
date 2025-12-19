<<<<<<< HEAD
/* TODO Meter header */
=======
>>>>>>> 3bf29d05174427f82771b4a8be92328049949f9c
#include "../../includes/mini.h"

int	count_items(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i])
		i++;
	return (i);
}

/*Uses mode to detect either if is here_doc or not*/
/*
** TODO
** 	- Siempre comprueba si falló el malloc después de hacerlo
**	  y limpiar todo si falla
**	- He metido cosas en los return pero divide la fución tú,
**	  si necesitas ayuda con esto dime porque sabes que yo haría
**	  un parse_line2(char ***out) xd
**	- Como buena práctica deberíamos empezar a poner const en las
**	  variables que no cambien en la función, lo hace más fácil
**	  de leer (al menos para mí)
*/
char	**parse_line(const char *line)
{
	char	*in;
	char	**cmds;
	char	**out;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmds = extract_commands(line);
	if (detect_mode(line) == 0)
	{
		out = malloc(sizeof(char *) * (count_items(cmds) + 2));
		while (cmds[i])
			out[j++] = ft_strdup(cmds[i++]);
		return (out[j++] = ft_strdup("0"), out[j] = NULL, out);
	}
	out = malloc(sizeof(char *) * (count_items(cmds) + 6));
	if (detect_mode(line) == 1)
	{
		in = extract_word_after(line, "<");
		if (in)
			out[j++] = in;
	}
	else if (detect_mode(line) == 2)
	{
		out[j++] = ft_strdup("here_doc");
		out[j++] = extract_word_after(line, "<<");
	}
	i = 0;
	while (cmds[i])
		out[j++] = ft_strdup(cmds[i++]);
	out[j++] = extract_outfile(line);
	if (detect_mode(line) == 1)
		out[j++] = ft_strdup("1");
	else
		out[j++] = ft_strdup("2");
	return (out[j] = NULL, out);
}
