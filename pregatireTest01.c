#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Televizor {
	int id;
	int nrButoane;
	char* producator;
	char* serieProducator;
};
typedef struct Televizor Televizor;

struct Nod {
	Televizor info;
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

int contorID = 1;

void alocaMemorieVariabilaChar(char** variabila, char* memorieDeAlocat) {
	(*variabila) = malloc((strlen(memorieDeAlocat) + 1) * sizeof(char));
	strcpy_s(*variabila, (strlen(memorieDeAlocat) + 1), memorieDeAlocat);
}

struct Televizor initializareTelevizor(const char* producator, const char* serieProducator, int nrButoane) {
	struct Televizor s;
	s.id = contorID;
	contorID++;
	s.nrButoane = nrButoane;
	
	s.serieProducator =(char*)malloc(sizeof(char) * (strlen(serieProducator) + 1 ));
	strcpy_s(s.serieProducator,strlen(serieProducator)+1, serieProducator);
	//strcpy(s.serieProducator, serieProducator);

	s.producator = (char*)malloc(sizeof(char) * (strlen(producator) + 1));
	strcpy_s(s.producator, strlen(producator) + 1, producator); 
	
	return s;
}

void afisareTelevizor(struct Televizor s) {
	printf("______________________\n");
	printf("Afisare televizor ");
	printf("id %d:\n", s.id);
	printf("nr butoane:%d\n", s.nrButoane);
	printf("producator:%s\n", s.producator);
	printf("serie producator:%s\n", s.serieProducator);
	printf("______________________\n");
}

void modificaAtribut(struct Televizor* s, const char* producatorNou) {
	if (s->producator != NULL)
	{
		free(s->producator);
		s->producator = NULL;
	}

	s->producator = malloc((strlen(producatorNou) + 1) * sizeof(char));
	strcpy_s(s->producator, (strlen(producatorNou) + 1) * sizeof(char), producatorNou);
}

void dezalocare(struct Televizor *s) {
	if (s) {
		free(s->producator);
		free(s->serieProducator);
		s->producator = NULL;
		s->serieProducator = NULL;
	}
}

void dezalocareVector(Televizor** vector, int* nrElemente){
	for (int i = 0; i < (*nrElemente); i++)
	{
		if ((*vector)[i].producator != NULL) {
			free((*vector)[i].producator);
		}

		if ((*vector)[i].serieProducator != NULL) {
			free((*vector)[i].serieProducator);
		}
	}

	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void afisareVector(struct Televizor* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++)
	{
		afisareTelevizor(vector[i]);
	}
}

void copiazaElementStructura(Televizor* elementCopie, Televizor elementDeCopiat){
	elementCopie->id = contorID; contorID++;
	elementCopie->nrButoane = elementDeCopiat.nrButoane;
	//elementCopie->producator = malloc(sizeof(char) * (strlen(elementDeCopiat.producator) + 1));
	//strcpy_s(elementCopie->producator, strlen(elementDeCopiat.producator) + 1, elementDeCopiat.producator);
	//elementCopie->serieProducator = malloc(sizeof(char) * (strlen(elementDeCopiat.serieProducator) + 1));
	//strcpy_s(elementCopie->serieProducator, strlen(elementDeCopiat.serieProducator) + 1, elementDeCopiat.serieProducator);

	alocaMemorieVariabilaChar(&(elementCopie->producator), (elementDeCopiat.producator));
	alocaMemorieVariabilaChar(&(elementCopie->serieProducator), (elementDeCopiat.producator));
}

Televizor* copiazaPrimeleNElemente(Televizor* vector, int nrElemente, int nrElementeCopiate){
	Televizor* vectorNou = NULL;
	vectorNou =(Televizor*)malloc(sizeof(Televizor) * nrElementeCopiate);
	for (int i = 0; i < nrElementeCopiate; i++)
	{
		copiazaElementStructura(&(vectorNou[i]), vector[i]);
	}
	return vectorNou;
}

void copiazaAnumiteElemente(Televizor* vector, int nrElemente, const char* conditie, Televizor** vectorNou, int* elementeVectorNou) {
	
	if ((*vectorNou) != NULL) {
		dezalocareVector(vectorNou, *elementeVectorNou);
		*vectorNou = NULL;
	}
	
	for (int i = 0; i < nrElemente; i++) {
		if (!(strcmp(vector[i].producator, conditie))) {
			(*elementeVectorNou)++;
		}
	}

	*vectorNou = malloc(sizeof(Televizor) * (*elementeVectorNou));

	int j = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (!(strcmp(vector[i].producator, conditie))) {
			copiazaElementStructura(&((*vectorNou)[j]), vector[i]);
			j++;
		}
	}
}

