#ifndef HIDDENWIDGET_H
#define HIDDENWIDGET_H

#include <QWidget>

// podobnie jak z rekreacją ekranów można by to zrobić???
// jak chowanie to setVisible(false) i width height na 0 i ewentualnie coś jeszcze o czym zapominam
// a jak setVisible(true) to ciągnąć z tego void* perhaps idk
// this could possible create a hideablelist as well but idk

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
