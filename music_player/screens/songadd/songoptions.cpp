#include "songoptions.h"



SongOptions::SongOptions(QWidget *parent)
    : QWidget(parent)
    , layout(new QVBoxLayout(this))
    , hte(new HiddenTextEdit(this))
    , tags(new TagInput(this))
    , volume(new VolumeTuneIn(this))
{
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    hideableWidget = new HideableWidget(hte, hte->getHiddenWidget(), this);
    layout->addWidget(hideableWidget, 0, Qt::AlignHCenter);
    hideableWidget->setText("asddsa");

    hideableWidget2 = new HideableWidget(tags->getLabel(), tags, tags->getHiddenWidget(), this);
    layout->addWidget(hideableWidget2, 0, Qt::AlignHCenter);
    //hideableWidget2->setText("drugi");


    layout->addWidget(tags, 0, Qt::AlignHCenter);

    layout->addWidget(volume, 0, Qt::AlignHCenter);
}

SongOptions::~SongOptions()
{

}


