#include "action_connector_widget.h"
#include <iostream>
#include <QRegion>
#include <QVector>
#include <QPolygon>
#include <QPen>
#include <math.h>
#include <QVector2D>
#include "basic_action_widget.h"

action_connector_widget::action_connector_widget(QWidget* parent):qt_arrow(0,0,parent)
{

}
action_connector_widget::action_connector_widget(QWidget* parent,action_connection_manager_iface* m,basic_action_widget* from,basic_action_widget* to):qt_arrow((QWidget*)from,(QWidget*)to,parent),to(to),from(from)
{
    std::cout<<"action_connector_widget ctor"<<std::endl;
    this->mgr = m;
    this->onActionMoved();
}
void action_connector_widget::onActionMoved()
{
    QPoint upperPoint;
    QPoint lowerPoint;

    if(this->widgetFrom->pos().y()<this->widgetTo->pos().y())
    {
        upperPoint = this->widgetFrom->pos();
        lowerPoint = this->widgetTo->pos();
    }else
    {
        upperPoint = this->widgetTo->pos();
        lowerPoint = this->widgetFrom->pos();
    }

    QPoint dir = this->widgetFrom->pos();
    dir-=this->widgetTo->pos();
    QSize s(abs(dir.x())+60,abs(dir.y())+60);
    this->resize(s);

    //Case 1: upper point is upper left corner of widget
    if(upperPoint.x()<lowerPoint.x())
    {
        this->upperLeft = upperPoint;
    }else
    {
        //Case 2: compute upper left corner of widget
        QPoint upperLeftCorner;
        upperLeftCorner.setX(lowerPoint.x());
        upperLeftCorner.setY(upperPoint.y());
        this->upperLeft = upperLeftCorner;
    }

    this->move(this->upperLeft-QPoint(30,30));

    dir = this->widgetFrom->pos()-this->widgetTo->pos();


    int px = dir.x();
    dir.setX(dir.y());
    dir.setY(-px);

    QVector2D dirVect(dir);
    dirVect.normalize();
    dirVect*=20;
    dir = dirVect.toPoint();
    QPoint p1 = this->widgetFrom->pos()+dir;
    QPoint p2 = this->widgetFrom->pos()-dir;
    QPoint p3 = this->widgetTo->pos()+dir;
    QPoint p4 = this->widgetTo->pos()-dir;

    QVector<QPoint> points;
    points.append(this->mapFromParent(p1));
    points.append(this->mapFromParent(p2));
    points.append(this->mapFromParent(p4));
    points.append(this->mapFromParent(p3));


    QPolygon poli(points);

    this->mask = poli;

    QRegion mask(poli);
    this->setMask(mask);
}
void action_connector_widget::deleteConnection()
{
    this->getFrom()->deleteTo();
    this->getTo()->deleteFrom();
    delete this;
}
void action_connector_widget::unmarkItem()
{
    this->marked=false;
    this->update();
}
void action_connector_widget::deleteItem()
{
    this->getFrom()->deleteTo();
    this->getTo()->deleteFrom();
    delete this;
}
void action_connector_widget::mousePressEvent(QMouseEvent *e)
{
    this->mgr->mark(this);
    qt_arrow::mousePressEvent(e);
}
