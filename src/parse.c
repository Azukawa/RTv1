/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esukava <esukava@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 11:11:07 by esukava           #+#    #+#             */
/*   Updated: 2022/02/18 22:57:20 by esukava          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

 void	skip_white(int *i, char *str)
 {
 	while(str[*i] == '\t' || str[*i] == ' ')
		 *i += 1;
 }

 t_bool	parse_quantity(t_doom *doom, char *str)
 {
 	int i;

 	i = 0;
 	if(str[i++] != 'q')
 		return (FALSE);
 	skip_white(&i, str);
 	if(str[i] >= 48 && str[i] <=57)
 		{
 			doom->object_count = ft_atoi(&str[i]);
 			return (TRUE);
 		}
 	else
 		return (FALSE);
 }

t_bool	parse_type(t_doom *doom, char *str, int index)
{
	int i;

	i = 0;
	if(str[i++] != 't')
		return (FALSE);
	skip_white(&i, str);
	if(str[i] == 's')
	{
		doom->object[index].type = SPHERE;
		return (TRUE);
	}
	else if (str[i] == '^')
	{
		doom->object[index].type = CONE;
		return (TRUE);
	}
	else if (str[i] == 'c')
	{
		doom->object[index].type = CYL;
		return (TRUE);
	}
	else if (str[i] == 'p')
	{
		doom->object[index].type = PLANE;
		return (TRUE);
	}
	else
		return (FALSE);
}

t_bool		val_sym(char c, int i)
{
	if (i == 0)
	{
		if (ft_isdigit(c) || c == '-')
			return (TRUE);
		else
			return (FALSE);
	}
	else
		if(ft_isdigit(c))
			return (TRUE);
	return (FALSE);
	
}

t_bool		str_to_int(int *i, char *str, float *pos)
{
	char ret[3];
	int  j;
	
	ft_bzero(ret, 3);
	j = 0;
	while(str[*i] != ',' && str[*i] != ';' && j < 3)
	{	
		if (!val_sym(str[*i], j))
			return (FALSE);
		ret[j] = str[*i];
		*i += 1;
		j++;
	}
	*i += 1;
	*pos = ft_atoi(ret);
	if (*pos >= -99 && *pos <= 99)
		return (TRUE);
	return (FALSE);
}


t_bool	parse_pos(t_doom *doom, char *str, int index)
{
	int i;
	
	i = 0;
	if (str[i++] != 'p')
		return (FALSE);
	skip_white(&i, str);
	if (!str_to_int(&i, str, &doom->object[index].pos.x))
		return(FALSE);
	if (!str_to_int(&i, str, &doom->object[index].pos.y))
		return(FALSE);
	if (!str_to_int(&i, str, &doom->object[index].pos.z))
		return (FALSE);
	return (TRUE);
}

t_bool	parse_dir(t_doom *doom, char *str, int index)
{
	int i;
	
	i = 0;
	if (str[i++] != 'd')
		return (FALSE);
	skip_white(&i, str);
	if (!str_to_int(&i, str, &doom->object[index].dir.x))
		return (FALSE);
	if (!str_to_int(&i, str, &doom->object[index].dir.y))
		return (FALSE);
	if (!str_to_int(&i, str, &doom->object[index].dir.z))
		return (FALSE);
	return (TRUE);
}


t_bool	parse_r(t_doom *doom, char *str, int index)
{
	int i;
	int val;
	
	i = 0;
	val = 0;
	if (str[i++] != 'r')
		return (FALSE);
	skip_white(&i, str);
	if(ft_isdigit(str[i]))
	{	
		val = ft_atoi(&str[i]);
		doom->object[index].r = val;
		return (TRUE);
	}
	else
		return (FALSE);
}

//material 0-2
t_bool	parse_material(t_doom *doom, char *str, int index)
{
	int i;
	int val;
	
	i = 0;
	val = 0;
	if (str[i++] != 'm')
		return (FALSE);
	skip_white(&i, str);
	if(ft_isdigit(str[i]))
	{	
		val = ft_atoi(&str[i]);
		if(val >= 0 && val <= 2)
		{	
			doom->object[index].material = val;
			return (TRUE);
		}
	}
	return (FALSE);
}

t_bool	parse_angle(t_doom *doom, char *str, int index)
{
	int i;
	int val;
	
	i = 0;
	val = 0;
	if (str[i++] != 'a')
		return (FALSE);
	skip_white(&i, str);
	if(ft_isdigit(str[i]))
	{	
		val = ft_atoi(&str[i]);	
		doom->object[index].angle = val;
		return (TRUE);
	}
	return (FALSE);
}

t_bool saveline(char *ret, char *str)
{
	int i;

	i = 0;
	if(ft_strlen(str) < 100)
	{	
		while (i < 99 && str[i] != '\0' && str[i] != '\n')
		{
			ret[i] = str[i];
			i++;
		}
		ret[i] = '\0';
		return(TRUE);
	}
	else
		return(FALSE);
}

t_bool	readscene(char *str, t_doom *doom)
{
	int		fd;
	int		ret;
	int		i;
	char	*output;

	i = 0;
	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (0);
	ret = get_next_line(fd, &output);
	while (ret > 0 && i < 100)
	{
		saveline(doom->scene[i], output);
		i++;
		free(output);
		ret = get_next_line(fd, &output);
	}
	doom->scene_len = i;
	return (1);
}

void	print_array(t_doom *doom)
{
	int i = 0;

	while(i < doom->scene_len)
	{
		printf("%s\n", doom->scene[i]);
		i++;
	}
	
}

void	print_stuff(t_doom *doom)
{
	int i = 0;
	
	printf("scene_len = %d\n", doom->scene_len);		
	printf("\nobject_count = %d\n\n", doom->object_count);
	while(i < doom->object_count && i <= 9)
	{
		printf("object[%d] type\t= %d\n",i , doom->object[i].type);
		printf("object[%d] posx\t= %f posy = %f posz = %f\n", i, doom->object[i].pos.x, doom->object[i].pos.y, doom->object[i].pos.z);
		printf("object[%d] dirx\t= %f diry = %f dirz = %f\n", i, doom->object[i].dir.x, doom->object[i].dir.y, doom->object[i].dir.z);
		printf("object[%d] r\t= %f\n", i, doom->object[i].r);
		printf("object[%d] mater = %d\n", i, doom->object[i].material);
		printf("object[%d] angle\t= %f\n\n", i, doom->object[i].angle);
		i++;
	}
}

t_bool		parse(char *str, t_doom *doom)
{
	int i = 0;
	int j = 0;
	if (!readscene(str, doom))
		return(FALSE);
	if(!parse_quantity(doom, doom->scene[j++]))
		return(FALSE);
	j++;
	while(i < doom->object_count)
	{
		if (!parse_type(doom, doom->scene[j++], i))
			return (FALSE);
		if (!parse_pos(doom, doom->scene[j++], i))
			return (FALSE);
		if (!parse_dir(doom, doom->scene[j++], i))
			return (FALSE);
		if (!parse_r(doom, doom->scene[j++], i))
			return (FALSE);
		 if(!parse_material(doom, doom->scene[j++], i))
		 	return(FALSE);
		 if (!parse_angle(doom, doom->scene[j++], i))
		 	return (FALSE);
		j++;
		i++;
	}
	
	
	print_array(doom);
	print_stuff(doom);
	return (TRUE);
}