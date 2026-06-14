#include "scrollablelabel.h"

ScrollableLabel::ScrollableLabel(QWidget *parent)
    : QLabel(parent)
{
    setAlignment(Qt::AlignHCenter);
}

ScrollableLabel::~ScrollableLabel()
{}

// set full text and calculates everyting because text changed
// green text wtf why is 'text' inside a fucking comment blueish and not green tf
void ScrollableLabel::setFullText(const QString &text)
{
    fullText = text;

    calculateOffsets();
    updateElidedText();
}

void ScrollableLabel::shrink()
{
    if(fitness == Fitness::All)
    {
        QFontMetrics fm(font());
        setFixedWidth(fm.horizontalAdvance(fullText));
    }
}

// updates the text based on how it fits
// text is here green tf
void ScrollableLabel::updateElidedText()
{
    switch(fitness)
    {
    case Fitness::All:
    {
        setText(fullText);
        break;
    }
    case Fitness::Elider:
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

// calculates how the text fits given the inputs
ScrollableLabel::Fitness ScrollableLabel::calculateFitness(const int availableSpace, const QString &text, const QString &elider, const QFont font) const
{
    // getting the font as font can change the size of letters
    QFontMetrics fm(font);

    // if available space is larger than the text simply display the full text?
    if(availableSpace >= fm.horizontalAdvance(text))
    {
        //fitness = Fitness::All;
        //offsetAt = OffsetAt::Start;
        return Fitness::All;
    }

    // '...' are used as a elider(?). I mean they hide the text like this "...onna giv..."
    const int eliderWidth = fm.horizontalAdvance(elider);

    // if there is less space than 2 eliders display one
    if(2*eliderWidth > availableSpace)
    {
        //fitness = Fitness::Dots;
        return Fitness::Elider;
    }

    // if there is less space than 1 elider display none xd
    if(availableSpace < eliderWidth)
    {
        //fitness = Fitness::None;
        return Fitness::None;
    }

    // now the only option left is that text that can be elided from both sides
    return Fitness::Partly;

}

//this function calculates min and max offset that results in text being double elided
// it assumes that the text is larger than available space
void ScrollableLabel::calculateOffsetDoublyElidedBounds(const int availableSpace, const QString& text, const QString elider, const QFont font)
{

/*
    // getting the font as font can change the size of letters
    QFontMetrics fm(font());
    
    // if available space is larger than the text simply display the full text?
    if(availableSpace >= fm.horizontalAdvance(text))
    {
        fitness = Fitness::All;
        //offsetAt = OffsetAt::Start;
        return;
    }

    // '...' are used as a elider(?). I mean they hide the text like this "...onna giv..."
    const int dotsWidth = fm.horizontalAdvance("...");

    // if there is less space than 2 eliders display one
    if(2*dotsWidth > availableSpace)
    {
        fitness = Fitness::Elider;
        return;
    }

    // if there is less space than 1 elider display none xd
    if(availableSpace < dotsWidth)
    {
        fitness = Fitness::None;
        return;
    }

    // now the only option left is that text that can be elided from both sides
    //  and that requires some calculations :(
    fitness = Fitness::Partly;
//*/

    Range offsetDoublyELided;
    QFontMetrics fm(font);
    const int eliderWidth = fm.horizontalAdvance(elider);

    //
    // left side offset
    //  we calculate the first letter from which we will begin eliding doubly
    //

    int pixels = 0;
    int chars = 0;

    // we calculate i first letters of the text + elider to see when it takes up more
    //  than available space like this for exmaple "never gonn..."
    while(pixels <= availableSpace)
    {
        chars++;
        pixels = fm.horizontalAdvance(text.first(chars)) + eliderWidth;
        qDebug() << "first loop pixels: " << pixels << text.first(chars) << availableSpace;
    }
    // because we increment chars in the loop and this loop failed that means previous one passed
    //  so we subtract 1 from it
    chars--;

    const QString fitsFromLeft = text.first(chars);
    //qDebug() << fitsFromLeft;

    pixels = eliderWidth + fm.horizontalAdvance(fitsFromLeft) + eliderWidth;
    while(pixels > availableSpace)
    {
        chars--;
        pixels = eliderWidth + fm.horizontalAdvance(fitsFromLeft.last(chars)) + eliderWidth;
        qDebug() << "second loop pixels: " << pixels << fitsFromLeft.last(chars) << availableSpace;
    }

    offsetDoublyElidedMin = fm.horizontalAdvance(text.first(fitsFromLeft.size() - chars + 1));
    offsetDoublyELided.min = fm.horizontalAdvance(text.first(fitsFromLeft.size() - chars + 1));
    qDebug() << offsetDoublyElidedMin << text.first(fitsFromLeft.size() - chars + 1);

    //
    // right side offset
    //

    pixels = 0;
    chars = 0;

    while(pixels <= availableSpace)
    {
        chars++;
        pixels = eliderWidth + fm.horizontalAdvance(text.last(chars));
        //qDebug() << "first loop pixels: " << pixels << text.last(chars) << availableSpace;
    }
    chars--;

    const QString fitsFromRight = text.last(chars);
    //qDebug() << fitsFromRight;

    pixels = eliderWidth + fm.horizontalAdvance(fitsFromRight) + eliderWidth;
    while(pixels > availableSpace)
    {
        chars--;
        pixels = eliderWidth + fm.horizontalAdvance(fitsFromRight.first(chars)) + eliderWidth;
        //qDebug() << "second loop pixels: " << pixels << fitsFromRight.first(chars) << availableSpace;
    }

    offsetDoublyElidedMax = fm.horizontalAdvance(text) - fm.horizontalAdvance(text.last(fitsFromRight.size() + 1));
    offsetDoublyELided.max = fm.horizontalAdvance(text) - fm.horizontalAdvance(text.last(fitsFromRight.size() + 1));
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
    fitness = calculateFitness(width(), fullText, "...", font());
    if(fitness == Fitness::Partly)
    {
        calculateOffsetDoublyElidedBounds(width(), fullText, "...", font());
    }

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
            //offsetAtMin = true;
            //offsetAtMax = false;
            offsetAt = OffsetAt::Start;
        }
        if(offset >= offsetMax)
        {
            //offsetAtMax = true;
            //offsetAtMin = false;
            offsetAt = OffsetAt::End;
        }

        clamp(offset, offsetMin, offsetMax);

        //qDebug() << offset << width();
        setText(elideBothSides(fullText, offset, width()));
    }

    qDebug() << "offsetDoublyElidedMin:" << offsetDoublyElidedMin;
    qDebug() << "offsetDoublyElidedMax:" << offsetDoublyElidedMax;
    qDebug() << "offsetMin:" << offsetMin;
    qDebug() << "offsetMax:" << offsetMax;
    //qDebug() << "offsetAtMin:" << offsetAtMin;
    //qDebug() << "offsetAtMax:" << offsetAtMax;



    // Możesz też sprawdzić wartość delta
    //int delta = event->angleDelta().y();
    //qDebug() << "Delta:" << delta;


    //event->accept(); // lub event->ignore() jeśli chcesz propagować dalej
}


