/*
 * This file is a modified version of the original code by Samuel R. Buss http://www.math.ucsd.edu/~sbuss/MathCG/
 * It is only used to read and process the input image.
 */

#ifndef IMAGE_READER_H
#define IMAGE_READER_H

#include <cstdio>
#include <cassert>

class ImageReader {
public:
    ImageReader();

    ImageReader(const char *filename);

    unsigned char *pixel;
    long height, width;

    bool LoadBmpFile(const char *filename);

    long GetNumBytesPerRow() const { return ((3 * NumCols + 3) >> 2) << 2; }

    void Reset();

private:
    long NumRows;
    long NumCols;

    static short readShort(FILE *infile);

    static long readLong(FILE *infile);

    static void skipChars(FILE *infile, int numChars);

};

inline ImageReader::ImageReader(const char *filename) {
    NumRows = 0;
    NumCols = 0;
    pixel = 0;
    LoadBmpFile(filename);
    height = NumRows;
    width = NumCols;
}


inline void ImageReader::Reset() {
    NumRows = 0;
    NumCols = 0;
    delete[] pixel;
    pixel = 0;
}


#endif // IMAGE_READER_H
