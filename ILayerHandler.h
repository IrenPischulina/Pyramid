#ifndef ILAYERHANDLER_H
#define ILAYERHANDLER_H

#include "AbstractImage.h"

/** ***************************************************************
 * @class ILayerHandler
 * @brief интерфейс для обработки слоев изображений
 * ****************************************************************/
class ILayerHandler
{
public:
    virtual QList<QImage> generatePyramid(double coefficient,
                                          AbstractImage &image) = 0;
    virtual int countLayersNumber(QImage & image, double coefficient) = 0;
    virtual QImage getLayer(int layer,
                            double coefficient,
                            AbstractImage &image) = 0;
};

#endif // ILAYERHANDLER_H
