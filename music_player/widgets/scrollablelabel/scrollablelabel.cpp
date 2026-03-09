#include "scrollablelabel.h"

ScrollableLabel::ScrollableLabel(QWidget *parent)
    : QLabel(parent)
{
    setAlignment(Qt::AlignHCenter);
}

ScrollableLabel::~ScrollableLabel()
{

}

void ScrollableLabel::setFullText(const QString &text)
{
    fullText = text;

    calculateOffsets();
    updateElidedText();
}

void ScrollableLabel::updateElidedText()
{
    switch(fitness)
    {
    case Fitness::All:
    {
        setText(fullText);
        break;
    }
    case Fitness::Dots:
    {
        setText("...");
        break;
    }
    case Fitness::None:
    {
        setText("");
        break;
    }
    case Fitness::Partly:
    {
        setText(elideBothSides(fullText, offset, width()));
        break;
    }
    default:
    {
        setText("tung tung tung hasur");
    }
    }
}

void ScrollableLabel::clamp(int &value, const int &min, const int &max)
{
    if(value < min)
    {
        value = min;
    }
    if(max < value)
    {
        value = max;
    }
}

void ScrollableLabel::calculateOffsetDoublyElidedBounds(const int availableSpace, const QString& text)
{
    QFontMetrics fm(font());

    if(availableSpace >= fm.horizontalAdvance(text))
    {
        fitness = Fitness::All;
        offsetAt = OffsetAt::Start;
        return;
    }

    const int dotsWidth = fm.horizontalAdvance("...");
    if(2*dotsWidth > availableSpace)
    {
        fitness = Fitness::Dots;
        return;
    }
    if(availableSpace < dotsWidth)
    {
        fitness = Fitness::None;
        return;
    }

    canBeELided = true;
    fitness = Fitness::Partly;

    //
    // left side offset
    //

    int pixels = 0;
    int chars = 0;
    while(pixels <= availableSpace)
    {
        chars++;
        pixels = fm.horizontalAdvance(text.first(chars)) + dotsWidth;
        //qDebug() << "first loop pixels: " << pixels << text.first(chars) << availableSpace;
    }
    chars--;

    const QString fitsFromLeft = text.first(chars);
    //qDebug() << fitsFromLeft;

    pixels = dotsWidth + fm.horizontalAdvance(fitsFromLeft) + dotsWidth;
    while(pixels > availableSpace)
    {
        chars--;
        pixels = dotsWidth + fm.horizontalAdvance(fitsFromLeft.last(chars)) + dotsWidth;
        //qDebug() << "second loop pixels: " << pixels << fitsFromLeft.last(chars) << availableSpace;
    }

    offsetDoublyElidedMin = fm.horizontalAdvance(text.first(fitsFromLeft.size() - chars + 1));
    //qDebug() << offsetDoublyElidedMin << text.first(fitsFromLeft.size() - chars + 1);

    //
    // right side offset
    //

    pixels = 0;
    chars = 0;

    while(pixels <= availableSpace)
    {
        chars++;
        pixels = dotsWidth + fm.horizontalAdvance(text.last(chars));
        //qDebug() << "first loop pixels: " << pixels << text.last(chars) << availableSpace;
    }
    chars--;

    const QString fitsFromRight = text.last(chars);
    //qDebug() << fitsFromRight;

    pixels = dotsWidth + fm.horizontalAdvance(fitsFromRight) + dotsWidth;
    while(pixels > availableSpace)
    {
        chars--;
        pixels = dotsWidth + fm.horizontalAdvance(fitsFromRight.first(chars)) + dotsWidth;
        //qDebug() << "second loop pixels: " << pixels << fitsFromRight.first(chars) << availableSpace;
    }

    offsetDoublyElidedMax = fm.horizontalAdvance(text) - fm.horizontalAdvance(text.last(fitsFromRight.size() + 1));
    //qDebug() << fm.horizontalAdvance(text) << availableSpace;
    //qDebug() << offsetDoublyElidedMax << text.last(fitsFromRight.size() + 1);
/*
    for(int i = 0; i<text.size(); i++)
    {
        if(fm.horizontalAdvance(text.first(i)) == offsetDoublyElidedMax)
        {
            qDebug() << text.first(i);
            qDebug() << text;
        }
    }
//*/
}

