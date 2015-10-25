/*** This file is part of FragmentFramework project ***/

#ifndef FFW_FILE
#define FFW_FILE

#include "../common.h"

/*!
 * @defgroup Utilities
 */

/*!
 * @ingroup Utilities
 */
namespace ffw{
    /*!
     * @memberof ffw
     * @ingroup Utilities
     */
	class FFW_API file{
    public:
        file();
		file(file&& Other) = delete;
        ~file();
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Opns a file for reading or writing
		 * @param Path UTF-8 compatible path
		 * @param Mode In what mode to open the file (e.g. std::ios::in)
		 * @return True if file opens successflly
         */
        bool open(const std::string& Path, std::ios_base::openmode Mode);
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Opens a file to reading or writing
		 * @param Path Multi byte encoded path
		 * @param Mode in what mode to open the file (e.g. std::ios::in)
		 * @return True if file opens successfully
         */
        bool open(const std::wstring& Path, std::ios_base::openmode Mode);
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Closes the file
         */
        void close();
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Checks if the file is open
         */
        bool isOpen();
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Reads data to a buffer
		 * @param Data Buffer in which to store the data
		 * @param Size Number of bytes to read
		 * @return Returns number of bytes read
         */
        std::streamsize read(void* Data, size_t Size);
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Writes data to the file
		 * @param Data Pointer to the data to write
		 * @param Size Number of bytes to write
		 * @return True on success
         */
        bool write(void* Data, size_t Size);
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Reads a single line of text
		 * @param Str Where to store the line
		 * @return Number of bytes read
         */
        std::streamsize readLine(std::string* Str);
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Writes single line of text
		 * @param Str Data to write
		 * @return True on success
         */
        bool writeLine(const std::string& Str);
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Reads a single char from file
		 * @param Chr Where to store the char
		 * @return True on success
         */
        bool readChar(char* Chr);
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Writes a sigle char to the file
		 * @param Chr What char to write
		 * @return True on success
         */
        bool writeChar(char Chr);
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Go to specific position in the file
		 * @param Pos Absolute offset in bytes
		 * @return True on success
         */
        bool gotoPos(unsigned int Pos);
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Go to specific position in the file (relative)
		 * @param Pos Relative offset in bytes
		 * @return True on success
         */
        bool gotoPosOffset(unsigned int Pos);
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Go to specific line in the file
		 * @param Num Absolute offset
		 * @return True on success
         */
        bool gotoLine(unsigned int Num);
		/*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Go to specific position in the file (relative)
		 * @param Num Relative offset
		 * @return True on success
         */
        bool gotoLineOffset(unsigned int Num);
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Goes to the end of the file
		 * @return True on success
         */
        bool gotoEnd();
		/*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Resets the file
		 * @return True on success
         */
		bool reset();
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Goes to the beginning of the file
		 * @return True on success
         */
        bool gotoBeginning();
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Counts all lines in the file
		 * @return Number of lines
         */
		size_t countLines();
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Returns the size of the file in bytes
		 * @return Size in bytes
         */
		size_t getSize();
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Returns the current position in the file in bytes
		 * @return Current position in bytes
         */
		size_t getPos();
        /*!
         * @memberof file
         * @ingroup Utilities
		 * @brief Checks if end of file
         */
        bool eof();
		file& operator = (file&& Other) = delete;
		file& operator = (const file& Other) = delete;
		file(const file& Other) = delete;
    private:
        std::fstream fileStream;
    };
};
#endif
