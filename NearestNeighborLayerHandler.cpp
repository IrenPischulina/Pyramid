#include "NearestNeighborLayerHandler.h"

NearestNeighborLayerHandler::NearestNeighborLayerHandler()
{}

NearestNeighborLayerHandler::~NearestNeighborLayerHandler()
{}

QList<QImage> NearestNeighborLayerHandler::generatePyramid(double coefficient,
                                                           AbstractImage & image)
{
    QList<QImage> layers{};

    //оригинальное изображение
    QImage * originalImage = new QImage(image.getOriginalImage());
    //текущий уровень
    int layer = 1;
    int needLayer = countLayersNumber(*originalImage, coefficient);

    while (layer <= needLayer) {
        QImage newImage = nearestNeighborMethod(layer, coefficient, originalImage);
        layers.append(newImage);
        layer++;
    }
    return layers;
}

int NearestNeighborLayerHandler::countLayersNumber(QImage &image, double coefficient)
{
    int originalWidth = image.width();
    int originalHeight = image.height();
    //последний уровень
    int size;
    if(originalWidth >= originalHeight)
        size = originalWidth;
    else size = originalHeight;
    return log(size) / log(coefficient);
}

QImage NearestNeighborLayerHandler::getLayer(int layer, double coefficient, AbstractImage &image)
{
    //оригинальное изображение
    QImage * originalImage = new QImage(image.getOriginalImage());
    return nearestNeighborMethod(layer, coefficient, originalImage);
}

QImage NearestNeighborLayerHandler::nearestNeighborMethod(int layer, double coefficient, QImage *originalImage)
{
    double currentCoefficient = pow(1/coefficient, layer);
    int needWidth = originalImage->width() * currentCoefficient;
    int needHeight = originalImage->height() * currentCoefficient;
    QImage * newImage = new QImage(needWidth, needHeight, originalImage->format());
    const uchar *originalImageBits = originalImage->bits();
    uchar *newImageBits = newImage->bits();
    double k = 1/currentCoefficient;

    for(int i=0; i<needHeight; i++)
        for(int j=0; j<needWidth; j++)
            for(int channel=0; channel<4; channel++)
                newImageBits[(i*needWidth+j)*4+channel] =
                        originalImageBits[(int(i*k)*originalImage->width()+int(j*k))*4+channel];
    return *newImage;
}
