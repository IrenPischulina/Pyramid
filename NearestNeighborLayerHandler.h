#ifndef NEARESTNEIGHBORLAYERHANDLER_H
#define NEARESTNEIGHBORLAYERHANDLER_H

#include "ILayerHandler.h"

/** *********************************************************************
 * @class NearestNeighborLayerHandler
 * @brief Класс для обработки слоев изображения методом ближайшего соседа
 * **********************************************************************/
class NearestNeighborLayerHandler : public ILayerHandler
{
public:
    NearestNeighborLayerHandler();
    virtual ~NearestNeighborLayerHandler();

    QList<QImage> generatePyramid(double coefficient,
                                  AbstractImage &image) override;
};

#endif // NEARESTNEIGHBORLAYERHANDLER_H
