#include<stdio.h>
#include<malloc.h>

struct Film {
	int id;
	int durata;
	char* denumire;
	float buget;
	char varstaMinima;

};
struct Film initializare(int id, int durata, char* nume, float buget, char varstaMinima) {
	struct Film s;
	s.id = id;
	s.durata = durata;
	s.denumire = malloc((strlen(nume) + 1) * sizeof(char));
	strcpy_s(s.denumire, (strlen(nume) + 1) * sizeof(char), nume);
	s.buget = buget;
	s.varstaMinima = varstaMinima;
	return s;
}

struct Film copyFilm(struct Film s) {
	return initializare(s.id, s.durata, s.denumire, s.buget, s.varstaMinima);
}

void afisare(struct Film s) {
	printf("id:%d\n", s.id);
	printf("durata:%d\n", s.durata);
	printf("nume:%s\n", s.denumire);
	printf("buget:%.2f\n", s.buget);
	printf("varsta minima:%d\n", s.varstaMinima);
	printf("\n");

}

void afisareVector(struct Film* vector, int nrElemente) {
	for (int i = 0; i < nrElemente; i++)
	{
		afisare(vector[i]);
	}
}

struct Film* copiazaPrimeleNElemente(struct Film* vector, int nrElemente, int nrElementeCopiate) {

	struct Film* vectorNou = malloc(nrElementeCopiate * sizeof(struct Film));
	for (int i = 0; i < nrElementeCopiate; i++)
	{
		vectorNou[i] = copyFilm(vector[i]);
	}

	return vectorNou;
}

void dezalocare(struct Film** vector, int* nrElemente) {
	for (int i = 0; i < *nrElemente; ++i) {
		free((*vector)[i].denumire);
	}
	free(*vector);
	*vector = NULL;
	*nrElemente = 0;
}

void copiazaAnumiteElemente(struct Film* vector, char nrElemente, float bugetMaxim, struct Film** vectorNou, int* dimensiune) {
	*dimensiune = 0;
	for (int i = 0; i < nrElemente; ++i)
	{
		if (vector[i].buget < bugetMaxim)
		{
			(*dimensiune)++;
		}
	}
	*vectorNou = malloc((*dimensiune) * sizeof(struct Film));
	int k = 0;
	for (int i = 0; i < nrElemente; i++) {
		if (vector[i].buget < bugetMaxim)
		{
			(*vectorNou)[k] = copyFilm(vector[i]);
			k++;
		}
	}


}

struct Film getPrimulElementConditionat(struct Film* vector, int nrElemente, const char* conditie) {
	struct Film s;
	s.id = 1;
	for (int i = 0; i < nrElemente; i++)
	{
		if (strcmp(vector[i].denumire, conditie)==0)
		{
			return vector[i];
		}

	}

	return s;
}



int main() {
	struct Film f = initializare(1, 120, "Dune", 20.6, 14);
	int nrFilme = 3;
	struct Film* filme = malloc(nrFilme * sizeof(struct Film));
	afisare(f);
	filme[0] = f;
	*(filme + 1) = initializare(2, 130, "The social network", 14, 16);
	filme[2] = initializare(3, 140, "The prestige", 3, 16);
	afisareVector(filme, nrFilme);

	int nrFilmeCopiate = 2;
	struct Film* vectorNou;
	vectorNou = copiazaPrimeleNElemente(filme, nrFilme, nrFilmeCopiate);
	printf("Filme vector nou\n");
	afisareVector(vectorNou, nrFilmeCopiate);
	printf("Final filme noi\n");
	dezalocare(&vectorNou, &nrFilmeCopiate);
	afisareVector(vectorNou, nrFilmeCopiate);

	struct Film* filmeIeftine;

	float prag = 20;
	int dimensiuneFilmeIeftine = 0;
	copiazaAnumiteElemente(filme, nrFilme, prag, &filmeIeftine, &dimensiuneFilmeIeftine);
	afisareVector(filmeIeftine, dimensiuneFilmeIeftine); 

	getPrimulElementConditionat(filme,nrFilme,"The social network");
	afisare(getPrimulElementConditionat(filme, nrFilme, "The social network"));

	return 0;
}