void copiazaAnumiteElementeActualizat(Televizor* vector, int nrElemente, const char* conditie, Televizor** vectorNou, int* elementeVectorNou) {
	if ((*vectorNou) != NULL) {
		dezalocareVector(vectorNou, *elementeVectorNou);
		*vectorNou = NULL;
	}
	int j = 0;
	*vectorNou = malloc(sizeof(Televizor));
	for (int i = 0; i < nrElemente; i++) {
		if (!(strcmp(vector[i].producator, conditie))) {
			(*elementeVectorNou)++;
			*vectorNou = realloc(*vectorNou, sizeof(Televizor) * (*elementeVectorNou));
			copiazaElementStructura(&((*vectorNou)[j]), vector[i]);
			j++;
		}
	}
}

Televizor getPrimulElementConditionat(Televizor* vector, int nrElemente, const char* conditie){
	Televizor t;
	t.nrButoane = 1;
	if (vector != NULL) {
		for (int i = 0; i < nrElemente; i++) {
			if (!(strcmp(vector[i].serieProducator, conditie))) {
				copiazaElementStructura(&t, vector[i]);
				return t;
			}
		}
	}
	else
		return t;
}

void adaugaTelevizorInVector(Televizor** vector, int* nrElemente, Televizor televizorNou) {
	Televizor* auxiliar = malloc(sizeof(Televizor) * ((*nrElemente) + 1));
	for (int i = 0; i < (*nrElemente); i++) {
		auxiliar[i] = (*vector)[i]; // shallow copy pt a pastra zona de memorie din vectorul vechi;
	}
	auxiliar[(*nrElemente)] = televizorNou;
	free(*vector);
	(*vector) = auxiliar;
	(*nrElemente)++;
}

Televizor citireTelevizorFisier(FILE* file) {
	Televizor t;
	char buffer[100];
	char sep[4] = ",\n";
	fgets(buffer, 100, file);
	t.id = atoi(strtok(buffer, sep));
	t.nrButoane = atoi(strtok(NULL, sep));
	char* aux = strtok(NULL,sep);
	t.producator = malloc((strlen(aux) + 1)*sizeof(char));
	strcpy_s(t.producator, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	t.serieProducator = (char*)malloc(strlen(aux) + 1);
	strcpy_s(t.serieProducator, strlen(aux) + 1, aux);
	return t;
}

Televizor* citireVectorTelevizoareFisier(const char* numeFisier, int* nrTelevizoare) {
	FILE* file = fopen(numeFisier, "r");
	Televizor* vector = NULL;
	(*nrTelevizoare) = 0;
	while (!feof(file)){
		adaugaTelevizorInVector(&vector, nrTelevizoare, citireTelevizorFisier(file));
	}
	fclose(file);
	return vector;
}

void afisareListaMasiniDeLaInceput(ListaDubla lista) {
	Nod* p = lista.first;
	while (p) {
		afisareTelevizor(p->info);
		p = p->next;
	}
}

void afisareListaMasiniDeLaFinal(ListaDubla lista) {
	Nod* p = lista.last;
	while (p) {
		afisareTelevizor(p->info);
		p = p->prev;
	}
}

void adaugareTelevizorLaFinalulListei(ListaDubla* lista, Televizor televizorNou) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = televizorNou; // shallow copy -> la inserare sa nu stergem masina!
	nou->next = NULL;
	nou->prev = lista->last;
	if (lista->last) {
		lista->last->next = nou;
	}
	else {
		lista->first = nou;
	}
	lista->last = nou;
	lista->nrNoduri++;
}

