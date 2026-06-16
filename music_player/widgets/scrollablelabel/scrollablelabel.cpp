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
void ScrollableLabel::calculateDoublyElidedBounds(const int availableSpace, const QString& text, const QString elider, const QFont font)
{
    QFontMetrics fm(font);
    const int eliderWidth = fm.horizontalAdvance(elider);


    //
    // left side offset
    //  we calculate the first letter from which we will begin eliding doubly
    //

    int pixels = 0;
    int chars = 0;

    while(pixels <= eliderWidth)
    {
        chars++;
        pixels = fm.horizontalAdvance(text.first(chars));
    }

    // from this pixel we can doubly elide
    doublyElidedPixels.min = pixels;

    // 1 character back scrolling can start as we don't want to scroll eliderWidth+ at the beginning for the text to move by 1 character xd
    offsetRange.min = fm.horizontalAdvance(text.first(chars-1));

    //
    // right side offset
    //

    pixels = 0;
    chars = 0;

    while(pixels <= availableSpace - eliderWidth)
    {
        chars++;
        pixels = fm.horizontalAdvance(text.last(chars));
    }

    // at this pixel doubly elide stops
    doublyElidedPixels.max = fm.horizontalAdvance(text.first(text.size() - chars));

    // one character foreward from here we stop scrolling because the same issue as at the beginning
    offsetRange.max = fm.horizontalAdvance(text.first(text.size() - chars + 1));
}

void ScrollableLabel::calculateOffsets()
{
    fitness = calculateFitness(width(), fullText, "...", font());
    if(fitness == Fitness::Partly)
    {
        calculateDoublyElidedBounds(width(), fullText, "...", font());

        clamp(offset, offsetRange.min, offsetRange.max);

        // technically redundant as the text always sticks to the left side(unless u r using arabic or something idk)
        if(offsetAt == OffsetAt::Start)
        {
            offset = offsetRange.min;
        }

        // makes it so that during resizing while increasing size while the text is max scrolled to the right the text actually sticks
        //  to the right side
        if(offsetAt == OffsetAt::End)
        {
            offset = offsetRange.max;
        }
    }
}

QString ScrollableLabel::elideBothSides(const QString &text, const int offset, const int width)
{
    QFontMetrics fm(font());
    const QString dots = "...";
    const int dotsWidth = fm.horizontalAdvance(dots);

    // if we are  at the beginning just elide normally
    if(offset < doublyElidedPixels.min)
    {
        for(int i = 0; i<text.length(); i++)
        {
            if(fm.horizontalAdvance(text.first(i+1)) + dotsWidth > width)
            {
                return text.first(i) + dots;
            }
        }
    }

    // the same for the end/right side
    if(doublyElidedPixels.max < offset)
    {
        for(int i = 0; i<text.length(); i++)
        {
            if(fm.horizontalAdvance(text.last(i+1)) + dotsWidth > width)
            {
                return dots + text.last(i);
            }
        }
    }

    // if not both of them that means we are in the middle :(

    int startingChar = 0;

    // calculate at what character offset currently is
    for(int i = 0; i<text.length(); i++)
    {
        if(fm.horizontalAdvance(text.first(i)) >= offset)
        {
            startingChar = i;
            break;
        }
    }


    // basically checks "......", then "...a...", then "...ab..."
    //  till it won't fit anymore at which boit we have found what we were looking for
    //qDebug() << "startingChar:" << startingChar;
    for(int i = 0; i<text.length() - startingChar; i++)
    {
        if(dotsWidth + fm.horizontalAdvance(
                                            text.first(startingChar + i + 1).last(i + 1)
                                             ) + dotsWidth > width)
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
        double scrollAmount = event->angleDelta().y() * scrollSpeed;
        // add fractional/decimal(??) part to the reminder
        offsetRemainder += scrollAmount - (int)scrollAmount;
        // if remainder has gone past -1 or 1 than we add whole value of remainder to scrollAmount and leave the fractional part
        if(-1 > offsetRemainder || offsetRemainder > 1)
        {
            scrollAmount += (int)offsetRemainder;
            offsetRemainder = offsetRemainder - (int)offsetRemainder;
        }
        offset += scrollAmount;

        // if wwe are at a start of an end set a flag so the text will stick to respective side
        if(offset <= offsetRange.min)
        {
            offsetAt = OffsetAt::Start;
        }
        if(offset >= offsetRange.max)
        {
            offsetAt = OffsetAt::End;
        }

        clamp(offset, offsetRange.min, offsetRange.max);

        setText(elideBothSides(fullText, offset, width()));
    }
}


