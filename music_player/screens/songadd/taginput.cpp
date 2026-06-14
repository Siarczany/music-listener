#include "taginput.h"

#include <QStringList>

TagInput::TagInput(QWidget *parent)
    : ListInput(new ClickableLabel(), parent)
    , hiddenWidget(new HiddenWidget(this, this))
{

    label = qobject_cast<ClickableLabel*>(getInput()->getLabel());
    connect(label, &ClickableLabel::pressed,
            this, [this](){
        qDebug() << "kliknięto";
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
        //setFixedWidth(0);
        getInput()->getLineEdit()->setFixedWidth(10);
    }
    else // visibility == true
    {
        //setFixedWidth(hwd.width);
    }
    //setVisible(visibility);
    qDebug() << "hello";
    //setInSight(visibility);
    getInput()->getLineEdit()->setVisible(visibility);
    getHideable()->setVisible(visibility);
}
