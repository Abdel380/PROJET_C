#include "area.h"

// Area functions
Area *create_area(unsigned int width, unsigned int height) {
    Area *area = NULL;
    area = malloc(sizeof(Area));
    area->height = height;
    area->width = width;
    area->mat = (BOOL **) malloc(sizeof(BOOL *) * height);
    area->nb_shape = 0;
    for (int i = 0; i < height; i++) {
        area->mat[i] = calloc(width, sizeof(BOOL));
    }
    return area;
}

void add_shape_to_area(Area *area, Shape *shape) {
    area->shapes[area->nb_shape] = shape;
    area->nb_shape++;
}

void clear_area(Area *area) {
    for (int i = 0; i < area->height; i++) {
        for (int j = 0; j < area->width; j++) {
            area->mat[i][j] = 0;
        }
    }
}

void erase_area(Area *area) {
    for (int i = 0; i < area->nb_shape; i++) {
        free(area->shapes[i]);
        area->shapes[i] = NULL;
    }
    area->nb_shape = 0;
}

void delete_area(Area *area) {
    erase_area(area);
    for (int i = 0; i < area->height; i++) {
        free(area->mat[i]);
        area->mat[i] = NULL;
    }

    free(area->mat);
    area->mat = NULL;
    free(area);
    area = NULL;

}

void draw_area(Area *area, Pixel **pixel, int nb_pixel) {
    for (int i = 0; i < nb_pixel; i++) {
        if ((pixel[i]->px >= 0) && (pixel[i]->px < area->width ) && (pixel[i]->py >= 0) && (pixel[i]->py < area->height)) {
            area->mat[pixel[i]->py][pixel[i]->px] = 1;
        }
    }
}

void print_area(Area *area) {
    for (int i = 0; i < area->height; i++) {
        for (int j = 0; j < area->width; j++) {
            if (area->mat[i][j] == 0) {
                printf(". ");
            }
            if (area->mat[i][j] == 1) {
                printf("\033[1;33m# \033[0m");
            }
        }
        printf("\n");
    }
}


//----------------------------------------------------------------
// Suppression
//----------------------------------------------------------------

void not_pixel_point(Shape *shape, Pixel **pixel, int *nb_pixels, Area *area) {
    Point *pt = (Point *) shape->ptrShape;
    int i = 0;
    while (pixel[i]->px != pt->pos_x || pixel[i]->py != pt->pos_y) {
        i++;
    }
    pixel[i]->px = 0;
    pixel[i]->py = 0;
    Pixel *temp;

    while (i < *nb_pixels) {
        temp = pixel[i];
        pixel[i] = pixel[i + 1];
        pixel[i + 1] = temp;
        i++;
    }
    *nb_pixels -= 1;

    clear_area(area);
    draw_area(area, pixel, *nb_pixels);
}


void not_pixel_line(Shape *shape, Pixel **pixel, int *nb_pixels, Area *area) {
    Line *line = (Line *) shape->ptrShape;
    int i = 0;
    while (pixel[i]->px != line->point1->pos_x || pixel[i]->py != line->point1->pos_y) {
        i++;
    }
    int cpt = 0;
    int j = i;
    while (pixel[i]->px != line->point2->pos_x || pixel[i]->py != line->point2->pos_y) {
        pixel[i]->px = -1;
        pixel[i]->py = -1;
        i++;
        cpt++;
    }

    // Suppression du dernier point de la ligne
    pixel[i]->px = -1;
    pixel[i]->py = -1;
    cpt++;

    Pixel *temp;
    while (j < *nb_pixels) {
        temp = pixel[j];
        pixel[j] = pixel[j + cpt];
        pixel[j + cpt] = temp;
        j++;
    }
    *nb_pixels -= cpt;

    clear_area(area);
    draw_area(area, pixel, *nb_pixels);
}


