/*** This file is part of FragmentFramework project ***/

#ifndef FFW_BMP_LOADER
#define FFW_BMP_LOADER

#include "imageLoader.hpp"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @inherit imageLoader
	 * @brief BMP file loader
	 */
    class FFW_API bmpLoader: public imageLoader {
    public:
        bmpLoader();
		/*!
         * @memberof bmpLoader
         * @ingroup File-Loaders
		 * @brief Move constructor
         */
		bmpLoader(bmpLoader&& Other);
        ~bmpLoader();
        /*!
         * @memberof bmpLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::string& Path) override;
        /*!
         * @memberof bmpLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::wstring& Path) override;
        /*!
         * @memberof bmpLoader
         * @ingroup File-Loaders
		 * @override
         */
        void close() override;
        /*!
         * @memberof bmpLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool readRow(unsigned char* Pixels) override;
		/*!
         * @memberof bmpLoader
         * @ingroup File-Loaders
		 * @const
		 * @override
         */
		bool firstRowIsTop() const override {
			return false;
		}
		/*!
         * @memberof bmpLoader
         * @ingroup File-Loaders
         */
		bmpLoader& operator = (bmpLoader&& Other);
		// Copy constructor is not allowed
		bmpLoader(const bmpLoader& Other) = delete;
		// Copy assigment operator is not allowed
		bmpLoader& operator = (const bmpLoader& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API loadBMP(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API loadBMP(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
};
#endif
