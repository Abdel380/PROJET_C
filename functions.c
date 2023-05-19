#include "functions.h"

extern unsigned int global_id;


// Point functions
Point *create_point(int px, int py){
    Point *point = NULL;
    point = (Point *) malloc(sizeof(Point));
    point->pos_x = px;
    point->pos_y = py;
    return point;


}
void delete_point(Point *point){
    free(point);
    point = NULL;

}
void print_point(Point *p){
    printf("POINT %d %d",p->pos_x,p->pos_y);
}

//Line functions
Line *create_line(Point *p1, Point *p2){
    Line *line = NULL;
    line = (Line*) malloc(sizeof(Line));
    line -> point1 = p1;
    line -> point2 = p2;
    return line;
}
void delete_line(Line *line){
    free(line->point1);
    line->point1 = NULL;
    free(line->point2);
    line->point2 = NULL;
    line = NULL;
    free(line);

}
void print_line(Line *line){
    printf("LINE %d %d %d %d",line->point1->pos_x,line->point1->pos_y,
           line->point2->pos_x,line->point2->pos_x);
}


// Square functions
Square *create_square(Point *point, int length){
    Square *square = NULL;
    square = (Square*) malloc(sizeof(Square));
    square -> p = point;
    square -> length = length;
    return square;
}
void delete_square(Square *square){
    free(square->p);
    square ->p = NULL;
    free(square);
    square = NULL;
}
void print_square(Square *square){
    int len = square -> length;
    printf("SQUARE p1[%d %d] p2[%d %d] p3[%d %d] p4[%d %d]",square->p->pos_x,square->p->pos_y,square->p->pos_x+len,square->p->pos_y,
           square->p->pos_x,square->p->pos_y+len,square->p->pos_x+len,square->p->pos_y+len);
}


//Rectangle Functions


Rectangle *create_rectangle(Point *point, int width, int height){
    Rectangle  * rectangle = NULL;
    rectangle = (Rectangle*) malloc(sizeof(Rectangle));
    rectangle -> p = point ;
    rectangle -> width = width;
    rectangle -> height = height;
    return rectangle;


}
void delete_rectangle(Rectangle *rectangle){
    free(rectangle->p);
    rectangle->p = NULL;
    rectangle = NULL;
    free(rectangle);

}
void print_rectangle(Rectangle *rectangle){
    int width = rectangle -> width;
    int height = rectangle -> height;
    printf("Rectangle p1[%d %d] p2[%d %d] p3[%d %d] p4[%d %d]",rectangle->p->pos_x,rectangle->p->pos_y,rectangle->p->pos_x+width,rectangle->p->pos_y,
           rectangle->p->pos_x,rectangle->p->pos_y+height,rectangle->p->pos_x+width,rectangle->p->pos_y+height);

}


//Circle Functions


Circle *create_circle(Point *center, int radius){
    Circle *circle = NULL;
    circle = (Circle *) malloc(sizeof(Circle));
    circle -> p = center;
    circle -> radius = radius;
    return circle;

}
void delete_circle(Circle *circle){
    free(circle->p);
    circle->p = NULL;
    circle = NULL;
    free(circle);

}
void print_circle(Circle *circle){
    printf("center[%d %d] radius:%d ",circle->p->pos_x,circle->p->pos_x,circle->radius);
}


// Polygon Functions


Polygon *create_polygon(int n,int **coordonnees){
    Polygon *p = malloc(sizeof(Polygon));
    p->n = n+1;
    p->points = malloc(sizeof(Point*)*(n+1));
    for (int i=0; i<(n+1); i++){
        p->points[i] = malloc(sizeof(Point));
        p->points[i] = create_point(coordonnees[i][0],coordonnees[i][1]);
    }
    p->points[n] = p->points[0];
    return p;
}



void delete_polygon(Polygon *polygon){
    for(int i=0;i>polygon->n;i++){
        free(polygon->points);
        polygon->points[i] = NULL;
    }
    free(polygon);
    polygon = NULL;
}
void print_polygon(Polygon *polygon){
    for(int i = 0;i<polygon->n;i++){
        printf("p%d[%d %d]",i+1,polygon->points[i]->pos_x,polygon->points[i]->pos_y);
    }
}


