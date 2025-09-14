#include "nicecolumns.h"

#include <QScrollBar>
#include <QTimer>
#include <QApplication>


NiceColumns::NiceColumns(QWidget *parent)
    : QWidget(parent)
    , mainLayout(new QGridLayout)
    , header(new QScrollArea(this))
    , headerContent(new HeaderOptions(this, &columns))
    , headerLayout(new QGridLayout)
    , body(new QScrollArea(this))
    , bodyContent(new QWidget(this))
    , bodyLayout(new QGridLayout)
    , verticalScrollBar(new QScrollBar(Qt::Vertical, this))
    , horizontalScrollBar(new QScrollBar(Qt::Horizontal, this))
{
    connect(headerContent, &HeaderOptions::setActive, this, columnChangedVisibility);

    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(mainLayout);

    header->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    header->setFrameStyle(QFrame::NoFrame);
    header->setWidgetResizable(true);
    header->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainLayout->addWidget(header, 0, 0, 1, 1);

    header->setWidget(headerContent);

    //headerContent->setLayout(headerLayout);
    //headerContent->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    //mainLayout->addWidget(headerContent);

    headerLayout->setContentsMargins(0, 0, 0, 0);
    headerLayout->setSpacing(0);
    headerContent->setLayout(headerLayout);

    body->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    body->setFrameStyle(QFrame::NoFrame);
    body->setWidgetResizable(true);
    body->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    body->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mainLayout->addWidget(body, 1, 0, 1, 1);

    body->setWidget(bodyContent);

    bodyLayout->setContentsMargins(0, 0, 0, 0);
    bodyLayout->setSpacing(0);
    bodyContent->setLayout(bodyLayout);

    //headerWidgets = column(0, QSize::height);

    // manual scrolling through the bar
    connect(verticalScrollBar, &QScrollBar::valueChanged,
            body->verticalScrollBar(), &QScrollBar::setValue);
    // scrolling through a 'side wheel' or a key
    connect(body->verticalScrollBar(), &QScrollBar::valueChanged,
            verticalScrollBar, &QScrollBar::setValue);
    // resizing the window
    connect(body->verticalScrollBar(), &QScrollBar::rangeChanged,
            verticalScrollBar, &QScrollBar::setRange);
    // hiding/showing the scrollbar if content fits
    connect(body->verticalScrollBar(), &QScrollBar::rangeChanged,
            this, [this](){
                if(verticalScrollBar->maximum() == 0)
                {
                    verticalScrollBar->setVisible(false);
                }
                else
                {
                    if(!verticalScrollBar->isVisible())
                    {
                        verticalScrollBar->setVisible(true);
                    }
                }
            });
    mainLayout->addWidget(verticalScrollBar, 0, 1, 2, 1);

    // manual scrolling through the bar
    connect(horizontalScrollBar, &QScrollBar::valueChanged,
            header->horizontalScrollBar(), &QScrollBar::setValue);
    connect(horizontalScrollBar, &QScrollBar::valueChanged,
            body->horizontalScrollBar(), &QScrollBar::setValue);
    // scrolling through a 'side wheel' or a key
    connect(header->horizontalScrollBar(), &QScrollBar::valueChanged,
            horizontalScrollBar, &QScrollBar::setValue);
    connect(body->horizontalScrollBar(), &QScrollBar::valueChanged,
            horizontalScrollBar, &QScrollBar::setValue);
    // resizing the window. Both the header and the body should have the same width xd
    connect(header->horizontalScrollBar(), &QScrollBar::rangeChanged,
            horizontalScrollBar, &QScrollBar::setRange);
    // hiding/showing the scrollbar if content fits
    connect(header->horizontalScrollBar(), &QScrollBar::rangeChanged,
            this, [this](){
                if(horizontalScrollBar->maximum() == 0)
                {
                    horizontalScrollBar->setVisible(false);
                }
                else
                {
                    if(!horizontalScrollBar->isVisible())
                    {
                        horizontalScrollBar->setVisible(true);
                    }
                }
            });

    mainLayout->addWidget(horizontalScrollBar, 2, 0, 1, 1);
    /*
    for(int i = 0; i<10; i++)
    {
        QLabel* l = new QLabel("basd", this);
        l->setAlignment(Qt::AlignCenter);
        addHeaderWidget(l, Qt::AlignCenter);
    }

    std::string str = "";
    for(int i = 0; i<60; i++)
    {
        ElidedLabel* l = new ElidedLabel(this);
        char c = 'A';
        c = c+i;
        //l->setText(QString::fromStdString(std::string(1, c)));
        str += c;
        l->setFullText(QString::fromStdString(str));
        l->setWidthOfText();
        //qDebug() << l->width();
        addBodyWidget(l, i, 0, Qt::AlignHCenter | Qt::AlignLeft);
    }
//*/

}

