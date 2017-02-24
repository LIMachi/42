/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom-frac.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/24 14:59:26 by qloubier          #+#    #+#             */
/*   Updated: 2016/11/21 08:50:28 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fractol.h"

//fractol.h

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qloubier <qloubier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/19 17:23:12 by qloubier          #+#    #+#             */
/*   Updated: 2016/11/01 22:30:05 by qloubier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <pthread.h>

# include "mlx.h"
# include "libdraw.h"
# include "basic.h"
# include "libft.h"

# include "fractol_proto.h"

# define MINZOOM 1.0

# if OPSYS == mac
#  define MAX_SLEEP 5
#  define MOVEVAL 12.0f
#  define ZOOMVAL 0.1f
# else
#  define MAX_SLEEP 50000
#  define ROTVAL 0.02f
#  define MOVEVAL 7.0f
#  define ZOOMVAL 0.02f
# endif

# define TEXNUM 3
# define THREADNUM 8

# define GRADNUM 8
# define FRACNUM 8

# define HGG " -g, --gradient\t\tGradient from void to c2\n"
# define HGGG " -G, --dualgradient\tGradient from c1 to c2\n"
# define HGH " -h, --huegradient\tHue gradient from c1 to c2\n"
# define HGHH " -H, --huetriplegrad\tHue gradient from void to c1 to c2\n"
# define HG_S " -s, --staticgradient\tStatic gradient starting at value 0\n"
# define HGS " -S, --stasatgradient\tStatic gradient starting at saturation 0\n"
# define HGF " -f, --fire\t\tFire-like gradient\n"
# define HGHHH " --hybrid\t\tHybrid gradient (H + S)\n"

struct				s_frac_vector
{
	t_frac			x;
	t_frac			y;
};

typedef enum		e_keycode
{
	NOKEY = 0,
	KUP = 1,
	KDOWN = 1 << 1,
	KLEFT = 1 << 2,
	KRIGHT = 1 << 3,
	K_W = 1 << 4,
	K_A = 1 << 5,
	K_S = 1 << 6,
	K_D = 1 << 7,
	KZOOM = 1 << 8,
	KUNZOOM = 1 << 9,
	KRESET = 1 << 10,
	KCOLF = 1 << 12,
	KCOLB = 1 << 13,
	K_RENDER = 1 << 11,
	K_NEEDREFRESH = 1 << 28,
	K_HUDREFRESH = 1 << 27,
	K_REFRESHGRADIENT = 1 << 29,
	K_REFCOL = KCOLF | KCOLB | K_REFRESHGRADIENT,
	K_REFRESH = 1 << 30,
	THREAD_K = K_REFRESH | K_HUDREFRESH,
	THREAD_PULL = K_REFRESH | K_NEEDREFRESH,
	THREAD_PUSH = K_RENDER | K_REFCOL
}					t_kc;

typedef enum		e_fractale_type
{
	NO_FRAC = -1,
	FRAC_MANDLEBROT = 0,
	FRAC_JULIA = 1,
	FRAC_BURNINGSHIP = 2,
	FRAC_X = 3,
	FRAC_CUSTOM = 4,
	FRAC_LUNA = 5,
	FRAC_CUBE = 6,
	FRAC_MULTIBROT = 7
}					t_frt;

typedef enum		e_frflags
{
	NOFLAG = 0,
	HIDE_HUD = 1,
	DISP_KCODE = 1 << 2,
	COLSET = 1 << 3,
	DUALCOLSET = 1 << 4,
	MULTITHREAD = 1 << 5,
	AUTOREFRESH = 1 << 6,
	VMOUSEMODE = 1 << 7,
	GRABMODE = 1 << 8,
	HELP_MODE = 1 << 9,
	SHIFT_MODE = 1 << 10
}					t_frf;

typedef enum		e_frcolormode
{
	UNICOLOR = 0,
	DUALCOLOR = 1,
	HUEGRADIENT = 2,
	STATICGRADIENT = 3,
	STASATGRADIENT = 4,
	HUETRIGRAD = 5,
	HSGRAD = 6,
	FIREGRAD = 7,
	NOTSET = -1
}					t_frcm;

struct				s_colorgrad
{
	t_col			start;
	t_col			end;
	t_col			voidcol;
	t_frcm			mode;
};

struct				s_view_fractal
{
	t_v2ui			ts;
	t_frac			x;
	t_frac			y;
	t_frac			sx;
	t_frac			sy;
	t_frac			lx;
	t_frac			ly;
	t_frac			d;
	t_frac			zoom;
	t_vec			offset;
};

struct				s_render_ctx
{
	t_ui			mxi;
	t_kc			activekey;
	t_col			*ctab;
	t_col			*(*process)(t_frac, t_frac, t_frctx *);
	t_tex			img;
	t_vec			vmouse;
	t_frv			view;
};

struct				s_render_mgr
{
	int				activetex;
	int				drawtex;
	t_kc			activekey;
	t_ui			mxi;
	t_cgr			gradient;
	t_col			*ctab;
	t_col			*(*process)(t_frac, t_frac, t_frctx *);
	t_vec			vmouse;
	t_frv			view;
	t_tex			textures[TEXNUM];
	t_frv			texview[TEXNUM];
};

struct				s_thread_ctx
{
	t_frctx			ctx;
	int				done;
	t_ui			column_id;
	t_thmgr			*mgr;
	pthread_mutex_t	data_mutex;
};

struct				s_thread_mgr
{
	int				quit;
	int				padding;
	t_frmgr			mgr;
	t_frv			view;
	t_frctx			ctx;
	t_frc			*frc;
	pthread_mutex_t	data_acces;
	pthread_cond_t	refresh;
	pthread_mutex_t	ref_mutex;
	pthread_cond_t	drawstart;
	pthread_mutex_t	start_mutex;
};

struct				s_fractol_param
{
	t_frt			ftype;
	t_frf			flags;
	unsigned int	maxiter;
	t_col			basecols[3];
	t_cgr			gradient;
	t_frac			minzoom;
	t_frac			vmsens;
};

struct				s_fractol_root
{
	t_frprm			params;
	t_kc			active;
	int				hudy;
	t_v2ui			texsize;
	t_v2f			texoffset;
	t_frac			texzoom;
	t_frv			texview;
	t_frctx			ctx;
	void			*hud;
	t_frmgr			*mgr;
	t_dsys			sys;
	t_win			win;
	t_thmgr			*thmgr;
	pthread_t		thid;
};

t_argb				toargb(t_col c);
t_col				fromargb(t_argb c);
t_argb				rgb2hsv(t_argb rgb);
void				rotate_hue(t_col *c, int i);
t_argb				hsv2rgb(t_argb hsv);
t_argb				hsv_lerp(t_argb a, t_argb b, float fac);

t_col				basic_grad(t_cgr *gr, t_ui i, t_ui mxi);
t_col				hue_grad(t_cgr *gr, t_ui i, t_ui mxi);
t_col				static_saturation_grad(t_cgr *gr, t_ui i, t_ui mxi);
t_col				static_grad(t_cgr *gr, t_ui i, t_ui mxi);
t_col				fire_grad(t_cgr *gr, t_ui i, t_ui mxi);

void				parse_col(t_frc *frc, const char *arg);
t_col				get_col(const char *c);
int					get_hexchar(char c);

int					frac_condwait(pthread_mutex_t *m, pthread_cond_t *c,
						void (*f)(void *), void *arg);

int					parse_args(t_frc *frc, int ac, char **av);
void				frac_start(t_frc *frc);
void				frac_set(t_frc *frc, t_frt type);
void				frac_reset(t_frc *frc);

t_col				*genrate_gradient(t_col *basecol, t_ui len, t_ui step,
						t_frf flags);
t_ui				gen_ctab(t_frmgr *mgr, t_ui mxi);
t_frv				frac_init_view(t_frt ftype, t_v2ui screen);
void				frac_clip_view(t_frc *frc);
void				frac_move_view(t_frc *frc, t_frac z, t_v2f mov, t_v2f zp);
void				frac_view_push(t_frc *frc);
t_frac				frac_zoom(t_frc *frc, t_frac zval);
void				up_iteration(t_frc *frc);
void				down_iteration(t_frc *frc);

t_frmgr				frac_mgr_create(t_frc *frc);
int					frac_mgr_render_request(t_frctx *newctx, t_frmgr *mgr);
void				frac_ctx_update(t_frctx *ctx, t_frmgr *mgr);
void				frac_ctx_sync(t_frctx *ctx, t_frctx *octx);
t_frctx				frac_create_frctx(t_frmgr *mgr);

int					frac_releasekey(int keycode, void *frc_context);
int					frac_presskey(int keycode, void *frc_context);
int					frac_mouse(int x, int y, void *param);
int					frac_mousebutton(int button, int x, int y, void *param);
int					frac_mouseupbutton(int button, int x, int y, void *param);
int					frac_mainloop(void *arg);
void				frac_reset(t_frc *frc);
void				frac_drawhud(t_frc *frc);
int					frac_drawexpose(void *arg);
void				frac_draw(t_frc *frc);
void				frac_moveview(t_frc *frc);
int					frac_quit(void *sys, char *message);

void				frac_render(t_frctx *ctx, t_ui cid, t_ui thnum, int *quit);
t_col				*mandlebrot_process(t_frac x, t_frac y, t_frctx *ctx);
t_col				*burningship_process(t_frac x, t_frac y, t_frctx *ctx);
t_col				*julia_process(t_frac x, t_frac y, t_frctx *ctx);
t_col				*x_process(t_frac x, t_frac y, t_frctx *ctx);
t_col				*circle_process(t_frac x, t_frac y, t_frctx *ctx);
t_col				*custom_process(t_frac x, t_frac y, t_frctx *ctx);
t_col				*cube_process(t_frac x, t_frac y, t_frctx *ctx);
t_col				*multibrot_process(t_frac x, t_frac y, t_frctx *ctx);

int					frac_init_thread(t_frc *frc);
int					frac_exit_thread(t_frc *frc);
void				frac_sync_thread(t_frc *frc);
void				*frac_thread_renderer(void *arg);
void				*frac_thread_mgr(void *arg);

#endif

//fractol.c

t_col			*x_process(t_frac x, t_frac y, t_frctx *ctx)
{
	t_frac		zr;
	t_frac		zi;
	t_frac		tr;
	t_frac		ti;
	t_ui		i;

	zr = y;
	zi = x;
	i = ctx->mxi;
	while (i)
	{
		tr = zr * zr;
		ti = zi * zi;
		if ((tr + ti) > 10.0)
			return (&(ctx->ctab[ctx->mxi - i]));
		zr = (tr - ti) - ctx->vmouse.y;
		zi = ((zr) ? zi / zr : 0.0) + ctx->vmouse.x;
		i--;
	}
	return (ctx->ctab);
}

t_col			*cube_process(t_frac x, t_frac y, t_frctx *ctx)
{
	t_frac		zr;
	t_frac		zi;
	t_frac		tr;
	t_frac		ti;
	t_ui		i;

	if ((x > 3.0) || (y > 3.0))
		return (ctx->ctab);
	zr = 3.0 + ctx->vmouse.y;
	zi = 1.0 + ctx->vmouse.x;
	i = ctx->mxi;
	while (i--)
	{
		tr = fmodl(x, zr);
		ti = fmodl(y, zr);
		if ((tr > zi) && (tr < (zi * 2)) && (ti > zi) && (ti < (zi * 2)))
			return (&(ctx->ctab[ctx->mxi - i]));
		zi /= 3.0;
		zr /= 3.0;
		if (zr < (ctx->view.d / ctx->view.zoom))
			break ;
	}
	return (ctx->ctab);
}

t_col			*multibrot_process(t_frac x, t_frac y, t_frctx *ctx)
{
	t_frac		zr;
	t_frac		zi;
	t_frac		tr;
	t_frac		ti;
	t_ui		i;

	zr = ctx->vmouse.x;
	zi = ctx->vmouse.y;
	i = ctx->mxi;
	while (i)
	{
		tr = zr * zr;
		ti = zi * zi;
		if ((tr + ti) >= 4)
			return (&(ctx->ctab[ctx->mxi - i]));
		zi = ((3 * tr * zi) - (zi * ti)) + y;
		zr = (tr * zr) - (3 * zr * ti) + x;
		i--;
	}
	return (ctx->ctab);
}

t_col			*circle_process(t_frac x, t_frac y, t_frctx *ctx)
{
	t_frac		zr;
	t_frac		zi;
	t_frac		tr;
	t_frac		ti;
	t_ui		i;

	zr = x;
	zi = y;
	i = ctx->mxi;
	while (i)
	{
		tr = zr * zr;
		ti = zi * zi;
		if (!(tr + ti) || ((tr + ti) > 4.0))
			return (&(ctx->ctab[ctx->mxi - i]));
		zi = (zi / (tr + ti)) + ctx->vmouse.y;
		zr = (zr / (tr + ti)) + ctx->vmouse.x;
		i--;
	}
	return (ctx->ctab);
}

t_col			*custom_process(t_frac x, t_frac y, t_frctx *ctx)
{
	t_frac		zr;
	t_frac		zi;
	t_frac		tr;
	t_frac		ti;
	t_ui		i;

	zr = 0;
	zi = 0;
	i = ctx->mxi;
	while (i)
	{
		tr = zr * zr;
		ti = zi * zi;
		if ((tr + ti) > 4)
		{
			return (&(ctx->ctab[(int)((tr + ti / ctx->vmouse.x) *
				ctx->vmouse.y) % ctx->mxi]));
		}
		zi = (2 * zi * zr) + y;
		zr = tr - ti + x;
		i--;
	}
	return (ctx->ctab);
}
