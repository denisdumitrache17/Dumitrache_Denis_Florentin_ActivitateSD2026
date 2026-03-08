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

void afisareMasina(Masina masina) {
	printf("id:%d\n", masina.id);
	printf("nr usi:%d\n", masina.nrUsi);
	printf("pret:%.2f\n", masina.pret);
	printf("model:%s\n", masina.model);
	printf("sofer:%s\n", masina.numeSofer);
	printf("serie:%c\n", masina.serie);
	printf("\n");
}

void afisareVectorMasini(Masina* masini, int nrMasini) {
	for (int i = 0; i < nrMasini; i++)
	{
		afisareMasina(masini[i]);
	}
}

void adaugaMasinaInVector(Masina** masini, int * nrMasini, Masina masinaNoua) {
	(*nrMasini)++;
	Masina* tempMasina = malloc(sizeof(Masina) * (*nrMasini));
	for (int i = 0; i < (*nrMasini)-1; i++) {
		tempMasina[i] = (*masini)[i]; //shallow copy
	}
	tempMasina[(*nrMasini) - 1] = masinaNoua;
	free(*masini);
	*masini = tempMasina;
}

Masina citireMasinaFisier(FILE* file) {
	
	char linie[55];
	fgets(linie, 55, file);
	char delim[3] = ",\n";
	Masina masina;
	masina.id = atoi(strtok(linie, delim));
	masina.nrUsi = atoi(strtok(NULL, delim));
	masina.pret = atof(strtok(NULL, delim));
	
	char* model = strtok(NULL, delim);
	masina.model = malloc((strlen(model) + 1) * sizeof(char));
	strcpy_s(masina.model, (strlen(model) + 1) * sizeof(char), model);
	
	//stergem cu free doar elemente pe care noi le alocam
	
	model = strtok(NULL, delim);
	masina.numeSofer = malloc((strlen(model) + 1) * sizeof(char));
	strcpy_s(masina.numeSofer, (strlen(model) + 1) * sizeof(char), model);
	
	model = strtok(NULL, delim);
	masina.serie = model[0];
	
	return masina;

}

Masina* citireVectorMasiniFisier(const char* numeFisier, int* nrMasiniCitite) {
	//functia primeste numele fisierului, il deschide si citeste toate masinile din fisier
	//prin apelul repetat al functiei citireMasinaFisier()
	//numarul de masini este determinat prin numarul de citiri din fisier
	//ATENTIE - la final inchidem fisierul/stream-ul
	Masina* masini = NULL;
	FILE* file = fopen(numeFisier, "r");
	*nrMasiniCitite = 0;
	while (!feof(file)){
		adaugaMasinaInVector(&masini, nrMasiniCitite, citireMasinaFisier(file));
	}
	fclose(file);
	return masini;
}

void dezalocareVectorMasini(Masina** vector, int* nrMasini) {
	//este dezalocat intreg vectorul de masini

}

int main() {

	FILE* file = fopen("masini.txt", "r");
	Masina masina = citireMasinaFisier(file);
	Masina* masini = NULL;
	afisareMasina(masina);
	int nrMasiniCitite=0;
	masini = citireVectorMasiniFisier("masini.txt", &nrMasiniCitite);
	afisareVectorMasini(&masini, &nrMasiniCitite);
	return 0;
}
