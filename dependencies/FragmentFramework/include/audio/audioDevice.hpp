/*** This file is part of FragmentFramework project ***/

#ifndef FFW_AUDIO_DEVICE
#define FFW_AUDIO_DEVICE

#include "../common.h"

/*!
 * @ingroup Audio
 */
namespace ffw {
	/*!
	 * @memberof ffw
	 * @ingroup Audio
	 */
	class FFW_API audioOutputDevice{
	public:
		/*!
		 * @memberof audioOutputDevice
		 * @ingroup Audio
		 * @brief Constructor
		 * @name audioOutputDevice
		 */
		audioOutputDevice(const std::string& Name, int Index, int DefaultSamples, double Low, double High, int MaxChannels);
		~audioOutputDevice();
		/*!
		 * @memberof audioOutputDevice
		 * @ingroup Audio
		 * @brief Returns the lower latency
		 * @const
		 */
		double getLatencyLow() const;
		/*!
		 * @memberof audioOutputDevice
		 * @ingroup Audio
		 * @brief Returns the higher latency
		 * @const
		 */
		double getLatencyHigh() const;
		/*!
		 * @memberof audioOutputDevice
		 * @ingroup Audio
		 * @brief Returns the maximum available channels
		 * @const
		 */
		int getMaxChannels() const;
		/*!
		 * @memberof audioOutputDevice
		 * @ingroup Audio
		 * @brief Returns the device index
		 * @const
		 */
		int getIndex() const;
		/*!
		 * @memberof audioOutputDevice
		 * @ingroup Audio
		 * @brief Returns the device name
		 * @const
		 */
		const std::string& getName() const;
		/*!
		 * @memberof audioOutputDevice
		 * @ingroup Audio
		 * @brief Returns the default sample rate
		 * @const
		 */
		int getDefaultSampleRate() const;
		/*!
		 * @memberof audioOutputDevice
		 * @ingroup Audio
		 * @brief Checks if a format is compatible with device
		 * @const
		 */
		bool isFormatCompatible(int Samples, int BitsPerSample, int NumOfChannels) const;
	private:
		std::string name;
		int index;
		int defaultSamples;
		double low;
		double high;
		int maxChannels;
	};

	/*!
	 * @memberof ffw
	 * @ingroup Audio
	 */
	class FFW_API audioInputDevice{
	public:
		/*!
		 * @memberof audioInputDevice
		 * @ingroup Audio
		 * @brief Constructor
		 * @name audioInputDevice
		 */
		audioInputDevice(const std::string& Name, int Index, int DefaultSamples, double Low, double High, int MaxChannels);
		~audioInputDevice();
		/*!
		 * @memberof audioInputDevice
		 * @ingroup Audio
		 * @brief Returns the lower latency
		 * @const
		 */
		double getLatencyLow() const;
		/*!
		 * @memberof audioInputDevice
		 * @ingroup Audio
		 * @brief Returns the higher latency
		 * @const
		 */
		double getLatencyHigh() const;
		/*!
		 * @memberof audioInputDevice
		 * @ingroup Audio
		 * @brief Returns the maximum available channels
		 * @const
		 */
		int getMaxChannels() const;
		/*!
		 * @memberof audioInputDevice
		 * @ingroup Audio
		 * @brief Returns the device index
		 * @const
		 */
		int getIndex() const;
		/*!
		 * @memberof audioInputDevice
		 * @ingroup Audio
		 * @brief Returns the device name
		 * @const
		 */
		const std::string& getName() const;
		/*!
		 * @memberof audioInputDevice
		 * @ingroup Audio
		 * @brief Returns the default sample rate
		 * @const
		 */
		int getDefaultSampleRate() const;
		/*!
		 * @memberof audioInputDevice
		 * @ingroup Audio
		 * @brief Checks if a format is compatible with device
		 * @const
		 */
		bool isFormatCompatible(int Samples, int BitsPerSample, int NumOfChannels) const;
	private:
		std::string name;
		int index;
		int defaultSamples;
		double low;
		double high;
		int maxChannels;
	};
};

#endif