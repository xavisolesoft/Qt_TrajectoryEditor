#pragma once

#include <QAbstractTableModel>
#include <QList>
#include <QPointF>

//! \brief Table model to view and edit a trajectory composed by points.
class PointsTableModel : public QAbstractTableModel
{
public:
	PointsTableModel();

	void initPoints(const QList<QPointF>& points);

	int rowCount(const QModelIndex &parent) const override;
	int columnCount(const QModelIndex &parent) const override;
	QVariant data(const QModelIndex &index, int role) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role) override;
	QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
	Qt::ItemFlags flags(const QModelIndex &index) const override;

	void appendPoint();
	void removePoint(uint pos);

private:
	QList<QPointF> points;
};
