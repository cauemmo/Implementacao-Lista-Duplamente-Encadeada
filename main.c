#include "gfx.h"
#include <stdio.h>
#include <stdlib.h>
//Cauê Mendonça Magela do Ó
//rgm : 43558

struct Lde{
    int valor;
    struct Lde *ant;
    struct Lde *prox;
};

void inserir(int x, struct Lde **ant, struct Lde **ptr,struct Lde **prox){
    struct Lde *pt = malloc(sizeof(struct Lde));
    pt->valor = x;
    pt->prox = *prox;
    pt->ant = *ant;
    *ptr = pt;
}

int main() {
    char string[50];
    int valor, resp, contr, width, height, textwidth, textheight;
    struct Lde *nocabeca = malloc(sizeof(struct Lde));
    struct Lde *ant;
    struct Lde *prox;
    struct Lde *ptlista = nocabeca;
    struct Lde *pt = NULL;
    nocabeca->prox = NULL;
    nocabeca->ant = NULL;
    gfx_init(1280, 720, "Lista duplamente encadeada");
    gfx_set_color(255, 255, 255);
    do{
        printf("1-Busca\n2-insercao\n3-remocao\n4-sair\n");
        scanf("%d", &resp);

        switch (resp) {
            case 1:
                printf("Informe o numero que sera buscado\n");
                scanf("%d", &valor);
                contr = 0;
                pt = ptlista->prox;
                while ((pt != ptlista) && (contr == 0)){
                    if(pt->valor == valor){
                        contr = 1;
                        printf("O valor estÃ¡ na lista\n");
                    }
                    pt = pt->prox;
                }
                if(contr == 0){
                    printf("O valor nao esta na lista\n");
                }
                break;
            case 2:
                printf("Informe o numero que sera inserido\n");
                scanf("%d", &valor);
                if(ptlista->prox == NULL){
                    inserir(valor, &ptlista, &pt, &ptlista);
                    ptlista->prox = pt;
                    ptlista->ant = pt;
                }else {
                    ant = ptlista->ant;
                    inserir(valor, &ant, &pt, &ptlista);
                    ant->prox = pt;
                    ptlista->ant = pt;
                }
                break;
            case 3:
                printf("Informe o numero que sera removido\n");
                scanf("%d", &valor);
                contr = 0;
                pt = ptlista->prox;
                while ((pt != ptlista) && (contr == 0)){
                    if(pt->valor == valor){
                        contr = 1;
                        ant = pt->ant;
                        prox = pt->prox;
                        ant->prox = prox;
                        prox->ant = ant;
                        printf("O valor retirado foi = %d\n", pt->valor);
                        free(pt);
                    }
                    pt = pt->prox;
                }
                if(contr == 0){
                    printf("O valor nao esta na lista\n");
                }
                break;
        }
        gfx_clear();
        width = 30;
        height = 0;
        pt = ptlista->prox;
        while ((pt != ptlista)){
            if(pt->prox != ptlista){
    	        sprintf(string, "%d <-> ", pt->valor);
    	    }else{
    	        sprintf(string, "%d ", pt->valor);
    	    }
    	    gfx_get_text_size(string, &textwidth, &textheight);
    	    if(width+textwidth <= 1280){
    	        gfx_text(width, height, string);
    	        width += textwidth;
    	    }else{
    	        height += textheight;
    	        gfx_text(10, height, string);
    	        width = textwidth + 10;
    	    }
            pt = pt->prox;
        }
        gfx_line(width, height+(textheight/2), width+10, height+5);
        gfx_line(width, height+(textheight/2), width+10, height+textheight-5);
        gfx_line(width, height+(textheight/2), width+30, height+(textheight/2));
        gfx_line(width+30, height+(textheight/2), width+30, height+textheight+10);
        gfx_line(width+30, height+textheight+10, 5, height+textheight+10);
        gfx_line(5, height+textheight+10, 5, textheight/2);
        gfx_line(5, textheight/2, 25, textheight/2);
        gfx_line(25, height+(textheight/2), 20, 5);
        gfx_line(25, height+(textheight/2), 20, textheight-5);
        gfx_paint();
    } while (resp != 4);
    pt = ptlista->prox;
    while ((pt != ptlista)){
        ant = pt;
        pt = pt->prox;
        free(ant);
    }
    free(ptlista);
    gfx_quit();
    return 0;
}
