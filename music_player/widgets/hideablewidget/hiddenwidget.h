#ifndef HIDDENWIDGET_H
#define HIDDENWIDGET_H

#include <QWidget>

class HiddenWidget : public QObject
{
    Q_OBJECT
public:
    HiddenWidget(QWidget* target, QObject* parent = nullptr);
    int width();
    void setFixedWidth(const int width);
signals:
    void setLabel(const QString text);
    void inSight(const bool visibility);
    void sizeChanged();
private:
    QWidget* target;
};

#endif // HIDDENWIDGET
