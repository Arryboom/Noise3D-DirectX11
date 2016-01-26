/***********************************************************************

										cpp��Noise2DText

************************************************************************/
#include "Noise3D.h"
#include "N2D_Noise2DTextStatic.h"

Noise2DTextStatic::Noise2DTextStatic()
{
	m_pTextureName = new std::string;

}

NVECTOR2 Noise2DTextStatic::GetFontSize(UINT fontID)
{
	if (!IsInitialized())return NVECTOR2(0, 0);
	return m_pFatherFontMgr->GetFontSize(fontID);
}

void Noise2DTextStatic::Destroy()
{
	m_pGraphicObj->SelfDestruction();
};

/************************************************************************
											P R I V A T E
************************************************************************/

void Noise2DTextStatic::mFunction_InitGraphicObject(UINT pxWidth, UINT pxHeight,NVECTOR4 color,UINT texID)
{

	m_pGraphicObj->AddRectangle(
		NVECTOR2(float(pxWidth) / 2.0f, float(pxHeight) / 2.0f),
		float(pxWidth),
		float(pxHeight),
		color,
		texID
		);

	mStringTextureID = texID;
	*m_pTextColor = color;
	*m_pTextGlowColor = color;
	Noise2DBasicContainerInfo::SetWidth(float(pxWidth));
	Noise2DBasicContainerInfo::SetHeight(float(pxHeight));
}

void Noise2DTextStatic::mFunction_UpdateGraphicObject()
{
	if (!NoiseClassLifeCycle::IsInitialized())return;

	//in case other font has been deleted 
	UINT stringTexID = mStringTextureID;

	m_pGraphicObj->SetRectangle(
		0,
		Noise2DBasicContainerInfo::GetTopLeft(),
		Noise2DBasicContainerInfo::GetBottomRight(),
		NVECTOR4(1.0f, 1.0f, 1.0f, 1.0f),
		stringTexID
		);

	//rectangle depth,used for 2D overlapping
	m_pGraphicObj->SetRectangleDepth(0, mPosZ);
};

