include "RTv1.h"

void	print_array(t_doom *doom)
{
	int	i;

	i = 0;
	while (i < doom->scene_len)
	{
		printf("%s\n", doom->scene[i]);
		i++;
	}
}

void	print_stuff(t_doom *doom)
{
	int i = 0;

	printf("scene_len = %d\n", doom->scene_len);
	printf("\nobject_count = %d\n", doom->object_count);
	printf("light\tposx = %f posy = %f posz = %f\n\n", doom->object[9].pos.x, doom->object[9].pos.y, doom->object[9].pos.z);
	while(i < doom->object_count && i < 9)
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