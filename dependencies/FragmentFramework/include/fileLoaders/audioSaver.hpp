/*** This file is part of FragmentFramework project ***/

#ifndef FFW_AUDIO_SAVER
#define FFW_AUDIO_SAVER

#include "../common.h"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @brief Audio saver base class
	 */
    class FFW_API audioSaver {
    public:
        audioSaver();
        virtual ~audioSaver();
		/*!
         * @memberof audioSaver
         * @ingroup File-Loaders
		 * @pure
		 * @brief Opens a file for writing
         */
		virtual bool open(const std::string& Path, size_t Size, int BitsPerSample, int SampleRate, int NumChannels, int Kbps) = 0;
		/*!
         * @memberof audioSaver
         * @ingroup File-Loaders
		 * @pure
		 * @brief Opens a file for writing
         */
		virtual bool open(const std::wstring& Path, size_t Size, int BitsPerSample, int SampleRate, int NumChannels, int Kbps) = 0;
		/*!
         * @memberof audioSaver
         * @ingroup File-Loaders
		 * @pure
		 * @brief Writes a chunk of data to file
		 * @see getChunkSize
         */
		virtual bool writeChunk(unsigned char* Data, size_t* BytesWritten) = 0;
		/*!
         * @memberof audioSaver
         * @ingroup File-Loaders
		 * @pure
		 * @brief Writes a footer
         */
		virtual bool writeFooter() = 0;
		/*!
         * @memberof audioSaver
         * @ingroup File-Loaders
		 * @pure
		 * @brief Closes the file
         */
		virtual void close() = 0;
		/*!
         * @memberof audioSaver
         * @ingroup File-Loaders
		 * @const
		 * @pure
		 * @brief Checks if end of file 
         */
		virtual bool eof() const = 0;
		/*!
         * @memberof audioSaver
         * @ingroup File-Loaders
		 * @const
		 * @pure
		 * @brief Returns current write position in bytes
         */
		virtual size_t getPos() const = 0;
        /*!
         * @memberof audioSaver
         * @ingroup File-Loaders
		 * @const
		 * @brief Checks if file is open
         */
        bool isOpen() const;
		/*!
         * @memberof audioSaver
         * @ingroup File-Loaders
		 * @const
		 * @brief Returns the target output size specified in function create()
         */
		size_t getSize() const;
		/*!
         * @memberof audioSaver
         * @ingroup File-Loaders
		 * @const
		 * @brief Returns the sample rate
         */
		int getSampleRate() const;
		/*!
         * @memberof audioSaver
         * @ingroup File-Loaders
		 * @const
		 * @brief Returns the number of channels
         */
		int getNumOfChannels() const;
		/*!
         * @memberof audioSaver
         * @ingroup File-Loaders
		 * @const
		 * @brief Returns the bit depth of one sample
         */
		int getBitsPerSample() const;
		/*!
         * @memberof audioSaver
         * @ingroup File-Loaders
		 * @const
		 * @brief Returns the size of a chunk in bytes used by function writeChunk()
         */
		size_t getChunkSize() const;
		/*!
         * @memberof audioSaver
         * @ingroup File-Loaders
		 * @const
		 * @brief Checks if a file is open
         */
		operator bool () const;
	protected:
		audioSaver(const audioSaver& Other) = default;
		audioSaver& operator = (const audioSaver& Other) = default;
		bool loaded;
        size_t size;
        int sampleRate;
        int channelCount;
        int bitsPerSample;
		size_t chunkSize;
	};
};
#endif

