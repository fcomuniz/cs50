#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include "bmp.h"



int main(int argc, char * argv[]){
    
    if(argc != 3){
        eprintf("usage: %s inputfile outputfile\n", argv[0]);
        return 1;
    }
    
    
    /**
     * Here we try to open the input file, if is not possible, return error
     */
    char * inputFilePath = argv[1];
    FILE * inputFile = fopen(inputFilePath, "r");
    if(inputFile == NULL){
        eprintf("Could not open %s\n", inputFilePath);
        return 2;
    }
    
    /**
     * Here we open the output file, and if it is not possible, return error value
     */
    char * outputFilePath = argv[2];
    FILE * outputFile = fopen(outputFilePath, "w");
    if(outputFile == NULL){
        eprintf("Could not write to %s\n", outputFilePath);
        return 3;    
    }
    
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inputFile);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inputFile);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outputFile);
        fclose(inputFile);
        eprintf( "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outputFile);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outputFile);

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanlineq
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inputFile);

            if(triple.rgbtRed == 0xff){
                triple.rgbtRed = 0;
                triple.rgbtBlue = 0;
                triple.rgbtGreen = 0;
            }
            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outputFile);
        }

        // skip over padding, if any
        fseek(inputFile, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outputFile);
        }
    }

    // close infile
    fclose(inputFile);

    // close outfile
    fclose(outputFile);
    
    
    
    
    
    return 0;
}