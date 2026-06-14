# include "hideablewidget.h"

HideableWidget::HideableWidget(QWidget *widget, HiddenWidget *hidden, QWidget *parent)
    : QWidget(parent)
    , label(new ClickableLabel(this))
    , hidden(hidden)
    , widget(widget)
    , layout(new QVBoxLayout(this))
{
    construct();
}

HideableWidget::HideableWidget(ClickableLabel *clickableLabel, QWidget *widget, HiddenWidget *hidden, QWidget *parent)
    : QWidget(parent)
    , label(clickableLabel)
    , hidden(hidden)
    , widget(widget)
    , layout(new QVBoxLayout(this))
{
    construct();
}

HideableWidget::~HideableWidget()
{

}

void HideableWidget::setText(const QString &text)
{
    label->setFullText(text);
}

HiddenWidget *HideableWidget::getWidget() const
{
    return hidden;
}

ClickableLabel *HideableWidget::getLabel() const
{
    return label;
}

void HideableWidget::setInSight(const bool visibility)
{
    if(visible == visibility)
        return;
    visible = visibility;
    if(visibleFull == false)
        return;
/*
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
//*/
    emit this->hidden->inSight(visible);

}
//*
void HideableWidget::setInSightFull(const bool visibility)
{
    if(visibleFull == visibility)
        return;
    qDebug() << "setinsightfull";
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

void HideableWidget::construct()
{
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(label, 0, Qt::AlignHCenter);
    layout->addWidget(this->widget, 0, Qt::AlignHCenter);

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
                qDebug() << visibleFull << visible;
                //if(visibleFull && visible)
                //{
                    //label->setFixedWidth(this->hidden->width());
                    //qDebug() << label->width();
                //}
                //label->shrink();
            });
}
//*/
