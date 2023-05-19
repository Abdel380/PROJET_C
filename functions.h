#include <stdlib.h>
#include <stdio.h>
#ifndef PHOTOSHOP_FUNCTIONS_H
#define PHOTOSHOP_FUNCTIONS_H


extern unsigned int global_id;

typedef struct{
    int pos_x;
    int pos_y;
}Point;

typedef struct{
    Point *point1;
    Point *point2;
}Line;

typedef struct{
    Point *p;
    int length;
}Square;

typedef struct{
    Point *p;
    int width;
    int height;
}Rectangle;

typedef struct{
    Point *p;
    int radius;
}Circle;

typedef struct{
    int n;
    Point ** points; //tableau dynamique de Point*
}Polygon;

typedef enum {POINT, LINE, SQUARE, RECTANGLE, CIRCLE, POLYGON} SHAPE_TYPE;

typedef struct{
    int id; //identifiant unique de la forme
    SHAPE_TYPE  shapeType; //type de la forme pointé
    void *ptrShape; // pointeur sur n'importe quelle forme
}Shape;



// Fonctions et structure pour le point

Point *create_point(int px, int py);
void delete_point(Point *point);
void print_point(Point *p);

// Fonctions et structure pour la ligne

Line *create_line(Point *p1, Point *p2);
void delete_line(Line *line);
void print_line(Line *line);

//Fonctions pour le carré

Square *create_square(Point *point, int length);
void delete_square(Square *square);
void print_square(Square *square);

// Fonctions pour le rectangle

Rectangle *create_rectangle(Point *point, int width, int height);
void delete_rectangle(Rectangle * rectangle);
void print_rectangle(Rectangle * rectangle);



// Fonctions pour le Cercle

Circle *create_circle(Point *center, int radius);
void delete_circle(Circle *circle);
void print_circle(Circle *circle);

// Fonctions pour le polygone

Polygon *create_polygon(int n,int **coordonnees);
void delete_polygon(Polygon *polygon);
void print_polygon(Polygon *polygon);

// Fonctions shape



Shape *create_empty_shape(SHAPE_TYPE shape_type);
Shape *create_point_shape(int px, int py);
Shape *create_line_shape(int px1, int py1, int px2, int py2);
Shape *create_square_shape(int px, int py, int length);
Shape *create_rectangle_shape(int px, int py, int width, int height);
Shape *create_circle_shape(int px, int py, int radius);
Shape *create_polygon_shape(int **coordonnees, int n);
void delete_shape(Shape * shape);
void print_shape(Shape * shape);

unsigned int get_next_id();

// Utilities function
void display_head();



void display_array(int ***A);

void initialize_array(int ***A);

int** initialise_coord_mat(int n);

char * get_string_enum(Shape * shape);




//void menu(LIST_SHAPE * lst);

#endif //PHOTOSHOP_FUNCTIONS_H