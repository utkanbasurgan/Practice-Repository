//
// Utkan Başurgan 22011063
//
//------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>

//------------------------------------------------------------------------//

// Matris Fonksiyonları

void matris_goster(int *matris, int dikey, int yatay)
{
    for (int i = 0; i < dikey; i++)
    {
        for (int j = 0; j < yatay; j++)
        {
            int baktigim_nokta = *(matris + i * yatay + j);
            printf("%d ", baktigim_nokta);
        }
        printf("\n");
    }
}

int matris_dene(int *matris, int yatay, int sayi)
{
    for (int i = 0; i < yatay; i++)
    {
        int bakilacak_nokta = *(matris + i);
        // Bakacağım noktatya pointer

        if (bakilacak_nokta == sayi)
        {
            return 0; // var
        }
    }
    return 1; // yok
}

void matris_doldur(int *matris, int dikey, int yatay)
{
    printf("%dx%d matrisini girin:\n", dikey, yatay);

    int alinan_sayi;
    
    for (int i = 0; i < dikey * yatay; i++)
    {
        scanf("%d", &alinan_sayi);
        
        if (i < yatay) // Sadece ilk satr için Kontrol
        {
            while (matris_dene(matris, yatay, alinan_sayi) == 0)
            {
                printf("İlk Satırda Aynı sayılar bulunamaz! Tekrar deneyin.\n");
                scanf("%d", &alinan_sayi);
            }
        }

        matris[i] = alinan_sayi;
    }
}

int matris_deger(int *matris, int yatay, int buyukluk)
{
    return *(matris + buyukluk + yatay);
}

//------------------------------------------------------------------------//

// Asıl amaç araması

void matris_tamdene(int *N_matris, int *M_matris, int N, int M)
{
    for (int i = 0; i < N; i++)
    {
        if (matris_dene(M_matris, M, *(N_matris + i)) == 0)
        {
            int X = matris_deger(N_matris, N, i);
            int Y = matris_deger(M_matris, M, i);
            int Z = X + Y;
            printf("[Sayı %d] %d + %d = %d\n", *(N_matris + i), X, Y, Z);
        }
    }
}

//------------------------------------------------------------------------//

// Başlatıcı Fonksiyon

int main()
{
    //========================================//

    int N, M;

    //========================================//
    
    printf("N değerini girin: ");
    scanf("%d", &N);
    
    printf("M değerini girin: ");
    scanf("%d", &M);

    //========================================//

    int *N_matris = (int *)malloc(2 * N * sizeof(int));
    int *M_matris = (int *)malloc(2 * M * sizeof(int));

    //========================================//

    // Matrisleri Doldurma

    matris_doldur(N_matris, 2, N);
    matris_doldur(M_matris, 2, M);

    //========================================//

    printf("\n2xN Matrisi:\n");
    matris_goster(N_matris, 2, N);

    printf("\n2xM Matrisi:\n");
    matris_goster(M_matris, 2, M);

    //========================================//

    printf("\n ");
    matris_tamdene(N_matris, M_matris, N, M);

    //========================================//

    free(N_matris);
    free(M_matris);

    //========================================//

    return 0;

    //========================================//
}

//------------------------------------------------------------------------//