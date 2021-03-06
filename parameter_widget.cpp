#include "parameter_widget.h"
#include <iostream>

parameter_widget::parameter_widget(point_3d_list* p,QWidget* parent,action_connection_manager_iface* con):
    qt_parameter(p->getName(),parent),parameter(p),connectionManager(con),connector(0)
{

}
void parameter_widget::mouseReleaseEvent(QMouseEvent * event)
{
    std::cout<<"basic_action_widget: mouseReleaseEvent"<<std::endl;

    qt_action::mouseReleaseEvent(event);

    if(this->rect().contains(event->pos())&&!this->isDragging)
    {
        this->connectionManager->connect(this);
    }
}
void parameter_widget::mousePressEvent(QMouseEvent * event)
{
    std::cout<<"basic_action_widget: mousePressEvent"<<std::endl;
    qt_action::mousePressEvent(event);
}
void parameter_widget::mouseMoveEvent(QMouseEvent * event)
{
    qt_action::mouseMoveEvent(event);
    if(connector != 0)
        this->connector->onActionMoved();
}
