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

struct Nod {
	Masina info;
	struct Nod* next;
	struct Nod* prev;
};
typedef struct Nod Nod;

struct ListaDubla {
	Nod* first;
	Nod* last;
	int nrNoduri;
};
typedef struct ListaDubla ListaDubla;

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

void afisareListaMasini(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afisareMasina(p->info);
		p = p->next;
	}
}

void afisareListaMasiniFinal(ListaDubla lista) {
	Nod* p = lista.last;
	while (p) {
		afisareMasina(p->info);
		p = p->prev;
	}
}

void adaugaMasinaLaFinalInLista(ListaDubla* lista, Masina masinaNoua) {
	//adauga la final in lista primita o noua masina pe care o primim ca parametru
	Nod* p = (Nod*)malloc(sizeof(Nod));
	p->info = masinaNoua; // shallow copy
	p->next = NULL;
	p->prev = lista->last;
	if (lista->last)
	{
		lista->last->next = p;
	}
	else
	{
		lista->first = p;
	}
	lista->last = p;
}

void adaugaLaInceputInLista(ListaDubla* lista, Masina masinaNoua) {
	Nod* p = (Nod*)malloc(sizeof(Nod));
	p->info = masinaNoua;
	p->prev = NULL;
	p->next = lista->first;
	if (lista->first)
	{
		lista->first->prev = p;
	}
	else
	{
		lista->last = p;
	}
	lista->first = p;
}

void* citireLDMasiniDinFisier(const char* numeFisier) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaDinFisier()
	//ATENTIE - la final inchidem fisierul/stream-ul
	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	Masina masina;
	lista.first = NULL;
	lista.last = NULL;
	lista.nrNoduri = 0;

	while (!feof(f)) {
		masina = citireMasinaDinFisier(f);
		adaugaMasinaLaFinalInLista(&lista, masina);
	}
	fclose(f);
	return &lista;

}

void dezalocareLDMasini(ListaDubla* lista) {
	//sunt dezalocate toate masinile si lista dublu inlantuita de elemente
	Nod* aux;
	if (lista->first) {
		if (lista->first->next) {
			aux = lista->first->next;
			while (aux) {
				free(aux->prev->info.model);
				free(aux->prev->info.numeSofer);
				free(aux->prev);
				aux = aux->next;
			}
			free(lista->last->info.model);
			free(lista->last->info.numeSofer);
			free(lista->last);
		}
		else
		{
			free((lista->first->info).model);
			free((lista->first->info).numeSofer);
			free(lista->first);
		}
		lista->first = NULL;
		lista->last = NULL;
	}
}

float calculeazaPretMediu(/*lista de masini*/) {
	//calculeaza pretul mediu al masinilor din lista.
	return 0;
}

void stergeMasinaDupaID(/*lista masini*/ int id) {
	//sterge masina cu id-ul primit.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
}

char* getNumeSoferMasinaScumpa(/*lista dublu inlantuita*/) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	return NULL;
}

int main() {

	ListaDubla* lista = citireLDMasiniDinFisier("masini.txt");
	afisareListaMasiniFinal(*lista);
	dezalocareLDMasini(&lista);
	return 0;
}
