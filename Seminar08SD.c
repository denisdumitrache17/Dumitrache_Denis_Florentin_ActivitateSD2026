#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//trebuie sa folositi fisierul masini.txt
//sau va creati un alt fisier cu alte date

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
	struct Nod* stanga;
	struct Nod* dreapta;
};
typedef struct Nod Nod;

Masina citireMasinaDinFisier(FILE* file) {
	char buffer[100];
	char sep[3] = ",\n";
	fgets(buffer, 100, file);
	char* aux;
	Masina m1;
	aux = strtok(buffer, sep);
	m1.id = atoi(aux);
	m1.nrUsi = atoi(strtok(NULL, sep));
	m1.pret= atof(strtok(NULL, sep));
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


void adaugaMasinaInArbore(Nod** radacina, Masina masinaNoua) {
	if (*radacina == NULL) {
		Nod* nou = malloc(sizeof(Nod));
		nou->info = masinaNoua;
		nou->dreapta = NULL;
		nou->stanga = NULL;
		*radacina = nou;
		return;
	}
	
	if (masinaNoua.id < (*radacina)->info.id) {
		adaugaMasinaInArbore(&(*radacina)->stanga, masinaNoua);
	}
	else
	{
			adaugaMasinaInArbore(&(*radacina)->dreapta, masinaNoua);
	}
}

void* citireArboreDeMasiniDinFisier(const char* numeFisier) {
	FILE* file = fopen(numeFisier, "r");
	Nod* radacina = NULL;
	while (!feof(file)) {
		adaugaMasinaInArbore(&radacina, citireMasinaDinFisier(file));
	}
	fclose(file);
	return radacina;
}

void afisareMasiniDinArbore(Nod* radacina) {
	//afiseaza toate elemente de tip masina din arborele creat
	//prin apelarea functiei afisareMasina()
	//parcurgerea arborelui poate fi realizata in TREI moduri
	//folositi toate cele TREI moduri de parcurgere
	if (radacina) {
		afisareMasiniDinArbore(radacina->stanga);
		afisareMasina(radacina->info);
		afisareMasiniDinArbore(radacina->dreapta);
	}
}

void afisareMasinaPostOrdine(Nod* radacina) {
	if (radacina) {
		afisareMasinaPostOrdine(radacina->stanga);
		afisareMasinaPostOrdine(radacina->dreapta);
		afisareMasina(radacina->info);
	}
}

void afisareMasinaPreOrdine(Nod* radacina) {
	if (radacina) {
		afisareMasina(radacina->info);
		afisareMasinaPreOrdine(radacina->stanga);
		afisareMasinaPreOrdine(radacina->dreapta);
	}
}

void dezalocareArboreDeMasini(Nod** radacina) {
	//sunt dezalocate toate masinile si arborele de elemente
	if (*radacina) {
		dezalocareArboreDeMasini(&((*radacina)->stanga));
		dezalocareArboreDeMasini(&((*radacina)->stanga));

			free((*radacina)->info.model);
			free((*radacina)->info.numeSofer);
			free(*radacina);

			*radacina = NULL;
	}
}

Masina getMasinaByID(Nod* radacina, int id) {
	Masina m;
	
	if (radacina) {
		if (radacina->info.id == id) {
			m = radacina->info;
			m.model = malloc(sizeof(char) * (strlen(radacina->info.model) + 1));
			strcpy_s(m.model, strlen(radacina->info.model) + 1, radacina->info.model);

			m.numeSofer = malloc(sizeof(char) * (strlen(radacina->info.numeSofer)+1));
			strcpy_s(m.numeSofer, strlen(radacina->info.numeSofer) + 1, radacina->info.numeSofer);
			return m;
		}
		else {
			if (radacina->info.id <= id) {
				m = getMasinaByID(radacina->dreapta, id);
			}
			else {
				m = getMasinaByID(radacina->stanga, id);
			}
		}
	}
	else {
		m.id = -1;
	}
	return m;
}

int determinaNumarNoduri(Nod* radacina) {
	if (radacina) {
		int nrNoduriStanga = determinaNumarNoduri(radacina->stanga);
		int nrNoduriDreapta = determinaNumarNoduri(radacina->dreapta);
		return nrNoduriStanga + nrNoduriDreapta + 1;
	}
	return 0;
}

int calculeazaMaxim(int a, int b) {
	if (a > b) {
		return a;
	}
	else
	{
		return b;
	}
}

int calculeazaInaltimeArbore(Nod* radacina) {
	if (radacina==NULL) {
		return -1;
	}
	else {
		return 1 + max(calculeazaInaltimeArbore(radacina->dreapta), calculeazaInaltimeArbore(radacina->stanga));
	}
}

float calculeazaPretTotal(Nod* radacina) {
	if (radacina == NULL) {
		return 0;
	}
	else {
		float nrStanga = calculeazaPretTotal(radacina->stanga);
		float nrDreapta = calculeazaPretTotal(radacina->dreapta);
		return radacina->info.pret + nrStanga + nrDreapta;
	}
}

float calculeazaPretulMasinilorUnuiSofer(/*arbore de masini*/ const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	return 0;
}

int main() {

	Nod* arbore = citireArboreDeMasiniDinFisier("masini_arbore.txt");
	afisareMasinaPostOrdine(arbore);
	afisareMasina(getMasinaByID(arbore, 3));
	printf("Numar total noduri:%d\n",determinaNumarNoduri(arbore));
	printf("inaltime:%d\n", calculeazaInaltimeArbore(arbore));
	printf("pret total: %.2f", calculeazaPretTotal(arbore));
	return 0;
}
