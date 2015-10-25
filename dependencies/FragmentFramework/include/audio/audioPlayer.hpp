/*** This file is part of FragmentFramework project ***/

#ifndef FFW_AUDIO_PLAYER
#define FFW_AUDIO_PLAYER

#include "../common.h"
#include "audioDevice.hpp"
#include "audioBuffer.hpp"
#include "audioStream.hpp"

/*!
 * @ingroup Audio
 */
namespace ffw {
	/*!
	 * @memberof ffw
	 * @ingroup Audio
	 */
	class FFW_API audioPlayer{
	public:
		audioPlayer();
		audioPlayer(audioPlayer&& Other);
		audioPlayer(const audioPlayer& Other) = delete;
		virtual ~audioPlayer();
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Creates an audio player
		 */
		bool create(const audioOutputDevice* Device, unsigned char* Data, size_t Size, int BitsPerSample, int SampleRate, int NumOfChannels);
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Creates an audio player from source file
		 */
		bool createFromFile(const audioOutputDevice* Device, const std::string& Path);
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Creates an audio player from source file
		 */
		bool createFromFile(const audioOutputDevice* Device, const std::wstring& Path);
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Returns a pointer to the raw buffer data
		 */
		unsigned char* getDataPtr();
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Returns a pointer to the raw buffer data
		 * @const
		 */
		const unsigned char* getDataPtr() const;
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Destroys the buffer
		 */
		void destroy();
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Checks if a player is created
		 * @const
		 */
		bool isCreated() const;
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Plays the audio from beginning
		 */
		bool play();
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Stops the audio
		 */
		bool stop();
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Continues playing the audio if stopped
		 */
		bool playContinue();
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Checks if playing
		 * @const
		 */
		bool isPlaying() const;
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Sets the loop flag
		 */
		void setLooping(bool Looping);
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Checks if an audio is on a loop
		 * @const
		 */
		bool isLooping() const;
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Returns the current audio play time in seconds
		 * @const
		 */
		double getTime() const;
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Returns the current audio play time in bytes
		 * @const
		 */
		size_t getTimeBytes() const;
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Sets the gain
		 */
		void setGain(float Gain);
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Returns the gain
		 * @const
		 */
		float getGain() const;
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Returns the bit depth of one sample
		 * @const
		 */
		int getBitsPerSample() const;
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Returns the sample rate
		 * @const
		 */
		int getSampleRate() const;
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Returns the number of channels
		 * @const
		 */
		int getNumOfChannels() const;
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Sets the time offset in seconds
		 */
		bool setOffset(double Seconds);
		/*!
		 * @memberof audioPlayer
		 * @ingroup Audio
		 * @brief Sets the time offset in bytes
		 */
		bool setOffsetBytes(size_t Bytes);
		
		audioPlayer& operator = (const audioPlayer& Other) = delete;
		audioPlayer& operator = (audioPlayer&& Other);
	private:
		audioBuffer buffer;
		audioOutputStream stream;
	};
};

#endif
