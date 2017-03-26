attribute vec4 position;
void	main()
{
	vec4	tmp = position;
	tmp.x = sin(tmp.x) / 1.5;
	tmp.y = sin(tmp.y) / 1.5;
	gl_Position = tmp;
}
