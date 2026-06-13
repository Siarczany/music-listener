#include "hiddentextedit.h"

HiddenTextEdit::HiddenTextEdit(QWidget *parent)
    : QTextEdit(parent)
    , hiddenWidget(new HiddenWidget(this, this))
{
    connect(hiddenWidget, &HiddenWidget::inSight,
            this, [this](bool visibility){
                setVisible(visibility);
            });

    resizableWidget = new ResizableWidget(this, this);
    connect(resizableWidget, &ResizableWidget::sizeChanged,
            this, [this](){
        emit sizeChanged();
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
