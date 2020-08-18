#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open file"),
                                                    tr(""),
                                                    tr( "Изображения(*.png *.jpg)" ));

    if(!fileName.isNull()) {
        addImage(fileName);
    }
}

void MainWindow::addImage(QString fileName)
{
    QFile file(fileName);
    QFileInfo info(file);
    QImage image(fileName);
    Image img(image.width(), image.height(), info.fileName(), image);
    m_imagesList.append(img);
    m_scene->addPixmap(QPixmap::fromImage(image));
    ui->fileComboBox->addItem(img.getName());
    ui->fileComboBox->setCurrentIndex(ui->fileComboBox->count()-1);
}

void MainWindow::changeCurrentImage(int index)
{
    m_scene->clear();
    m_scene->addPixmap(QPixmap::fromImage(m_imagesList[index].getLayer(0)));
    ui->sizeLabel->setText("Size: " +
                           QString::number(m_imagesList[index].getWidth()) +
                           "x" +
                           QString::number(m_imagesList[index].getHeight()));
}

void MainWindow::changeCurrentLayer(int index)
{
    Q_UNUSED(index);
}
