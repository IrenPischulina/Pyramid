#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QImage>
#include <QDebug>
#include <QGraphicsScene>

#include "AbstractImage.h"
#include "Image.h"
#include "ILayerHandler.h"
#include "NearestNeighborLayerHandler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void openFile();

private:
    void addImage(QString &fileName);
    void changeCurrentImage(int index);
    void changeCurrentLayer(int index);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *m_scene;
    ILayerHandler * m_layerHandler;
    QList<Image> m_imagesList;
};
#endif // MAINWINDOW_H
