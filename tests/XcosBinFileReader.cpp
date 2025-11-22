#include <XcosBinFileReader.h>

#include <cstdio>

bool XcosBinFileReader::ReadData(const char* file_path, std::vector<double>* vals)
{
    FILE* file = fopen(file_path, "rb");

    if ( file )
    {
        char buffer[4];

        while ( fread(buffer, 1, 4, file) == 4 )
        {
            float *y = (float*)(buffer);
            vals->push_back(*y);
        }

        fclose(file);
        return true;
    }

    return false;
}
