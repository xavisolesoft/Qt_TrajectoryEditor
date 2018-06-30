#pragma once

#include <QList>
#include <QPointF>
#include <QObject>

//! \brief Data model for all system data representation.
class PointsModel : public QObject
{
	Q_OBJECT
public:
	PointsModel();

	void appendPoint(QPointF&& point);
	const QList<QPointF>& getPoints() const;

signals:
	void pointAppended();
	void pointModified(uint pos, const QPointF& point);
	void pointRemoved(uint pos);

public slots:
	void appendPoint();
	void modifyPoint(uint pos, const QPointF& point);
	void removePoint(uint pos);

private:
	QList<QPointF> points;
};
