#ifndef SCROLLABLELABEL_H
#define SCROLLABLELABEL_H

#include <QLabel>
#include <QWheelEvent>

class ScrollableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ScrollableLabel(QWidget* parent = nullptr);
    ~ScrollableLabel();
    void setFullText(const QString &text);
private:
    void updateElidedText();
    QString fullText;
    int offset = 0;
    int offsetMax;
    int offsetMin;
    bool canBeELided;
    int offsetDoublyElidedMin;
    int offsetDoublyElidedMax;
    bool offsetAtMin = true;
    bool offsetAtMax = false;
    void clamp(int& value, const int& min, const int& max);
    void calculateOffsetDoublyElidedBounds(const int availableSpace, const QString& text);
    void calculateOffsetBounds(const QString& text);
    void calculateOffsets();
    QString elideBothSides(const QString& text, const int offset, const int width);

    int pixelsScrolled = 10;
protected:
    void resizeEvent(QResizeEvent* event) override;
    void wheelEvent(QWheelEvent *event) override;

};

#endif // SCROLLABLELABEL_H