NiceColumns::~NiceColumns()
{

}

void NiceColumns::addHeader(QString label, Qt::Alignment alignment)
{
    ElidedLabel* eLabel = new ElidedLabel(this);
    eLabel->setFullText(label);
    eLabel->setAlignment(alignment);
    addHeaderWidget(eLabel);

}

void NiceColumns::addHeaderWidget(ElidedLabel *widget)
{
    int lastColumn = 0;

    if(headerLayout->columnCount() == 1)
    {
        setColumnMinimumWidth(0, (sliderWidth-1)/2); // padding left
        setColumnStretch(0, 0);

        lastColumn = 1;
    }
    else
    {
        lastColumn = headerLayout->columnCount()-1;
        setColumnStretch(lastColumn, 0);
    }

    headerLayout->addWidget(widget, 0, lastColumn, 1, 1);

    column c(lastColumn, QSize::width);
    c.addHeader(widget);
    c.setHeaderText(widget->text());
    //c.setSlider(dw);
    columns.push_back(c);

    updateHeight(widget);

    setColumnStretch(lastColumn, 0);

    //qDebug() << columnCount << columns[columnCount].max();
    setColumnMinimumWidth(lastColumn, columns[columnCount].max());




    DragWidget* dw = new DragWidget(this);
    dw->setIndex(columnCount);
    connect(dw, &DragWidget::dragged, this, sliderMoved);
    dw->setFixedWidth(sliderWidth);
    columns[columnCount].setSlider(dw);
    headerLayout->addWidget(dw, 0, lastColumn+1, 1, 3, Qt::AlignHCenter);

    setColumnStretch(lastColumn+1, 0);
    setColumnMinimumWidth(lastColumn+1, (sliderWidth-1)/2);
    setColumnStretch(lastColumn+2, 0);
    setColumnMinimumWidth(lastColumn+2, 1);
    setColumnStretch(lastColumn+3, 0);
    setColumnMinimumWidth(lastColumn+3, (sliderWidth-1)/2);

    setColumnStretch(lastColumn+4, 1);



    columnCount++;
}

void NiceColumns::addBodyWidget(QWidget *widget, int row, int column)
{
    if(column >= columnCount)
    {
        return;
    }
    //int lastRow = bodyLayout->rowCount()-1; // last row is a spacer
    int lastRow = rowsMenu.size();
    if(row >= lastRow)
    {
        bodyLayout->setRowStretch(lastRow, 0);
        bodyLayout->setRowStretch(row+1, 1);
        rowsMenu.resize(row+1, nullptr);
    }

    bodyLayout->addWidget(widget, row, column*4+1, 1, 1);
    addWidgetToHeap(column, widget);

    if(autoResizing == true)
    {
        resizeColumn(column);
    }

    if(rowsMenu[row] == nullptr)
    {
        RowOptions* management = new RowOptions(this);
        //management->setMenu(rowMenu);
        //connect(management, &RowOptions::tag, this, &NiceColumns::tag);
        //connect(management, &RowOptions::edit, this, &NiceColumns::edit);
        //connect(management, &RowOptions::remove, this, &NiceColumns::remove);

        bodyLayout->addWidget(management, row, 0, 1, bodyLayout->columnCount()-1);
        management->raise();
        rowsMenu[row] = management;
    }
    else
    {
        rowsMenu[row]->raise();
    }
    //updateWidths(column, widget);
}

void NiceColumns::setColumnMinimumWidth(int column, int minSize)
{
    headerLayout->setColumnMinimumWidth(column, minSize);
    bodyLayout->setColumnMinimumWidth(column, minSize);
}

void NiceColumns::setColumnStretch(int column, int stretch)
{
    headerLayout->setColumnStretch(column, stretch);
    bodyLayout->setColumnStretch(column, stretch);
}

void NiceColumns::setAutoResizable(bool mode)
{
    autoResizing = mode;
}

bool NiceColumns::autoResizable() const
{
    return autoResizing;
}

void NiceColumns::updateWidths()
{
    for(column& element : columns)
    {
        setColumnMinimumWidth(element.index(), element.max());
        element.setFixedWidth(element.max());
    }
/*
    for(int i = 0; i<headerLayout->columnCount(); i++)
    {
        qDebug() << i << headerLayout->columnMinimumWidth(i) << bodyLayout->columnMinimumWidth(i);
    }
//*/
}

