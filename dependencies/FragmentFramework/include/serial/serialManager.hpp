/*** This file is part of FragmentFramework project ***/

#ifndef FFW_SERIAL
#define FFW_SERIAL

#include "../common.h"

/*!
    @ingroup Serial
*/
namespace ffw {
    /*!
        @memberof ffw
        @ingroup Serial
    */
	class FFW_API serialManager {
    public:
        serialManager();
        ~serialManager();
        /*!
            @memberof serialManager
            @ingroup Serial
        */
        bool connect(const std::string& portName, unsigned int baudRate);
        /*!
            @memberof serialManager
            @ingroup Serial
        */
        bool isConnected();
        /*!
            @memberof serialManager
            @ingroup Serial
        */
        unsigned int isAvailable();
        /*!
            @memberof serialManager
            @ingroup Serial
        */
        size_t write(const std::string& message);
		bool write(char Byte);
        /*!
            @memberof serialManager
            @ingroup Serial
        */
        size_t write(const char* Data, unsigned int Size);
        /*!
            @memberof serialManager
            @ingroup Serial
        */
        size_t read(char* Data, unsigned int Size);
		char read();
        /*!
            @memberof serialManager
            @ingroup Serial
        */
        void close();

		void setTimeout(unsigned int ReadMillis, unsigned int WriteMillis);

		void flushIn();
		void flushOut();

    private:
        class impl;
        impl* pimpl;
    };
};
#endif
