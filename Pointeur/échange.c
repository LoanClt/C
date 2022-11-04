#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b);

int main()
{
    int a,b;
    a = 5;
    b = 3;
    printf("Avant echange: a=%d, b=%d \n", a, b);
    swap(&a, &b);
    printf("Apres echange: a=%d, b=%d \n",a ,b);
}

void swap(int* p_a, int* p_b){
    int p_mediateur = *p_a;
    *p_a = *p_b;
    *p_b = p_mediateur;
}
