//
// Utkan Başurgan 22011063
//
//------------------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>

//------------------------------------------------------------------------//

void matris_doldur(int *matris, int dikey, int yatay)
{
    printf("%dx%d matrisini girin:\n", dikey, yatay);

    int alinan_sayi;
    
    for (int i = 0; i < dikey * yatay; i++)
    {
        scanf("%ds", &alinan_sayi);
        matris[i] = alinan_sayi;
    }
}

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

int matris_deger(int *matris, int yatay, int buyukluk)
{
    return *(matris + buyukluk + yatay);
}

int matris_say(int *matris, int yatay, int dikey)
{
    int bulunan = 0;

    for (int i = 0; i < yatay*dikey; i++)
    {
        int bakilacak_nokta = *(matris + i);
        // Bakacağım noktatya pointer

        if (bakilacak_nokta != 0)
        {
            bulunan++;
        }
    }

    return bulunan; // yok
}

void matris_olustur(int *kullanici_matris, int *konum_matrisi, int yatay, int dikey)
{
    int bulunmus_sayisi = 0;

    for (int i = 0; i < yatay; i++)
    {
        for (int j = 0; j < dikey; j++)
        {
            int bakilacak_nokta = *(kullanici_matris + i*j + j);

            //printf("%d", bakilacak_nokta); //debug için

            if (bakilacak_nokta != 0)
            {
                *(konum_matrisi + bulunmus_sayisi*3 + 0) = i+1;
                *(konum_matrisi + bulunmus_sayisi*3 + 1) = j+1;
                *(konum_matrisi + bulunmus_sayisi*3 + 2) = bakilacak_nokta;
                bulunmus_sayisi++;
            }
        }
    }
}

void matris_ara(int *konum_matrisi, int yatay, int sayi)
{
    int bulunma_sayisi = 0;

    for (int i = 0; i < yatay; i++)
    {
        int bakilacak_nokta = *(konum_matrisi + 3*i + 2);

        if (bakilacak_nokta == sayi)
        {
            bulunma_sayisi++;
            int x = *(konum_matrisi + 3*i + 0);
            int y = *(konum_matrisi + 3*i + 1);
            printf("%d Sayısının %d. bulunduğu nokta: X: %d, Y: %d\n", sayi, bulunma_sayisi, x, y); //debug için
        }
    }

    if (bulunma_sayisi == 0)
    {
        printf("Bulunamadı."); 
    }
}

//------------------------------------------------------------------------//

int main()
{
    //========================================//

    int N, M, K;

    //========================================//
    
    printf("N değerini girin: ");
    scanf("%d", &N);
    
    printf("M değerini girin: ");
    scanf("%d", &M);

    //========================================//

    int *kullanici_matris = (int *)malloc(N * M * sizeof(int));

    //========================================//

    // Matrisleri Doldurma

    matris_doldur(kullanici_matris, N, M);

    printf("\nNxM Matrisi:\n");

    matris_goster(kullanici_matris, N, M);

    //========================================//

    int bulunan_sayi = matris_say(kullanici_matris, N, M);

    int *konum_matrisi = (int *)malloc(bulunan_sayi * 3 * sizeof(int));

    matris_olustur(kullanici_matris, konum_matrisi, N, M);

    printf("\nKonum Matrisi:\n");

    matris_goster(konum_matrisi, bulunan_sayi, 3);

    //========================================//

    printf("Aranan değerini girin: ");
    scanf("%d", &K);

    matris_ara(konum_matrisi, bulunan_sayi, K);

    return 0;

    //========================================//

}

//------------------------------------------------------------------------//
