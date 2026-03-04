#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include "widgets/scrollablelabel/scrollablelabel.h"

class ClickableLabel : public ScrollableLabel
{
    Q_OBJECT
public:
    using ScrollableLabel::ScrollableLabel;

protected:
    void mousePressEvent(QMouseEvent* event) override;

signals:
    void pressed();
};

#endif // CLICKABLELABEL
