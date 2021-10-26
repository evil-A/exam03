/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evila-ro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 12:35:46 by evila-ro          #+#    #+#             */
/*   Updated: 2021/10/26 11:49:52 by evila-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	ft_strlen(char *str)
{
	int	i;

	for (i = 0; str[i]; i++);
	return (i);
}

int	draw(float x, float y, float xp, float yp, float w, float h)
{
	if (x < xp || x > xp + w || y < yp || y > yp + h)
		return (0);
	else if (x - xp < 1.00000000 || (xp + w) - x < 1.00000000 || y - yp < 1.00000000 || (yp + h) - y < 1.00000000)
		return (1);
	return (2);
}

int	main(int argc, char **argv)
{
	FILE	*file;
	char	*sheet, back, type, fill;
	int		line, p, x, y, bw, bh;
	float	xp, yp, w, h;

	if (argc != 2)
		return (!(!(write(1, "Error: argument\n", 16))));
	if (!(file = fopen(argv[1], "r")) ||
		(fscanf(file, "%i %i %c\n", &bw, &bh, &back) != 3) || (!(bw > 0 && bw <= 300 && bh > 0 && bh <= 300)) || (!(sheet = (char *)malloc(sizeof(char) * (bw * bh)))))
		return (!(!(write(1, "Error: Operation file corrupted\n", 32))));
	memset(sheet, back, bw * bh);
	while ((line = fscanf(file, "%c %f %f %f %f %c\n", &type, &xp, &yp, &w, &h, &fill)) == 6)
	{
		if (!(w > 0 && h > 0) || !(type == 'R' || type == 'r'))
		{
			break ;
		}
		for (x = 0; x < bw; x++)
		{
			for (y = 0; y < bh; y++)
			{
				p = draw((float)x, (float)y, xp, yp, w, h);
				if ( p == 1 || (p == 2 && type == 'R'))
					sheet[y * bw + x] = fill;
			}
		}
	}
	if (line != -1)
	{
		free(sheet);
		return (!(!(write(1, "Error: Operation file corrupted\n", 32))));
	}
	for (y = 0; y < bh; y++)
	{
		write(1, sheet + y * bw, bw);
		write(1, "\n", 1);
	}
	free(sheet);
	fclose(file);
	return (0);
}
