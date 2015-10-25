/*** This file is part of FragmentFramework project ***/

#ifndef FFW_PNG_LOADER
#define FFW_PNG_LOADER

#include "imageLoader.hpp"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @inherit imageLoader
	 * @brief PNG file loader
	 */
    class FFW_API pngLoader: public imageLoader {
    public:
        pngLoader();
		/*!
         * @memberof pngLoader
         * @ingroup File-Loaders
		 * @brief Move constructor
         */
		pngLoader(pngLoader&& Other);
        ~pngLoader();
        /*!
         * @memberof pngLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::string& Path) override;
        /*!
         * @memberof pngLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::wstring& Path) override;
        /*!
         * @memberof pngLoader
         * @ingroup File-Loaders
		 * @override
         */
        void close() override;
        /*!
         * @memberof pngLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool readRow(unsigned char* Pixels) override;
		/*!
         * @memberof pngLoader
         * @ingroup File-Loaders
		 * @const
		 * @override
         */
		bool firstRowIsTop() const override {
			return true;
		}
		/*!
         * @memberof pngLoader
         * @ingroup File-Loaders
         */
		pngLoader& operator = (pngLoader&& Other);
		// Copy constructor is not allowed
		pngLoader(const pngLoader& Other) = delete;
		// Copy assigment operator is not allowed
		pngLoader& operator = (const pngLoader& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API loadPNG(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API loadPNG(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
};
#endif


