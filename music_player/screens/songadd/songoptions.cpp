#include "songoptions.h"



SongOptions::SongOptions(QWidget *parent)
    : QWidget(parent)
    , layout(new QVBoxLayout(this))
    , hte(new HiddenTextEdit(this))
    , tte(new testtest(this))
    , tags(new TagInput(this))
    , volume(new VolumeTuneIn(this))
{
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);

    hideableWidget = new HideableWidget(hte, hte->getHiddenWidget(), this);
    layout->addWidget(hideableWidget, 0, Qt::AlignHCenter);
    hideableWidget->setText("asddsa");

    hide2 = new HideableWidget(tte, tte->getHiddenWidget(), this);
    layout->addWidget(hide2, 0, Qt::AlignHCenter);
    hide2->setText("123321");

    //hide3 = new HideableWidget(tags, tags->getHiddenWidget(), this);
    layout->addWidget(tags, 0, Qt::AlignHCenter);

    layout->addWidget(volume, 0, Qt::AlignHCenter);
}

SongOptions::~SongOptions()
{

}

testtest::testtest(QWidget *parent)
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

testtest::~testtest()
{

}

HiddenWidget *testtest::getHiddenWidget() const
{
    return hiddenWidget;
}

void testtest::resizeEvent(QResizeEvent *event)
{
    QTextEdit::resizeEvent(event);
    resizableWidget->resize();
    emit hiddenWidget->sizeChanged();
}
