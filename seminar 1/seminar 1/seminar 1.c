#include<stdio.h>
#include<stdlib.h>

struct Joc {
	int id;
	int nrJucatoriMin;
	char* denumire;
	float pret;
	char rating;
};

struct Joc initializare(int _id, int _nrJucatoriMin, char* _denumire, float _pret, char _rating) {
	struct Joc s;
	s.id = _id;
	s.nrJucatoriMin = _nrJucatoriMin;
	s.denumire = malloc(sizeof(char) * (strlen(_denumire) +1));
	strcpy(s.denumire, _denumire);
	s.pret = _pret;
	s.rating = _rating;
	return s;
}

void afisare(struct Joc j) {
	//afisarea tuturor atributelor.
	printf("ID: %d \n", j.id);
	printf("Nume: %s \n", j.denumire);
	printf("nr min jucatori: %d \n", j.nrJucatoriMin);
	printf("Rating: %d \n", j.rating);
	printf("Pret: %f \n", j.pret);

}

void modifica_Atribut_denumire(struct Joc* s, char _denumire) {	//modificarea unui atribut
	free((*s).denumire);
	(*s).denumire = malloc((strlen(_denumire) + 1) * sizeof(char));
	strcpy((*s).denumire, _denumire);
}
float calcPretIndividual(struct Joc s) {
	float pr;
	pr = s.pret / s.nrJucatoriMin;
	return pr;
}

void dezalocare(struct Joc *s) {
	//dezalocare campuri alocate dinamic
	free((*s).denumire);

}

int main() {
	struct Joc s;
	s = initializare(1, 2, "Monopoly", 33, 9);
	afisare(s);
	modifica_Atribut_denumire(&s, "Secret Hitler");
	afisare(s);
	int pret;
	pret = calcPretIndividual(s);
	printf("%d", pret);

	int nrJocuri = 3;
	struct Joc* jocuri = malloc(sizeof(struct Joc) * nrJocuri);
	jocuri[0] = s;
	jocuri[1] = initializare(2,2,"Catan",60,6);
	jocuri[2] = initializare(3, 2, "Nu te supara frATE", 76, 4);
	afisare(*(jocuri + 2));
	dezalocare(&s);

	// -> deferentiere si accesare
	// [] deplasare si deferentiere
	return 0;
}