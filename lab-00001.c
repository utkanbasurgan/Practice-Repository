//
// Utkan Başurgan 22011063
//
//------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//------------------------------------------------------------------------//

void array_goster(int *array, int buyukluk)
{
    printf("[");
    for (int j = 0; j < buyukluk; j++)
    {
        printf("%d", *(array + j));
        if (j != buyukluk - 1)
        printf(" ");
    }
    printf("]");
}

//------------------------------------------------------------------------//

void arama(int *keys, int *locks, int buyukluk)
{
    int sayi = *(locks + 0);

    printf("Sayı: %d\n", sayi);

    printf("Keys: ");
    array_goster(keys, buyukluk);
    printf(" <> ");

    printf("Locks: ");
    array_goster(locks, buyukluk);
    printf("\n");

    int *sol_keys = (int *)malloc(buyukluk * sizeof(int));
    int *sol_locks = (int *)malloc(buyukluk * sizeof(int));

    int *sag_keys = (int *)malloc(buyukluk * sizeof(int));
    int *sag_locks = (int *)malloc(buyukluk * sizeof(int));

    int sol_sayi = 0;
    int sag_sayi = 0;
    for (int i = 0; i < buyukluk; i++)
    {
        //printf("%d bakılıyor.\n", *(keys + i));

        if (*(keys + i) == sayi)
        {
            printf("Anahtarlarda %d Bulundu. Konumu: %d\n", sayi, i);
        }
        else if (*(keys + i) < sayi)
        {
            *(sol_keys + sol_sayi) = *(keys + i);
            sol_sayi++;
        }
        else if (*(keys + i) > sayi)
        {
            *(sag_keys + sag_sayi) = *(keys + i);
            sag_sayi++;
        }
    }

    sol_sayi = 0;
    sag_sayi = 0;
    for (int i = 0; i < buyukluk; i++)
    {
        //printf("%d bakılıyor.\n", *(locks + i));

        if (*(locks + i) == sayi)
        {
            printf("Kilitlerde %d bulundu. Konumu: %d\n", sayi, i);
        }
        else if (*(locks + i) < sayi)
        {
            *(sol_locks + sol_sayi) = *(locks + i);
            sol_sayi++;
        }
        else if (*(locks + i) > sayi)
        {
            *(sag_locks + sag_sayi) = *(locks + i);
            sag_sayi++;
        }
    }

    printf("Sol Keys: ");
    array_goster(sol_keys, sol_sayi);
    printf(" ");
    printf("Sol Locks: ");
    array_goster(sol_locks, sol_sayi);
    printf(" <> ");
    printf("Sağ Keys: ");
    array_goster(sag_keys, sag_sayi);
    printf(" ");
    printf("Sağ Locks: ");
    array_goster(sag_locks, sag_sayi);

    if (sol_sayi != 0)
    {
        printf("\n----------------------\n");

        printf("Soldan Devam Ediyor: \n");

        arama(sol_keys, sol_locks, sol_sayi);
    }
    if (sag_sayi != 0)
    {
        printf("\n----------------------\n");

        printf("Sağdan Devam Ediyor: \n");

        arama(sag_keys, sag_locks, sag_sayi);
    }
}

//------------------------------------------------------------------------//


int main()
{
    //========================================//

    int buyukluk;
    int *keys;
    int *locks;

    //========================================//

    FILE *datalar = fopen("dataset.txt", "r");

    char *satir = (char *)malloc(256 * sizeof(char));

    printf("%s", satir);

    for (int i=0; i<3; i++)
    {
        fgets(satir, 256, datalar);

        if (i == 0)
        {
            sscanf(satir, "%d", &buyukluk);
            keys = (int *)malloc(buyukluk * sizeof(int));
            locks = (int *)malloc(buyukluk * sizeof(int));
        }
        else if (i == 1)
        {
            char *bakilan_nokta = strtok(satir, " ");

            for (int j = 0; j < buyukluk && bakilan_nokta; j++)
            {
                *(keys + j) = atoi(bakilan_nokta);
                bakilan_nokta = strtok(NULL, " ");
            }
        }
        else if (i == 2)
        {
            char *bakilan_nokta = strtok(satir, " ");

            for (int j = 0; j < buyukluk && bakilan_nokta; j++)
            {
                *(locks + j) = atoi(bakilan_nokta);
                bakilan_nokta = strtok(NULL, " ");
            }
        }

        printf("\n");
    }

    fclose(datalar);

    //========================================//

    printf("\n");

    printf("Keys: ");
    array_goster(keys, buyukluk);
    printf("\n");

    printf("Locks: ");
    array_goster(locks, buyukluk);
    printf("\n----------------------\n");

    //========================================//

    arama(keys, locks, buyukluk);

    //========================================//

    free(satir);
    free(keys);
    free(locks);

    //========================================//

    return 0;

    //========================================//
}

//------------------------------------------------------------------------//