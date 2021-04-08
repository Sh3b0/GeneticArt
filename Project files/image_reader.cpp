/*
 * This file is a modified version of the original code by Samuel R. Buss http://www.math.ucsd.edu/~sbuss/MathCG/OpenGLsoft/RgbImage/RgbImage.zip
 * It is only used to read the input image.
 */

#include "image_reader.h"

bool ImageReader::LoadBmpFile(const char *filename) {
    Reset();
    FILE *infile = fopen(filename, "rb");

    int bChar = fgetc(infile);
    int mChar = fgetc(infile);
    if (bChar == 'B' && mChar == 'M') {
        skipChars(infile, 4 + 2 + 2 + 4 + 4);
        NumCols = readLong(infile);
        NumRows = readLong(infile);
        skipChars(infile, 2);
        int bitsPerPixel = readShort(infile);
        skipChars(infile, 4 + 4 + 4 + 4 + 4 + 4);
    }

    pixel = new unsigned char[NumRows * GetNumBytesPerRow()];

    unsigned char *cPtr = pixel;
    for (int i = 0; i < NumRows; i++) {
        int j;
        for (j = 0; j < NumCols; j++) {
            *(cPtr + 2) = fgetc(infile);
            *(cPtr + 1) = fgetc(infile);
            *cPtr = fgetc(infile);
            cPtr += 3;
        }
        int k = 3 * NumCols;
        for (; k < GetNumBytesPerRow(); k++) {
            fgetc(infile);
            *(cPtr++) = 0;
        }
    }

    fclose(infile);
    return true;
}

short ImageReader::readShort(FILE *infile) {
    unsigned char lowByte, hiByte;
    lowByte = fgetc(infile);
    hiByte = fgetc(infile);

    short ret = hiByte;
    ret <<= 8;
    ret |= lowByte;
    return ret;
}

long ImageReader::readLong(FILE *infile) {
    unsigned char byte0, byte1, byte2, byte3;
    byte0 = fgetc(infile);
    byte1 = fgetc(infile);
    byte2 = fgetc(infile);
    byte3 = fgetc(infile);

    long ret = byte3;
    ret <<= 8;
    ret |= byte2;
    ret <<= 8;
    ret |= byte1;
    ret <<= 8;
    ret |= byte0;
    return ret;
}

void ImageReader::skipChars(FILE *infile, int numChars) {
    for (int i = 0; i < numChars; i++) {
        fgetc(infile);
    }
}
