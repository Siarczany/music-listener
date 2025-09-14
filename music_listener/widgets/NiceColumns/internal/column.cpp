#include "column.h"

column::column(int trueIndex, int (QSize::* axis)() const)
{
    this->trueIndex = trueIndex;
    this->axis = axis;
}

void column::addElement(QWidget *widget)
{
    if(widget == nullptr)
    {
        return;
    }
    heapWidgets.push_back(widget);

    size_t currentIndex = heapWidgets.size()-1;

    while(currentIndex != 0)
    {
        if(value(currentIndex) > value((currentIndex-1)/2))
        {
            std::swap(heapWidgets[currentIndex], heapWidgets[(currentIndex-1)/2]);
            currentIndex = (currentIndex-1)/2;
        }
        else
        {
            return;
        }
    }
}

void column::addHeader(QWidget *widget)
{
    addElement(widget);
    headerWidget = widget;
}

int column::max() const
{
    if(heapWidgets.size() == 0)
    {
        return 0;
    }
    return value(0);
}

void column::setVisible(bool visibility)
{
    visible = visibility;
    for(QWidget*& element : heapWidgets)
    {
        element->setVisible(visibility);
    }
    slider->setVisible(visibility);
}

int column::index() const
{
    return trueIndex;
}

bool column::active() const
{
    return visible;
}

void column::setFixedWidth(int newWidth)
{
    for(QWidget*& ele : heapWidgets)
    {

        ele->setFixedWidth(newWidth);
    }
    lastWidth = newWidth;
}

void column::setHeaderText(QString string)
{
    headerString = string;
}

QString column::header() const
{
    return headerString;
}

int column::width() const
{
    return lastWidth;
}

void column::setSlider(DragWidget *widget)
{
    slider = widget;
}

void column::clearBody()
{
    heapWidgets.clear();
    addElement(headerWidget);
}



int column::value(size_t index) const
{
    return (heapWidgets[index]->sizeHint().*axis)();
}
