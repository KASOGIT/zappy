/*
** utils.h for  in /home/kaso/Documents/rendu/EPITECH/YEAR2/PROJECT/PSU_2015_myftp/src
** 
** Made by 
** Login   <@epitech.net>
** 
** Started on  Thu May  5 17:04:20 2016 
** Last update Sun Jun 26 23:15:11 2016 
*/

#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "zappy_error.h"

#define ASSERT_ARGS_CMD(x)  (!x || !x[0]) ? (-1) : (0)

char	**str_to_wordtab(char *str);
int	size_wordtab(char **tab);
void	free_wordtab(char **tab);
void	show_wordtab(char **tab);
char	*wordtab_to_str(char **tab);

enum    WHICH_PREND_POSE
{
    PREND,
    POSE
};

enum    WHOSE_SEND_MSG
{
    CLIENT,
    GRAPHICS
};

#endif /* !UTILS_H_ */
