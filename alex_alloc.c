#include "alex_alloc.h"

BlocoMetadados * blocos =(void*)memoria;

void inicializarMemoria() {
	blocos->tamanhoDoBloco = 4096 - sizeof(BlocoMetadados);
	blocos->livre = 1;
	blocos->proximo = NULL;
}

void particionar(BlocoMetadados * bloco_bruto, size_t tamanhoNecessario) {
	//printf("BEFORE TEMP APONTANDO PARA %p\n", bloco_bruto);
	BlocoMetadados * temp = (void*)((char*)(bloco_bruto) + sizeof(BlocoMetadados) + tamanhoNecessario);
	//printf("TEMP APONTANDO PARA %p\n", temp);
	temp->tamanhoDoBloco = (bloco_bruto->tamanhoDoBloco) - sizeof(BlocoMetadados) - tamanhoNecessario;
	temp->livre = 1;
	temp->proximo = bloco_bruto->proximo;
	bloco_bruto->tamanhoDoBloco = tamanhoNecessario;
	bloco_bruto->livre = 0;
	bloco_bruto->proximo = temp;
	//printf("Bloco particionado!\n ");
}

void* alocar(size_t bytes) {
	//variaveis utilizadas para percorrer os blocos de metadados
	BlocoMetadados  *atual,*anterior;
	
	//variavel utilizada para percorrer os blocos da memoria
	void *saida;

	//inicializa a lista caso ainda nao esteja inicializada
	if (!(blocos->tamanhoDoBloco)) {
		inicializarMemoria();
		blocos = memoria;
		printf("------------------------------------------------------------------------------------------------\n");
		printf("Memoria inicializada com %d bytes\n",blocos->tamanhoDoBloco);
		printf("Endereco inicial: %p     Endereco final: %p\n", memoria, (memoria + 4096));
		printf("Tamanho do bloco de metadados %d  memoria:%p  blocos:%p\n", sizeof(BlocoMetadados),memoria,blocos);
		printf("------------------------------------------------------------------------------------------------\n");
	}

	atual = blocos;

	while ((atual->proximo != NULL) && ((atual->tamanhoDoBloco < bytes) || (atual->livre == 0))) {
		//anterior = atual;
		//printf("Bloco verificado! Tamanho:%d  Livre:%d\n", atual->tamanhoDoBloco, atual->livre);
		atual = atual->proximo;		
	}

	//Caso em que o bloco encontrado tem o tamanho exato de alocacao
	if ((atual->tamanhoDoBloco) == bytes) {
		atual->livre = 0;
		saida = (void *)(++atual);
		printf("Bloco de memoria exato alocado!\n");
		return saida;
	}

	else if ((atual->tamanhoDoBloco) > (bytes + sizeof(BlocoMetadados)) ){
		particionar(atual, bytes);
		saida = (void *)(++atual);
		printf("Bloco de memoria particionado alocado!\n");
		return saida;
	}
	else {
		saida = NULL;
		printf("Nao foi possivel alocar a quantidade de memoria solicitada\n");
		return saida;
	}
}

void desfragmentarMemoria() {
	BlocoMetadados *atual,*anterior;
	atual = blocos;
	int passo = 0;
	while ((atual !=NULL) && (atual->proximo) != NULL) {

		if ((atual->livre) && (atual->proximo->livre)) {
			atual->tamanhoDoBloco += sizeof(BlocoMetadados) + atual->proximo->tamanhoDoBloco;
			atual->proximo = atual->proximo->proximo;
			for (int k = 0; k < passo;k++) {
				printf("	");
			}
			printf("Dois blocos fragmentados se uniram em um!\n");
		}
		else {
			anterior = atual;
			atual = atual->proximo;
		}
		passo++;
	}
	//printBlocos();
}

void liberar(void * lixo) {
	if ((lixo >= ((void*)memoria)) && (lixo <= (void*)(memoria + 4096))) {
		BlocoMetadados *atual = lixo;
		printf("Liberando %p\n",(void*)(atual-1));
		--atual;//volta para o bloco de metadados
		atual->livre = 1;
		desfragmentarMemoria();
	}
	else {
		printf("Nao e possivel desalocar memoria(%p) fora do escopo de alocacao pre-definido (%p ~ %p)\n",lixo,memoria,memoria+4096);
	}
}

void printBlocos() {
	BlocoMetadados * percorrer = blocos;
	int index= 0;
	printf("\n\n\n");
	printf("--------Blocos em memoria--------\n");
	while (percorrer != NULL) {
		printf(" Bloco %d\n Tamanho %d bytes\n Livre? %d\n Endereco do inicio do bloco   %p\n Endereco do inicio da memoria %p \n\n", index, percorrer->tamanhoDoBloco, percorrer->livre, percorrer,percorrer+1);
		index++;
		percorrer = percorrer->proximo;
	}
	printf("---------------------------------\n\n\n\n");

}