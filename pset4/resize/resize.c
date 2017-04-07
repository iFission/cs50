/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    int n = atoi(argv[1]); // assign factor

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

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
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

    //change header
    int biWidthOld= bi.biWidth;
    bi.biWidth = biWidthOld * n;

    int biHeightOld = bi.biHeight;
    bi.biHeight = biHeightOld * n;


    // determine padding for scanlines
    int paddingOld =  (4 - (biWidthOld * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // determine size of new header
    //size of pixels and padding
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);

    //total size of file, plus headers
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(biHeightOld); i < biHeight; i++)
    {
    	// re-copy for vertical resize, repeat n times
    	for (int j = 0; j < n; j++)
    	{
    		// iterate over pixels in scanline
    		for (int k = 0; k < biWidthOld; k++)
    		{
    		    // temporary storage
    		    RGBTRIPLE triple;

    		    // read RGB triple from infile
    		    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

    		    // write RGB triple to outfile
    		    for (int l = 0; l < n; ++l)
    		    {
    		    	fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr); // changed 1 to n, to repeat n times
    		    }
    		}

    		// skip over padding, if any / from inptr
    		fseek(inptr, paddingOld, SEEK_CUR);

    		// then add it back (to demonstrate how) / write padding to outptr
    		for (int m = 0; m < padding; m++)
    		{
    		    fputc(0x00, outptr);
    		}
    		
    		// move back to the beginning of the horizontal line
	    	if (j < n - 1)
	    	{
	    		fseek(inptr, -(3 * biWidthOld + paddingOld) , SEEK_CUR);
	    	}
    	}
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
