/*** This file is part of FragmentFramework project ***/

#ifndef FFW_TIFF_SAVER
#define FFW_TIFF_SAVER

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
    class FFW_API tiffSaver: public imageSaver {
    public:
        tiffSaver();
		/*!
         * @memberof tiffSaver
         * @ingroup File-Loaders
		 * @brief Move constructor
         */
		tiffSaver(tiffSaver&& Other);
        ~tiffSaver();
        /*!
         * @memberof tiffSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::string& Path, int Width, int Height, imageType Type) override;
        /*!
         * @memberof tiffSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::wstring& Path, int Width, int Height, imageType Type) override;
        /*!
         * @memberof tiffSaver
         * @ingroup File-Loaders
		 * @override
         */
        void close() override;
        /*!
         * @memberof tiffSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool writeRow(unsigned char* Pixels) override;
        /*!
         * @memberof tiffSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool writeFooter() override;
		/*!
         * @memberof tiffSaver
         * @ingroup File-Loaders
		 * @override
		 * @const
         */
		bool firstRowIsTop() const override {
			return true;
		}
		/*!
         * @memberof tiffSaver
         * @ingroup File-Loaders
		 * @override
         */
		tiffSaver& operator = (tiffSaver&& Other);
		// Copy constructor is not allowed
		tiffSaver(const tiffSaver& Other) = delete;
		// Copy assigment is not allowed
		tiffSaver& operator = (const tiffSaver& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API saveTIFF(const std::wstring& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API saveTIFF(const std::string& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
};
#endif


