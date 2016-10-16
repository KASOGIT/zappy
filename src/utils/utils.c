/*
** utils.c for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp/src
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu May  5 17:01:19 2016 
** Last update Wed Jun 22 11:33:05 2016 
*/

#include "utils.h"

static int	count_word(char *str)
{
  int		i;
  int		count;

  count = 0;
  i = 0;
  while (str[i] && str[i] != '\r')
    {
      while (str[i] == ' ' || str[i] == '\t'
	     || str[i] == '\r' || str[i] == '\n')
	i++;
      if (!str[i])
	return (count);
      count++;
      while (str[i]
	     && str[i] != '\r'
	     && str[i] != ' '
	     && str[i] != '\t')
	i++;
    }
  return (count);
}

char		**str_to_wordtab(char *str)
{
  char		**tab;
  char		*tmp;
  int		nb_word;
  int		i;

  i = 0;
  nb_word = count_word(str);
  if ((tab = malloc(sizeof(char *) * (nb_word + 1))) == NULL)
    return (NULL);
  while ((tmp = strsep(&str, " ")) != NULL)
    {
      tab[i] = strdup(tmp);
      if (tab[i][0])
	i++;
    }
  tab[i] = NULL;
  return (tab);
}

int	size_wordtab(char **tab)
{
  int	s;

  s = 0;
  while (tab && tab[s] != NULL)
    {
      s++;
    }
  return (s);
}

char	*wordtab_to_str(char **tab)
{
  char	*str;
  int	s;
  int	i;

  i = 0;
  s = 0;
  while (tab[i] != NULL)
    {
      s += strlen(tab[i]) + 1;
      i++;
    }
  str = malloc(sizeof(char) * (s + 1));
  if (str == NULL)
    zappy_error("malloc wordtab to str");
  i = 0;
  while (tab[i] != NULL)
    {
      str = strcat(strcat(str, tab[i]), " ");
      i++;
    }
  return (str);
}
