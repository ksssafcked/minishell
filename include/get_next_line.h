/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsaiti <lsaiti@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 16:55:18 by lsaiti            #+#    #+#             */
/*   Updated: 2024/12/28 14:55:29 by lsaiti           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_buffer
{
	char	buffer[BUFFER_SIZE];
	long	buff_pos;
	long	bytesread;
	long	buff_read;
}	t_buffer;

typedef struct s_string
{
	char	*str;
}	t_string;

char	*get_next_line(int fd);
char	*get_next_line_buff(int fd, t_buffer *b, t_string *s);
char	*get_next_line_buff_set(int fd, t_string *s, t_buffer *b);
void	get_next_line_read(int fd, t_buffer *b);
char	*get_next_line_onebuff(int fd, t_string *s, t_buffer *b);
void	*ft_freestr(char **str);
char	*ft_strjoinline(char *s1, char const *s2, long n);

#endif
