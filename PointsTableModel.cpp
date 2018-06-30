#include "PointsTableModel.h"

#include <QString>

PointsTableModel::PointsTableModel()
{

}

void PointsTableModel::initPoints(const QList<QPointF> &points)
{
	beginResetModel();
	this->points = points;
	endResetModel();
}

int PointsTableModel::rowCount(const QModelIndex &parent) const
{
	Q_UNUSED( parent );
	return points.size();
}

int PointsTableModel::columnCount(const QModelIndex &parent) const
{
	Q_UNUSED( parent );
	return 2;
}

QVariant PointsTableModel::data(const QModelIndex &index, int role) const
{
	if(role == Qt::DisplayRole || role == Qt::EditRole){
        switch(index.column()){
		case 0:
			return points[index.row()].x();
		case 1:
			return points[index.row()].y();
		default:
			;
		}
    }

	return QVariant();
}

bool PointsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	if(role == Qt::EditRole){
		switch (index.column()) {
		case 0:
			points[index.row()].setX(value.toDouble());
			emit dataChanged(index,index);
			return true;
		case 1:
			points[index.row()].setY(value.toDouble());
			emit dataChanged(index,index);
			return true;
		default:
			;
		}
	}

	return false;
}

QVariant PointsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if(role == Qt::DisplayRole){
		if(orientation == Qt::Horizontal){
			switch (section) {
			case 0:
				return tr("X");
			case 1:
				return tr("Y");
			default:
				;
			}
		}else{
			return QString::number(section);
		}
	}

	return QVariant();
}

Qt::ItemFlags PointsTableModel::flags(const QModelIndex &index) const
{
	Q_UNUSED(index);
	return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled ;
}

void PointsTableModel::appendPoint()
{
	beginResetModel();
	points.push_back(std::move(QPointF()));
	endResetModel();
}

void PointsTableModel::removePoint(uint pos)
{
	beginResetModel();
	points.removeAt(pos);
	endResetModel();
}
