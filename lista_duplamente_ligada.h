#include <stdio.h>
#include <stdlib.h>


typedef struct lista_duplamente_ligada {
	int n;
	struct lista_duplamente_ligada * anterior;
	struct lista_duplamente_ligada * proximo;
}ListaD;

void inicializar_lista();

void inserir();

void remover();

void printLista(ListaD * d);