#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Converstion ASCII d'un nombre en hexa au un nombre entier
int val(char c)
{
	if (c >= '0' && c <= '9') // Verification par code ASCII
		return (int)c - '0';  // Cast du char en int
	else
		return (int)c - 'A' + 10;
}

// Fonction pour convertir un nonbre en decimale
int aDeci(char *str, int base1)
{
	int len = strlen(str);
	int power = 1;
	int num = 0;
	int i;

	// Equivalent de decimale = str[len-1]*1 + str[len-2]*base + str[len-3]*(base^2) + ...
	for (i = len - 1; i >= 0; i--)
	{
		num += val(str[i]) * power;
		power = power * base1;
	}

	return num;
}

// Fonctiom pour detecte le nombre de bits optimale
int len(int entier)
{
	int j = 0;
	while (entier > 0)

	{
		j = j + 1;
		entier = entier / 2;
	}

	if (j < 4 && j >= 1)
	{
		j = 4;
	}
	else if (j >= 4 && j < 8)
	{
		j = 8;
	}
	else if (j >= 8 && j <= 16)
	{
		j = 16;
	}
	else
	{
		j = 32;
	}
	return j;
}


int main()
{

	int n, entier, base1;
	char str[100];

	printf("Entrer un nombre: ");
	scanf("%s", str);
	printf("Entrer sa base: ");
	scanf("%d", &base1);
	printf("\n");

	// Condition pour le nombre 0 et -0
	if ((str[0] == '-' && str[1] == '0') || str[0] == '0')
	{
		printf("Les differentes representations de -0 :");
		printf("La valeur signee: 00\n");
		printf("Le complement a 1: 11\n");
		printf("Le complement a 2: 00\n\n");
		printf("Les differentes representations de 0 :");
		printf("La valeur signee: 00\n");
		printf("Le complement a 1: 00\n");
		printf("Le complement a 2: 00\n");
	}

	// Condition de traitement des nombres negatifs
	else if (str[0] == '-')
	{
		// Boocle pour traite juste le nombre sans signe (car c'est un string)
		for (int i = 0; i < strlen(str); i++)
		{
			str[i] = str[i + 1];
		}

		entier = aDeci(str, base1);

		n = entier;

		int j = len(entier);

		int T[j];
		int i = 0, l = 0;

		// Conversion binaire
		for (i = 0; i < j; i++)
		{
			T[i] = n % 2;
			n = n / 2;
		}

		printf("\n");
		int vs[j];

		// Inverser le tableau
		for (i = j - 1; i >= 0; i--)
		{
			vs[i] = T[l];
			l++;
		}

		// Ajoutant le 1 de signe en l'indice 0
		vs[0] = 1;

		printf("La valeur signee: ");

		for (i = 0; i < j; i++)

			printf("%d", vs[i]);
		printf("\n");

		int ca1[j + 1];
		ca1[0] = 1;

		// Complement a un on inversant 1 par 0 et 0 par 1 pour chaque
		// case du tableau vs[]

		for (i = 1; i < j + 1; i++)
		{
			if (vs[i] == 0)
			{
				ca1[i] = 1 / vs[i] + 1;
			}

			else
			{
				ca1[i] = vs[i] - 1;
			}
		}

		printf("Le complement a 1: ");

		for (i = 0; i < j; i++)
			printf("%d", ca1[i]);

		printf("\n");

		int ca2[j];
		int reste = 1; // Inisiation du reste a un

		// Complement a deux inversant 1 par 0 si le reste est a 1 et
		// on inverse 0 par 1 si l'indice est a 0 et le reste est a 1
		// et le reste dans ce cas devient 0 pour que l'indice suivant
		// soit le meme
		for (int i = j - 1; i >= 0; i--)
		{
			if (ca1[i] == 1 && reste == 1)
			{
				ca2[i] = 0;
			}
			else if (ca1[i] == 0 && reste == 1)
			{
				ca2[i] = 1;
				reste = 0;
			}
			else
			{
				ca2[i] = ca1[i];
			}
		}
		ca2[j] = '\0';


		printf("Le complement a 2: ");

		for (i = 0; i < j; i++)
			printf("%d", ca2[i]);
		printf("\n");
	}

	// Traitement des nombres negatifs
	else if (str[0] != '-')
	{

		entier = aDeci(str, base1);
		int j = len(entier);
		int T[j];
		int i = 0, l = 0;

		// Conversion binaire
		for (i = 0; i < j; i++)
		{
			T[i] = entier % 2;
			entier = entier / 2;
		}

		int vs[j];

		// Inverser le tableau
		for (i = j - 1; i >= 0; i--)
		{
			vs[i] = T[l];
			l++;
		}

		// La valeur signee et le complement a un et a deux est le meme
		// dans le cas des nombre positif
		printf("La valeur signee: ");

		for (i = 0; i < j; i++)
			printf("%d", vs[i]);
		printf("\n");

		printf("Le complement a 1: ");

		for (i = 0; i < j; i++)
			printf("%d", vs[i]);
		printf("\n");

		printf("Le complement a 2: ");

		for (i = 0; i < j; i++)
			printf("%d", vs[i]);
		printf("\n");
	}

	return 0;
}