void adaugareTelevizorLaInceputulListei(ListaDubla* lista, Televizor televizorNou) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = televizorNou; // shallow copy
	nou->prev = NULL;
	nou->next = lista->first;
	if (lista->first) {
		lista->first->prev = nou;
	}
	else {
		lista->last = nou;
	}
	lista->first = nou;
	lista->nrNoduri++;
}

void initializareListaDublaNULL(ListaDubla* lista) {
	lista->first = NULL;
	lista->last = NULL;
	lista->nrNoduri = 0;
}

void intializareTelevizorNULL(Televizor* televizor) {
	televizor->id = -1;
	televizor->nrButoane = -1;
	televizor->producator = NULL;
	televizor->serieProducator = NULL;
}

ListaDubla* citireListaDublaDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	ListaDubla lista;
	initializareListaDublaNULL(&lista);
	while (!feof(file)) {
		adaugareTelevizorLaInceputulListei(&lista, citireTelevizorFisier(file));
		lista.nrNoduri++;
	}
	fclose(file);
	return &lista;
}

void dezalocareListaDubla(ListaDubla* lista) {
	Nod* p = lista->first;
	while (p) {
		Nod* aux = p;
		p = p->next;
		if (&(aux->info)) {
			dezalocare(&(aux->info));
		}
		free(aux);
	}
	initializareListaDublaNULL(lista);
}

void dezalocareListaSimpla(Nod** cap) {
	Nod* p = *cap;
	while (p)
	{
		Nod* temp = p;
		p = p->next;
		dezalocare(&(p->info));

		free(temp);
	}
	*cap = NULL;
}

int calculeazaNrButoaneMediu(ListaDubla lista) {
	if (lista.nrNoduri)
	{
		int suma = 0;
		Nod* p = lista.first;
		while (p) {
			suma += p->info.nrButoane;
			p = p->next;
		}
		return suma / (lista.nrNoduri);
	}
	return 0;
}


void stergereTelevizorDupaId(ListaDubla* lista, int id) {
	if (lista->first == NULL) {
		return;
	}
	Nod* p = lista->first;
	while (p && p->info.id!=id){
		p = p->next;
	}
	if (p == NULL) {
		return;
	}
	//avem ce sterge:
	if (p->prev == NULL) {  // verificam daca suntem pe primul nod, daca se indeplineste conditia if-ului inseamna ca suntem pe primul nod
		lista->first = p->next;
		if (lista->first) {  //am mutat lista de first pe al doilea element(am gasit id-ul pe primul element), daca exista al doilea element si lista nu a fost cu un singur element il transformam pe lista de first in primul element
			lista->first->prev = NULL;
		}
	}
	else {
		p->prev->next = p->next; // daca nu se indeplineste conditia din if-ul de mai sus, inseamna ca nodul nostru pe care il stergem nu este primul din lista
	}
	if (p->next) { // verificam daca exista urmatorul nod, iar daca exista inseamna ca nu suntem la finalul listei si ii dam urmatorului nod adresa nodului din urma (cel din fata noastra primeste adresa celui din spate, pt ca cel pe care suntem acum o sa dispara)
		p->next->prev = p->prev; 
	}
	else { //daca nu exista urmatorul nod, marcam nodul din spate ca fiind finalul listei
		lista->last = p->prev;
	}
	dezalocare(&(p->info));
	free(p);
	lista->nrNoduri--;
}


Televizor getNodTelevizorCuCeleMaiMulteButoane(ListaDubla lista) {
	Nod* p = lista.first;
	Nod* max = lista.first;
	char* serieTelevizor = NULL;
	alocaMemorieVariabilaChar(&serieTelevizor, (lista.first->info.serieProducator));
	while (p) {
		if ((p->info.nrButoane) > (max->info.nrButoane)) {
			copiazaElementStructura(&(max->info), p->info);
		}
		p = p->next;
	}
	return max->info;
}

//structura HashTable
struct HashTable {
	int dimensiune;
	Nod** tabela;
};
typedef struct HashTable HashTable;


