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
    int originalWidth = originalImage->width();
    int originalHeight = originalImage->height();
    //текущий уровень
    int layer = 1;
    //последний уровень
    int size;
    if(originalWidth >= originalHeight)
        size = originalWidth;
    else size = originalHeight;
    int needLayer = log(size) / log(coefficient);

    while (layer <= needLayer) {
        double currentCoefficient = pow(1/coefficient, layer);
        int needWidth = originalWidth * currentCoefficient;
        int needHeight = originalHeight * currentCoefficient;
        QImage * newImage = new QImage(needWidth, needHeight, originalImage->format());
        const uchar *originalImageBits = originalImage->bits();
        uchar *newImageBits = newImage->bits();
        double k = 1/currentCoefficient;

        for(int i=0; i<needHeight; i++)
            for(int j=0; j<needWidth; j++)
                for(int channel=0; channel<4; channel++)
                    newImageBits[(i*needWidth+j)*4+channel] =
                            originalImageBits[(int(i*k)*originalWidth+int(j*k))*4+channel];

        layers.append(*newImage);
        layer++;
    }
    return layers;
}
