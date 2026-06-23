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

    HiddenWidget* getHiddenWidget() const;
protected:
    void resizeEvent(QResizeEvent *event);
private:
    HiddenWidget* hiddenWidget;
    struct HiddenWidgetData
    {
        int width;
    };
    HiddenWidgetData hiddenWidgetData;
    void inSight(bool visibility);

    QVBoxLayout* layout;

    HideableWidget* hideableWidget;
    HiddenTextEdit* hte;

    HideableWidget* hideableWidget2;
    TagInput* tags;

    //HideableWidget* hide3;
    HideableWidget* hideableWidget3;
    VolumeTuneIn* volume;
};

#endif // SONGOPTIONS_H
