/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int getPadding(BITMAPINFOHEADER bi)
{
    return ( 4 - (bi.biWidth * sizeof(RGBTRIPLE) ) % 4) %4;
}

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s scale-factor infile outfile\n", argv[0]);
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char * outfile = argv[3];
    double scale = atof(argv[1]);

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    
    if(!(val > 0 || val <=100)){
        fprintf(stderr, "Incorrect value for scale, must be in (0,100]");
        return 5;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER inputbf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // create a outputFile bf
    BITMAPFILEHEADER outputBF;
    // TODO Put correct values form outputBF

    // write outfile's BITMAPFILEHEADER
    fwrite(&outputBF, sizeof(BITMAPFILEHEADER), 1, outptr);


    BITMAPINFOHEADER outputBI;


    // write outfile's BITMAPINFOHEADER
    fwrite(&outputBI, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    int inputPadding = getPadding(bi);

    int outputPadding = getPadding(outputBI);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
