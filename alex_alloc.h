#ifndef ALEX_ALLOC_H_
#define ALEX_ALLOC_H_
#endif
#include<stdio.h>
#include<stddef.h>


//Memoria de 4096 bytes
char memoria[4096];



//Esse struct representa um especie de header de um bloco alocado, 
//indicando seu tamanho, se esta alocado ou nao e caso haja um proximo bloco, aponta para o endereco do mesmo
//    _________________________________
//   |          |				      |
//   |Metadados |	    Dados		  | 
//   ----------------------------------
//   Exemplo de como o struct seria ao alocar memoria

typedef struct bloco {
	size_t tamanhoDoBloco;
	int livre;
	struct bloco* proximo;
}BlocoMetadados;



void inicializarMemoria();

void particionar(BlocoMetadados * bloco_bruto, size_t tamanhoNecessario);

void* alocar(size_t bytes);

void desfragmentarMemoria();

void liberar(void * ptr);

void printBlocos();
