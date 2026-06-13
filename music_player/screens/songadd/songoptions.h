#ifndef SONGOPTIONS_H
#define SONGOPTIONS_H

#include <QWidget>
#include "widgets/hideablewidget/hideablewidget.h"
#include "hiddentextedit.h"

class testtest : public QTextEdit
{
    Q_OBJECT
public:
    testtest(QWidget* parent = nullptr);
    ~testtest();

    HiddenWidget* getHiddenWidget() const;
protected:
    void resizeEvent(QResizeEvent* event) override;
signals:
    void sizeChanged();
private:
    HiddenWidget* hiddenWidget;
    ResizableWidget* resizableWidget;
};

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

    HideableWidget* hide2;
    testtest* tte;

    //HideableWidget* hide3;
    TagInput* tags;
    VolumeTuneIn* volume;
};

#endif // SONGOPTIONS_H
