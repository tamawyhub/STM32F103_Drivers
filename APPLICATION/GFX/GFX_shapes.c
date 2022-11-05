#include <stddef.h>
#include "GFX_shapes.h"

int gfx_draw_point (GFX *gfx, const GFX_POINT *point){
	if (gfx==NULL || point == NULL) return GFX_FAILED;
	GFX_CURSOR cur = {point->x, (point->y) >> 3};
	char dummy = 1 << ((point->y) % 8);
	return GFX_update_buff(gfx,&dummy,&cur,1,GFX_UMETHOD_OR);
}
int gfx_draw_line_segment (GFX *gfx, const GFX_LINE_SEGMENT *line_segment){
	//see http://members.chello.at/~easyfilter/Bresenham.pdf (8.1 thick lines)
	if (gfx == NULL || line_segment == NULL) return GFX_FAILED;
	gfx_size_t x0 = line_segment->s_point.x,
		   x1 = line_segment->e_point.x,
		   y0 = line_segment->s_point.y,
		   y1 = line_segment->e_point.y,
		   wd = line_segment-> thickness;
	 int dx = x0 < x1 ? (x1-x0) : (x0-x1), sx = x0 < x1 ? 1 : -1;
 	 int dy = y0 < y1 ? (y1-y0) : (y0-y1), sy = y0 < y1 ? 1 : -1;
 	 int err = dx-dy, e2, x2, y2; /* error value e_xy */
	 double ed = (dx+dy == 0) ? 1 : (dx < dy ? dy + 0.428 *dx*dx/dy : dx + 0.428 * dy*dy/dx);
	 int comp = ed*(wd=(wd+1)/2);
	GFX_POINT pt;
	 for (; ; ) { /* pixel loop */
	 	if (gfx_draw_point(gfx,&(line_segment->s_point)) == GFX_FAILED) return GFX_FAILED;
	 	e2 = err; pt.x = x0, pt.y = y0;
	 	if (2*e2 >= -dx) { /* x step */
	 		for (e2 += dy, pt.y = y0; e2 < comp && (y1 != pt.y || dx > dy); e2 += dx)
	 			if ( (pt.y+=sy, gfx_draw_point(gfx, &pt)) == GFX_FAILED) return GFX_FAILED;
	 		if (x0 == x1) break;
	 		e2 = err; err -= dy; x0 += sx;
	 	}
	 	if (2*e2 <= dy) { /* y step */
	 		for (e2 = dx-e2; e2 < comp && (x1 != pt.x || dx < dy); e2 += dy)
	 			if ( (pt.x+=sx, gfx_draw_point(gfx, &pt)) == GFX_FAILED) return GFX_FAILED;
	 		if (y0 == y1) break;
	 		err += dx; y0 += sy;
	 	}
	 }
	 return GFX_OK;

}
int gfx_draw_poly (GFX *gfx, const GFX_POLY *poly){
	if (gfx == NULL || poly == NULL) return GFX_FAILED;
	if (poly->n_vertices == 0) return GFX_OK;
	GFX_POINT *vertices = poly->vertices;
	if (vertices == NULL) return GFX_FAILED;
	GFX_LINE_SEGMENT edge = {.s_point = vertices[0], .e_point = vertices[0], .thickness = poly->thickness};
	for (uint8_t i = 1; i < poly->n_vertices; i++){
		edge.e_point = vertices[i];
		if (gfx_draw_line_segment(gfx,&edge) == GFX_FAILED) return GFX_FAILED;
		edge.s_point = edge.e_point;
	}
	edge.e_point = vertices[0];
	return gfx_draw_line_segment(gfx,&edge);
}
int gfx_draw_circle (GFX *gfx, const GFX_CIRCLE *cir){
	if (gfx == NULL || cir == NULL) return GFX_FAILED;
	gfx_size_t r = cir->radius;
	gfx_size_t xm = cir->center.x, ym = cir->center.y;
	int x = -r, y = 0, err = 2-2*r; /* bottom left to top right */
	GFX_POINT pt;
	do {
		pt.x = xm-x, pt.y = ym + y;
		if (gfx_draw_point(gfx, &pt) == GFX_FAILED) return GFX_FAILED; /* I. Quadrant +x +y */
		pt.x = xm-y, pt.y = ym - x;
		if (gfx_draw_point(gfx, &pt) == GFX_FAILED) return GFX_FAILED; /* II. Quadrant -x +y */
		pt.x = xm+x, pt.y = ym - y;
		if (gfx_draw_point(gfx, &pt) == GFX_FAILED) return GFX_FAILED; /* III. Quadrant -x -y */
		pt.x = xm+y, pt.y = ym + x;
		if (gfx_draw_point(gfx, &pt) == GFX_FAILED) return GFX_FAILED; /* IV. Quadrant +x -y */
		r = err;
		if (r <= y) err += ++y*2+1; /* e_xy+e_y < 0 */
		if (r > x || err > y) /* e_xy+e_x > 0 or no 2nd y-step */
			err += ++x*2+1; /* -> x-step now */
	} while (x < 0);
	return GFX_OK;
}
