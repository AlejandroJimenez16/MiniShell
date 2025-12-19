#include "../../includes/mini.h"

int count_items(char **cmds)
{
    int i = 0;
    while (cmds[i])
        i++;
    return (i);
}

char **parse_line(char *line)
{
    int     mode = detect_mode(line);
    char    **cmds;
    char    **out;
    int     i = 0;
    int     j = 0;

    cmds = extract_commands(line);

    if (mode == 0)
    {
        out = malloc(sizeof(char *) * (count_items(cmds) + 2));
        while (cmds[i])
            out[j++] = ft_strdup(cmds[i++]);
        out[j++] = ft_strdup("0");
        out[j] = NULL;
        return (out);
    }

    /* mode 1 or 2 */
    out = malloc(sizeof(char *) * (count_items(cmds) + 6));
    if (mode == 1)
    {
        char *in = extract_word_after(line, "<");
        if (in)
            out[j++] = in;
    }
    else if (mode == 2)
    {
        out[j++] = ft_strdup("here_doc");
        out[j++] = extract_word_after(line, "<<"); // limiter
    }

    /* add commands */
    i = 0;
    while (cmds[i])
        out[j++] = ft_strdup(cmds[i++]);

    /* outfile for mode 1 and 2 */
    out[j++] = extract_outfile(line);

    /* mode number */
    if (mode == 1)
        out[j++] = ft_strdup("1");
    else
        out[j++] = ft_strdup("2");

    out[j] = NULL;
    return (out);
}
