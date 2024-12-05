//---------------------------------------------------------------------------//

void RESULTS_write(const char *filename, float results[100][4])
{
    FILE *file = fopen(filename, "w");

    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        return;
    }

    for (int i = 0; i < 100; i++) // Loop over epochs
    {
        for (int j = 0; j < 4; j++) // Loop over time, loss, accuracy
        {
            fprintf(file, "%f ", results[i][j]);
        }
        fprintf(file, "\n"); // Newline after each epoch
    }

    fclose(file);
}

//---------------------------------------------------------------------------//