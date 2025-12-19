#include "../../includes/mini.h"

int	detect_mode(char *line)
{
    if (ft_strnstr(line, "<<", ft_strlen(line)))
        return (2);
    if (ft_strnstr(line, "<", ft_strlen(line))
        || ft_strnstr(line, ">", ft_strlen(line)))
        return (1);
    return (0);
}

char	*extract_word_after(char *line, char *key)
{
    char    *p;
    char    *start;
    int     i = 0;

    p = ft_strnstr(line, key, ft_strlen(line));
    if (!p)
        return (NULL);
    p += ft_strlen(key);
    while (*p == ' ')
        p++;
    start = p;
    while (p[i] && p[i] != ' ' && p[i] != '|' && p[i] != '<' && p[i] != '>')
        i++;
    return (ft_substr(start, 0, i));
}

static char	*remove_redir(char *line)
{
    char    *copy;
    int     i = 0;
    int     j = 0;

    copy = malloc(ft_strlen(line) + 1);
    while (line[i])
    {
        if (line[i] == '<' || line[i] == '>')
        {
            i++;
            while (line[i] == ' ')
                i++;
            while (line[i] && line[i] != ' ' && line[i] != '|')
                i++;
        }
        else
            copy[j++] = line[i++];
    }
    copy[j] = 0;
    return (copy);
}

char	**extract_commands(char *line)
{
    char    *clean;
    char    **cmds;
    int     i = 0;

    clean = remove_redir(line);
    cmds = ft_split(clean, '|');
    while (cmds && cmds[i])
    {
        cmds[i] = ft_strtrim(cmds[i], " ");
        i++;
    }
    free(clean);
    return (cmds);
}

char	*extract_outfile(char *line)
{
    char *out;

    out = extract_word_after(line, ">>");
    if (out)
        return (out);
    out = extract_word_after(line, ">");
    return (out);
}
