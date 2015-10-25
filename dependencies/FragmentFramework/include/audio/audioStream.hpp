/*** This file is part of FragmentFramework project ***/

#ifndef FFW_AUDIO_STREAM
#define FFW_AUDIO_STREAM

#include "../common.h"
#include "audioDevice.hpp"
#include "audioBuffer.hpp"

/*!
 * @ingroup Audio
 */
namespace ffw {
	/*!
	 * @memberof ffw
	 * @ingroup Audio
	 */
	class FFW_API audioOutputStream{
	public:
		audioOutputStream();
		audioOutputStream(audioOutputStream&& Other);
		audioOutputStream(const audioOutputStream& Other) = delete;
		virtual ~audioOutputStream();
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Creates the output stream
		 */
		bool create(const audioOutputDevice* Device, int BitsPerSample, int SampleRate, int NumOfChannels, int QueueSize);
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Adds a buffer to queue
		 */
		bool queueBuffer(audioBuffer* Buffer);
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Returns a used buffer from a queue
		 */
		bool unqueueBuffer(audioBuffer** Buffer);
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Destroys the stream
		 */
		void destroy();
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Checks if the stream is created
		 * @const
		 */
		bool isCreated() const;
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Continues playing the audio if stopped
		 */
		bool playContinue();
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Plays the audio from beginning
		 */
		bool play();
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Stops the audio
		 */
		bool stop();
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Checks if the audio is playing
		 * @const
		 */
		bool isPlaying() const;
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Sets the loop flag
		 */
		void setLooping(bool Looping);
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Checks if the audio is in a loop
		 * @const
		 */
		bool isLooping() const;
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Returns the current audio play time in seconds
		 * @const
		 */
		double getTime() const;
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Returns the current audio play time in bytes
		 * @const
		 */
		size_t getTimeBytes() const;
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Sets the gain
		 */
		void setGain(float Gain);
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Returns the gain
		 * @const
		 */
		float getGain() const;
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Returns the bit depth of one sample
		 * @const
		 */
		int getBitsPerSample() const;
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Returns the sample rate
		 * @const
		 */
		int getSampleRate() const;
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Returns the number of channels
		 * @const
		 */
		int getNumOfChannels() const;
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Returns the buffer queue length
		 * @const
		 */
		int getQueueSize() const;
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Returns the used space in input queue
		 * @const
		 */
		size_t getQueueInSize() const;
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Returns the used space in output queue
		 * @const
		 */
		size_t getQueueOutSize() const;
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Clears the input and output queue
		 */
		void clearQueue();
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Sets the time offset in seconds
		 */
		bool setOffset(double Seconds);
		/*!
		 * @memberof audioOutputStream
		 * @ingroup Audio
		 * @brief Sets the time offset in bytes
		 */
		bool setOffsetBytes(size_t Bytes);
		
		audioOutputStream& operator = (const audioOutputStream& Other) = delete;
		audioOutputStream& operator = (audioOutputStream&& Other);
	private:
		class impl;
		impl* pimpl;
	};
};

#endif