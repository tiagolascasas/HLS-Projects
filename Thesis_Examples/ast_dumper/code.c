int if2(int counter, int fragments[], int size, int pixels[])
{
    // initilize the z-buffer in rendering first triangle for an image
    static int z_buffer[300][300];
    if (counter == 0)
    {
        for (int i = 0; i < 300; i++)
        {
            for (int j = 0; j < 300; j++)
            {
                z_buffer[i][j] = 255;
            }
        }
    }
    int x = 0;
    for (int i = 0; i < 300; i++)
        x += 1;
}
