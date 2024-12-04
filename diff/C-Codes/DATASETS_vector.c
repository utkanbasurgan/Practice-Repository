//---------------------------------------------------------------------------//

// Görüntü veri kümesini oluştur ve normalize et
void DATASETS_vector(float veriKumesi[CLASS_COUNT][EXAMPLES_PER_CLASS][IMAGE_SIZE][IMAGE_SIZE])
{
    for (int c = 0; c < CLASS_COUNT; c++)
    {
        for (int ex = 0; ex < EXAMPLES_PER_CLASS; ex++)
        {
            for (int i = 0; i < IMAGE_SIZE; i++)
            {
                for (int j = 0; j < IMAGE_SIZE; j++)
                {
                    // 0-1 arası normalize et
                    veriKumesi[c][ex][i][j] = veriKumesi[c][ex][i][j] / 255.0f;
                }
            }
        }
    }
}

//---------------------------------------------------------------------------//