//SHAPE functions

Shape *create_empty_shape(SHAPE_TYPE shape_type){
    Shape *shp = (Shape*) malloc(sizeof(Shape));
    shp -> ptrShape = NULL;
    shp-> id = get_next_id();
    shp ->shapeType = shape_type;
    return shp;
}
Shape *create_point_shape(int px, int py, LIST_SHAPE *lst){
    Shape * shp = create_empty_shape(POINT);
    shp ->ptrShape = create_point(px,py);
    add_shape(shp,lst);
    return shp;
}
Shape *create_line_shape(int px1, int py1, int px2, int py2, LIST_SHAPE *lst){
    Shape * shp = create_empty_shape(LINE);
    Point *p1,*p2;
    p1 = create_point(px1,py1);
    p2 = create_point(px2,py2);
    shp -> ptrShape = create_line(p1,p2);
    add_shape(shp, lst);
    return shp;
}
Shape *create_square_shape(int px, int py, int length, LIST_SHAPE *lst){
    Shape *shp = create_empty_shape(SQUARE);
    Point *p = create_point(px,py);
    Square  * s = create_square(p,length);
    shp -> ptrShape = s;
    add_shape(shp,lst);
    return shp;
}
Shape *create_rectangle_shape(int px, int py, int width, int height,LIST_SHAPE* lst){
    Shape *shp = create_empty_shape(RECTANGLE);
    Point *p = create_point(px,py);
    shp -> ptrShape = create_rectangle(p,width,height);
    add_shape(shp,lst);
    return shp;
}
Shape *create_circle_shape(int px, int py, int radius,LIST_SHAPE* lst){
    Shape *shp = create_empty_shape(CIRCLE);
    Point *p = create_point(px,py);
    shp -> ptrShape = create_circle(p,radius);
    add_shape(shp,lst);
    return shp;
}
Shape *create_polygon_shape(int **coordonnees, int n,LIST_SHAPE* lst){
    if(n%2!=0){
        printf("nombre de coord invalide");
        return NULL;
    }
    Shape *shp = create_empty_shape(POLYGON);
    shp -> ptrShape = create_polygon(n/2,coordonnees);
    add_shape(shp, lst);
    return shp;

}
void delete_shape(Shape * shape){
    free(shape->ptrShape);
    shape->ptrShape =NULL;
    shape = NULL;
    free(shape);


}
void print_shape(Shape * shape){
    printf("Id : %d \tShape:%s ",shape->id, get_string_enum(shape));
    switch (shape->shapeType) {
        case 0:
            print_point(shape->ptrShape);
            break;

        case 1:
            print_line(shape->ptrShape);
            break;
        case 2:
            print_square(shape->ptrShape);
            break;
        case 3 :
            print_rectangle(shape->ptrShape);
            break;
        case 4:
            print_circle(shape->ptrShape);
            break;
        case 5:
            print_polygon(shape->ptrShape);
            break;
    }
    printf("\n");
}

unsigned int get_next_id(){
    return ++global_id;
}

// Utilities function
void display_head(){}



void display_array(int ***A){
    for (int i = 0; i<30; i++){
        for (int j = 0; j<115; j++){
            if ((*A)[i][j] == 0){
                printf(".");}
        }
        printf("\n");
    }
}
char * get_string_enum(Shape * shape){
    switch(shape->shapeType){
        case 0:
            return "POINT";
            break;
        case 1:
            return "LINE";
            break;
        case 2:
            return "SQUARE";
            break;
        case 3:
            return "RECTANGLE";
            break;
        case 4:
            return "CIRCLE";
            break;
        case 5:
            return "POLYGON";
            break;
    }
}


/*void initialize_array(int ***A)
{
    *A = calloc(30,sizeof(int*));

    for (int i=0; i<30; i++)
    {
        (*A)[i] = calloc(115,sizeof(int));
    }
}
*/
int** initialise_coord_mat(int n){
    int **tab = calloc(n+1 , sizeof(int*));
    for (int i=0; i<n+1; i++){
        tab[i] = malloc(2 * sizeof(int));
        for (int j=0; j<2; j++){
            tab[i] = calloc(2,sizeof(int));
        }
    }
    return tab;

}

