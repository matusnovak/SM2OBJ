/*** This file is part of FragmentFramework project ***/

#ifndef FFW_AUDIO_LOADER
#define FFW_AUDIO_LOADER

#include "../common.h"

/*!
 * @defgroup File-Loaders
 */



/*!
 * @ingroup File-Loaders
 */
namespace ffw{
    /*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @brief Audio loader base class
	 */
    class FFW_API audioLoader {
    public:
        audioLoader();
        virtual ~audioLoader();
        /*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Opens a file for reading
         */
        virtual bool open(const std::string& Path) = 0;
        /*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Opens a file for reading
         */
        virtual bool open(const std::wstring& Path) = 0;
        /*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Closes the file
         */
        virtual void close() = 0;
        /*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Reads one chunk from file
		 * @see getChunkSize
         */
        virtual bool readChunk(unsigned char* Bytes, size_t* BytesOut) = 0;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Skips one chunk in file
		 * @see getChunkSize
         */
		virtual bool skipChunk(size_t* BytesOut) = 0;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
         * @pure
		 * @brief Jumps to beginning of the file
         */
		virtual bool reset() = 0;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
		 * @const
         * @pure
		 * @brief Checks if end of file
         */
		virtual bool eof() const = 0;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
		 * @const
         * @pure
		 * @brief Returns current read position
         */
		virtual size_t getPos() const = 0;
        /*!
         * @memberof audioLoader
         * @ingroup File-Loaders
		 * @const
		 * @brief Checks if a file is open
         */
        bool isOpen() const;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
		 * @const
		 * @brief Returns the total size of all samples in bytes
         */
		size_t getSize() const;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
		 * @const
		 * @brief Returns the sample rate
         */
		int getSampleRate() const;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
		 * @const
		 * @brief Returns the number of channels
         */
		int getNumOfChannels() const;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
		 * @const
		 * @brief Returns the bit depth of one sample
         */
		int getBitsPerSample() const;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
		 * @const
		 * @brief Returns the size of a buffer in bytes used by functioon readChunk()
         */
		size_t getChunkSize() const;
		/*!
         * @memberof audioLoader
         * @ingroup File-Loaders
		 * @const
		 * @brief Checks if a file is open
         */
		operator bool () const;

    protected:
		audioLoader(const audioLoader& Other) = default;
		audioLoader& operator = (const audioLoader& Other) = default;
        bool loaded;
        size_t size;
        int sampleRate;
        int channelCount;
        int bitsPerSample;
		size_t chunkSize;
    };
};
#endif