void afisareListaSimpla(Nod* cap) {
	while (cap) {
		afisareTelevizor(cap->info);
		cap = cap->next;
	}
}

void adaugaTelevizorInListaSimpla(Nod* cap, Televizor televizor) {
	Nod* p = cap;
	while (p->next) {
		p = p->next;
	}
	Nod* nou = malloc(sizeof(Nod));
	nou->info = televizor;
	nou->next = NULL;
	p->next = nou;
}

HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.dimensiune = dimensiune;
	ht.tabela = (Nod**)malloc(dimensiune * sizeof(Nod*));
	for (int i = 0; i < dimensiune; i++) {
		ht.tabela[i] = NULL;
	}
	return ht;
}

int calculeazaHash(const char* producator, int dimensiune) {
	int suma = 0;
	for (int i = 0; i < strlen(producator); i++) {
		suma += producator[i];
	}
	return suma % dimensiune;
}

void creareNodTabela(HashTable hash, Televizor televizor, int pozitie) {
	if (pozitie >= 0 && pozitie < hash.dimensiune) {
		hash.tabela[pozitie] = (Nod*)malloc(sizeof(Nod));
		hash.tabela[pozitie]->info = televizor;
		hash.tabela[pozitie]->next = NULL;
	}
}

void inserareTelevizorInTabela(HashTable hash, Televizor televizor) {
	int pozitie = calculeazaHash(televizor.producator, hash.dimensiune);
	if (hash.tabela[pozitie] == NULL) {
		creareNodTabela(hash, televizor, pozitie);
	}
	else {
		adaugaTelevizorInListaSimpla(hash.tabela[pozitie], televizor);
	}
}

HashTable citireaMasinilorDinFisierHashTable(const char* numeFisier,int dimensiune) {
	HashTable hash = initializareHashTable(dimensiune);
	FILE* file = fopen("televizoare.txt", "r");
	while (!feof(file)) {
		Televizor televizor = citireTelevizorFisier(file);
		inserareTelevizorInTabela(hash, televizor);
	}
	fclose(file);
	return hash;
}

void afisareTabelaDeMasini(HashTable ht) {
	for (int i = 0; i < ht.dimensiune; i++)
	{
		if (ht.tabela[i] != NULL) {
			printf("\nTelevizoarele de pe pozitia %d sunt:\n", i);
			afisareListaSimpla(ht.tabela[i]);
		}
		else {
			printf("\nPe pozitia %d, nu sunt televizoare \n", i);
		}
	}
}

void dezalocareHashTable(HashTable* ht) {
	for (int i = 0; i < ht->dimensiune; i++) {
		dezalocareListaSimpla(&(ht->tabela[i]));
	}
	free(ht->tabela);
	ht->tabela = NULL;
	ht->dimensiune = 0;
}

float calculeazaNrMediuButoaneLista(Nod* cap) {
	Nod* p = cap;
	float medieButoane = 0;
	int contor = 0;
	while (p) {
		medieButoane += p->info.nrButoane;
		contor++;
		p = p->next;
	}
	if (contor > 0) {
		return medieButoane / contor;
	}
	return 0;
}

float* calculeazaNrButoaneMediiPerCluster(HashTable ht, int* nrClustere) {
	float* butoane = NULL;
	*nrClustere = 0;
	for (int i = 0; i < ht.dimensiune; i++) {
		if (ht.tabela[i] != NULL) {
			(*nrClustere)++;
		}
	}

	butoane = malloc(sizeof(float) * (*nrClustere));
	int contor = 0;
	for (int i = 0; i < ht.dimensiune; i++) {
		if (ht.tabela[i]) {
			butoane[contor] = calculeazaNrMediuButoaneLista(ht.tabela[i]);
			contor++;
		}
	}

	return butoane;
}

Televizor getTelevizorDinLista(Nod* cap, const char* producator) {
	while (cap && strcmp(cap->info.producator,producator)) {
		cap = cap->next;
	}

	if (cap) {
		Televizor t;
		intializareTelevizorNULL(&t);
		copiazaElementStructura(&t, cap->info);
		return t;
	}

	return;
}

