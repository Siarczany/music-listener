#ifndef EDITSCREEN_H
#define EDITSCREEN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
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
    QPushButton* getBackPushButton() const;
    QPushButton* getEditPushButton() const;
    QLabel* getUserOutputLabel() const;
    QVBoxLayout* getLayout() const;
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

#endif // EDITSCREEN_H
