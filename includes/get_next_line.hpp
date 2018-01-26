/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: magouin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 19:02:41 by magouin           #+#    #+#             */
/*   Updated: 2015/12/17 19:02:42 by magouin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <maths.hpp>
# include <stdlib.h>
# include <cstring>
# define BUFF_SIZE 42

int	get_next_line(int const fd, char **line);

#endif
