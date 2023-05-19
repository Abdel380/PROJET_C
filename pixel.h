#ifndef PHOTOSHOP_PIXEL_H
#define PHOTOSHOP_PIXEL_H

#include "functions.h"


typedef  struct area Area;


struct pixel {
    int px;
    int py;
};

typedef struct pixel Pixel;

Pixel *create_pixel(int px, int py);
void delete_pixel(Pixel * pixel);

void pixel_point(Point *point, Pixel **pixel, int *nb_pixels);
void pixel_line(Line* line,Pixel** pixel, int* nb_pixels);
void pixel_circle(Circle *circle, Pixel **pixel, int *nb_pixels);
void pixel_rectangle(Rectangle *rectangle, Pixel **pixel, int *nb_pixel);
void pixel_square(Square *square, Pixel **pixel, int *nb_pixels);
void pixel_polygon(Polygon *polygon, Pixel **pixel, int *nb_pixels);
int min(int dx,int dy);
int max(int dx, int dy);
int abs_val(int dy);

void create_shape_to_pixel(Shape * shape, int* nb_pixels,Pixel** pixel);





#endif //PHOTOSHOP_PIXEL_H