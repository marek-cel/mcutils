#ifndef LIBMCUTILS_TESTS_XCOSBINFILEREADER_H_
#define LIBMCUTILS_TESTS_XCOSBINFILEREADER_H_

#include <vector>

/**
 * \brief The XcosBinFileReader class
 */
class XcosBinFileReader
{
public:

    /**
     * \brief Reads data from Xcos binary output file
     * \param file_path file path
     * \param vals vector of doubles to store data
     * \return true on success false on failure
     */
    static bool ReadData(const char* file_path, std::vector<double>* vals);
};

#endif // LIBMCUTILS_TESTS_XCOSBINFILEREADER_H_
