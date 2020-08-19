#include "Image.h"

Image::Image(int width, int height, QString name, QImage image)
    : AbstractImage(width, height, name, image)
{}

Image::~Image()
{}

