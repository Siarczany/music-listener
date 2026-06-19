#include "examplewidget.h" // .h file


ExampleResizable::ExampleResizable(QWidget *parent)
    : QWidget(parent)
    , resizableWidget(new ResizableWidget(this, this))
{
    // if you want to pass a signal about size change somewhere upper
    //  like in NiceLineEdit for example resizing label alongside the line edit
    connect(resizableWidget, &ResizableWidget::sizeChanged,
            this, [this](){
        emit sizeChanged();
    });
}

ExampleResizable::~ExampleResizable()
{

}

void ExampleResizable::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    resizableWidget->resize();
}
