//---------------------------------------------------------------------------//

void DATASETS_read(const char *filename, float matrix[IMAGE_SIZE][IMAGE_SIZE])
{
    int width, height, channels;

    // Load the image
    unsigned char *data = stbi_load(filename, &width, &height, &channels, 0);
    if (data == NULL)
    {
        //printf("Error loading image: %s\n", filename);
        return;
    }

    // Resize and convert to grayscale
    for (int i = 0; i < IMAGE_SIZE; i++)
    {
        for (int j = 0; j < IMAGE_SIZE; j++)
        {
            int orig_x = i * width / IMAGE_SIZE;
            int orig_y = j * height / IMAGE_SIZE;
            int idx = (orig_y * width + orig_x) * channels;

            unsigned char gray = (unsigned char)(0.299 * data[idx] + 0.587 * data[idx + 1] + 0.114 * data[idx + 2]);
            matrix[i][j] = gray / 255.0f;
        }
    }

    // Free the image data
    stbi_image_free(data);
}

//---------------------------------------------------------------------------//