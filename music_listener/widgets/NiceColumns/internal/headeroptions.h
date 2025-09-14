#ifndef HEADEROPTIONS_H
#define HEADEROPTIONS_H

#include <QWidget>
#include "column.h"

class HeaderOptions : public QWidget
{
    Q_OBJECT

public:
    explicit HeaderOptions(QWidget* parent = nullptr, QVector<column>* vec = nullptr);

protected:
    void contextMenuEvent(QContextMenuEvent* event) override;

signals:
    setActive(int index, bool state);

private:
    bool optionEnabled = true;
    QVector<column>* contents;
};

#endif // HEADEROPTIONS_H
