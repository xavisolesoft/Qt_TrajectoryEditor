#include "PointsModel.h"

#include <QPointF>

PointsModel::PointsModel()
{

}
void PointsModel::appendPoint()
{
	points.push_back(std::move(QPointF()));
	emit pointAppended();
}


void PointsModel::appendPoint(QPointF &&point)
{
	points.push_back(std::move(point));
}

const QList<QPointF> &PointsModel::getPoints() const
{
	return points;
}

void PointsModel::modifyPoint(uint pos, const QPointF &point)
{
	points[pos] = point;
	emit pointModified(pos,point);
}

void PointsModel::removePoint(uint pos)
{
	points.removeAt(pos);
	emit pointRemoved(pos);
}
