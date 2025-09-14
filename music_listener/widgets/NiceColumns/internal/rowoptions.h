#ifndef ROWOPTIONS_H
#define ROWOPTIONS_H

#include <QWidget>

class RowOptions : public QWidget
{
    Q_OBJECT

public:
    explicit RowOptions(QWidget* parent = nullptr);
    void setIndex(int index);
    void setMenu(QMenu* menu);

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;

signals:
    //void edit(int index);
    //void remove(int index);
    //void tag(int index);

private:
    int index;
    QMenu* menu = nullptr;


};

#endif // ROWOPTIONS_H
