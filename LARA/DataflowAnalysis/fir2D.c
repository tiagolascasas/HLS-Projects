//Fir2D
#define WIDTH_SIZE 800
#define HEIGHT_SIZE 600

const short K[] = {1, 2, 1, 2, 4, 2, 1, 2, 1};

void fir2D(unsigned char in[HEIGHT_SIZE*WIDTH_SIZE], unsigned char out[HEIGHT_SIZE*WIDTH_SIZE])
{
    for (int row = 0; row < HEIGHT_SIZE - 3 + 1; row++)
    {
        for (int col = 0; col < WIDTH_SIZE - 3 + 1; col++)
        {
            unsigned short sumval = 0;
            for (int wrow = 0; wrow < 3; wrow++)
            {
                for (int wcol = 0; wcol < 3; wcol++)
                {
                    sumval += (unsigned short)in[(row + wrow) * WIDTH_SIZE + (col + wcol)] * (unsigned short)K[wrow * 3 + wcol];
                }
            }
            sumval = sumval / 16;
            out[row * WIDTH_SIZE + col] = (unsigned char)sumval;
        }
    }
}