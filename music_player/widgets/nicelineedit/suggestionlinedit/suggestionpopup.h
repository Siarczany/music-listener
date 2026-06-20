#ifndef SUGGESTIONPOPUP_H
#define SUGGESTIONPOPUP_H

#include <QListWidget>
#include <functional>
#include <QMouseEvent>

// a popup with a text list that you can click and it will select it
class SuggestionPopup : public QListWidget {
    Q_OBJECT
public:
    SuggestionPopup(QWidget* parent = nullptr);
    ~SuggestionPopup();

signals:
    void itemChosen(const QString& text);

protected:
    void mousePressEvent(QMouseEvent* event);
};

#endif //SUGGESTIONPOPUP
