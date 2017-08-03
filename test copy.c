#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_dllnode	t_dllnode;

#define DLLA_SORTUP 1
#define DLLA_SORTDOWN 2
#define DLLA_EMPTY 4

int	black_list[11][3] = {
	{1, -1, -1}, //sa 0
	{0, -1, -1}, //sb 1
	{0, 1, -1}, //ss 2
	{3, -1, -1}, //pa 3
	{2, -1, -1}, //pb 4
	{6, 8, 10}, //ra 5
	{5, 9, 10}, //rb 6
	{9, 8, 10}, //rr 7
	{9, 5, 7}, //rra 8
	{8, 5, 7}, //rrb 9
	{5, 5, 7} //rrr 10
};

struct						s_dllnode
{
	t_dllnode				*prev;
	t_dllnode				*next;
	int						data;
};

typedef struct				s_dllarray
{
	unsigned int			size;
	t_dllnode				*head;
	t_dllnode				*tail;
	int						status;
}							t_dllarray;

typedef struct	s_ps_frame	t_ps_frame;

struct						s_ps_frame
{
	t_dllarray	a;
	t_dllarray	b;
	t_dllnode	*pool;
	int			last_action;
	t_ps_frame	*actions[11];
	int			head;
};

typedef struct				s_ps_game
{
	char		*data;
	int			frame_size;
	t_ps_frame	*frames[1024];
	int			pile[1024];
	int			head;
}							t_ps_game;

// int	debug(t_dllarray *a)
// {
// 	printf("debug:\nlabel: %s\nsize: %d\n", a->label, a->size);
// 	printf("head: %p\ntail: %p\nstatus: %d\n", a->head, a->tail, a->status);
// 	return (0);
// }

int	recheck_sort(t_dllarray *a)
{
	t_dllnode	*n;

	if (a->size == 0)
	{
		a->status &= ~(DLLA_SORTUP | DLLA_SORTDOWN);
		a->status |= DLLA_EMPTY;
		return (0);
	}
	a->status |= DLLA_SORTUP | DLLA_SORTDOWN;
	a->status &= ~DLLA_EMPTY;
	n = a->head;
	while (n->next != NULL && a->status & (DLLA_SORTUP | DLLA_SORTDOWN))
	{
		if (n->next->data > n->data)
			a->status &= ~DLLA_SORTUP;
		if (n->next->data < n->data)
			a->status &= ~DLLA_SORTDOWN;
		n = n->next;
	}
	return (0);
}

int	push(t_dllarray *a, t_dllnode *n)
{
	if (a != NULL && n != NULL && ++a->size)
	{
		if (a->size > 1)
		{
			if (a->head->data > n->data)
				a->status &= ~DLLA_SORTUP;
			if (a->head->data < n->data)
				a->status &= ~DLLA_SORTDOWN;
			a->head->prev = n;
		}
		else
		{
			a->status |= DLLA_SORTUP | DLLA_SORTDOWN;
			a->status &= ~DLLA_EMPTY;
			a->tail = n;
		}
		n->next = a->head;
		n->prev = NULL;
		a->head = n;
		return (0);
	}
	return (-1);
}

int	append(t_dllarray *a, t_dllnode *n)
{
	if (a != NULL && n != NULL && ++a->size)
	{
		if (a->size > 1)
		{
			if (a->tail->data > n->data)
				a->status &= ~DLLA_SORTDOWN;
			if (a->tail->data < n->data)
				a->status &= ~DLLA_SORTUP;
			a->tail->next = n;
		}
		else
		{
			a->status |= DLLA_SORTUP | DLLA_SORTDOWN;
			a->status &= ~DLLA_EMPTY;
			a->head = n;
		}
		n->prev = a->tail;
		n->next = NULL;
		a->tail = n;
		return (0);
	}
	return (-1);
}

int	pop(t_dllarray *a, t_dllnode **n)
{
	if (a != NULL && n != NULL && a->size--)
	{
		*n = a->head;
		a->head = a->head->next;
		(*n)->next = NULL;
		a->head->prev = NULL;
		if (a->size == 0)
		{
			a->status &= ~(DLLA_SORTUP | DLLA_SORTDOWN);
			a->status |= DLLA_EMPTY;
		}
		else
			recheck_sort(a);
		return (0);
	}
	return (-1);
}

int	rotate(t_dllarray *a)
{
	if (a != NULL)
	{
		a->tail->next = a->head;
		a->head->prev = a->tail;
		a->head = a->head->next;
		a->tail = a->tail->next;
		a->tail->next = NULL;
		a->head->prev = NULL;
	}
	return (0);
}

int	rrotate(t_dllarray *a)
{
	if (a != NULL)
	{
		a->tail->next = a->head;
		a->head->prev = a->tail;
		a->head = a->head->prev;
		a->tail = a->tail->prev;
		a->tail->next = NULL;
		a->head->prev = NULL;
	}
	return (0);
}

