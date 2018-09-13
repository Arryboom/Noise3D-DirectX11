#pragma once

#include <QMessageBox>
#include <qtimer.h>
#include <qevent.h>
#include <QtWidgets/QMainWindow>
#include "Main3D.h"
#include "Widget_RenderCanvas.h"
#include "ui_GUISHLighting.h"

class GUISHLightingApp : public QMainWindow
{
	Q_OBJECT

public:
	GUISHLightingApp(QWidget *parent = Q_NULLPTR);

	~GUISHLightingApp();

public slots:

	void Slot_Menu_Exit();

	void Slot_Menu_About();

	void Slot_LoadSphericalTexture();

	void Slot_LoadCubeMap();

	//void Slot_MouseInputProcess(QMouseEvent * ev);


private:

	Ui::SHLightingGuiApp mUI;
	Widget_RenderCanvas* m_pRenderCanvas;//customized widget (manually created)
};