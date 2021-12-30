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

int main(int argc, char* argv[])
{
	
  QQuickVTKRenderWindow::setupGraphicsBackend();
  //QQuickWindow::setGraphicsApi(QSGRendererInterface::OpenGLRhi);

  QGuiApplication app(argc, argv);
 
  QQmlApplicationEngine engine;
  engine.addImportPath("D:/Project/vtk/build-master/lib/qml/Release");
  qDebug() << "QML2_IMPORT_PATH:" << engine.importPathList();
  engine.load(QUrl("qrc:///qmlvtk.qml"));
 
  QObject* topLevel = engine.rootObjects().value(0);
  QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel);
 
  window->show();
 
  // Fetch the QQuick window using the standard object name set up in the constructor
  QQuickVTKRenderItem* qquickvtkItem = topLevel->findChild<QQuickVTKRenderItem*>("ConeView");
 
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