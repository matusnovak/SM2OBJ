/*** This file is part of FragmentFramework project ***/

#ifndef FFW_TIFF_LOADER
#define FFW_TIFF_LOADER

#include "imageLoader.hpp"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @inherit imageLoader
	 * @brief TIFF file loader
	 */
    class FFW_API tiffLoader: public imageLoader {
    public:
        tiffLoader();
		/*!
         * @memberof tiffLoader
         * @ingroup File-Loaders
		 * @brief Move constructor
         */
		tiffLoader(tiffLoader&& Other);
        ~tiffLoader();
        /*!
         * @memberof tiffLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::string& Path) override;
        /*!
         * @memberof tiffLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::wstring& Path) override;
        /*!
         * @memberof tiffLoader
         * @ingroup File-Loaders
		 * @override
         */
        void close() override;
        /*!
         * @memberof tiffLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool readRow(unsigned char* Pixels) override;
		/*!
         * @memberof tiffLoader
         * @ingroup File-Loaders
		 * @const
		 * @override
         */
		bool firstRowIsTop() const override {
			return true;
		}
		/*!
         * @memberof tiffLoader
         * @ingroup File-Loaders
         */
		tiffLoader& operator = (tiffLoader&& Other);
		// Copy constructor is not allowed
		tiffLoader(const tiffLoader& Other) = delete;
		// Copy assigment operator is not allowed
		tiffLoader& operator = (const tiffLoader& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API loadTIFF(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API loadTIFF(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
};
#endif