Televizor getTelevizorDupaProducator(HashTable ht, const char* producator) {
	Televizor t;
	intializareTelevizorNULL(&t);
	int pozitie = calculeazaHash(producator, ht.dimensiune);
	if (pozitie >= 0 && pozitie < ht.dimensiune) {
		return getTelevizorDinLista(ht.tabela[pozitie], producator);
	}

	return t;
}

int main() {
	struct Televizor t = initializareTelevizor("Samsung", "SMA31234", 4);;
	afisareTelevizor(t);
	modificaAtribut(&t, "LG");
	afisareTelevizor(t);

	Televizor* televizoare = NULL;
	int nrTelevizoare = 3;
	televizoare = (struct Televizor*)malloc(sizeof(Televizor) * nrTelevizoare);
	televizoare[0] = initializareTelevizor("Sony", "SN33821", 12);
	televizoare[1] = initializareTelevizor("Samsung", "SG33217", 3);
	televizoare[2] = initializareTelevizor("Samsung", "HZN22351", 7);
	int primeleNElemente = 2;
	
	printf("\nAfisare vector televizoare:\n");
	afisareVector(televizoare,nrTelevizoare);

	printf("\nAfisare vector televizoare copiat cu primele n:\n");
	Televizor* vectorNou = copiazaPrimeleNElemente(televizoare, nrTelevizoare, primeleNElemente);
	afisareVector(vectorNou,primeleNElemente);
	Televizor* doarSamsung = NULL;
	int elementeSamsung = 0;

	/*
	printf("\n\n\nanumite elemente!!:\n");
	copiazaAnumiteElemente(televizoare, nrTelevizoare, "Samsung", &doarSamsung, &elementeSamsung);
	afisareVector(vectorNou, elementeSamsung);
	*/

	printf("\n");
	printf("\n\n\nanumite elemente mai interesant!!:\n");
	copiazaAnumiteElementeActualizat(televizoare, nrTelevizoare, "Samsung", &doarSamsung, &elementeSamsung);
	afisareVector(doarSamsung,elementeSamsung);
	printf("\n");

	Televizor t2 = getPrimulElementConditionat(televizoare, nrTelevizoare, "SG33217");
	afisareTelevizor(t2);
	
	printf("\nvector televizoare fisier:\n");
	int nrNouTelevizoare = 0;
	Televizor* vectorFisier = citireVectorTelevizoareFisier("televizoare.txt", &nrNouTelevizoare);
	afisareVector(vectorFisier, nrNouTelevizoare);
	printf("\n");

	printf("\n Lista dublu inlantuita:\n");
	ListaDubla lista = (*citireListaDublaDinFisier("televizoare.txt"));
	afisareListaMasiniDeLaFinal(lista);
	
	printf("\nnumar mediu de butoane:%d\n", calculeazaNrButoaneMediu(lista));

	afisareListaMasiniDeLaInceput(lista);
	stergereTelevizorDupaId(&lista, 2);
	afisareListaMasiniDeLaInceput(lista);

	printf("\n");
	printf("\nTelevizor complet:\n");
	afisareTelevizor(getNodTelevizorCuCeleMaiMulteButoane(lista));

	HashTable ht = citireaMasinilorDinFisierHashTable("televizoare.txt",5);
	afisareTabelaDeMasini(ht);
	int nrClustere = 0;
	float* butoane = calculeazaNrButoaneMediiPerCluster(ht, &nrClustere);
	for (int i = 0; i < nrClustere; i++) {
		printf("\n%.2f  \n", butoane[i]);
	}
	printf("\nTelevizor dupa producator:\n");
	Televizor t3 = getTelevizorDupaProducator(ht, "LG");
	afisareTelevizor(t3);
	dezalocare(&t3);

	dezalocareHashTable(&ht);
	dezalocare(&t);
	dezalocareVector(&televizoare, &nrTelevizoare);
	dezalocareVector(&vectorNou, &primeleNElemente);
	dezalocareVector(&doarSamsung, &elementeSamsung);
	dezalocareVector(&vectorFisier, &nrNouTelevizoare);
	dezalocare(&t2);
	dezalocareListaDubla(&lista);
	return 0;
}
