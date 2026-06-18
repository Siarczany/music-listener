#include "exampleitem.h" // .h file

#include "exampleview.h" // ExampleView for signals

class ExampleView;

ExampleItem::ExampleItem(QWidget *parent, ExampleData *data)
    : ItemWidgetBase(parent)
    , layout(new QHBoxLayout(this))
    , label(new QLabel())
    , del(new QPushButton("x"))
{
    layout->addWidget(label);
    layout->addStretch();
    layout->addWidget(del);

    update(data);

    setFullyVisible(false);

    connect(del, &QPushButton:: clicked,
            this, &ExampleItem::deleted);
}

ExampleItem::~ExampleItem()
{

}

void ExampleItem::setFullyVisible(bool visible)
{
    del->setVisible(visible);
}

void ExampleItem::update(ModelData *data)
{
    if(data == nullptr)
    {
        return;
    }
    ExampleData* newData = static_cast<ExampleData*>(data);
    label->setText(newData->name);
}

void ExampleItem::connectToList(ViewBase *list, int index)
{
    ExampleView* view = static_cast<ExampleView*>(list);
    connect(this, &ExampleItem::deleted,
            this, [view, index](){
        emit view->deleted(index);
    });
    connect(this, &ExampleItem::sus,
               this, [view](){
        emit view->amogus();
    });
    connect(this, &ExampleItem::amogus,
            this, [view](){
        emit view->sus();
    });
}

ItemWidgetBase *ExampleItem::nowy(QWidget *parent, ModelData *data)
{
    ExampleItem* item = new ExampleItem(parent, data);
    return item;
}


