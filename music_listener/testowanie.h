#ifndef TESTOWANIE_H
#define TESTOWANIE_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QLineEdit>

class editScreen : public QWidget
{
    Q_OBJECT

public:
    explicit editScreen(QWidget *parent = nullptr);
    ~editScreen();

    void addLabelLineEdit(QLabel* label,
                          QLineEdit* lineEdit,
                          const QString name,
                          const QString toolTip,
                          const int width);
    void addWidget(QWidget* widget, const int width);
    void addLayout(QLayout* layout, const int width);
signals:
    void back();
private:
    QVBoxLayout* layout;


    void loadQuery();
    void editQuery();


    void addEditStuff();
};

class testowanie : public editScreen
{
    Q_OBJECT

public:
    explicit testowanie(QWidget *parent = nullptr);
    ~testowanie();

private:
    QLineEdit* le1;
    QLineEdit* le2;
};


#endif // TESTOWANIE_H