void NiceColumns::setRowIndex(int row, int index)
{
    if(row >= rowsMenu.size())
    {
        return;
    }

    rowsMenu[row]->setIndex(index);
}

void NiceColumns::checkScrollbars()
{
    header->widget()->updateGeometry();
    header->widget()->adjustSize();
    header->viewport()->updateGeometry();
    header->viewport()->adjustSize();
    body->widget()->updateGeometry();
    body->widget()->adjustSize();
    body->viewport()->updateGeometry();
    body->viewport()->adjustSize();

    bool fitsWidth = header->widget()->width() <= header->viewport()->width();
    horizontalScrollBar->setVisible(!fitsWidth);

    bool fitsHeight = body->widget()->height() <= body->viewport()->height();
    verticalScrollBar->setVisible(!fitsHeight);
}

void NiceColumns::clearBody()
{
    clearLayout(bodyLayout);
    for(column& element : columns)
    {
        element.clearBody();
    }
    rowsMenu.clear();
    //qDebug() << bodyLayout->columnCount() << bodyLayout->rowCount();
}

void NiceColumns::setRowMenu(int row, QMenu *menu)
{
    if(row >= rowsMenu.size())
    {
        return;
    }

    rowsMenu[row]->setMenu(menu);
}

void NiceColumns::sliderMoved(int slider, int moveAmount)
{
    if(slider >= columns.size())
    {
        return;
    }
    if(columns[slider].active() == false)
    {
        return;
    }

    int minWidth = 10;
    int newWidth = std::max(headerLayout->columnMinimumWidth(columns[slider].index()) + moveAmount, minWidth);
    columns[slider].setFixedWidth(newWidth);
    setColumnMinimumWidth(columns[slider].index(), newWidth);

/*
    qDebug() << headerLayout->sizeHint() << bodyLayout->sizeHint();

    int sum = 0;
    for(int i = 0; i<headerLayout->columnCount(); i++)
    {
        sum += headerLayout->columnMinimumWidth(i);
    }
    qDebug() << "sum header" << sum;

    sum = 0;
    for(int i = 0; i<bodyLayout->columnCount(); i++)
    {
        sum += bodyLayout->columnMinimumWidth(i);
    }
    qDebug() << "sum body" << sum;
//*/
}


void NiceColumns::columnChangedVisibility(int column, int visibility)
{
    //qDebug() << column << visibility;
    class column& col = columns[column];
    col.setVisible(visibility);
    if(visibility == true)
    {
        setColumnMinimumWidth(col.index()-1, (sliderWidth-1)/2);
        setColumnMinimumWidth(col.index(), col.width());
        setColumnMinimumWidth(col.index()+1, (sliderWidth-1)/2);
        setColumnMinimumWidth(col.index()+2, 1);
    }
    else
    {
        if(column != 0)
        {
            setColumnMinimumWidth(col.index()-1, 0);
        }
        setColumnMinimumWidth(col.index(), 0);
        setColumnMinimumWidth(col.index()+1, 0);
        setColumnMinimumWidth(col.index()+2, 0);
    }
}

void NiceColumns::updateWidths(int column, QWidget* widget)
{
    class column& heap = columns[column];
    int oldMax = heap.max();
    heap.addElement(widget);
    if(oldMax >= heap.max())
    {
        return;
    }
    columns[column].setFixedWidth(heap.max());
    setColumnMinimumWidth(columns[column].index(), heap.max());
}

void NiceColumns::updateHeight(QWidget* widget)
{

    if(widget->sizeHint().height() > maxHeightHeader)
    {
        maxHeightHeader = widget->sizeHint().height();
    }

    header->setFixedHeight(maxHeightHeader);
    /*
    class column& heap = headerWidgets;
    int oldMax = heap.max();
    heap.addElement(widget);

    if(oldMax >= heap.max())
    {
        return;
    }

    header->setFixedHeight(heap.max());
//*/
}

void NiceColumns::addWidgetToHeap(int column, QWidget *widget)
{
    columns[column].addElement(widget);
}

void NiceColumns::resizeColumn(int column)
{
    int newWidth = columns[column].max();
    if(creationMaxWidth < newWidth)
    {
        newWidth = creationMaxWidth;
    }
    setColumnMinimumWidth(columns[column].index(), newWidth);
    columns[column].setFixedWidth(newWidth);
}

void NiceColumns::clearLayout(QLayout *layout)
{
    if (!layout) return;

    while (QLayoutItem* item = layout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();  // Schedules deletion
        }
        if (QLayout* childLayout = item->layout()) {
            clearLayout(childLayout);
        }
        delete item;
    }
}
