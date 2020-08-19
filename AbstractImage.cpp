#include "AbstractImage.h"

AbstractImage::AbstractImage(int width, int height, QString name, QImage image)
    : m_width(width),
      m_height(height),
      m_name(name)
{
    m_layers.append(image);
}

AbstractImage::~AbstractImage()
{}

int AbstractImage::getWidth()
{
    return m_width;
}

int AbstractImage::getHeight()
{
    return m_height;
}

QString AbstractImage::getName()
{
    return m_name;
}

QImage AbstractImage::getLayer(int index)
{
    if(0 <= index && index < m_layers.size())
    {
        return m_layers[index];
    }
    return QImage();
}

int AbstractImage::getLayersCount()
{
    return m_layers.size();
}

QImage AbstractImage::getOriginalImage()
{
    return m_layers.at(0);
}

void AbstractImage::addPyramid(QList<QImage> layers)
{
    for(auto & layer : layers) {
        m_layers.append(layer);
    }
}
