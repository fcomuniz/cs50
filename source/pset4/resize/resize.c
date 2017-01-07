/**
 * Resizes a BMP file
 */
       
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int getPadding(BITMAPINFOHEADER bi)
{
    return ( 4 - (bi.biWidth * sizeof(RGBTRIPLE) ) % 4) %4;
}

DWORD getBISizeImage(BITMAPINFOHEADER bi, int padding){
    return ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
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
    
    if(!(scale > 0 || scale <=100)){
        fprintf(stderr, "Incorrect value for scale, must be in (0,100]");
        fclose(inptr);
        fclose(outptr);
        return 5;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER inputBF;
    fread(&inputBF, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER inputBI;
    fread(&inputBI, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (inputBF.bfType != 0x4d42 || inputBF.bfOffBits != 54 || inputBI.biSize != 40 ||
        inputBI.biBitCount != 24 || inputBI.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // create a outputFile inputBF
    BITMAPFILEHEADER outputBF;
    outputBF = inputBF;
    // determine inputPadding for scanlines
    int inputPadding = getPadding(inputBI);
    // write outfile's BITMAPFILEHEADER



    BITMAPINFOHEADER outputBI;

    outputBI = inputBI;


//    Scaling the output width and height for the output file
    outputBI.biWidth *=scale;
    outputBI.biHeight *=scale;

//    Calculating the padding for the output fiel
    int outputPadding = getPadding(outputBI);


//    Updating the Size Image of the file, that will be used for calculating the new size of the file
    outputBI.biSizeImage = getBISizeImage(outputBI, outputPadding);

    // update output bfSize
    outputBF.bfSize = outputBI.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPINFOHEADER
    fwrite(&outputBF, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&outputBI, sizeof(BITMAPINFOHEADER), 1, outptr);



    // write every line of outputBI
    for (int i = 0, biHeight = abs(outputBI.biHeight); i < biHeight; i++)
    {// iterate over pixels in scanline
        // seek to the correspondind row
        int inputLinePos = i/scale;
        int inputLineSize = (inputBI.biWidth*sizeof(RGBTRIPLE)) + inputPadding;
        fseek(inptr,sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER), SEEK_SET);
        fseek(inptr,(inputLinePos)*inputLineSize,SEEK_CUR);

        RGBTRIPLE inputLine[inputBI.biWidth];
        fread(inputLine, sizeof(RGBTRIPLE), inputBI.biWidth, inptr);

        // write RGB triple to outfile
        RGBTRIPLE outputLine[outputBI.biWidth];

        // Put the elements in each line
        for(int j = 0 ; j < outputBI.biWidth; j++){
            int valuePos = j/scale;
            outputLine[j] = inputLine[valuePos];
        }
        fwrite(outputLine, sizeof(RGBTRIPLE), outputBI.biWidth, outptr);


        // then add the outputPadding to the output file
        for (int k = 0; k < outputPadding; k++)
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
