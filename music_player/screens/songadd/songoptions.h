#ifndef SONGOPTIONS_H
#define SONGOPTIONS_H

#include <QWidget>
#include "widgets/hideablewidget/hideablewidget.h"
#include "hiddentextedit.h"

#include "taginput.h"
#include "volumetunein.h"

class SongOptions : public QWidget
{
    Q_OBJECT
public:
    SongOptions(QWidget* parent = nullptr);
    ~SongOptions();
private:
    QVBoxLayout* layout;

    HideableWidget* hideableWidget;
    HiddenTextEdit* hte;

    HideableWidget* hideableWidget2;


    //HideableWidget* hide3;
    TagInput* tags;
    VolumeTuneIn* volume;
};

#endif // SONGOPTIONS_H
