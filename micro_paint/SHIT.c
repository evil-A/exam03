/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 10:58:08 by evila-ro          #+#    #+#             */
/*   Updated: 2021/10/26 12:35:51 by evila-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	terror(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int	draw(float x, float y, float xp, float yp, float w, float h)
{
	if (x < xp || x > xp + w || y < yp || y > yp + h)
		return (0);
	else if (x - xp < 1 || (xp + w) - x < 1 || y - yp < 1 || (yp + h) - y < 1)
		return (1);
	return (2);
}

int	main(int argc, char **argv)
{
	FILE	*file;
	char	*sheet;
	char	back;
	char	type;
	char	fill;
	int		line;
	int		p;
	int		x;
	int		y;
	int		bw;
	int		bh;
	float	xp;
	float	yp;
	float	w;
	float	h;

	if (argc != 2)
		return (terror("Error: argument\n"));
	if (!(file = fopen(argv[1], "r")) ||
		(fscanf(file, "%i %i %c\n", &bw, &bh, &back) != 3) ||
		(!(bw > 0 && bw <= 300 && bh > 0 && bh <= 300)) ||
		(!(sheet = (char *)malloc(sizeof(char) * (bw * bh)))))
		return (terror("Error: Operation file corrupted\n"));
	memset(sheet, back, bw * bh);
	while ((line = fscanf(file, "%c %f %f %f %f %c\n", &type, &xp, &yp, &w, &h, &fill)) == 6)
	{
		if (!(w > 0 && h > 0) || !(type == 'R' || type == 'r'))
			break ;
		x = 0;
		while (x < bw)
		{
			y = 0;
			while (y < bh)
			{
				p = draw((float)x, (float)y, xp, yp, w, h);
				if (p == 1 || (p == 2 && type == 'R'))
					sheet[y * bw + x] = fill;
				y++;
			}
			x++;
		}
	}
	if (line != -1)
	{
		free(sheet);
		return (terror("Error: Operation file corrupted\n"));
	}
	y = 0;
	while (y < bh)
	{
		write(1, sheet + y * bw, bw);
		write(1, "\n", 1);
		y++;
	}
	free(sheet);
	fclose(file);
	return (0);
}
