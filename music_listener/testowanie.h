#ifndef TESTOWANIE_H
#define TESTOWANIE_H

#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

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
    void addEditStuff(const int width);
    void setUserOutputText(const QString& text);
    void addUserOutput(const QString& text);
signals:
    void back();
private:
    QVBoxLayout* layout;

    QPushButton* back_pb;
    QLabel* userOutput_l;
    QPushButton* edit_pb;

    int longestUserOutputWidth = 0;

    virtual void loadQuery();
    virtual void editQuery();


    void clearUserOutput();
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

    void editQuery() override;
    void loadQuery() override;
};


#endif // TESTOWANIE_H
