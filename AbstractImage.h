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

    int getWidth();
    int getHeight();
    QString getName();
    QImage getLayer(int index);

private:
    int m_width{0};
    int m_height{0};
    QString m_name{};
    QList<QImage> m_layers{};
};

#endif // ABSTRACTIMAGE_H
