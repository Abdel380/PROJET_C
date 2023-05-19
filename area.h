//
// Created by Alexandre on 14/04/2023.
//

#ifndef PHOTOSHOP_AREA_H
#define PHOTOSHOP_AREA_H

#include "functions.h"
#include "pixel.h"

#define SHAPE_MAX 100 // Nombre max de formes
#define BOOL int

struct area{
    unsigned int width; // Nombre de pixels en largeur ou nombre de colonnes (axe y)
    unsigned int height; // Nombre de pixels en hauteur ou nombre de lignes (axe x)
    BOOL **mat; // Matrice des pixels de taille (width * height)
    Shape* shapes[SHAPE_MAX]; // Tableau des formes;
    int nb_shape; // Nombre de formes dans le tableau shapes (taille logique)

};

typedef  struct area Area;


Area* create_area(unsigned int width, unsigned int height);
void add_shape_to_area(Area* area, Shape* shape);
void clear_area(Area* area);
void erase_area(Area* area);
void delete_area(Area* area);
void draw_area(Area* area, Pixel ** pix, int nb_pixels);
void print_area(Area* area);

void not_pixel_point(Shape *shape, Pixel **pixel, int *nb_pixels, Area * area);
void not_pixel_line(Shape *shape, Pixel **pixel, int *nb_pixels, Area * area);
void not_pixel_circle(Shape *shape, Pixel **pixel, int *nb_pixels, Area * area);
void not_pixel_square(Shape *shape, Pixel **pixel, int *nb_pixels, Area *area);

#endif //PHOTOSHOP_AREA_H
