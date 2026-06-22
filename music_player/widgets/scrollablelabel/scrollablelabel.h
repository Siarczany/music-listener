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

    // shrinks the widget size if text fully fits inside the size
    void shrink();

    void setShrinkInsteadOfResize0(bool value);
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

    // value between 0 and 1 because I am not about to refactor this whole class because scrolling via a touchpad at low speeds doesn't work due to rounding :)
    double offsetRemainder;

    // maximum and minimum scroll amounts
    //  is a case that text starts with for example 'iii' which is 9 pixels long in a font I waws testing on
    //  '...' which is used to mark the contination of text has 9 pixels of length in a font I was testing on
    //  if the scroll amount started from 0, you could scroll 8 pixels and at point
    //  you cannot yet replace the beginning 'iii' with '...' because user is at the third 'i' and adding dots now
    //  would result in '...i' which has a length of 12 so our text would shift slightly to the right which looks bad
    //  those bounds exist beacuse you start scrolling from the 9 of 10th(error by one moment I'm wwriting this like 2 months after implementation xd)
    //  and not from the 0 pixel
    //  the same thing happenes at the end of the text so offset for that side exists as well
    Range offsetRange;

    // denotes how much of a text can fit inside the label
    enum class Fitness
    {
        All
        , Partly
        , Elider // there is some space but just for '...'
        , None // '' <- empty string xd
    };
    Fitness fitness;

    // range in pixels in which text is elided from both sides
    // used for knowing when to stop showing eliders on both sides
    Range doublyElidedPixels;
    //Range DoublyElidedChars;

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

    // calculates bounds for scroll amount as well as bounds used in elideBothSides function used for checking if we even need to elide both sides
    void calculateDoublyElidedBounds(const int availableSpace, const QString& text, const QString elider, const QFont font);

    // runs 2 functions above as well as clamping the scroll and sticking to the end while resizing
    void calculateOffsets();

    // compared to eliding from 1 side this one needs some constraint because text "Do I Matter to Me" can become for examaple
    //  "...I Matter..." or "...atter to..."
    //  and we use offset for this extra constaint
    QString elideBothSides(const QString& text, const int offset, const int width);

    // mouse and touchpad scrolls are different xd
    //  my mouse scrolls by 120 units every wheel tick(?)
    //  and my touchpad scrolls whatever amount did you scroll in some small amount of time
    //   that means it constantly scrolls by 2 or 3 or more
    // and that means you can't have a scrollAmount because while touch pad scrolling you will go much faster as it receives inputs faster xd
    double scrollSpeed = 1.0/12.0;

    // hideable widget sets fixed width to 0
    //  because widget can be invisible but layout or the widget itself
    //  remembers the width and the app window wont resize past the apparantly
    //  invisible point because the widget/layout prevents it or smth idk
    // in tag input the label from nicelineedit is used as the label from hideable
    //  so setting width to 0 hides the label xdd
    //  this bool will instead of resizing to 0 call shrink()
    bool shrinkInsteadOfResize0 = false;
protected:
    // as the widget is meant to be in a form screen resizing is roughly doubled to compensate for being in the middle of a layout
    void resizeEvent(QResizeEvent* event) override;

    // scrolling the wheel scrolls the text
    void wheelEvent(QWheelEvent *event) override;
};

#endif // SCROLLABLELABEL_H
