#include "lista_duplamente_ligada.h"
#include "alex_alloc.h"

void inicializar_lista(ListaD** lista) {
	*lista = NULL;
}

void inserir(ListaD** lista,int entrada) {
	ListaD * temp = *lista;
	ListaD * novo = alocar(sizeof(ListaD));
	novo->n = entrada;

	if (temp == NULL) {
		*lista = novo;
		novo->anterior = NULL;
		novo->proximo = NULL;
		return;
	}
	else {
		while (temp->proximo != NULL) {
			temp = temp->proximo;
		}
		temp->proximo = novo;
		novo->anterior = temp;
		novo->proximo = NULL;
	}
}

void remover(ListaD** lista, int numero_remover) {
	ListaD * temp = *lista;
	
	if (temp == NULL) {
		printf("Lista vazia, nao ha o que remover!\n");
		return;
	}
	else {
		if (temp->n == numero_remover) {
			*lista = temp->proximo;
			if (temp->proximo != NULL) {
				temp->proximo->anterior = *lista;
			}
			liberar(temp);
			return;
		}
		while (temp->n != numero_remover && temp->proximo != NULL) {
			temp = temp->proximo;
		}
		if (temp->n == numero_remover) {
			temp->anterior->proximo = temp->proximo;
			if (temp->proximo != NULL) {
				temp->proximo->anterior = temp->anterior;
			}
			liberar(temp);
		}
		else {
			printf("O numero solicitado a se remover, nao estava na lista ligada\n");
		}
	}
}

void printLista(ListaD* lista) {
	while (lista != NULL) {
		printf("%d\n", lista->n);
		lista = lista->proximo;
	}
	return;
}