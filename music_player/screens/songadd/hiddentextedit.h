#ifndef HIDDENTEXTEDIT_H
#define HIDDENTEXTEDIT_H

#include <QTextEdit>
#include "widgets/hideablewidget/hiddenwidget.h"
#include "widgets/resizablewidget/resizeablewidget.h"

class HiddenTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    HiddenTextEdit(QWidget* parent = nullptr);
    ~HiddenTextEdit();

    HiddenWidget* getHiddenWidget() const;
protected:
    void resizeEvent(QResizeEvent *e) override;
signals:
    void sizeChanged();
private:
    HiddenWidget* hiddenWidget;
    struct HiddenWidgetData
    {
        int width;
    };
    HiddenWidgetData hwd;
    void inSight(bool visibility);
    ResizableWidget* resizableWidget;
};


#endif // HIDDENTEXTEDIT_H
