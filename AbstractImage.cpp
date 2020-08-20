#include "AbstractImage.h"

AbstractImage::AbstractImage(int width, int height, QString name, QImage image, int layersCount)
    : m_width(width),
      m_height(height),
      m_name(name)
{
    m_layers.append(image);
    for(int i=1; i<layersCount; i++) {
        m_layers.append(QImage());
    }
    m_diagonal = sqrt(pow(m_width, 2) + pow(m_height, 2));
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

double AbstractImage::getDiagonal()
{
    return m_diagonal;
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

//void AbstractImage::addPyramid(QList<QImage> layers)
//{
//    for(auto & layer : layers) {
//        m_layers.append(layer);
//    }
//}

void AbstractImage::insertLayer(int layer, QImage &image)
{
    if(0 <= layer && layer < m_layers.size()) {
        m_layers[layer]=image;
    }
}
