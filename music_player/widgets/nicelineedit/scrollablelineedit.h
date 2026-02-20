#ifndef SCROLLABLELINEEDIT_H
#define SCROLLABLELINEEDIT_h

#include <QLineEdit>

class ScrollableLineEdit : public QLineEdit
{
public:
    ScrollableLineEdit(QWidget* parent = nullptr);
    ~ScrollableLineEdit();
private:

protected:
    void wheelEvent(QWheelEvent *event) override;
};

#endif //SCROLLABLELINEEDIT
