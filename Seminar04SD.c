#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//lista simplu inlantuita este o structura de date, liniara, omogena cu acces secvential
// " -> " = dereferentiere + accesare

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

void afisareListaMasini(Nod* cap) {
	while (cap) {
		afisareMasina(cap->info); //sageata pt ca fac dereferentiere si accesare;
		cap = cap->next;
 	}
}

void adaugaMasinaInLista(Nod** cap, Masina masinaNoua) {
	Nod* temp = malloc(sizeof(Nod));
	temp->info = masinaNoua;
	temp->next = NULL;
	if (!(*cap)) {
		*cap = temp;
	}

	else
	{
		Nod* p = *cap;
		while (p->next)
		{
			p = p->next;
		}
		p->next = temp;
	}
}

void adaugaLaInceputInLista(Nod** cap, Masina masinaNoua) {
	Nod* nou = (Nod*)malloc(sizeof(Nod));
	nou->info = masinaNoua;
	nou->next = *cap;
	*cap = nou;
}

void* citireListaMasiniDinFisier(const char* numeFisier) {
	Nod* cap = NULL;
	FILE* file = fopen(numeFisier, "r");
	while (!feof(file)) {
		adaugaMasinaInLista(&cap, citireMasinaDinFisier(file));
	}
	fclose(file);
	return cap;
}

void dezalocareListaMasini(Nod** nod) {
	while (*nod) {
		free((*nod)->info.numeSofer);
		free((*nod)->info.model);
		Nod* nou = (*nod)->next;
		free(*nod);
		*nod = nou;
	}

}

float calculeazaPretMediu(Nod** nod) {
	//calculeaza pretul mediu al masinilor din lista.
	Nod* temp = NULL;
	temp = (Nod*)malloc(sizeof(Nod));
	temp = *nod;
	float medie = 0;
	int nrMedie = 0;
	while (temp)
	{
		medie = medie + (temp)->info.pret;
		temp = (temp)->next;
		nrMedie++;
	}

	dezalocareListaMasini(&temp);

	if (nrMedie > 0)
	{
		return medie / nrMedie;
	}
	else
		return 0;
}



void stergeMasiniDinSeria(Nod** cap, char serieCautata) {
	//sterge toate masinile din lista care au seria primita ca parametru.
	//tratati situatia ca masina se afla si pe prima pozitie, si pe ultima pozitie
	while ((*cap) && (*cap)->info.serie == serieCautata)
	{
		Nod* aux = *cap;
		(*cap) = aux->next;

		if (aux->info.numeSofer) {
			free(aux->info.numeSofer);
		}

		if (aux->info.model) {
			free(aux->info.model);
		}

		free(aux);
	}

	if ((*cap)) {
		Nod* p = *cap;
		while (p) {

			while (p->next && p->next->info.serie != serieCautata) {
				p = p->next;
			}
			if (p->next) {
				Nod* aux = p->next;
				p->next = aux->next;

				if (aux->info.numeSofer) {
					free(aux->info.numeSofer);
				}
				if (aux->info.model) {
					free(aux->info.model);
				}

				free(aux);
			}
			else {
				p = NULL;
			}
		}
	}

}

float calculeazaPretulMasinilorUnuiSofer(Nod** nod ,const char* numeSofer) {
	//calculeaza pretul tuturor masinilor unui sofer.
	Nod* temp = NULL;
	temp = (Nod*)malloc(sizeof(Nod));
	temp = *nod;
	float medie = 0;
	int nrMedie = 0;
	while (temp)
	{
		if (!(strcmp(temp->info.numeSofer, numeSofer)))
		{
			medie = medie + (temp)->info.pret;
			temp = (temp)->next;
			nrMedie++;
		}
		else
			temp = temp->next;
	}
	dezalocareListaMasini(&temp);
	if (nrMedie > 0)
	{
		return medie / nrMedie;
	}
	else
		return 0;
	
}

int main() {

	Nod* cap = citireListaMasiniDinFisier("masini.txt");
	afisareListaMasini(cap);
	printf("pret mediu:%f\n", calculeazaPretMediu(&cap));
	printf("pret mediu sofer:%f\n", calculeazaPretulMasinilorUnuiSofer(&cap,"Ionescu"));
	printf("Stergere masini cu seria A:\n");
	stergeMasiniDinSeria(&cap, 'A');
	afisareListaMasini(cap);
	printf("Stergere masini cu seria B:\n");
	stergeMasiniDinSeria(&cap, 'B');
	afisareListaMasini(cap);
	dezalocareListaMasini(&cap);
	return 0;
}
