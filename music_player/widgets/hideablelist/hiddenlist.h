#ifndef HIDDENLIST_H
#define HIDDENLIST_H

#include "widgets/hideablewidget/hideablewidget.h"

class HiddenList : public QWidget
{
    Q_OBJECT
public:
    HiddenList(QWidget* parent = nullptr);
    ~HiddenList();

    void addVisibleWidget(QWidget* widget);
    void addHiddenWidget(QString& text, QWidget* widget);
private:
    struct WidgetInfo
    {
        bool hideable;
        bool visible;
        QWidget* widget;
    };
    QVBoxLayout* layout;
    QVector<WidgetInfo> widgets;
};

#endif // HIDDENLIST
