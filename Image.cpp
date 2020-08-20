#include "Image.h"

Image::Image(int width, int height, QString name, QImage image, int layersCount)
    : AbstractImage(width, height, name, image, layersCount)
{}

Image::~Image()
{}

