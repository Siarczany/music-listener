#ifndef TESTOWANIE_H
#define TESTOWANIE_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include "editscreen.h"

class testowanie : public editScreen
{
    Q_OBJECT

public:
    explicit testowanie(QWidget *parent = nullptr);
    ~testowanie();

private:
    QLineEdit* le1;
    QLineEdit* le2;

    void editQuery() override;
    void loadQuery() override;
};


#endif // TESTOWANIE_H
