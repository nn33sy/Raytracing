/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: how-choongines <how-choongines@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 14:39:59 by how-choon         #+#    #+#             */
/*   Updated: 2021/04/03 20:06:46 by how-choongi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFFER_SIZE 50
# include "minirt.h"

t_list_gnl		*ft_new(t_list_gnl **list, int fd);
t_list_gnl		*ft_list(t_list_gnl **list, int fd);
void			ft_read_line(t_list_gnl *ptn);
int				ft_strlen_gnl(char *s);
char			*ft_strjoin_gnl(char *s1, char *s2);
char			*ft_split_gnl(char **buffer, int stop);
char			*ft_strdup_gnl(char *src);
void			ft_free(t_list_gnl *ptn);
int				get_next_line(int fd, char **line);
int				find_char(char *str);
#endif
