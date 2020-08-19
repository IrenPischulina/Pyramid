#ifndef ABSTRACTIMAGE_H
#define ABSTRACTIMAGE_H

#include <QString>
#include <QList>
#include <QImage>

/** ***********************************************************
 * @class AbstractImage
 * @brief абстрактный класс изображений
 * ************************************************************/
class AbstractImage
{
public:
    AbstractImage(int width, int height, QString name, QImage image);
    virtual ~AbstractImage();

    virtual int getWidth();
    virtual int getHeight();
    virtual double getDiagonal();
    virtual QString getName();
    virtual QImage getLayer(int index);
    virtual int getLayersCount();
    virtual QImage getOriginalImage();

    virtual void addPyramid(QList<QImage> layers);

protected:
    int m_width{0};
    int m_height{0};
    double m_diagonal{0};
    QString m_name{};
    QList<QImage> m_layers{};
};

#endif // ABSTRACTIMAGE_H
