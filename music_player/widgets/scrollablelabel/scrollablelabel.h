#ifndef SCROLLABLELABEL_H
#define SCROLLABLELABEL_H

#include <QLabel>
#include <QWheelEvent>

// a label that can contain a text longer then the label length itself.
// and the user can scroll throgh this text using a mouse wheel
class ScrollableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ScrollableLabel(QWidget* parent = nullptr);
    ~ScrollableLabel();

    // QLabel's setText is used to actually display the text so no overriding it :(
    void setFullText(const QString &text);
    void shrink();
private:
    struct Range
    {
        int min;
        int max;
    };

    // updates the displayed text
    void updateElidedText();

    QString fullText;

    // storage for the amount the user has scrolled through the text
    int offset = 0;

    // maximum and minimum scroll amounts
    //  is a case that text starts with for example 'iii' which is 9 pixels long in a font I waws testing on
    //  '...' which is used to mark the contination of text has 9 pixels of length in a font I was testing on
    //  if the scroll amount started from 0, you could scroll 8 pixels and at point
    //  you cannot yet replace the beginning 'iii' with '...' because user is at the third 'i' and adding dots now
    //  would result in '...i' which has a length of 12 so our text would shift slightly to the right which looks bad
    //  those bounds exist beacuse you start scrolling from the 9 of 10th(error by one moment I'm wwriting this like 2 months after implementation xd)
    //  and not from the 0 pixel
    //  the same thing happenes at the end of the text so offset for that side exists as well
    int offsetMax;
    int offsetMin;

    // denotes how much of a text can fit inside the label
    enum class Fitness
    {
        All
        , Partly
        , Elider // there is some space but just for '...'
        , None // '' <- empty string xd
    };
    Fitness fitness;

    // god and me from 2 months ago knows what this does
    //  it's the same as offsetMin/Max but shifted towards the middle by 1 letter????
    int offsetDoublyElidedMin;
    int offsetDoublyElidedMax;

    // for remembering where in the text the user was in case of resising
    //  without it when you are at the beginning nothing different happenes :)
    //  if you are at the end of the text still nothing different happens as long as you are resizing positively(increasing the size of the label)
    //  if decreasing size then the beginning would stay in place and the end which was 'something' would became 'somet...' which isn't nice :(
    // with this if you resize the end of the text sticks to the right side
    enum class OffsetAt
    {
        Start
        , Middle
        , End
    };
    OffsetAt offsetAt = OffsetAt::Start;

    void clamp(int& value, const int& min, const int& max);
    Fitness calculateFitness(const int availableSpace, const QString& text, const QString& elider, const QFont font) const;
    void calculateOffsetDoublyElidedBounds(const int availableSpace, const QString& text, const QString elider, const QFont font);
    void calculateOffsetBounds(const QString& text);

    // runs 2 functions above
    void calculateOffsets();

    QString elideBothSides(const QString& text, const int offset, const int width);

    int pixelsScrolled = 10;
protected:
    // as the widget is meant to be in a form screen resizing is roughly doubled to compensate for being in the middle of a layout
    void resizeEvent(QResizeEvent* event) override;

    // scrolling the wheel scrolls the text
    void wheelEvent(QWheelEvent *event) override;

};

#endif // SCROLLABLELABEL_H
