/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shit_paint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 08:15:51 by evila-ro          #+#    #+#             */
/*   Updated: 2021/10/22 12:41:56 by evila-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shit_micro.h"

int	ft_strlen(char *str)
{
	int  i;

	i = 0;
	while(str[i])
		i++;
	return (i);
}

int	fterror(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

int	draw(float x, float y, float xp, float yp, float w, float h)
{
	if (x < xp || x > xp + w || y < yp || y > yp + h)
		return (0);
	else if (x - xp < 1 || (xp + w) - x < 1 || y - yp < 1 || (y - yp) < 1 || (yp + h) - y < 1)
		return (1);
	return (2);
}

int	main(int argc, char **argv)
{
	FILE 	*file;
	char	*sheet;
	char	back;
	char	line;
	char	fill;
	int		empty;
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
		return (fterror("Error: argument\n"));
	if (!(file = fopen(argv[1], "r")) ||
		(fscanf(file, "%i %i %c\n", &bw, &bh, &back) != 3) ||
		(!(bw > 0 && bw <= 300 && bh > 0 && bh <= 300)) ||
		 (!(sheet = (char *)malloc(sizeof(char) * (bw * bh)))))
		return (fterror("Error: Operation file corrupted\n"));
	memset(sheet, back, bw * bh);
	while ((empty = fscanf(file, "%c %f %f %f %f %c\n", &line, &xp, &yp, &w, &h, &fill)) == 6)
	{
		if (!(w > 0 && h > 0) || !(line == 'R' || line == 'r'))
			break;
		x = -1;
		while(++x < bw)
		{
			y = -1;
			while (++y < bh)
			{
				p = draw((float)x, (float)y, xp, yp, w, h);
				if (p == 1 || (p == 2 && line == 'R'))
					sheet[y * bw + x] = fill;
			}
		}
	}
	if (empty != -1)
	{
		free(sheet);
		return (fterror("Error: Operation file corrupted\n"));
	}
	y = -1;
	while (++y < bh)
	{
		write(1, sheet + y * bw, bw);
		write(1, "\n", 1);
	}
	free(sheet);
	fclose(file);
	return (0);
}
