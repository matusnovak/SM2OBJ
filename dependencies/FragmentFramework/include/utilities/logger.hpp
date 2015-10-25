/*** This file is part of FragmentFramework project ***/

#ifndef FFW_LOGGER
#define FFW_LOGGER

#include "../common.h"
#include "mutex.hpp"

/*!
 * @ingroup Utilities
 */
namespace ffw{
	/*!
     * @memberof ffw
     * @ingroup Utilities
     */
	enum logType {
		notice,
		debug,
		success,
		error,
		info,
		warning,
	};

	class logMsg;

	/*!
     * @memberof ffw
     * @ingroup Utilities
     */
	class FFW_API logger {
	public:
		logger();
		logger(logger&& Other) = delete;
		logger(const logger& Other) = delete;
		virtual ~logger();
		/*!
         * @memberof logger
         * @ingroup Utilities
		 * @brief Sets the output stream (default = std::cout)
         */
		void setOutputStream(std::ostream* Stream);
		/*!
         * @memberof logger
         * @ingroup Utilities
		 * @brief Sets the output file
         */
		bool setOutputFile(const std::string& Path);
		/*!
         * @memberof logger
         * @ingroup Utilities
		 * @brief Writes a message to the log
         */
		void write(const logMsg& Msg);
		/*!
         * @memberof logger
         * @ingroup Utilities
		 * @brief Enables or disables the colors
         */
		void enableColors(bool Enabled);

		logger& operator = (logger&& Other) = delete;
		logger& operator = (const logger& Other) = delete;
	private:
		std::fstream file;
		void* handle;
		bool colors;
		std::ostream* stream;
		ffw::mutex mut;
	};

	/*!
     * @memberof ffw
     * @ingroup Utilities
     */
	class FFW_API logMsg{
	public:
		/*!
         * @memberof logMsg
         * @ingroup Utilities
         */
		logMsg(logger& Logger, const std::string& Tag);
		/*!
         * @memberof logMsg
         * @ingroup Utilities
         */
		logMsg(logger& Logger, logType Type);
		virtual ~logMsg();
		/*!
         * @memberof logMsg
         * @ingroup Utilities
         */
		template<typename T> logMsg& operator << (const T& Object){
			*ss << Object;
			return *this;
		}
		/*!
         * @memberof logMsg
         * @ingroup Utilities
         */
		logMsg& operator << (std::ostream& (*func)(std::ostream&)){
			func(*ss);
			return *this;
		}
		friend class logger;
	private:
		logger& output;
		std::ostringstream* ss;
		std::string tag;
		logType type;
	};

	/*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Logs a message as default
     */
	logMsg FFW_API log();
	/*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Logs a message as notice
     */
	logMsg FFW_API logNotice();
	/*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Logs a message as debug
     */
	logMsg FFW_API logDebug();
	/*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Logs a message as success
     */
	logMsg FFW_API logSuccess();
	/*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Logs a message as error
     */
	logMsg FFW_API logError();
	/*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Logs a message as info
     */
	logMsg FFW_API logInfo();
	/*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Logs a message as warning
     */
	logMsg FFW_API logWarning();
	/*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Logs a message with specific tag
     */
	logMsg FFW_API log(const std::string& Tag);
	/*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Enables color messages in terminal
     */
	void FFW_API logEnableColors();
	/*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Disables color messages in terminal
     */
	void FFW_API logDisableColors();
	/*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Sets log's output file
     */
	bool FFW_API logSetOutputFile(const std::string& Path);
	/*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Sets log's output file to log.txt next to executable
     */
	void FFW_API logSetOutputFileDefault();
	/*!
     * @memberof ffw
     * @ingroup Utilities
	 * @brief Default logger class instance
     */
	extern logger mainLog;
};
#endif
