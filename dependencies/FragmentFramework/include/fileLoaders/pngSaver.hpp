/*** This file is part of FragmentFramework project ***/

#ifndef FFW_PNG_SAVER
#define FFW_PNG_SAVER

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
	class FFW_API pngSaver: public imageSaver {
    public:
        pngSaver();
		/*!
         * @memberof pngSaver
         * @ingroup File-Loaders
		 * @brief Move constructor
         */
		pngSaver(pngSaver&& Other);
        ~pngSaver();
        /*!
         * @memberof pngSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::string& Path, int Width, int Height, imageType Type) override;
        /*!
         * @memberof pngSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::wstring& Path, int Width, int Height, imageType Type) override;
        /*!
         * @memberof pngSaver
         * @ingroup File-Loaders
		 * @override
         */
        void close() override;
        /*!
         * @memberof pngSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool writeRow(unsigned char* Pixels) override;
        /*!
         * @memberof pngSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool writeFooter() override;
		/*!
         * @memberof pngSaver
         * @ingroup File-Loaders
		 * @override
		 * @const
         */
		bool firstRowIsTop() const override {
			return true;
		}
		/*!
         * @memberof pngSaver
         * @ingroup File-Loaders
		 * @override
         */
		pngSaver& operator = (pngSaver&& Other);
		// Copy constructor is not allowed
		pngSaver(const pngSaver& Other) = delete;
		// Copy assigment is not allowed
		pngSaver& operator = (const pngSaver& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API savePNG(const std::string& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API savePNG(const std::wstring& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
};
#endif


