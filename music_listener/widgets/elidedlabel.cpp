#include "elidedlabel.h"


ElidedLabel::ElidedLabel(QWidget *parent) :
    QLabel(parent)
{
    //qDebug() << "elidedLabelWidth:" << maximumWidth();
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

ElidedLabel::~ElidedLabel()
{

}

void ElidedLabel::setFullText(const QString &text)
{
    fullText = text;
    updateElidedText();
}

void ElidedLabel::setWidthOfText()
{
    QFontMetrics fm(font());
    int textWidth = fm.horizontalAdvance(fullText);
    setFixedWidth(textWidth);
}

void ElidedLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    updateElidedText();
    //qDebug() << width();
}

void ElidedLabel::updateElidedText()
{
    QFontMetrics metrics(font());
    setText(metrics.elidedText(fullText, Qt::ElideRight, width()));
}
