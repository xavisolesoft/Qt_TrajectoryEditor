#include "TrajectoryEditor.h"
#include "PointsModel.h"

#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	PointsModel pointsModel;
	pointsModel.appendPoint(QPointF(0,6));
	pointsModel.appendPoint(QPointF(2,4));
	pointsModel.appendPoint(QPointF(3,8));
	pointsModel.appendPoint(QPointF(7,4));
	pointsModel.appendPoint(QPointF(10,5));
	pointsModel.appendPoint(QPointF(11,1));
	pointsModel.appendPoint(QPointF(13,3));
	pointsModel.appendPoint(QPointF(17,6));
	pointsModel.appendPoint(QPointF(18,3));
	pointsModel.appendPoint(QPointF(20,2));

    TrajectoryEditor w;
	w.init(pointsModel);
	w.show();

	return a.exec();
}
