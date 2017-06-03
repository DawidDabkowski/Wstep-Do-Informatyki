#include<stdio.h>
#include<stdlib.h>

void swap (int *a, int *b)									// Funkcja zamieniaj¹ca ze sob¹ zmienne typu int
{
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
}
void transp (char** tab, int m, int max)					// Funkcja, która transponuje tablicê
{
	int i;
	int j;
	int k=1;
	char tmp;
	for (i=0; i<m; i++)
	{
		for (j=k; j<max; j++)
		{
			tmp=tab[i][j];
			tab[i][j]=tab[j][i];
			tab[j][i]=tmp;
		}
		k++;
	}
}
void sympoz (char** tab, int m, int n)						// Funkcja, która odbija tablicê w symetrii poziomej
{
	int i;
	int j;
	char tmp;
	for (i=0; i<m; i++)
	{
		for (j=0; j<n/2; j++)
		{
			tmp=tab[i][j];
			tab[i][j] = tab[i][n-j-1];
			tab[i][n-j-1] = tmp;
		}
	}
}
void sympion (char** tab, int m, int n)						// Funkcja, która odbija tablicê w symetrii pionowej
{
	int i;
	int j;
	char tmp;
	for (i=0; i<n; i++)
	{
		for (j=0; j<m/2; j++)
		{
			tmp=tab[j][i];
			tab[j][i]=tab[m-j-1][i];
			tab[m-j-1][i]=tmp;
		}
	}
}
int main(void)
{
	FILE *f;
	f = fopen("tin.txt","r");
	if (f == NULL)
	{
		printf("Nie udalo sie otworzyc pliku");
		exit(-1);
	}
	FILE *g;
	g = fopen("tout.txt","w");
	if (f == NULL)
	{
		printf("Nie udalo sie otworzyc pliku");
		exit(-1);
	}	
	int m, n;												// Wysokosc i szerokosc tablicy
	int i, j;												// Zmienne sluzace do iterowania
	char obrazek;											// Pierwszy parametr operacji typu 6
	int wsp1, wsp2, wsp3, wsp4;								// Pozosta³e parametry operacji typu 6
	int cykl = 0;											// Oznacza obrót tablicy (0, 1, 2, 3)
	int stan = 1;											// Oznacza czy tablicê nale¿y transponowaæ (-1) czy nie (1)
	fscanf(f,"%d%d",&m,&n);									// Wczytanie wysokosci i szerokosci tablicy z pierwszego wiersza
	int wynik_fscanf = 1;									// Przechowuje informacjê czy wczytana zosta³a liczba (czy te¿ skoñczy³ siê plik)
	int operacja;											// Przechowuje numer operacji któr¹ nale¿y wykonaæ
	char ch=fgetc(f);										// Wczytany znak z pliku
	char tab;												// Tablica przechowuj¹ca znaki
	int max;												// Wartosc maksymalna sposrod 'm' i 'n'
	if (m>=n)
		max=m;
	else
		max=n;
	tab = (char**)malloc(max*sizeof(char*));				// Przydzielanie pamiêci na tablicê
	for (i=0; i<max; i++)
		tab[i] = (char*)malloc(max*sizeof(char));
	for (i=0; i<m; i++)										// Odczytanie znaków i zapisanie do tablicy
	{
		for (j=0; j<n; j++)
		{	
			while (ch =='\n')
				ch=fgetc(f);
			tab[i][j]=ch;
			ch=fgetc(f);
		}
	}
	while (wynik_fscanf == 1)								// Odczytywanie ostatniego wiersza z operacjami
	{
		wynik_fscanf = fscanf(f, "%d", &operacja);
		if ((operacja == 6) || (wynik_fscanf != 1))			// Jesli natrafiono na operacje typu 6 lub koniec pliku nale¿y
		{													// przekszta³ciæ tablicê
			cykl = cykl%4;
			if (stan == -1)
			{
				if (cykl == 0)
					sympion(tab, m, n);
				else if (cykl == 2)
					sympoz(tab, m, n);
				else if (cykl == 3)
				{
					transp(tab, m, max);
					swap(&m, &n);
				}
				else
				{			
					transp(tab, m, max);
					swap(&m, &n);
					sympion(tab, m, n);	
					sympoz(tab, m, n);	
				}
			}
			else if (stan == 1)
			{
				if (cykl == 1)
				{
					transp(tab, m, max);
					swap(&m, &n);				
					sympoz(tab, m, n);
				}
				else if (cykl == 2)
				{
					sympion(tab, m, n);
					sympoz(tab, m, n);
				}
				else if (cykl == 3)
				{
					transp(tab, m, max);
					swap(&m, &n);
					sympion(tab, m, n);
				}
			}
			if (operacja == 6)								// Dodatkowo jesli to byla operacja typu 6 to nalezy fragment tablicy
			{												// wype³niæ znakiem.
				cykl = 0;
				stan = 1;
				fgetc(f);
				obrazek = fgetc(f);
				wynik_fscanf=fscanf(f, "%d", &wsp1);
				wynik_fscanf=fscanf(f, "%d", &wsp2);
				wynik_fscanf=fscanf(f, "%d", &wsp3);
				wynik_fscanf=fscanf(f, "%d", &wsp4);
				for (i=wsp1; i<=wsp3; i++)
				{
					for (j=wsp2; j<=wsp4; j++)
						tab[i][j]=obrazek;
				}
				operacja = 7;								// Nadpisujê wartosc operacji aby program nie trafi³ ponownie do tej samej pêtli
			}
		}
		else if (0 <= operacja <= 5)						// Odczytanie poleceñ i obliczenie stanu tablicy
		{
			if 		(operacja == 0)
				cykl=cykl+stan+4;							// Dodajê 4 aby wynik na pewno nie by³ ujemny
			else if (operacja == 1)
				cykl=cykl-stan+4;							
			else if ((operacja == 2) || (operacja == 5))
				cykl=cykl+2;
			else if (operacja == 3)
				stan=-1*stan;
			else
			{
				stan=-1*stan;
				cykl=cykl+2;
			}
		}
	}
	for (i=0; i<m; i++)										// Po wykonaniu operacji zapisywanie koñcowej tablicy do pliku
	{
		for (j=0; j<n; j++)
		{
			fprintf(g,"%c ",tab[i][j]);
			printf("%c ",tab[i][j]);
		}
		fprintf(g,"\n");
		printf("\n");
	}
	for (i=0; i<max; i++)									// Zwalnianie pamiêci i zamykanie plików
		free(tab[i]);
	free(tab);
	fclose(f);
	fclose(g);
	return 0;
}
