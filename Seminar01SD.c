#include<stdio.h>
#include<stdlib.h>

struct Joc {
	int id;
	int numarJucatori;
	char* denumire;
	float pret;
	char rating;
};

struct Joc initializare(int id, int numarJucatori, char* denumire, float pret, char rating) {
	struct Joc s;
	s.id = 1;
	s.numarJucatori = numarJucatori;
	s.denumire = malloc(sizeof(char)*(strlen(denumire)+1));
	strcpy_s(s.denumire, sizeof(char) * (strlen(denumire)+1), denumire);
	s.pret = pret;
	s.rating = rating;
	return s;
}

void afisare(struct Joc s) {
	printf("Id: %d\n", s.id);
	printf("Nume:%s\n", s.denumire);
	printf("Numar jucatori:%d\n", s.numarJucatori);
	printf("Rating: %c\n", s.rating);
	printf("Pret: %f\n", s.pret);
}

void modificaDenumire(struct Joc* s,char* denumire) {
	free(s->denumire);
	s->denumire = malloc((strlen(denumire) + 1) * sizeof(char));
	strcpy_s(s->denumire, ((strlen(denumire) + 1) * sizeof(char)) , denumire);
}

float caculeazaPretIndividual(struct Joc s){
	float cpret;
	cpret = s.pret / s.numarJucatori;
}

void dezalocare(struct Joc *s) {
	free(s->denumire);
}

int main() {
	struct Joc s;
	s = initializare(1, 2, "monopoly", 120, 'a');
	afisare(s);
	modificaDenumire(&s, "secret h");
	afisare(s);
	printf("pret individual: %f\n", caculeazaPretIndividual(s));
	int numarJocuri = 3;
	struct Joc* vectorJocuri = malloc(sizeof(struct Joc)*numarJocuri);
	vectorJocuri[0] = s;
	vectorJocuri[1] = initializare(2, 4, "Catan", 60, 'A');
	vectorJocuri[2] = initializare(3, 3, "Nu te supara frate", 37, 'A');
	afisare(*(vectorJocuri + 1));



	dezalocare(&s);
	return 0;
}

// ce face " -> " = dereferentiere + accesare
// ce face "[]" = deplasare + dereferentiere
