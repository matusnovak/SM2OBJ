/*** This file is part of FragmentFramework project ***/

#ifndef FFW_PBM_SAVER
#define FFW_PBM_SAVER

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
    class FFW_API pbmSaver: public imageSaver {
    public:
        pbmSaver();
		/*!
         * @memberof pbmSaver
         * @ingroup File-Loaders
		 * @brief Move constructor
         */
		pbmSaver(pbmSaver&& Other);
        ~pbmSaver();
        /*!
         * @memberof pbmSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::string& Path, int Width, int Height, imageType Type) override;
        /*!
         * @memberof pbmSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool open(const std::wstring& Path, int Width, int Height, imageType Type) override;
        /*!
         * @memberof pbmSaver
         * @ingroup File-Loaders
		 * @override
         */
        void close() override;
        /*!
         * @memberof pbmSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool writeRow(unsigned char* Pixels) override;
        /*!
         * @memberof pbmSaver
         * @ingroup File-Loaders
		 * @override
         */
        bool writeFooter() override;
		/*!
         * @memberof pbmSaver
         * @ingroup File-Loaders
		 * @override
		 * @const
         */
		bool firstRowIsTop() const override {
			return true;
		}
		/*!
         * @memberof pbmSaver
         * @ingroup File-Loaders
		 * @override
         */
		pbmSaver& operator = (pbmSaver&& Other);
		// Copy constructor is not allowed
		pbmSaver(const pbmSaver& Other) = delete;
		// Copy assigment is not allowed
		pbmSaver& operator = (const pbmSaver& Other) = delete;

    private:
        class impl;
        impl* pimpl;
    };
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API savePBM(const std::string& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
    /*!
     * @memberof ffw
     * @ingroup File-Loaders
     */
	bool FFW_API savePBM(const std::wstring& Path, unsigned char* Pixels, int Width, int Height, imageType Type);
};
#endif
