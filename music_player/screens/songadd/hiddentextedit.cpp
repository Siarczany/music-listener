#include "hiddentextedit.h"

HiddenTextEdit::HiddenTextEdit(QWidget *parent)
    : QTextEdit(parent)
    , hiddenWidget(new HiddenWidget(this, this))
{
    connect(hiddenWidget, &HiddenWidget::inSight,
            this, &HiddenTextEdit::inSight);

    resizableWidget = new ResizableWidget(this, this);
    connect(resizableWidget, &ResizableWidget::sizeChanged,
            this, [this](){
        //emit sizeChanged();
    });
}

HiddenTextEdit::~HiddenTextEdit()
{

}

HiddenWidget *HiddenTextEdit::getHiddenWidget() const
{
    return hiddenWidget;
}

void HiddenTextEdit::resizeEvent(QResizeEvent *e)
{
    QTextEdit::resizeEvent(e);
    resizableWidget->resize();
    emit hiddenWidget->sizeChanged();
}

void HiddenTextEdit::inSight(bool visibility)
{
    if(visibility == false)
    {
        hwd.width = width();
        setFixedWidth(0);
    }
    else // visibility == true
    {
        setFixedWidth(hwd.width);
    }
    setVisible(visibility);
    //qDebug() << hwd.width;
}
