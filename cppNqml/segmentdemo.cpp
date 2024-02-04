#include "segmentdemo.h"

SegmentDemo::SegmentDemo(QObject *parent)
    : QObject{parent}, image_path("Demo"), count(10)
{
}

void SegmentDemo::set_image_path(QString path) {
    image_path = path;
    emit image_path_changed();
}

QString SegmentDemo::read_image_path() {
    return image_path;
}

