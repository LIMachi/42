/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frustrum.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmartzol <hmartzol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 16:39:54 by hmartzol          #+#    #+#             */
/*   Updated: 2016/11/01 17:19:23 by hmartzol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ftx.h>

static t_frustrum	ft_frustrum1(t_frustrum out, t_vector fur, t_vector fdl)
{
	out.bottom_normal = ft_vector_add(out.bottom_point, ft_vector_normalize(
		ft_vector_cross_product(ft_vector_from_a_to_b(out.bottom_point,
		ft_vector(fdl.x, fdl.y, fdl.z)), ft_vector_from_a_to_b(out.bottom_point,
		ft_vector(fur.x, fdl.y, fdl.z)))));
	return (out);
}

static t_frustrum	ft_frustrum0(t_frustrum out, t_vector ndl,
								t_vector nur, t_vector fdl)
{
	t_vector fur;

	fur = out.bottom_normal;
	out.near_normal = ft_vector_add(out.near_point, ft_vector_normalize(
		ft_vector_cross_product(ft_vector_from_a_to_b(out.near_point,
		ft_vector(ndl.x, nur.y, ndl.z)), ft_vector_from_a_to_b(out.near_point,
		ft_vector(ndl.x, ndl.y, ndl.z)))));
	out.far_normal = ft_vector_add(out.far_point, ft_vector_normalize(
		ft_vector_cross_product(ft_vector_from_a_to_b(out.far_point,
		ft_vector(fdl.x, fdl.y, fdl.z)), ft_vector_from_a_to_b(out.far_point,
		ft_vector(fdl.x, fur.y, fdl.z)))));
	out.right_normal = ft_vector_add(out.right_point, ft_vector_normalize(
		ft_vector_cross_product(ft_vector_from_a_to_b(out.right_point,
		ft_vector(fur.x, fur.y, fdl.z)), ft_vector_from_a_to_b(out.right_point,
		ft_vector(nur.x, ndl.y, ndl.z)))));
	out.left_normal = ft_vector_add(out.left_point, ft_vector_normalize(
		ft_vector_cross_product(ft_vector_from_a_to_b(out.left_point,
		ft_vector(fdl.x, fdl.y, fdl.z)), ft_vector_from_a_to_b(out.left_point,
		ft_vector(ndl.x, ndl.y, ndl.z)))));
	out.top_normal = ft_vector_add(out.top_point, ft_vector_normalize(
		ft_vector_cross_product(ft_vector_from_a_to_b(out.top_point,
		ft_vector(nur.x, nur.y, ndl.z)), ft_vector_from_a_to_b(out.top_point,
		ft_vector(fur.x, fur.y, fdl.z)))));
	return (ft_frustrum1(out, fur, fdl));
}

t_frustrum			ft_frustrum(t_point dl, t_point ur, t_point nf,
														t_vector focal)
{
	t_vector	ndl;
	t_vector	nur;
	t_vector	fdl;
	t_vector	fur;

	focal.x = (focal.z + nf.y) / focal.z;
	fdl = ft_vector(focal.x * dl.x, focal.x * dl.y, nf.y);
	fur = ft_vector(focal.x * ur.x, focal.x * ur.y, nf.y);
	focal.x = (focal.z + nf.x) / focal.z;
	ndl = ft_vector(focal.x * dl.x, focal.x * dl.y, nf.x);
	nur = ft_vector(focal.x * ur.x, focal.x * ur.y, nf.x);
	return (ft_frustrum0((t_frustrum){.near_point = ft_vector_middle(ft_vector(
		ndl.x, ndl.y, nf.x), ft_vector(nur.x, nur.y, nf.x)), .far_point =
		ft_vector_middle(ft_vector(fdl.x, fdl.y, nf.y), ft_vector(fur.x, fur.y,
		nf.y)), .bottom_point = ft_vector_middle(ft_vector((ndl.x + nur.x) / 2,
		ndl.y, nf.x), ft_vector((fdl.x + fur.x) / 2, fdl.y, nf.y)), .top_point =
		ft_vector_middle(ft_vector((ndl.x + nur.x) / 2, nur.y, nf.x),
		ft_vector((fdl.x + fur.x) / 2, fur.y, nf.y)), .left_point =
		ft_vector_middle(ft_vector(ndl.x, (ndl.y + nur.y) / 2, (nf.x + nf.y) /
		2), ft_vector(fdl.x, (fur.y + fdl.y) / 2, (nf.y + nf.x) / 2)),
		.right_point = ft_vector_middle(ft_vector(nur.x, (ndl.y + nur.y) / 2,
		(nf.x + nf.y) / 2), ft_vector(fur.x, (fur.y + fdl.y) / 2, (nf.y + nf.x)
		/ 2)), .bottom_normal = fur}, ndl, nur, fdl));
}
