#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //построение слоев будет осуществляться методом k ближайших соседей
    m_layerHandler = new NearestNeighborLayerHandler();
    //создание сцены и задание параметров отображения скроллбаров
    m_scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //открытие файла
    connect(ui->openFileAction, &QAction::triggered,
            this, &MainWindow::openFile);
    //смена изображения
    connect(ui->fileComboBox,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int index){this->changeCurrentImage(index);});
    //смена слоя
    connect(ui->layerComboBox,
            QOverload<int>::of(&QComboBox::currentIndexChanged),
            [this](int index){this->changeCurrentLayer(index);});
}

MainWindow::~MainWindow()
{
    delete m_scene;
    delete ui;
}

void MainWindow::openFile()
{
    //вызов диалогового окна для выбора png или jpg изображения
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open file"),
                                                    tr(""),
                                                    tr( "Изображения(*.png *.jpg)" ));

    if(!fileName.isNull()) {
        addImage(fileName);
    }
}

void MainWindow::addImage(QString &fileName)
{
    QFile file(fileName);
    QFileInfo info(file);
    QImage image(fileName);
    int layersCount = m_layerHandler->countLayersNumber(image, 2);
    Image img(image.width(), image.height(), info.fileName(), image, layersCount);
    int insertIndex=0;
    if(m_imagesList.size() == 1) {
        if(m_imagesList[0].getDiagonal() < img.getDiagonal()) {
            insertIndex = 1;
        }
    }
    else {
        for (int i=m_imagesList.size()-1; i > 0; i--) {
            if(m_imagesList[i].getDiagonal() <= img.getDiagonal()) {
                insertIndex = i;
                break;
            }
        }
    }
    m_imagesList.insert(insertIndex, img);

    //отрисовка добавленного с компьютера изображения на сцене
    m_scene->addPixmap(QPixmap::fromImage(image));
    ui->fileComboBox->insertItem(insertIndex, img.getName());
    ui->fileComboBox->setCurrentIndex(insertIndex);
}

void MainWindow::changeCurrentImage(int index)
{
    QImage originalImage = m_imagesList[index].getOriginalImage();
    m_scene->clear();
    m_scene->addPixmap(QPixmap::fromImage(originalImage));
    ui->sizeLabel->setText("Size: " +
                           QString::number(originalImage.width()) +
                           "x" +
                           QString::number(originalImage.height()));

    //обновление списка номеров слоев изображения
    ui->layerComboBox->clear();
    int layersCount = m_layerHandler->countLayersNumber(originalImage, 2);
    for(int i=0; i<layersCount; i++)
    {
        ui->layerComboBox->addItem(QString::number(i));
    }
}

void MainWindow::changeCurrentLayer(int index)
{
    //вывод выбранного слоя на сцену
    Image originalImage = m_imagesList[ui->fileComboBox->currentIndex()];
    QImage currentLayer;
    if(originalImage.getLayer(index) == QImage()) {
        currentLayer = m_layerHandler->getLayer(index, 2, originalImage);
        m_imagesList[ui->fileComboBox->currentIndex()].insertLayer(index, currentLayer);
    } else {
        currentLayer = originalImage.getLayer(index);
    }
    m_scene->clear();
    m_scene->addPixmap(QPixmap::fromImage(currentLayer).scaled(originalImage.getWidth(),
                                                               originalImage.getHeight()));
    ui->sizeLabel->setText("Size: " +
                           QString::number(currentLayer.width()) +
                           "x" +
                           QString::number(currentLayer.height()));
}

