#include "examplelist.h" // .h file

#include "exampleitem.h" // ExampleItem

ExampleList::ExampleList(QWidget *parent)
    : QWidget(parent)
    , layout(new QVBoxLayout(this))
    , model(new Model())
    , view(new ExampleView(new ExampleItem()))
{
    layout->addWidget(view);

    refresh();

    connect(view, &ExampleView::deleted,
            this, [this](int index){
        model->remove(index);
        refresh();
    });
    connect(view, &ExampleView::amogus,
            this, [this](){
        qDebug() << "sus";
    });
    connect(view, &ExampleView::sus,
            this, [this](){
        qDebug() << "amogus";
    });
}

ExampleList::~ExampleList()
{
    delete model;
}

void ExampleList::refresh()
{
    view->refresh(model->getAll());
}
