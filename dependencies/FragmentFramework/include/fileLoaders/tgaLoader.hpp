/*** This file is part of FragmentFramework project ***/

#ifndef FFW_TGA_LOADER
#define FFW_TGA_LOADER

#include "imageLoader.hpp"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @inherit imageLoader
	 * @brief TGA file loader
	 */
	class FFW_API tgaLoader: public imageLoader {
    public:
        tgaLoader();
		/*!
         * @memberof tgaLoader
         * @ingroup File-Loaders
		 * @brief Move constructor
         */
		tgaLoader(tgaLoader&& Other);
        ~tgaLoader();
        /*!
         * @memberof tgaLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::string& Path) override;
        /*!
         * @memberof tgaLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::wstring& Path) override;
        /*!
         * @memberof tgaLoader
         * @ingroup File-Loaders
		 * @override
         */
        void close() override;
        /*!
         * @memberof tgaLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool readRow(unsigned char* Pixels) override;
		/*!
         * @memberof tgaLoader
         * @ingroup File-Loaders
		 * @const
		 * @override
         */
		bool firstRowIsTop() const override {
			return false;
		}
		/*!
         * @memberof tgaLoader
         * @ingroup File-Loaders
         */
		tgaLoader& operator = (tgaLoader&& Other);
		// Copy constructor is not allowed
		tgaLoader(const tgaLoader& Other) = delete;
		// Copy assigment operator is not allowed
		tgaLoader& operator = (const tgaLoader& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API loadTGA(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API loadTGA(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
};
#endif

