/*** This file is part of FragmentFramework project ***/

#ifndef FFW_TGA_SAVER
#define FFW_TGA_SAVER

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
    class FFW_API tgaSaver: public imageSaver {
    public:
        tgaSaver();
		/*!
         * @memberof tgaSaver
         * @ingroup File-Loaders
		 * @brief Move constructor
         */
		tgaSaver(tgaSaver&& Other);
        ~tgaSaver();
        /*!
         * @memberof tgaSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::string& Path, int Width, int Height, imageType Type) override;
        /*!
         * @memberof tgaSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::wstring& Path, int Width, int Height, imageType Type) override;
        /*!
         * @memberof tgaSaver
         * @ingroup File-Loaders
		 * @override
         */
        void close() override;
        /*!
         * @memberof tgaSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool writeRow(unsigned char* Pixels) override;
        /*!
         * @memberof tgaSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool writeFooter() override;
		/*!
         * @memberof tgaSaver
         * @ingroup File-Loaders
		 * @override
		 * @const
         */
		bool firstRowIsTop() const override {
			return false;
		}
		/*!
         * @memberof tgaSaver
         * @ingroup File-Loaders
		 * @override
         */
		tgaSaver& operator = (tgaSaver&& Other);
		// Copy constructor is not allowed
		tgaSaver(const tgaSaver& Other) = delete;
		// Copy assigment is not allowed
		tgaSaver& operator = (const tgaSaver& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API saveTGA(const std::string& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API saveTGA(const std::wstring& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
};
#endif

