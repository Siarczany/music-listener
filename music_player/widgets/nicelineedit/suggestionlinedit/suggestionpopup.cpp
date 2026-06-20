#include "suggestionpopup.h"

SuggestionPopup::SuggestionPopup(QWidget *parent) : QListWidget(parent) {
    // the popup is a actually the same as the tooltip or something idk xd
    setWindowFlags(Qt::ToolTip);

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

    // hide the popup after selecting a wanted text
    hide();
}
