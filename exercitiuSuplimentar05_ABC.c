#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

struct Avion {
	char* model;
	int nrLocuri;
	int nrLocuriOcupate;
	float* preturiBilete;
};
typedef struct Avion Avion;

struct NodArboreBinar {
	Avion info;
	struct Nod* stanga;
	struct Nod* dreapta;
};
typedef struct NodArboreBinar Nod;

Avion initialziareAvion(const char* model, int nrLocuri, int nrLocuriOcupate, float* preturiBilete) {
	Avion avion;
	avion.model = (char*)malloc(sizeof(char) * (strlen(model) + 1));
	strcpy_s(avion.model, strlen(model) + 1, model);
	avion.nrLocuri = nrLocuri;
	avion.nrLocuriOcupate = nrLocuriOcupate;
	avion.preturiBilete = (float*)malloc(sizeof(float));
	for (int i = 0; i < nrLocuriOcupate; i++) {
		avion.preturiBilete[i] = preturiBilete[i];
	}
	return avion;
}

void afisareAvion(Avion avion) {
	printf("Avionul: %s\n", avion.model);
	printf("Numar Locuri: %d\n", avion.nrLocuri);
	printf("numar locuri ocupate: %d\n", avion.nrLocuriOcupate);
	for (int i = 0; i < avion.nrLocuriOcupate; i++) {
		printf("pret bilet pe loc %d: %.2f",i,avion.preturiBilete[i]);
		printf("\n");
	}
}

Avion citireAvionDinFisier(FILE* file) {
	char sep[4] = ", \n";
	char buffer[50];
	Avion avion;
	char* aux;
	fgets(buffer, 50, file);
	aux = strtok(buffer, sep);
	avion.model = (char*)malloc(sizeof(char) * (strlen(aux) + 1));
	strcpy_s(avion.model, strlen(aux) + 1, aux);
	aux = strtok(NULL, sep);
	avion.nrLocuri = atoi(aux);
	aux = strtok(NULL, sep);
	avion.nrLocuriOcupate = atoi(aux);
	avion.preturiBilete = (float*)malloc(sizeof(float)*avion.nrLocuriOcupate);
	for (int i = 0; i < avion.nrLocuriOcupate; i++) {
		aux = strtok(NULL, sep);
		avion.preturiBilete[i] = atof(aux);
	}
	printf("\n");
	return avion;
}

void afisareListaAvioaneFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	while (!feof(file)) {
		afisareAvion(citireAvionDinFisier(file));
	}
	fclose(file);
}

Nod* inserareAvionInArbore(Nod* radacina, Avion avion) {
	if (radacina) {
		if (radacina->info.nrLocuriOcupate > avion.nrLocuriOcupate) {
			radacina->stanga = inserareAvionInArbore(radacina->stanga, avion);
		}
		else
		{
			radacina->dreapta = inserareAvionInArbore(radacina->dreapta, avion);
		}
		return radacina;
	}
	else {
		Nod* nou = (Nod*)malloc(sizeof(Nod));
		nou->info = avion; //shallow copy
		nou->dreapta = NULL;
		nou->stanga = NULL;
		return nou;
	}
}

Nod* inserareAvionDinFisierInArbore(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* radacina = NULL;

	while (!feof(file)) {
		radacina = inserareAvionInArbore(radacina, citireAvionDinFisier(file));
	}
	fclose(file);
	return radacina;
}
//Inordine:
void afisareArboreSRD(Nod* arbore) {
	if (arbore) {
		afisareArboreSRD(arbore->stanga);
		afisareAvion(arbore->info);
		afisareArboreSRD(arbore->dreapta);
	}
}
//Preordine:
void afisareArboreRSD(Nod* arbore) {
	if (arbore) {
		afisareAvion(arbore->info);
		afisareArboreRSD(arbore->stanga);
		afisareArboreRSD(arbore->dreapta);
	}
}
//Postordine:
void afisareArboreSDR(Nod* arbore) {
	if (arbore) {
		afisareArboreSDR(arbore->stanga);
		afisareArboreSDR(arbore->dreapta);
		afisareAvion(arbore->info);
	}
}


Avion cautareAvionInArbore(Nod* radacina, int nrLocuri) {
	if (radacina) {
		if (nrLocuri == radacina->info.nrLocuri)
			return radacina->info;
	}
	else if (radacina->info.nrLocuri > nrLocuri) {
		return cautareAvionInArbore(radacina->stanga, nrLocuri);
	}
	else {
		return cautareAvionInArbore(radacina->dreapta, nrLocuri);
	}
	
	return initialziareAvion("", -1, -1, NULL);
}

void dezalocareArbore(Nod* arbore) {
	if (arbore) {
		if (arbore->stanga) {
			dezalocareArbore(arbore->stanga);
		}
		if (arbore->dreapta) {
			dezalocareArbore(arbore->dreapta);
		}
		free(arbore->info.model);
		free(arbore->info.preturiBilete);
		arbore->info.model = NULL;
		arbore->info.preturiBilete = NULL;
	}
}

void main() {
	float bilete[] = {10, 20, 30 };
	Avion avion = initialziareAvion("A330", 300, 3, bilete);
	afisareAvion(avion);
	afisareListaAvioaneFisier("avioane.txt");
	Nod* radacina = NULL;
	radacina = inserareAvionDinFisierInArbore("avioane.txt");
	Avion avionCautat = cautareAvionInArbore(radacina,330);
	afisareAvion(avionCautat);
	dezalocareArbore(radacina);

}
