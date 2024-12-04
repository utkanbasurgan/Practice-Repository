//---------------------------------------------------------------------------//

void DATASETS_files(float veriKumesi[CLASS_COUNT][EXAMPLES_PER_CLASS][IMAGE_SIZE][IMAGE_SIZE])
{
    const char *classA = "../Datasets/Pawn/pawn-";
    const char *classB = "../Datasets/Knight/knight-";
    char filename[256];

    for (int i = 0; i < EXAMPLES_PER_CLASS; i++)
    {
        // Read class A images
        sprintf(filename, "%s%05d.jpg", classA, i + 1);
        DATASETS_read(filename, veriKumesi[0][i]);

        // Read class B images
        sprintf(filename, "%s%05d.jpg", classB, i + 1);
        DATASETS_read(filename, veriKumesi[1][i]);
    }
}

//---------------------------------------------------------------------------//