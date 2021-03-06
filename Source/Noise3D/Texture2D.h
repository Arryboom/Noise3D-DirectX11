
/***********************************************************************

                           h��ITexture

************************************************************************/

#pragma once

namespace Noise3D
{
	enum NOISE_IMAGE_FILE_FORMAT
	{
		NOISE_IMAGE_FILE_FORMAT_BMP,//Supported by DirectXTex.WIC
		NOISE_IMAGE_FILE_FORMAT_JPG,//Supported by  DirectXTex.WIC
		NOISE_IMAGE_FILE_FORMAT_PNG,//Supported by  DirectXTex.WIC
		NOISE_IMAGE_FILE_FORMAT_TIFF,//Supported by  DirectXTex.WIC
		NOISE_IMAGE_FILE_FORMAT_GIF,//Supported by  DirectXTex.WIC
		NOISE_IMAGE_FILE_FORMAT_TGA,//supported by DirectXTex
		NOISE_IMAGE_FILE_FORMAT_HDR,//supported by DirectXTex
		NOISE_IMAGE_FILE_FORMAT_DDS,//supported by DirectXTex
		NOISE_IMAGE_FILE_FORMAT_NOT_SUPPORTED = 0xffff
	};

	class /*declspec(dllexport)*/ Texture2D:
		public ITexture
	{
	public:

		void				SetPixel(UINT x, UINT y, const Color4u& color);

		Color4u		GetPixel(UINT x, UINT y) const;

		bool				SetPixelArray(const std::vector<Color4u>& in_ColorArray);//faster than setPixel() for every pixel because less check will be done

		bool				SetPixelArray(std::vector<Color4u>&& in_ColorArray);//faster than setPixel() for every pixel because less check will be done

		bool				GetPixelArray(std::vector<Color4u>& outColorArray) const;

		Color4f			SamplePixelBilinear(Vec2 texcoord) const;//sample a pixel

		bool				UpdateToVideoMemory();//update image's memory data to video memory

		bool				ConvertTextureToGreyMap();

		bool				ConvertTextureToGreyMap(float factorR, float factorG, float factorB);

		bool				ConvertHeightMapToNormalMap(float heightFieldScaleFactor = 10.0f);

		bool				SaveTexture2DToFile(NFilePath filePath, NOISE_IMAGE_FILE_FORMAT picFormat);

	private:

		friend  class TextureManager;

		friend IFactory<Texture2D>;

		Texture2D();

		~Texture2D();
		
		void	  NOISE_MACRO_FUNCTION_EXTERN_CALL mFunction_InitTexture(
			ID3D11ShaderResourceView* pSRV,
			const N_UID& uid,
			std::vector<Color4u>&& pixelBuff,
			bool isSysMemBuffValid) override;

	};

};