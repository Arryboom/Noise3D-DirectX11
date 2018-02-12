
/***********************************************************************

										IRenderer
			Composition of infrastructure and render modules

************************************************************************/

#include "Noise3D.h"

using namespace Noise3D;

IRenderer::IRenderer():
	IFactory<IRenderInfrastructure>(1)
{
}

IRenderer::~IRenderer()
{
	IFactory<IRenderInfrastructure>::DestroyAllObject();
};

void IRenderer::AddToRenderQueue(IMesh * obj)
{
	IRenderModuleForMesh::AddToRenderQueue(obj);
}

void IRenderer::AddToRenderQueue(IGraphicObject * obj)
{
	IRenderModuleForGraphicObject::AddToRenderQueue(obj);
}

void IRenderer::AddToRenderQueue(IDynamicText * obj)
{
	IRenderModuleForText::AddToRenderQueue(obj);
}

void IRenderer::AddToRenderQueue(IStaticText * obj)
{
	IRenderModuleForText::AddToRenderQueue(obj);
}

void IRenderer::SetActiveAtmosphere(IAtmosphere * obj)
{
	IRenderModuleForAtmosphere::SetActiveAtmosphere(obj);
}

void IRenderer::Render()
{
	//this affects the decision of Render Targets
	m_pRenderInfrastructure->SetPostProcessRemainingPassCount(IRenderModuleForPostProcessing::GetPostProcessPassCount());

	IRenderModuleForMesh::RenderMeshes();
	IRenderModuleForAtmosphere::RenderAtmosphere();
	IRenderModuleForGraphicObject::RenderGraphicObjects();
	IRenderModuleForText::RenderTexts();

	IRenderModuleForPostProcessing::PostProcess();
	
}

void	IRenderer::ClearBackground(const NVECTOR4& color)
{
	m_pRenderInfrastructure->ClearRtvAndDsv(color);
};

void	IRenderer::PresentToScreen()
{
	m_pRenderInfrastructure->SwapChainPresent();

	//pop out rendered objects
	IRenderModuleForAtmosphere::ClearRenderList();
	IRenderModuleForGraphicObject::ClearRenderList();
	IRenderModuleForMesh::ClearRenderList();
	IRenderModuleForText::ClearRenderList();
	IRenderModuleForPostProcessing::ClearRenderList();//no use
};


UINT IRenderer::GetBackBufferWidth()
{
	return m_pRenderInfrastructure->GetBackBufferWidth();
};

UINT IRenderer::GetBackBufferHeight()
{
	return m_pRenderInfrastructure->GetBackBufferHeight();
}

HWND IRenderer::GetRenderWindowHWND()
{
	return m_pRenderInfrastructure->GetRenderWindowHWND();
}

void IRenderer::SwitchToFullScreenMode()
{
	m_pRenderInfrastructure->SwitchToFullScreenMode();
}

void IRenderer::SwitchToWindowedMode()
{
	m_pRenderInfrastructure->SwitchToWindowedMode();
}

/************************************************************************
                                            PRIVATE                        
************************************************************************/
bool	IRenderer::mFunction_Init(UINT BufferWidth, UINT BufferHeight, HWND renderWindowHandle)
{
	//1. try to init a unique render infrastructure 
	//(failure could affect the creation of IRenderer)
	static const N_UID uid = "RI";
	if (IFactory<IRenderInfrastructure>::GetObjectCount() == 0)
	{
		m_pRenderInfrastructure = IFactory<IRenderInfrastructure>::CreateObject(uid);
		if (!m_pRenderInfrastructure->Init(BufferWidth, BufferHeight,renderWindowHandle))
		{
			IFactory<IRenderInfrastructure>::DestroyObject(uid);
			m_pRenderInfrastructure = nullptr;
			ERROR_MSG("IRenderer: failed to init render infrastructure.");
			return false;
		}
	}

	//2. Init Render Modules
	IShaderVariableManager* pSVM = m_pRenderInfrastructure->GetRefToShaderVarMgr();
	IRenderModuleForAtmosphere::Initialize(m_pRenderInfrastructure, pSVM);
	IRenderModuleForGraphicObject::Initialize(m_pRenderInfrastructure, pSVM);
	IRenderModuleForMesh::Initialize(m_pRenderInfrastructure, pSVM);
	IRenderModuleForText::Initialize(m_pRenderInfrastructure, pSVM);
	IRenderModuleForPostProcessing::Initialize(m_pRenderInfrastructure, pSVM);

	return true;
}


