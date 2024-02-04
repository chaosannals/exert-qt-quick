#ifndef GLOBALDEMO_H
#define GLOBALDEMO_H

#include <QObject>

class GlobalDemo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int timestamp READ get_timestamp WRITE set_timestamp NOTIFY timestamp_changed)
public:
    explicit GlobalDemo(QObject *parent = nullptr);

    int get_timestamp() { return timestamp; }

    // 修改后必须手动调用自定义的信号 emit timestamp_changed(); 通知 timestamp 更新了。
    void set_timestamp(int v) { timestamp = v; emit timestamp_changed(); }
signals:
    void timestamp_changed();
private:
    int timestamp;
};

#endif // GLOBALDEMO_H
