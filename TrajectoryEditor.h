#pragma once

#include <QMainWindow>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>

class PointsModel;

QT_CHARTS_USE_NAMESPACE

namespace Ui {
class TrajectoryEditor;
}

//! \brief Main window of the program.
class TrajectoryEditor : public QMainWindow
{
	Q_OBJECT

public:
	explicit TrajectoryEditor(QWidget *parent = 0);
	~TrajectoryEditor();

	void init(PointsModel& pointsModel);

signals:
	void appenPoint(const QPointF& point);

private slots:
	void pointsTableModelDataChanged(const QModelIndex &topLeft,const QModelIndex &bottomRight);

private:
	void initMenuActions();
	void initShowEditorAction();

	void initChartView();
	QLineSeries* createLineSeries() const;
	QChart* createChart(QLineSeries *lineSeries) const;

	void initEditor();
	void initAddButton();
	void initRemoveButton();
	void initPointsTable();

	Ui::TrajectoryEditor *ui;
	PointsModel* pointsModel;
};
