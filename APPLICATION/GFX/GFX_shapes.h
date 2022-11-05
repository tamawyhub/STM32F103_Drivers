#ifndef _GFX_SHAPES_H_
#define _GFX_SHAPES_H_

#include "GFX_bitmap.h"

typedef struct gfx_point_t {
	gfx_size_t x;
	gfx_size_t y;
} GFX_POINT;

typedef struct gfx_line_segment_t {
	GFX_POINT s_point;
	GFX_POINT e_point;
	gfx_size_t thickness;
} GFX_LINE_SEGMENT;

typedef struct gfx_poly_t {
	uint8_t n_vertices;
	GFX_POINT *vertices;
	gfx_size_t thickness;
} GFX_POLY;

typedef struct gfx_circle_t {
	GFX_POINT center;
	gfx_size_t radius;
	gfx_size_t thickness;
} GFX_CIRCLE;

int gfx_draw_point (GFX *gfx, const GFX_POINT *point);
int gfx_draw_line_segment (GFX *gfx, const GFX_LINE_SEGMENT *line_segment);
int gfx_draw_poly (GFX *gfx, const GFX_POLY *poly);
int gfx_draw_circle (GFX *gfx, const GFX_CIRCLE *cir);
	
#endif
