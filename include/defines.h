/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 21:28:13 by eniini            #+#    #+#             */
/*   Updated: 2022/02/22 20:32:46 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <stdint.h>

//WINDOW
# define WIN_W	400
# define WIN_H	300
# define WIN_HW 200
# define WIN_HH 150
# define WIN_NAME	"RTv1 build version 0.1"

typedef struct s_fvector {
	float	x;
	float	y;
	float	z;
}			t_fvector;
typedef t_fvector	t_fvec3;

//Datatype to store an ARBG image data. Each pixel can be found by calculating
//[(h * y) + (x % w)]
typedef struct s_buffer {
	uint32_t	*px;
	uint32_t	w;
	uint32_t	h;
}				t_buffer;

#endif