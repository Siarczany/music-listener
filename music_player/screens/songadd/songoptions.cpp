#include "songoptions.h"



SongOptions::SongOptions(QWidget *parent)
    : QWidget(parent)
    , layout(new QVBoxLayout(this))
    , hte(new HiddenTextEdit(this))
    , tags(new TagInput(this))
    , volume(new VolumeTuneIn(this))
    , hiddenWidget(new HiddenWidget(this, this))
{
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    hideableWidget = new HideableWidget(hte, hte->getHiddenWidget(), this);
    hideableWidget->setText("Opis");
    hideableWidget->setInSight(false);
    layout->addWidget(hideableWidget, 0, Qt::AlignHCenter);

    hideableWidget2 = new HideableWidget(tags->getLabel(), tags, tags->getHiddenWidget(), this);
    hideableWidget2->setInSight(false);
    layout->addWidget(hideableWidget2, 0, Qt::AlignHCenter);

    hideableWidget3 = new HideableWidget(volume, volume->getHiddenWidget(), this);
    hideableWidget3->setText("Głośność");
    hideableWidget3->setInSight(false);
    layout->addWidget(hideableWidget3, 0, Qt::AlignHCenter);

    connect(hiddenWidget, &HiddenWidget::inSight,
            this, &SongOptions::inSight);
    connect(hte->getHiddenWidget(), &HiddenWidget::sizeChanged,
            this, [this](){
        if(hte->width() > width())
        {
            setFixedWidth(hte->width());
        }
    });

    connect(tags, &TagInput::sizeChanged,
            this, [this](){
        qDebug() << "aaa";
        if(tags->width() > width())
        {
            setFixedWidth(tags->width());
        }
    });
}

SongOptions::~SongOptions()
{

}

HiddenWidget *SongOptions::getHiddenWidget() const
{
    return hiddenWidget;
}

void SongOptions::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    emit hiddenWidget->sizeChanged();
}

void SongOptions::inSight(bool visibility)
{
    if(visibility == false)
    {
        hiddenWidgetData.width = width();
    }
    else
    {
        setFixedWidth(hiddenWidgetData.width);
    }
    setVisible(visibility);
}


