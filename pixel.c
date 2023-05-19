#include "pixel.h"

// Pixel functions
Pixel *create_pixel(int px, int py) {
    Pixel *pixel = (Pixel *) malloc(sizeof(Pixel));
    pixel->px = px;
    pixel->py = py;
    return pixel;
}

void delete_pixel(Pixel *pixel) {
    free(pixel);
    pixel = NULL;
}

void pixel_point(Point * point, Pixel **pixel, int *nb_pixels) {
    pixel[*nb_pixels] = create_pixel(point->pos_x, point->pos_y);
    *nb_pixels += 1;
}

void pixel_line(Line *line, Pixel **pixel, int *nb_pixels) {

    int xa = line->point1->pos_x, ya = line->point1->pos_y;
    int xb = line->point2->pos_x, yb = line->point2->pos_y;

    // si jamais xb < xa on inverse les deux droites
    if (xb < xa) {
        int temp = xb;
        xb = xa;
        xa = temp;
        temp = yb;
        yb = ya;
        ya = temp;
    }


    int dx = xb- xa;
    int dy = yb - ya;
    int dmin = min(dx, abs(dy));
    int dmax = max(dx, abs(dy));

    int nb_segs = (dmin + 1);
    int long_seg = (dmax + 1) / (dmin + 1);
    int segments[nb_segs];

    int restants = (dmax + 1) % (dmin + 1);
    int *cumuls = (int *) malloc(sizeof(int) * nb_segs);
    int x = xa;
    int y = ya;
    for (int i = 0; i < nb_segs; i++) {
        segments[i] = long_seg;
    }

    cumuls[0] = 0;
    for (int i = 1; i < nb_segs; i++) {
        cumuls[i] = (((i + 1) * restants) % (dmin + 1) < (i * restants) % (dmin + 1));
        segments[i] = segments[i] + cumuls[i];
    }

    Point * temp_point = create_point(x,y);
    pixel_point(temp_point,pixel,nb_pixels);

    if (dy < 0) {
        if (dx > abs(dy)) {
            for (int i = 0; i < nb_segs; i++) {
                for (int j = 0; j < segments[i]; j++) {

                    temp_point->pos_x= x++;
                    temp_point->pos_y = y;
                    pixel_point(temp_point,pixel,nb_pixels);

                    // pixel[*nb_pixels] = create_pixel(x++, y);

                }
                y--;
            }
        } else {
            for (int i = 0; i < nb_segs; i++) {
                for (int j = 0; j < segments[i]; j++) {
                    temp_point->pos_x = x;
                    temp_point->pos_y= y--;
                    pixel_point(temp_point,pixel,nb_pixels);
                    //pixel[*nb_pixels] = create_pixel(x, y--);

                }
                x++;
            }
        }
    } else {
        if (dx > abs(dy)) {
            for (int i = 0; i < nb_segs; i++) {
                for (int j = 0; j < segments[i]; j++) {
                    temp_point->pos_x = x++;
                    temp_point->pos_y = y;
                    pixel_point(temp_point,pixel,nb_pixels);
                    //pixel[*nb_pixels] = create_pixel(x++, y);

                }
                y++;
            }
        } else {
            for (int i = 0; i < nb_segs; i++) {
                for (int j = 0; j < segments[i]; j++) {
                    temp_point->pos_x = x;
                    temp_point->pos_y = y++;
                    pixel_point(temp_point,pixel,nb_pixels);
                    //pixel[*nb_pixels] = create_pixel(x, y++);

                }
                x++;
            }
        }
    }

}

// Utilities functions
int abs_val(int dy) {
    if (dy < 0) {
        return -dy;

    } else {
        return dy;
    }
}

int min(int dx, int dy) {
    dy = abs_val(dy);
    if (dy > dx) {
        return dx;
    } else {
        return dy;
    }
}

int max(int dx, int dy) {
    dy = abs_val(dy);
    if (dy > dx) {
        return dy;
    } else {
        return dx;
    }
}


