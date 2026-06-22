#include "taginput.h"

#include <QStringList>

TagInput::TagInput(QWidget *parent)
    : ListInput(new ClickableLabel(), parent)
    , hiddenWidget(new HiddenWidget(this, this))
{

    label = qobject_cast<ClickableLabel*>(getNiceLineEdit()->getLabel());
    connect(label, &ClickableLabel::pressed,
            this, [this](){
        //qDebug() << "kliknięto";
    });

    setInputLabel("Tag");
    setListLabel("Tagi");
    setQuery([this](const QString& text){
        QStringList all;
        all << "1a" << "1b" << "2" << "3" << "5" << "8" << "13" << "21";
        QStringList ret;
        for(QString& str : all)
        {
            if(rand()%3 == 0)
            {
                ret << str;
            }
        }
        return ret;
    });

    connect(hiddenWidget, &HiddenWidget::inSight,
            this, &TagInput::inSight);
}

TagInput::~TagInput()
{

}

QStringList TagInput::getList() const
{
    return ListInput::getList();
}

HiddenWidget *TagInput::getHiddenWidget() const
{
    return hiddenWidget;
}

ClickableLabel *TagInput::getLabel() const
{
    return label;
}

void TagInput::resizeEvent(QResizeEvent *event)
{
    ListInput::resizeEvent(event);
    emit hiddenWidget->sizeChanged();
}

void TagInput::inSight(bool visibility)
{
    if(visibility == false)
    {
        hwd.width = width();

        // in theory we could set labels' shrinkInsteadOfResize0 to always be true
        //  because even the line as a resizable widget has a min width
        //  but yyy idk
        getNiceLineEdit()->getLabel()->setShrinkInsteadOfResize0(true);
        setFixedWidth(0);
        getNiceLineEdit()->getLabel()->setShrinkInsteadOfResize0(false);
    }
    else // visibility == true
    {
        setFixedWidth(hwd.width);
    }
    getNiceLineEdit()->getLineEdit()->setVisible(visibility);
    getHideable()->setVisible(visibility);
}