LIST_SHAPE * initialise_lst_shp(){

    LIST_SHAPE *lst_shp = (LIST_SHAPE *) malloc(sizeof(LIST_SHAPE));
    lst_shp->lst_shape = (Shape *) malloc(sizeof(Shape));
    lst_shp->nb =0;
    return lst_shp;
}

void add_shape(Shape * shape, LIST_SHAPE * lst){
    lst->nb += 1;
    lst->lst_shape = (Shape *) realloc(lst->lst_shape, lst->nb * sizeof(Shape));
    lst->lst_shape[lst->nb-1] = *shape;
}

void menu(LIST_SHAPE * lst){
    int choice_1 = 0;
    int choice_2 = 0;
    int choice_3 = 0;
    do{
        printf("Veuillez choisir une action :\n");
        printf("1 - Ajouter une forme \n2 - Afficher la liste des formes\n3 - Arreter\nChoix : ");
        scanf("%d", &choice_1);
        if (choice_1 == 1){
            printf("1- Ajouter un point\n2- Ajouter une ligne\n3- Ajouter un cercle\n4- Ajouter un carre\n5- Ajouter un rectangle\n6- Ajouter un polygone\n7- Revenir au menu precedent\nChoix :");
            scanf("%d", &choice_2);
            if (choice_2 == 1){
                int x, y;
                printf("Entrez les coordonnees de votre point :\n");
                scanf("%d %d", &x, &y);
                Shape * point = create_point_shape(x, y, lst);
            }
            else if(choice_2==2) {
                int x1, x2, y1, y2;
                printf("Saisir les informations de la ligne :\n");
                printf("Saisir le premier point x1 y1 : \n");
                scanf("%d %d", &x1, &y1);
                printf("Saisir le deuxieme point x2 y2 : \n");
                scanf("%d/%d", &x2, &y2);
                Shape *line = create_line_shape(x1, y1, x2, y2, lst);
            }
            else if(choice_2==3){
                int x, y, radius;
                printf("Saisir les informations du cercle :\n");
                printf("Saisir les coordonnes du centre du cercle sous format x y: \n");
                scanf("%d %d", &x, &y);
                printf("Entrez le rayon de votre cerle :\n");
                scanf("%d", &radius);
                Shape * cercle = create_circle_shape(x, y, radius, lst);
            }
            else if(choice_2==4){
                int x, y, length;
                printf("Saisir les information sur le carre : \n");
                printf("Saisir les coordonnes x y du carre : \n");
                scanf("%d %d", &x, &y);
                printf("Saisir la longueur du carre :\n");
                scanf("%d", &length);
                Shape * square = create_square_shape(x, y, length, lst);
            }
            else if(choice_2 == 5){
                int x ,y, width, height;
                printf("Saisir les information sur le rectangle : \n");
                printf("Saisir les coordonnes x y du rectangle : ");
                scanf("%d %d", &x, &y);
                printf("Saisir la longueur du rectangle : \n");
                scanf("%d",&width);
                printf("Saisir la hauteur du rectangle :\n");
                scanf("%d",&height);
                Shape * rectangle = create_rectangle_shape(x, y, width, height, lst);
            }
            else if(choice_2 == 6){
                int nb_points;
                int ** coord = NULL;
                printf("Saisir le nombre de point de votre polygone :\n");
                scanf("%d", &nb_points);
                coord = initialise_coord_mat(nb_points);
                printf("Veuiller rentrer les differentes coordonnees\n");
                for(int i = 0;i<nb_points;i++){
                    printf("x,y:\n");
                    scanf("%d %d",&coord[i][0],&coord[i][1]);
                }
                Shape * polygone = create_polygon_shape(coord, nb_points*2, lst);
            }

        }
        else if (choice_1 == 2){
            if(lst -> nb == 0){
                printf("Pas de formes creees veuillez en creer\n");
            }
            else{
                for(int i = 0; i<lst -> nb; i++){
                    print_shape(&lst -> lst_shape[i]);
                }
            }
        }

    }while(choice_1 != 3);
}