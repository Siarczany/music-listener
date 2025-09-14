#ifndef SUGGESTIONLINEEDIT_H
#define SUGGESTIONLINEEDIT_H

#include <QListWidget>
#include <QLineEdit>
#include <functional>


class SuggestionPopup : public QListWidget {
    Q_OBJECT
public:
    SuggestionPopup(QWidget* parent = nullptr);
    ~SuggestionPopup();

signals:
    void itemChosen(const QString& text);

protected:
    void mousePressEvent(QMouseEvent* event) override;
};

class SuggestionLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    SuggestionLineEdit(QWidget* parent = nullptr);
    ~SuggestionLineEdit();

    void setQuery(std::function<QStringList(const QString&)> func);
protected:
    void focusOutEvent(QFocusEvent* event) override;

private:
    //QListWidget* popup;
    SuggestionPopup* popup;

    void setupPopup(const QString& text);
    const QStringList queryDatabase(const QString& text);
    std::function<QStringList(const QString&)> queryFunc = nullptr;


};

#endif // SUGGESTIONLINEEDIT_H
