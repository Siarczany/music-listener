# include "hideablewidget.h"

HideableWidget::HideableWidget(QWidget *widget, HiddenWidget *hidden, QWidget *parent)
    : QWidget(parent)
    , label(new ClickableLabel(this))
    , hidden(hidden)
    , widget(widget)
    , layout(new QVBoxLayout(this))
{
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(label);
    layout->addWidget(this->widget);

    connect(label, &ClickableLabel::pressed,
            this, [this](){
                //visible = !visible;
                //emit this->hidden->inSight(visible);
                setInSight(!visible);
            });

    connect(hidden, &HiddenWidget::setLabel,
            this, &HideableWidget::setText);

    connect(hidden, &HiddenWidget::sizeChanged,
            this, [this](){
        label->setFixedWidth(this->hidden->width());
    });

}

HideableWidget::~HideableWidget()
{

}

void HideableWidget::setText(const QString &text)
{
    label->setFullText(text);
    //qDebug() << "label" << label->width();
}

HiddenWidget *HideableWidget::getWidget() const
{
    return hidden;
}

void HideableWidget::setInSight(const bool visibility)
{
    if(visible == visibility)
        return;
    visible = visibility;
    if(visibleFull == false)
        return;

    if(visible == true)
    {
        hidden->setFixedWidth(visibleWidth);
        label->setFixedWidth(visibleWidth);
    }
    else // visible == false
    {
        visibleWidth = hidden->width();
        hidden->setFixedWidth(0);
        label->setFixedWidth(100);
    }

    emit this->hidden->inSight(visible);
}

void HideableWidget::setInSightFull(const bool visibility)
{
    if(visibleFull == visibility)
        return;
    //qDebug() << visibility;
    label->setVisible(visibility);
    if(visibility == true)
    {
        setInSight(visible);
    }
    else
    {
        setInSight(false);
    }

    visibleFull = visibility;
}
