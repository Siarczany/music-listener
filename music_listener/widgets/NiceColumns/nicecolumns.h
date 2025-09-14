#ifndef NICECOLUMNS_H
#define NICECOLUMNS_H

#include "internal/column.h"
#include "internal/dragwidget.h"
#include "internal/headeroptions.h"
#include <QGridLayout>
#include <QScrollArea>
#include "widgets/elidedlabel.h"
#include "internal/rowoptions.h"


class NiceColumns : public QWidget
{
    Q_OBJECT

public:
    explicit NiceColumns(QWidget* parent = nullptr);
    ~NiceColumns();

    void addHeader(QString label, Qt::Alignment alignment);

    void addBodyWidget(QWidget* widget, int row, int column);
    void setBodyCount(int amount);
    //int bodyCount() const;
    void setColumnMinimumWidth(int column, int minSize);
    void setColumnStretch(int column, int stretch);
    void setAutoResizable(bool mode);
    bool autoResizable() const;
    void updateWidths();

    void setRowIndex(int row, int index);
    void checkScrollbars();

    void clearBody();

    void setRowMenu(int row, QMenu* menu);

protected:

private slots:
    void sliderMoved(int slider, int moveAmount);
    void columnChangedVisibility(int column, int visibility);

signals:
    void tag(int index);
    void edit(int index);
    void remove(int index);

private:
    QGridLayout* mainLayout;
    QScrollArea* header;
    HeaderOptions* headerContent;
    QGridLayout* headerLayout;
    QScrollArea* body;
    QWidget* bodyContent;
    QGridLayout* bodyLayout;
    QScrollBar* verticalScrollBar;
    QScrollBar* horizontalScrollBar;

    int sliderWidth = 11;
    int columnCount = 0;
    int rowCount = 0;

    void addHeaderWidget(ElidedLabel* widget);

    //column headerWidgets;
    int maxHeightHeader = 0;


    QVector<column> columns;

    void updateWidths(int column, QWidget* widget);
    void updateHeight(QWidget* widget);
    void addWidgetToHeap(int column, QWidget* widget);
    void resizeColumn(int column);



    bool autoResizing = true;
    int creationMaxWidth = 100;

    QVector<RowOptions*> rowsMenu;
    QMenu* rowMenu = nullptr;

    void clearLayout(QLayout* layout);
};

#endif // NICECOLUMNS_H
