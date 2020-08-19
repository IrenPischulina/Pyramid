#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    Image img(image.width(), image.height(), info.fileName(), image);
    m_imagesList.append(img);

    ILayerHandler * layerHandler;
    //построение слоев будет осуществляться методом k ближайших соседей
    layerHandler = new NearestNeighborLayerHandler();
    //генерация пирамиды
    QList<QImage> images = layerHandler->generatePyramid(2.0, img);
    //добавление результата к картинке
    m_imagesList[m_imagesList.size()-1].addPyramid(images);

    //отрисовка добавленного с компьютера изображения на сцене
    m_scene->addPixmap(QPixmap::fromImage(image));
    ui->fileComboBox->addItem(img.getName());
    ui->fileComboBox->setCurrentIndex(ui->fileComboBox->count()-1);
}

void MainWindow::changeCurrentImage(int index)
{
    m_scene->clear();
    m_scene->addPixmap(QPixmap::fromImage(m_imagesList[index].getOriginalImage()));
    ui->sizeLabel->setText("Size: " +
                           QString::number(m_imagesList[index].getWidth()) +
                           "x" +
                           QString::number(m_imagesList[index].getHeight()));

    //обновление списка номеров слоев изображения
    ui->layerComboBox->clear();
    for(int i=0; i<m_imagesList[index].getLayersCount(); i++)
    {
        ui->layerComboBox->addItem(QString::number(i));
    }
}

void MainWindow::changeCurrentLayer(int index)
{
    //вывод выбранного слоя на сцену
    Image originalImage = m_imagesList[ui->fileComboBox->currentIndex()];
    QImage currentLayer = originalImage.getLayer(index);
    m_scene->clear();
    m_scene->addPixmap(QPixmap::fromImage(currentLayer).scaled(originalImage.getWidth(),
                                                               originalImage.getHeight()));
    ui->sizeLabel->setText("Size: " +
                           QString::number(currentLayer.width()) +
                           "x" +
                           QString::number(currentLayer.height()));
}

