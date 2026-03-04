# include "hideablewidget.h"

HideableWidget::HideableWidget(HiddenWidget* widget, QWidget *parent)
    : QWidget(parent)
    , label(new ClickableLabel(this))
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
        this->widget->setVisible(visible);
    });

    connect(widget, &HiddenWidget::setLabel,
            label, &ClickableLabel::setText);
}

HideableWidget::~HideableWidget()
{

}

void HideableWidget::setText(const QString &text)
{
    label->setFullText(text);
}

QWidget *HideableWidget::getWidget() const
{
    return widget;
}
