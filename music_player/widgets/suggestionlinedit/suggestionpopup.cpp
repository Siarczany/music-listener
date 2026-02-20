#include "suggestionpopup.h"

SuggestionPopup::SuggestionPopup(QWidget *parent) : QListWidget(parent) {
    setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setFocusPolicy(Qt::NoFocus);
    setMouseTracking(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

SuggestionPopup::~SuggestionPopup()
{

}

void SuggestionPopup::mousePressEvent(QMouseEvent *event) {
    QListWidgetItem* item = itemAt(event->pos());
    if (item) {
        emit itemChosen(item->text());
    }

    hide();
}
