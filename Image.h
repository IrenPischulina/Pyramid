#ifndef IIMAGE_H
#define IIMAGE_H

#include <QImage>

#include "AbstractImage.h"

/** ***********************************************************
 * @class Image
 * @brief класс jpg, png изображений
 * ************************************************************/
class Image : public AbstractImage
{
public:
    Image(int width, int height, QString name, QImage image);
    virtual ~Image();
};

#endif // IIMAGE_H
