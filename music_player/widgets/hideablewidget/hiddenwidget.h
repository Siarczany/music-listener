#ifndef HIDDENWIDGET_H
#define HIDDENWIDGET_H

#include <QWidget>

// podobnie jak z rekreacją ekranów można by to zrobić???
// jak chowanie to setVisible(false) i width height na 0 i ewentualnie coś jeszcze o czym zapominam
// a jak setVisible(true) to ciągnąć z tego void* perhaps idk
// this could possible create a hideablelist as well but idk


// since qt doesn't allow classes to dziedziczyć z 2 klas z Q_OBJECT jednocześnie nie można zrobić np.
//  class Something : public SomeParent, public HideableWidget
//  a więc obchodzimy to tą tutaj właśnie klasą
// this class is supposed to go inside, using the example above, SomeParent class a sa pointer
// unfortunatelly you have to connect things between HiddenWidget and SomeParent manually
class HiddenWidget : public QObject
{
    Q_OBJECT
public:
    HiddenWidget(QWidget* target, QObject* parent = nullptr);

    // returns width of the target widget
    int width();

    // sets width for the target widget
    void setFixedWidth(const int width);
signals:
    // signal used for communicating between Something and HideableWidget
    void setLabel(const QString text);
    void sizeChanged();

    // setVisibility is already taken :(
    void inSight(const bool visibility);
private:
    // the pointer to the class that this is inside of
    QWidget* target;
    bool visibility;
};

#endif // HIDDENWIDGET