void not_pixel_circle(Shape *shape, Pixel **pixel, int *nb_pixels, Area *area) {
    Circle *circle = (Circle *) shape->ptrShape;
    int cpt = 0;
    int x = 0, k = 0;
    int y = circle->radius;
    int d = circle->radius - 1;

    while (y >= x) {
        for (int i = 0; i < *nb_pixels; i++) {
            if ((pixel[i]->px == circle->p->pos_x + x) && (pixel[i]->py == circle->p->pos_y + y)) {
                pixel[i]->px = -1;
                pixel[i]->py = -1;
                cpt++;
            }
            if ((pixel[i]->px == circle->p->pos_x + y) && (pixel[i]->py == circle->p->pos_y + x)) {
                pixel[i]->px = -1;
                pixel[i]->py = -1;
                cpt++;
            }
            if ((pixel[i]->px == circle->p->pos_x - x) && (pixel[i]->py == circle->p->pos_y + y)) {
                pixel[i]->px = -1;
                pixel[i]->py = -1;
                cpt++;
            }
            if ((pixel[i]->px == circle->p->pos_x - y) && (pixel[i]->py == circle->p->pos_y + x)) {
                pixel[i]->px = -1;
                pixel[i]->py = -1;
                cpt++;
            }
            if ((pixel[i]->px == circle->p->pos_x + x) && (pixel[i]->py == circle->p->pos_y - y)) {
                pixel[i]->px = -1;
                pixel[i]->py = -1;
                cpt++;
            }
            if ((pixel[i]->px == circle->p->pos_x + y) && (pixel[i]->py == circle->p->pos_y - x)) {
                pixel[i]->px = -1;
                pixel[i]->py = -1;
                cpt++;
            }
            if ((pixel[i]->px == circle->p->pos_x - x) && (pixel[i]->py == circle->p->pos_y - y)) {
                pixel[i]->px = -1;
                pixel[i]->py = -1;
                cpt++;
            }
            if ((pixel[i]->px == circle->p->pos_x - y) && (pixel[i]->py == circle->p->pos_y - x)) {
                pixel[i]->px = -1;
                pixel[i]->py = -1;
                cpt++;
            }
        }

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

    Pixel * temp;
    for (int i = 0; i < *nb_pixels; i++) {
        if ((pixel[i]->px == -1) && (pixel[i]->py == -1)){
            temp = pixel[i];
            pixel[i] = pixel[i + cpt];
            pixel[i + cpt] = temp;
        }
    }
    *nb_pixels -= cpt;
    clear_area(area);
    draw_area(area, pixel, *nb_pixels);;
}


void not_pixel_square(Shape *shape, Pixel **pixel, int *nb_pixels, Area *area) {
    Square *square = (Square *) shape->ptrShape;
    int i = 0;
    int cpt = 0;

    while (pixel[i]->px!= square->p->pos_x || pixel[i]->py != square->p->pos_y) {
        i++;

    }
    while (((pixel[i]->px!= square->p->pos_x) || (pixel[i]->py != square->p->pos_y + square->length))){
        pixel[i]->px = -1;
        pixel[i]->py = -1;
        i++;
        cpt++;
    }
    while (((pixel[i]->px!= square->p->pos_x + square->length) || (pixel[i]->py != square->p->pos_y + square->length))){
        pixel[i]->px = -1;
        pixel[i]->py = -1;
        i++;
        cpt++;
    }
    while (((pixel[i]->px!= square->p->pos_x + square->length) || (pixel[i]->py != square->p->pos_y))){
        pixel[i]->px = -1;
        pixel[i]->py = -1;
        i++;
        cpt++;
    }

    pixel[i]->px = -1;
    pixel[i]->py = -1;
    cpt++;

    Pixel * temp;
    for (int j = 0; j < *nb_pixels; j++) {
        if ((pixel[j]->px == -1) && (pixel[j]->py == -1)){
            temp = pixel[j];
            pixel[j] = pixel[j + cpt];
            pixel[j + cpt] = temp;
        }
    }

    *nb_pixels -= cpt;

    clear_area(area);
    draw_area(area, pixel, *nb_pixels);
}