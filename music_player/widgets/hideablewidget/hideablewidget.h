#ifndef HIDEABLEWIDGET_H
#define HIDEABLEWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include "clickablelabel.h"
#include "hiddenwidget.h"

class Idktest : QWidget
{
    Q_OBJECT
public:
    Idktest(QWidget* parent = nullptr)
    : QWidget(parent)
    , hiddenWidget(new HiddenWidget(this, this))
    {
        connect(hiddenWidget, &HiddenWidget::inSight,
                this, [this](bool visibility){
                    //setVisible(visibility);
                    if(visibility == false)
                    {
                        hiddenWidgetData.width = width();
                        hiddenWidgetData.something = 6.7;

                        setVisible(false);
                    }
                    else
                    {
                        setFixedWidth(hiddenWidgetData.width);
                        hiddenWidgetData.something = 6.9;

                        setVisible(true);
                    }
                });
    }
    HiddenWidget* getHiddenWidget() const
    {
        return hiddenWidget;
    }
    void setHideableLabel(const QString& text)
    {
        emit hiddenWidget->setLabel(text);
    }
signals:

protected:
    void resizeEvent(QResizeEvent *event)
    {
        QWidget::resizeEvent(event);
        emit hiddenWidget->sizeChanged();
    }
private:
    HiddenWidget* hiddenWidget;
    struct HiddenWidgetData
    {
        int width;
        double something = 6.9;
    };
    HiddenWidgetData hiddenWidgetData;
};

class HideableWidget : public QWidget
{
    Q_OBJECT
public:
    HideableWidget(QWidget* widget, HiddenWidget* hidden, QWidget* parent = nullptr);
    HideableWidget(ClickableLabel* clickableLabel, QWidget* widget, HiddenWidget* hidden, QWidget* parent = nullptr);
    ~HideableWidget();

    // sets text to the label
    void setText(const QString& text);

    // gets widget that can hide
    HiddenWidget* getWidget() const;
    ClickableLabel* getLabel() const;

    // setVisibility was taken :(
    void setInSight(const bool visibility);

    // setVisibility is actually also used internally by somethings so
    //  we cannot even override it so this function exists :)
    void setInSightFull(const bool visibility);
signals:
    //void inSight(const bool visibility);
private:
    ClickableLabel* label;
    //int hiddenWidth = 100;
    int visibleWidth = 250;

    HiddenWidget* hidden;
    QWidget* widget;
    QVBoxLayout* layout;

    bool visible = true;
    bool visibleFull = true;

    void construct();
};

#endif // HIDEABLEWIDGET
