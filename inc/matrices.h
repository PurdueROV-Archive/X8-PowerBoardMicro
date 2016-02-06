/*
Created by Jason King
January 2016
Purdue IEEE ROV
*/

#ifndef __MATRICES__H
#define __MATRICES__H
typedef struct{
    int x;
    int y;
    int z;
}vect3;

typedef struct{
    vect3 L;
    vect3 R;
}vect6;

typedef struct{
    vect6 t1;
    vect6 t2;
    vect6 t3;
    vect6 t4;
    vect6 t5;
    vect6 t6;
    vect6 t7;
    vect6 t8;
}matrix8_6;

typedef struct{
    vect3 t1;
    vect3 t2;
    vect3 t3;
    vect3 t4;
    vect3 t5;
    vect3 t6;
    vect3 t7;
    vect3 t8;
}matrix8_3;

typedef struct{
    vect3 a;
    vect3 b;
    vect3 c;
}matrix3_3;

typedef struct{
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
}vect8;

typedef struct{
    int a;
    int b;
}vect2;

typedef struct{
    vect2 one;
    vect2 two;
}matrix2_2;

vect3 cross(vect3, vect3);
int dot(vect3, vect3);
int dot6(vect6, vect6);
int dot2(vect2, vect2);

vect3 add(vect3, vect3);
vect6 add6(vect6, vect6);

vect3 sub(vect3, vect3);
vect6 sub6(vect6, vect6);

vect3 mul(vect3, int);
vect6 mul6(vect6, int);

vect3 div(vect3, int);
vect6 div6(vect6, int);

vect3 vect3Make(int, int, int);
vect6 vect6Make(int, int, int, int, int, int);
vect2 vect2Make(int, int);

vect8 matMul_86x61(matrix8_6, vect6);
vect3 matMul_33x31(matrix3_3,vect3);
matrix2_2 matMul_22x22(matrix2_2, matrix2_2);

matrix2_2 invert2_2(matrix2_2);

#endif