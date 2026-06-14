#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include "widgets/scrollablelabel/scrollablelabel.h"

// just a label with an ability to click it
//  it also changes the cursor into a pointing finger one so the user knows they can click it
class ClickableLabel : public ScrollableLabel
{
    Q_OBJECT
public:
    ClickableLabel(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void pressed();
};

#endif // CLICKABLELABEL
