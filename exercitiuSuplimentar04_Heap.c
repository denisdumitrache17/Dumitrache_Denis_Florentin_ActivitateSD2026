#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct StructuraMasina {
	int id;
	int nrUsi;
	float pret;
	char* model;
	char* numeSofer;
	unsigned char serie;
};
typedef struct StructuraMasina Masina;


struct Heap {
	Masina* vector;
	int lungime;
	int nrElemente;
};
typedef struct Heap Heap;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret = atof(strtok(NULL, sep));
	aux = strtok(NULL, sep);
	m1.model = malloc(strlen(aux) + 1);
	strcpy_s(m1.model, strlen(aux) + 1, aux);

	aux = strtok(NULL, sep);
	m1.numeSofer = malloc(strlen(aux) + 1);
	strcpy_s(m1.numeSofer, strlen(aux) + 1, aux);

	m1.serie = *strtok(NULL, sep);
	return m1;
}

void afisareMasina(Masina masina) {
	printf("Id: %d\n", masina.id);
	printf("Nr. usi : %d\n", masina.nrUsi);
	printf("Pret: %.2f\n", masina.pret);
	printf("Model: %s\n", masina.model);
	printf("Nume sofer: %s\n", masina.numeSofer);
	printf("Serie: %c\n\n", masina.serie);
}

Heap initializareHeap(int lungime) {
	//initializeaza heap-ul cu 0 elemente 
	//dar cu o lungime primita ca parametru
	Heap heap;
	heap.lungime = lungime;
	heap.nrElemente = 0;
	heap.vector = (Masina*)malloc(sizeof(Masina) * lungime);
	return heap;
}

// cum se face filtrarea -> ma pozitionez pe nodul pe care il filtrez si aplic urmatoarele formule:
// fiu stanga = 2*poz+1
// fiu dreapta = 2*poz+2
void filtreazaHeap(Heap heap, int pozitieNod) {
	
	int pozitieStanga = 2 * pozitieNod + 1;
	int pozitieDreapta = 2 * pozitieNod + 2;
	int pozitieMaxima = pozitieNod;

	if (heap.vector[pozitieMaxima].id < heap.vector[pozitieStanga].id) {
		pozitieMaxima = pozitieStanga;
	}

	if (heap.vector[pozitieMaxima].id < heap.vector[pozitieDreapta].id) {
		pozitieMaxima = pozitieDreapta;
	}
	if (pozitieMaxima != pozitieNod) {
		Masina  aux = heap.vector[pozitieMaxima];
		heap.vector[pozitieMaxima] = heap.vector[pozitieNod];
		heap.vector[pozitieNod] = aux;
		//if(2*pozitieMaxima+1 < heap.nrElemente-1)
		if (pozitieMaxima <= (heap.nrElemente - 2) / 2) {
			filtreazaHeap(heap, pozitieMaxima);
		}
	}
}

Heap citireHeapDeMasiniDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Heap heap = initializareHeap(10);
	while (!feof(file)) {
		heap.vector[heap.nrElemente++] = citireMasinaDinFisier(file);
	}
	fclose(file);
	for (int i = (heap.nrElemente - 2) / 2; i >= 0; i--) {
		filtreazaHeap(heap, i);
	}
	return heap;
}

void afisareHeap(Heap heap) {
	for (int i = 0; i < heap.nrElemente; i++) {
		afisareMasina(heap.vector[i]);
	}
}

void afiseazaHeapAscuns(Heap heap) {
	for (int i = heap.nrElemente; i < heap.lungime; i++) {
		afisareMasina(heap.vector[i]);
	}
}


Masina extrageMasina(Heap* heap) {
	if (heap->nrElemente > 0) {
		Masina aux = heap->vector[0];
		heap->vector[0] = heap->vector[heap->nrElemente - 1];
		heap->vector[heap->nrElemente - 1] = aux;
		heap->nrElemente--;
		for (int i = (heap->nrElemente - 2) / 2; i >= 0; i--) {
			filtreazaHeap(*heap, i);
		}
		return aux; // shallow copy
	}
}


void dezalocareHeap(Heap* heap) {
	for (int i = 0; i < heap->lungime; i++) {
		free(heap->vector[i].model);
		free(heap->vector[i].numeSofer);
	}
	free(heap->vector);
	heap->vector = NULL;
	heap->lungime = 0;
	heap->nrElemente = 0;
}

int main() {

	Heap heap = citireHeapDeMasiniDinFisier("masini.txt");
	afisareHeap(heap);
	printf("Masini extrase:");
	afisareMasina(extrageMasina(&heap));
	dezalocareHeap(&heap);
	return 0;
}
