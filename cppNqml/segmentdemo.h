#ifndef SEGMENTDEMO_H
#define SEGMENTDEMO_H

#include <QObject>

class SegmentDemo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString image_path READ read_image_path WRITE set_image_path NOTIFY image_path_changed)
    Q_PROPERTY(int count READ read_count WRITE set_count NOTIFY count_changed)
public:
    explicit SegmentDemo(QObject *parent = nullptr);

    void set_image_path(QString path);
    QString read_image_path();

    void set_count(int c) { count = c; emit count_changed(); }
    int read_count() { return count; }
signals:
    void image_path_changed();
    void count_changed();

    void segment_call(); // TODO
protected:
    QString image_path;
    int count;
};

#endif // SEGMENTDEMO_H
