/*** This file is part of FragmentFramework project ***/

#ifndef FFW_BMP_SAVER
#define FFW_BMP_SAVER

#include "imageSaver.hpp"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @inherit imageSaver
	 * @brief BMP file saver
	 */
    class FFW_API bmpSaver: public imageSaver {
    public:
        bmpSaver();
		/*!
         * @memberof bmpSaver
         * @ingroup File-Loaders
		 * @brief Move constructor
         */
		bmpSaver(bmpSaver&& Other);
        ~bmpSaver();
        /*!
         * @memberof bmpSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::string& Path, int Width, int Height, imageType Type) override;
        /*!
         * @memberof bmpSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::wstring& Path, int Width, int Height, imageType Type) override;
        /*!
         * @memberof bmpSaver
         * @ingroup File-Loaders
		 * @override
         */
        void close() override;
        /*!
         * @memberof bmpSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool writeRow(unsigned char* Pixels) override;
        /*!
         * @memberof bmpSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool writeFooter() override;
		/*!
         * @memberof bmpSaver
         * @ingroup File-Loaders
		 * @override
		 * @const
         */
		bool firstRowIsTop() const override {
			return false;
		}
		/*!
         * @memberof bmpSaver
         * @ingroup File-Loaders
		 * @override
         */
		bmpSaver& operator = (bmpSaver&& Other);
		// Copy constructor is not allowed
		bmpSaver(const bmpSaver& Other) = delete;
		// Copy assigment is not allowed
		bmpSaver& operator = (const bmpSaver& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveBMP(const std::string& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
    /*!
        @memberof ffw
        @ingroup Utilities
    */
	bool FFW_API saveBMP(const std::wstring& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
};
#endif
