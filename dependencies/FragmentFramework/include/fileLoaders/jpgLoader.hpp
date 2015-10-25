/*** This file is part of FragmentFramework project ***/

#ifndef FFW_JPG_LOADER
#define FFW_JPG_LOADER

#include "imageLoader.hpp"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @inherit imageLoader
	 * @brief JPG file loader
	 */
	class FFW_API jpgLoader: public imageLoader {
    public:
        jpgLoader();
		/*!
         * @memberof jpgLoader
         * @ingroup File-Loaders
		 * @brief Move constructor
         */
		jpgLoader(jpgLoader&& Other);
        ~jpgLoader();
        /*!
         * @memberof jpgLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::string& Path) override;
        /*!
         * @memberof jpgLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::wstring& Path) override;
        /*!
         * @memberof jpgLoader
         * @ingroup File-Loaders
		 * @override
         */
        void close() override;
        /*!
         * @memberof jpgLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool readRow(unsigned char* Pixels) override;
		/*!
         * @memberof jpgLoader
         * @ingroup File-Loaders
		 * @const
		 * @override
         */
		bool firstRowIsTop() const override {
			return true;
		}
		/*!
         * @memberof jpgLoader
         * @ingroup File-Loaders
         */
		jpgLoader& operator = (jpgLoader&& Other);
		// Copy constructor is not allowed
		jpgLoader(const jpgLoader& Other) = delete;
		// Copy assigment operator is not allowed
		jpgLoader& operator = (const jpgLoader& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API loadJPG(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API loadJPG(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
};
#endif
