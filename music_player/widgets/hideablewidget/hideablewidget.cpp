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
                visible = !visible;
                //this->widget->setVisible(visible);
                //emit outOfSight(visible);
                emit this->hidden->outOfSight(visible);
            });

    connect(hidden, &HiddenWidget::setLabel,
            label, &ClickableLabel::setText);
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
