/*
*   This file is part of FragmentFramework framework.
*   Copyright (C) 2013-2015 by Matus Novak matusnov@gmail.com
*   Licensed under the MIT License
*/

#ifndef FFW_LOGGER
#define FFW_LOGGER

#include "../common.h"

/*!
    @ingroup Utilities
*/
namespace ffw{
	enum logType {
		notice,
		debug,
		success,
		error,
		info,
		warning,
	};

	class logMsg;
	
	class FFW_API logger {
	public:
		logger();
		virtual ~logger();
		void setOutputStream(std::ostream* Stream);
		bool setOutputFile(const std::string& Path);
		void write(const logMsg& Msg);
		void enableColors(bool Enabled);
	private:
		std::fstream file;
		void* handle;
		bool colors;
		bool own;
		std::ostream* stream;
	};

	class FFW_API logMsg{
	public:
		logMsg(logger& Logger, const std::string& Tag);
		logMsg(logger& Logger, logType Type);
		virtual ~logMsg();

		template<typename T> logMsg& operator << (const T& Object){
			*ss << Object;
			return *this;
		}

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

	logMsg FFW_API log();
	logMsg FFW_API logNotice();
	logMsg FFW_API logDebug();
	logMsg FFW_API logSuccess();
	logMsg FFW_API logError();
	logMsg FFW_API logInfo();
	logMsg FFW_API logWarning();
	logMsg FFW_API log(const std::string& Tag);
	void FFW_API logEnableColors();
	void FFW_API logDisableColors();
	bool FFW_API logSetOutputFile(const std::string& Path);
	void FFW_API logSetOutputFileDefault();
};
#endif
