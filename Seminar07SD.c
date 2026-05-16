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

//creare structura pentru un nod dintr-o lista simplu inlantuita
typedef struct Nod Nod;
struct Nod 
{
	Masina info;
	Nod* next;
};

//facem chaining
// aceasta este un vector de liste
struct HashTable 
{
	int dim;
	Nod** tabela;
};
typedef struct HashTable HashTable;

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

void afisareListaMasini(Nod* head) {

	while (head) {
		afisareMasina(head->info);
		head = head->next;
	}
	
}

void adaugaMasinaInLista(Nod** head, Masina masinaNoua) {
	Nod* nodNou = (Nod*)malloc(sizeof(Nod));
	nodNou->info = masinaNoua;
	nodNou->next = NULL;
	if (*head) {
		Nod* aux = (*head);
		while (aux->next) {
			aux = aux->next;
		}

		aux->next = nodNou;
	}
	else {
		(*head) = nodNou;
	}

	//adauga la final in lista primita o noua masina pe care o primim ca parametru
}


HashTable initializareHashTable(int dimensiune) {
	HashTable ht;
	ht.dim = dimensiune;
	ht.tabela = (Nod**)malloc(dimensiune * sizeof(Nod*));
	for (int i = 0; i < dimensiune; i++) 
	{
		ht.tabela[i] = NULL;
	}
	return ht;
}

//de preferat sa folosim ceva unic, cum ar fi id-ul 
int calculeazaHash(int id, int dimensiune) {

	//return id % dimensiune;
	//daca inmultim cu un nr prim reducem sansele de coliziune
	id = id * 23 + 123;
	return id % dimensiune;

	// este calculat hash-ul in functie de dimensiunea tabelei si un atribut al masinii
}

void inserareMasinaInTabela(HashTable hash, Masina masina) {

	int poz = calculeazaHash(masina.id, hash.dim);
	if (hash.tabela[poz]) {
		//avem coliziune 
		adaugaMasinaInLista(&(hash.tabela[poz]), masina);
	}
	else {
		//nu avem coliziune
		adaugaMasinaInLista(&(hash.tabela[poz]), masina);
	}
	

	//CHAINING
	//este determinata pozitia si se realizeaza inserarea pe pozitia respectiva
}

HashTable citireMasiniDinFisier(const char* numeFisier) {

	HashTable hash = initializareHashTable(3); //hardcodam
	FILE* f = fopen(numeFisier, "r");
	if (!f) 
	{
		printf("nu exista!\n");
		return hash;
	}

	while (!feof(f)) 
	{
		Masina masina = citireMasinaDinFisier(f);
		inserareMasinaInTabela(hash, masina);
	}
	fclose(f);
	return hash;
}

void afisareTabelaDeMasini(HashTable ht) {
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			printf("Cluster : %d\n", i + 1);
			afisareListaMasini(ht.tabela[i]);
			printf("=============\n");
		}
	}
}

void dezalocareTabelaDeMasini(HashTable *ht) {
	if (ht->tabela != NULL) {
		for (int i = 0; i < ht->dim; i++) {
			Nod* temp = ht->tabela[i];
			while (temp) {
				Nod* nodSters = temp;
				temp = temp->next;
				free(nodSters->info.model);
				free(nodSters->info.numeSofer);
				free(nodSters);
			}
		}
		free(ht->tabela);
		ht->tabela = NULL;
	}

	ht->dim = 0;
}

float* calculeazaPreturiMediiPerClustere(HashTable ht, int* nrClustere) {
	*nrClustere = 0;
	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			(*nrClustere)++;
		}

	}
	float* vectorPreturi = malloc(sizeof(float) * (*nrClustere));
	int k = 0;

	for (int i = 0; i < ht.dim; i++) {
		if (ht.tabela[i] != NULL) {
			float suma = 0;
			int nrMasini = 0;
			Nod* temp = ht.tabela[i];
			while (temp) {
				suma += temp->info.pret;
				nrMasini++;
				temp = temp->next;
			}

			vectorPreturi[k++] = suma / nrMasini;
		}

	}

	return vectorPreturi;
}

//cautam in fiecare cluster la tabela de dispersie si calculam mai intai hash ul, iar cheia este id-ul masinii
Masina getMasinaDupaCheie(HashTable ht, int id) {
	Masina m;
	int hash = calculeazaHash(id, ht.dim);
	if (hash >= 0 && hash < ht.dim) {
		Nod* aux = ht.tabela[hash];
		while (aux)
		{
			if (aux->info.id == id) {
				m = aux->info;
				m.model = malloc(sizeof(char) * (strlen(aux->info.model)+1));
				strcpy(m.model, aux->info.model);
				m.numeSofer = malloc(sizeof(char) * (strlen(aux->info.numeSofer) + 1));
				strcpy(m.numeSofer, aux->info.numeSofer);
				break;
			}
			aux = aux->next;
		}
	}

	return m;
}

int main() {

	HashTable tabelaMea = citireMasiniDinFisier("Masini.txt");
	afisareTabelaDeMasini(tabelaMea);

	printf("Cautam dupa cheie\n");
	Masina m = getMasinaDupaCheie(tabelaMea, 5);
	afisareMasina(m);

	printf("Calculam pretul mediu pe fiecare cluster\n");
	int nrClustere;
	float* vectorPreturi = calculeazaPreturiMediiPerClustere(tabelaMea, &nrClustere);
	for (int i = 0; i < nrClustere; i++) {
		printf("Pretul mediu este: %f\n", i, vectorPreturi[i]);
	}

	free(vectorPreturi);
	dezalocareTabelaDeMasini(&tabelaMea);

	return 0;
}
