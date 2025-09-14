#include "playlists_screen_slider.h"

#include <QMouseEvent>

sliding_widget::sliding_widget(QWidget *parent
                               , QGridLayout *layout
                               , QWidget* screen_1
                               , QWidget* screen_2)
    : QFrame(parent)
{
    this->layout = layout;
    this->screen_1 = screen_1;
    this->screen_2 = screen_2;
    setFrameStyle(QFrame::Raised | QFrame::StyledPanel);
    setAcceptDrops(true);
}

sliding_widget::~sliding_widget()
{

}

void sliding_widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        start_point = event->pos();
        dragging = true;
    }
}

void sliding_widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        dragging = false;
    }
}

void sliding_widget::mouseMoveEvent(QMouseEvent *event)
{
    if(dragging)
    {
        int new_middle = mapToParent(event->pos()).x();
        int parent_width = parentWidget()->width();

        int unfillable_space = width()+2;
        int free_space = parent_width - unfillable_space;
        int width_one_direction = (width()-1)/2;

        // +1 in the first check is from the left padding which is 1 pixel
        // -2 in the second check is from the right padding which is also 1 pixel
        //  and I think from the mouse position starting from 0 so last pixel is for example
        //  799 but width says that widget is 800 long so -1 because of that
        if(std::max(screen_1->minimumWidth(), width_one_direction) + 1  < new_middle
            && new_middle < parent_width - std::max(screen_2->minimumWidth(), width_one_direction) - 2)
        {
            //int screen_1_size = new_middle-(width()+2)/2;
            //layout->setColumnStretch(1, new_middle-unfillable_space);
            //layout->setColumnStretch(5, parent_width - new_middle-(width()+2)/2-1);
            //layout->setColumnStretch(5, parent_width - new_middle-unfillable_space-1);

            int screen_1_size = new_middle - 1 - width_one_direction;
            layout->setColumnStretch(1, screen_1_size);
            layout->setColumnStretch(5, free_space-screen_1_size);
        }

    }
}

void sliding_widget::setExtraSpace(int space)
{
    extra_space = space;
}

int sliding_widget::extraSpace() const
{
    return extra_space;
}

