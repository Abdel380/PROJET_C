#include <stdio.h>
#include "functions.h"
#include "area.h"
#include "pixel.h"
int main(){
    system("cls");
    LIST_SHAPE *lst = initialise_lst_shp();

    /*int x, y;
    printf("Veuillez choisir un point x y: ");
    scanf("%d %d", &x, &y);*/

    //int tab[3][2] = {1, 3, 7, 8, 9, 1};
    int ** tab = malloc(sizeof(int *)*3);
    for(int i = 0;i<3;i++){
        tab[i] = malloc(sizeof(int)*2);
    }

    tab[0][0] = 2;
    tab[0][1] = 3;
    tab[1][0] = 7;
    tab[1][1] = 8;
    tab[2][0] = 9;
    tab[2][1] = 1;


    //menu(lst);
    Pixel ** pix = (Pixel **) malloc( (2500) * sizeof(Pixel *));
    Area * area = create_area(50, 50);
    Point * point = create_point(10, 10);
    Square * square = create_square(point, 5);


    int  nb_pixels = 0;

    Shape * shp0 = create_point_shape(-1,-1, lst);
    Shape * shp = create_point_shape(4,7, lst);

    //Shape * shp2 = create_line_shape(0, 0, 49, 0, lst);
    //Shape * shp3 = create_line_shape(0, 1, 25,1, lst);
    //Shape * shp3 = create_circle_shape(25, 25, 15, lst);
    //Shape * shp4 = create_point_shape(25, 25, lst);
    Shape * shp4 = create_square_shape(5,5,10,lst);
    //Shape * shp5 = create_rectangle_shape(5,5,10,15,lst);

    //pixel_square(square, pix, )

    add_shape_to_area(area, shp0);

    //create_shape_to_pixel(shp2, &nb_pixels, pix, *lst);
    //create_shape_to_pixel(shp4, &nb_pixels, pix, *lst);
    create_shape_to_pixel(shp4, &nb_pixels, pix);
    //create_shape_to_pixel(shp4, &nb_pixels, pix);
    //create_shape_to_pixel(shp5, &nb_pixels, pix);





    draw_area(area, pix, nb_pixels);
    printf("======================= %d \n", nb_pixels);
    print_area(area);

    not_pixel_square(shp4, pix, &nb_pixels, area);

    printf("======================= %d \n", nb_pixels);

    print_area(area);


    for (int i=1; i < nb_pixels; i++){
        printf("i = %d  pixel : x=%d y=%d\n", i, pix[i]->px, pix[i]->py);
    }




    return 0;
}
