/*** This file is part of FragmentFramework project ***/

#ifndef FFW_PBM_LOADER
#define FFW_PBM_LOADER

#include "imageLoader.hpp"

/*!
 * @ingroup File-Loaders
 */
namespace ffw{
	/*!
	 * @memberof ffw
	 * @ingroup File-Loaders
	 * @inherit imageLoader
	 * @brief PBM file loader
	 */
    class FFW_API pbmLoader: public imageLoader {
    public:
        pbmLoader();
		/*!
         * @memberof pbmLoader
         * @ingroup File-Loaders
		 * @brief Move constructor
         */
		pbmLoader(pbmLoader&& Other);
        ~pbmLoader();
        /*!
         * @memberof pbmLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::string& Path) override;
        /*!
         * @memberof pbmLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::wstring& Path) override;
        /*!
         * @memberof pbmLoader
         * @ingroup File-Loaders
		 * @override
         */
        void close() override;
        /*!
         * @memberof pbmLoader
         * @ingroup File-Loaders
		 * @override
         */
        bool readRow(unsigned char* Pixels) override;
		/*!
         * @memberof pbmLoader
         * @ingroup File-Loaders
		 * @const
		 * @override
         */
		bool firstRowIsTop() const override {
			return true;
		}
		/*!
         * @memberof pbmLoader
         * @ingroup File-Loaders
         */
		pbmLoader& operator = (pbmLoader&& Other);
		// Copy constructor is not allowed
		pbmLoader(const pbmLoader& Other) = delete;
		// Copy assigment operator is not allowed
		pbmLoader& operator = (const pbmLoader& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API loadPBM(const std::string& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API loadPBM(const std::wstring& Path, unsigned char** Pixels, int* Width, int* Height, imageType* Type);
};
#endif
