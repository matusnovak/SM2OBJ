/*** This file is part of FragmentFramework project ***/

#ifndef FFW_JPG_SAVER
#define FFW_JPG_SAVER

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
    class FFW_API jpgSaver: public imageSaver {
    public:
        jpgSaver();
		/*!
         * @memberof jpgSaver
         * @ingroup File-Loaders
		 * @brief Move constructor
         */
		jpgSaver(jpgSaver&& Other);
        ~jpgSaver();
        /*!
         * @memberof jpgSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::string& Path, int Width, int Height, imageType Type) override;
        /*!
         * @memberof jpgSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::wstring& Path, int Width, int Height, imageType Type) override;
        /*!
         * @memberof jpgSaver
         * @ingroup File-Loaders
		 * @override
         */
        void close() override;
        /*!
         * @memberof jpgSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool writeRow(unsigned char* Pixels) override;
        /*!
         * @memberof jpgSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool writeFooter() override;
		/*!
         * @memberof jpgSaver
         * @ingroup File-Loaders
		 * @override
		 * @const
         */
		bool firstRowIsTop() const override {
			return true;
		}
		/*!
         * @memberof jpgSaver
         * @ingroup File-Loaders
		 * @override
         */
		jpgSaver& operator = (jpgSaver&& Other);
		// Copy constructor is not allowed
		jpgSaver(const jpgSaver& Other) = delete;
		// Copy assigment is not allowed
		jpgSaver& operator = (const jpgSaver& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API saveJPG(const std::string& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API saveJPG(const std::wstring& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
};
#endif
