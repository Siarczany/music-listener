#ifndef HIDDENWIDGET_H
#define HIDDENWIDGET_H

#include <QWidget>

class HiddenWidget : public QObject
{
    Q_OBJECT
public:
    HiddenWidget(QObject* parent = nullptr);
signals:
    void setLabel(const QString text);
    void outOfSight(const bool visibility);
};

#endif // HIDDENWIDGET
