#ifndef COLUMN_H
#define COLUMN_H

#include <QWidget>
#include "dragwidget.h"

class column
{
public:
    column(int trueIndex = 0, int (QSize::* axis)() const = nullptr);
    void addElement(QWidget* widget);
    void addHeader(QWidget* widget);
    int max() const;
    void setVisible(bool visibility);
    int index() const;
    bool active() const;
    void setFixedWidth(int newWidth);
    void setHeaderText(QString string);
    QString header() const;
    int width() const;
    void setSlider(DragWidget* widget);
    void clearBody();
private:
    int trueIndex;
    QWidget* headerWidget;
    QVector<QWidget*> heapWidgets;
    int (QSize::* axis)() const;
    int value(size_t index) const;
    bool visible = true;
    int lastWidth;
    QString headerString;
    DragWidget* slider;
};

#endif // COLUMN_H
