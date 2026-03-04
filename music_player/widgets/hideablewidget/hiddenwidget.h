#ifndef HIDDENWIDGET_H
#define HIDDENWIDGET_H

#include <QWidget>

class HiddenWidget : public QWidget
{
    Q_OBJECT
public:
    HiddenWidget(QWidget* parent = nullptr);
signals:
    void setLabel(const QString text);
};

#endif // HIDDENWIDGET