void pixel_circle(Circle *circle, Pixel **pixel, int *nb_pixels) {

    int x = 0, k = 0;
    int y = circle->radius;
    int d = circle->radius - 1;
    int perimeter = circle->radius * 3.14;


    while (y >= x) {
        pixel[(*nb_pixels)++] = create_pixel(circle->p->pos_x + x, circle->p->pos_y + y);

        pixel[(*nb_pixels)++] = create_pixel(circle->p->pos_x + y, circle->p->pos_y + x);

        pixel[(*nb_pixels)++] = create_pixel(circle->p->pos_x - x, circle->p->pos_y + y);

        pixel[(*nb_pixels)++] = create_pixel(circle->p->pos_x - y, circle->p->pos_y + x);

        pixel[(*nb_pixels)++] = create_pixel(circle->p->pos_x + x, circle->p->pos_y - y);

        pixel[(*nb_pixels)++] = create_pixel(circle->p->pos_x + y, circle->p->pos_y - x);

        pixel[(*nb_pixels)++] = create_pixel(circle->p->pos_x - x, circle->p->pos_y - y);

        pixel[(*nb_pixels)++] = create_pixel(circle->p->pos_x - y, circle->p->pos_y - x);


        if (d >= 2 * x) {
            d -= 2 * x + 1;
            x++;
        } else if (d * (circle->radius - y)) {
            d += 2 * y - 1;
            y--;
        } else {
            d += 2 * (y - x - 1);
            y--;
            x++;
        }
    }
}


void pixel_square(Square *square, Pixel **pixel, int *nb_pixels) {
    Point *p1 = create_point(square->p->pos_x, square->p->pos_y);
    Point *p2 = create_point(square->p->pos_x + square->length, square->p->pos_y);
    Point *p3 = create_point(square->p->pos_x, square->p->pos_y + square->length);
    Point *p4 = create_point(square->p->pos_x + square->length, square->p->pos_y + square->length);


    Line *line1 = create_line(p1, p2);
    Line *line2 = create_line(p1, p3);
    Line *line3 = create_line(p3, p4);
    Line *line4 = create_line(p4, p2);

    pixel_line(line1, pixel, nb_pixels);
    pixel_line(line2, pixel, nb_pixels);
    pixel_line(line3, pixel, nb_pixels);
    pixel_line(line4, pixel, nb_pixels);

}

void pixel_rectangle(Rectangle *rectangle, Pixel **pixel, int *nb_pixels) {
    Point *p1 = create_point(rectangle->p->pos_x, rectangle->p->pos_y);
    Point *p2 = create_point(rectangle->p->pos_x + rectangle->width, rectangle->p->pos_y);
    Point *p3 = create_point(rectangle->p->pos_x, rectangle->p->pos_y + rectangle->height);
    Point *p4 = create_point(rectangle->p->pos_x + rectangle->width, rectangle->p->pos_y + rectangle->height);


    Line *line1 = create_line(p1, p2);
    Line *line2 = create_line(p1, p3);
    Line *line3 = create_line(p3, p4);
    Line *line4 = create_line(p4, p2);

    pixel_line(line1, pixel, nb_pixels);
    pixel_line(line2, pixel, nb_pixels);
    pixel_line(line3, pixel, nb_pixels);
    pixel_line(line4, pixel, nb_pixels);

}


void pixel_polygon(Polygon *polygon, Pixel **pixel, int *nb_pixels) {
    Line *line = NULL;
    int nb_cote = polygon->n, i = 0;
    Point *p1 = NULL, *p2 = NULL;

    while (nb_cote > 1) {
        p1 = polygon->points[i++];
        p2 = polygon->points[i];
        line = create_line(p1, p2);
        pixel_line(line, pixel, nb_pixels);
        nb_cote -= 2;
    }
}

void create_shape_to_pixel(Shape *shape, int *nb_pixels, Pixel **pixel) {
    switch (shape->shapeType) {
        case POINT:

            pixel_point(shape->ptrShape, pixel, nb_pixels);
            break;

        case LINE:
            pixel_line(shape->ptrShape, pixel, nb_pixels);
            break;
        case SQUARE:
            pixel_square(shape->ptrShape, pixel, nb_pixels);
            break;
        case RECTANGLE :
            pixel_rectangle(shape->ptrShape, pixel, nb_pixels);
            break;
        case CIRCLE:
            pixel_circle(shape->ptrShape, pixel, nb_pixels);
            break;
        case POLYGON:
            pixel_polygon(shape->ptrShape, pixel, nb_pixels);
            break;
    }

}