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

void initializareListaNULL(ListaDubla* lista) {
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;
}

ListaDubla citireLDMasiniDinFisier(const char* numeFisier) {
	FILE* f = fopen(numeFisier, "r");
	ListaDubla lista;
	Masina masina;
	initializareListaNULL(&lista);

	while (!feof(f)) {
		masina = citireMasinaDinFisier(f);
		adaugaMasinaLaFinalInLista(&lista, masina);
	}
	fclose(f);
	return lista;

}

void dezalocareMasina(Nod* p) {
	if (p->info.model) {
		free(p->info.model);
	}
	if (p->info.numeSofer) {
		free(p->info.numeSofer);
	}
	free(p);
}

void dezalocareLDMasini(ListaDubla* lista) {
	Nod* p = lista->first;
	while (p) {
		Nod* aux = p;
		p = p->next;
		dezalocareMasina(aux);
	}
	initializareListaNULL(lista);
	
}

float calculeazaPretMediu(ListaDubla lista) {
	//calculeaza pretul mediu al masinilor din lista.
	float suma = 0;
	int contor = 0;
	Nod* p = lista.first;
	while (p) {
		suma = suma + p->info.pret;
		p = p->next;
		contor++;
	}
	if (contor) {
		return suma / contor;
	}

	return 0;
}

void stergeMasinaDupaID(ListaDubla* lista, int id) {
	if (lista->first == NULL) {
		return;
	}

	Nod* p = lista->first;
	while (p && p->info.id != id) {
		p = p->next;
	}

	if (p == NULL) {
		return;
	}

	if (p->prev == NULL) {
		lista->first = p->next;
		if (lista->first) {
			lista->first->prev = NULL;
		}
	}
	else {
		p->prev->next = p->next;
	}

	if (p->next) {
		p->next->prev = p->prev;
	}
	else
	{
		lista->last = p->prev;
	}
	dezalocareMasina(p);
	lista->nrNoduri--;
}

char* getNumeSoferMasinaScumpa(ListaDubla lista) {
	//cauta masina cea mai scumpa si 
	//returneaza numele soferului acestei maasini.
	Nod* p = lista.first;
	Nod* max = lista.first;
	while (p) {
		if (p->info.pret > max->info.pret) {
			max = p;
		}
		p = p->next;
	}
	char* nume = (char*)malloc(strlen(max->info.numeSofer) + 1);
	strcpy_s(nume, strlen(max->info.numeSofer) + 1, max->info.numeSofer);
	return nume;
}

int main() {

	ListaDubla lista = citireLDMasiniDinFisier("masini.txt");
	stergeMasinaDupaID(&lista, 1);
	stergeMasinaDupaID(&lista, 6);
	stergeMasinaDupaID(&lista, 10);
	afisareListaMasiniFinal(lista);
	printf("\npret mediu:%.2f\n", calculeazaPretMediu(lista));
	dezalocareLDMasini(&lista);
	return 0;
}
