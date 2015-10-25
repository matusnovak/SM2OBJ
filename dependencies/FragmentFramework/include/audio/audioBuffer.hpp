/*** This file is part of FragmentFramework project ***/

#ifndef FFW_AUDIO_BUFFER
#define FFW_AUDIO_BUFFER

#include "../common.h"

/*!
 * @ingroup Audio
 */
namespace ffw {
	/*!
	 * @memberof ffw
	 * @ingroup Audio
	 */
	class FFW_API audioBuffer{
	public:
		audioBuffer();
		audioBuffer(audioBuffer&& Other);
		audioBuffer(const audioBuffer& Other);
		virtual ~audioBuffer();
		/*!
		 * @memberof audioBuffer
		 * @ingroup Audio
		 * @brief Creates a buffer
		 */
		bool create(unsigned char* Data, size_t Size, int BitsPerSample, int SampleRate, int NumChannels);
		/*!
		 * @memberof audioBuffer
		 * @ingroup Audio
		 * @brief Returns a pointer to the raw data
		 */
		unsigned char* getDataPtr();
		/*!
		 * @memberof audioBuffer
		 * @ingroup Audio
		 * @brief Returns a pointer to the raw data
		 * @const
		 */
		const unsigned char* getDataPtr() const;
		/*!
		 * @memberof audioBuffer
		 * @ingroup Audio
		 * @brief Returns the size of the buffer
		 * @const
		 */
		size_t getSize() const;
		/*!
		 * @memberof audioBuffer
		 * @ingroup Audio
		 * @brief Returns the sample rate
		 * @const
		 */
		int getSampleRate() const;
		/*!
		 * @memberof audioBuffer
		 * @ingroup Audio
		 * @brief Returns the bit depth of one sample
		 * @const
		 */
		int getBitsPerSample() const;
		/*!
		 * @memberof audioBuffer
		 * @ingroup Audio
		 * @brief Returns the number of channels
		 * @const
		 */
		int getNumOfChannels() const;
		/*!
		 * @memberof audioBuffer
		 * @ingroup Audio
		 * @brief Destroys the buffer
		 */
		void destroy();
		
		audioBuffer& operator = (const audioBuffer& Other);
		audioBuffer& operator = (audioBuffer&& Other);
	private:
		unsigned char* data;
		size_t size;
		int sampleRate;
		int bitsPerSample;
		int numChannels;
	};
};

#endif
