#include "QQuickVTKRenderItem.h"
#include "QQuickVTKRenderWindow.h"
#include "vtkActor.h"
#include "vtkConeSource.h"
#include "vtkGenericOpenGLRenderWindow.h"
#include "vtkNew.h"
#include "vtkPNGWriter.h"
#include "vtkPolyDataMapper.h"
#include "vtkRenderer.h"
#include "vtkTestUtilities.h"
#include "vtkTesting.h"
#include "vtkWindowToImageFilter.h"

#include <QApplication>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QTimer>
#include <QUrl>
#include <QDir>

#include "config.h"

int main(int argc, char* argv[])
{
	
  QQuickVTKRenderWindow::setupGraphicsBackend();
  //QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);

  QGuiApplication app(argc, argv);
 
  QDir vtkqmlDir(VTK_QML_DIR);
  
	 
  QQmlApplicationEngine engine;
#ifdef _DEBUG
  engine.addImportPath(vtkqmlDir.absoluteFilePath("Debug"));
#else
  engine.addImportPath(vtkqmlDir.absoluteFilePath("Release"));
#endif // _DEBUG

  engine.load(QUrl("qrc:///qmlvtk.qml"));
 
  QObject* topLevel = engine.rootObjects().value(0);
  QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);
 
  window->show();
 
  // Fetch the QQuick window using the standard object name set up in the constructor
  auto* qquickObject = topLevel->findChild<QObject*>("ConeView");
  auto* qquickvtkItem = dynamic_cast<QQuickVTKRenderItem*>(qquickObject);
 
  // Create a cone pipeline and add it to the view
  vtkNew<vtkActor> actor;
  vtkNew<vtkPolyDataMapper> mapper;
  vtkNew<vtkConeSource> cone;
  mapper->SetInputConnection(cone->GetOutputPort());
  actor->SetMapper(mapper);
  qquickvtkItem->renderer()->AddActor(actor);
  qquickvtkItem->renderer()->ResetCamera();
  qquickvtkItem->renderer()->SetBackground(0.5, 0.5, 0.7);
  qquickvtkItem->renderer()->SetBackground2(0.7, 0.7, 0.7);
  qquickvtkItem->renderer()->SetGradientBackground(true);
  qquickvtkItem->update();
  app.exec();
}