void ScrollableLabel::calculateOffsetBounds(const QString& text)
{
    if(fitness == Fitness::Partly)
    {
        QFontMetrics fm(font());

        for(int i = 0; i<text.length(); i++)
        {
            if(fm.horizontalAdvance(text.first(i + 1)) == offsetDoublyElidedMin)
            {
                offsetMin = fm.horizontalAdvance(text.first(i));
                break;
            }
        }
        for(int i = 0; i<text.length(); i++)
        {
            if(fm.horizontalAdvance(text.first(i)) == offsetDoublyElidedMax)
            {
                offsetMax = fm.horizontalAdvance(text.first(i+1));
                break;
            }
        }
    }
    clamp(offset, offsetMin, offsetMax);

    if(offsetAt == OffsetAt::Start)
    {
        offset = offsetMin;
    }
    if(offsetAt == OffsetAt::End)
    {
        offset = offsetMax;
    }
}

void ScrollableLabel::calculateOffsets()
{
    calculateOffsetDoublyElidedBounds(width(), fullText);
    calculateOffsetBounds(fullText);
}

QString ScrollableLabel::elideBothSides(const QString &text, const int offset, const int width)
{
    QFontMetrics fm(font());
    const QString dots = "...";
    const int dotsWidth = fm.horizontalAdvance(dots);

    if(offset < offsetDoublyElidedMin)
    {
        for(int i = 0; i<text.length(); i++)
        {
            if(fm.horizontalAdvance(text.first(i+1)) + dotsWidth > width)
            {
                return text.first(i) + dots;
            }
        }
    }

    if(offsetDoublyElidedMax < offset)
    {
        for(int i = 0; i<text.length(); i++)
        {
            if(fm.horizontalAdvance(text.last(i+1)) + dotsWidth > width)
            {
                return dots + text.last(i);
            }
        }
    }

    int startingChar = 0;

    for(int i = 0; i<text.length(); i++)
    {
        if(fm.horizontalAdvance(text.first(i)) >= offset)
        {
            startingChar = i;
            break;
        }
    }
    //qDebug() << "startingChar:" << startingChar;
    for(int i = 0; i<text.length() - startingChar; i++)
    {
        if(dotsWidth + fm.horizontalAdvance(text.first(startingChar + i + 1)
                                        .last(i + 1)) + dotsWidth > width)
        {
            if(i == 0)
            {
                return dots;
            }
            return dots + text.first(startingChar + i).last(i) + dots;
        }
    }

    return "no";
}

void ScrollableLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);

    calculateOffsets();
    updateElidedText();
}

void ScrollableLabel::wheelEvent(QWheelEvent *event)
{
    if(fitness == Fitness::Partly)
    {
        if (event->angleDelta().y() > 0) {
            // Przewijanie w górę
            //qDebug() << "Scroll w górę";
            offset += pixelsScrolled;
        }
        else
        {
            // Przewijanie w dół
            //qDebug() << "Scroll w dół";
            offset -= pixelsScrolled;
        }

        if(offset <= offsetMin)
        {
            offsetAtMin = true;
            offsetAtMax = false;
            offsetAt = OffsetAt::Start;
        }
        if(offset >= offsetMax)
        {
            offsetAtMax = true;
            offsetAtMin = false;
            offsetAt = OffsetAt::End;
        }

        clamp(offset, offsetMin, offsetMax);

        //qDebug() << offset << width();
        setText(elideBothSides(fullText, offset, width()));
    }

    //qDebug() << "offsetAtMin:" << offsetAtMin;
    //qDebug() << "offsetAtMax:" << offsetAtMax;



    // Możesz też sprawdzić wartość delta
    //int delta = event->angleDelta().y();
    //qDebug() << "Delta:" << delta;


    //event->accept(); // lub event->ignore() jeśli chcesz propagować dalej
}