int	swap(t_dllarray *a)
{
	t_dllnode	*t1;
	t_dllnode	*t2;

	if (a != NULL && a->size > 1)
	{
		t1 = a->head->next;
		a->head->next = t1->next;
		a->head->prev = t1;
		t1->next = a->head;
		t1->prev = NULL;
		a->head = t1;
		recheck_sort(a);
		return (0);
	}
	return (-1);
}

int	move(t_dllarray *a, t_dllarray *b)
{
	t_dllnode	*t;

	return (pop(a, &t) || push(b, t));
}

int	print(t_dllarray *a, char *label)
{
	t_dllnode	*n;

	n = a->head;
	printf("%s:", label);
	while (n != NULL)
	{
		// printf("data: %d, d: %p, p: %p, n: %p\n", n->data, n, n->prev, n->next);
		printf(" %d", n->data);
		n = n->next;
	}
	return (0);
}

int	status(t_ps_frame *f)
{
	const char	*action_names[11] = {

	"sa", "sb", "ss", "pa", "pb", "ra", "rb", "rr", "rra", "rrb", "rrr"};
	if (f->last_action != -1)
		printf("action: '%s', result ", "db");
	else
		printf("first frame, status ");
	print(&f->a, "a");
	printf(" | ");
	print(&f->b, "b");
	printf("\n");
	return (0);
}

//a: -48, -70, -45, 4, -90, 49, 75, 60
// sa
// pb
// pb
// pb
//a: 4, -90, 49, 75, 60 b: -45, -48, -70
// sa
// pb
// rb
//a: 4, 49, 75, 60 b: -45, -48, -70, -90
// rra
// rra
// sa
// ra
// ra
//a: 4, 49, 60, 75 b: -45, -48, -70, -90
// pa
// pa
// pa
// pa
//a: -90, -70, -48, -45, 4, 49, 60, 75

t_ps_game	*init(int argc, char **argv)
{
	static t_ps_game	game;
	char				*t;
	int					i;

	game.frame_size = sizeof(t_ps_frame) + sizeof(t_dllnode) * argc;
	game.data = malloc(game.frame_size * 1024);
	game.head = 1;
	i = -1;
	while (++i < 1024)
		game.frames[i] = (t_ps_frame*)(game.data + game.frame_size * i);
	game.pile[0] = 0;
	game.frames[0]->a = (t_dllarray){
				.size = 0, .head = NULL, .tail = NULL, .status = DLLA_EMPTY};
	game.frames[0]->b = game.frames[0]->a;
	game.frames[0]->pool = (t_dllnode*)(game.data + sizeof(t_ps_frame));
	game.frames[0]->last_action = -1;
	game.frames[0]->head = 0;
	i = 0;
	while (++i < argc)
	{
		game.frames[0]->pool[i - 1] = (t_dllnode){.prev = NULL, .next = NULL,
								.data = (int)strtol(argv[i], &t, 10)};
		if (*t != '\0')
		{
			free(game.data);
			write(2, "Error\n", 6);
			return (NULL);
		}
		push(&game.frames[0]->a, &game.frames[0]->pool[i - 1]);
	}
	return (&game);
}

int	main(int argc, char **argv)
{
	t_ps_game	*game;

	game = NULL;
	if (argc > 1)
		game = init(argc, argv);
	if (game == NULL)
		return (0);
	printf("%d\n", game->frames[0]->a.size);
	status(game->frames[0]);
	free(game->data);
	// t_dllnode	*pool;
	// t_dllarray	a = {.label = "a", .head = NULL, .tail = NULL, .size = 0};
	// t_dllarray	b = {.label = "b", .head = NULL, .tail = NULL, .size = 0};
	// t_dllnode	*r;
	// int			i;
	// char		*t;
	//
	// if (argc > 1)
	// {
	// 	pool = malloc(sizeof(t_dllnode) * (argc - 1));\
	// 	i = 0;
	// 	while (++i < argc)
	// 	{
	// 		pool[i - 1] = (t_dllnode){.prev = NULL, .next = NULL,
	// 								.data = (int)strtol(argv[i], &t, 10)};
	// 		if (*t != '\0')
	// 		{
	// 			free(pool);
	// 			write(2, "Error\n", 6);
	// 			return (0);
	// 		}
	// 		push(&a, &pool[i - 1]);
	// 	}
	// 	status(&a, &b);
	// 	debug(&a);
	// 	swap(&a);
	// 	// pop(&a, &r);
	// 	// printf("r: %d, d: %p, p: %p, n: %p\n", r->data, r, r->prev, r->next);
	// 	status(&a, &b);
	// 	debug(&a);
	// 	swap(&a);
	// 	debug(&a);
	// 	free(pool);
	// }
}
