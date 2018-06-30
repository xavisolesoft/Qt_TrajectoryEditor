#include "TrajectoryEditor.h"
#include "ui_TrajectoryEditor.h"
#include "PointsTableModel.h"
#include "PointsModel.h"

TrajectoryEditor::TrajectoryEditor(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::TrajectoryEditor)
{
	ui->setupUi(this);
}

TrajectoryEditor::~TrajectoryEditor()
{
	delete ui;
}

void TrajectoryEditor::init(PointsModel &pointsModel)
{
	this->pointsModel = &pointsModel;

	initMenuActions();
	initChartView();
	initEditor();
}

void TrajectoryEditor::pointsTableModelDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight)
{
	Q_UNUSED(bottomRight);
	QAbstractItemModel* tableModel = ui->pointsTableView->model();

	QModelIndex topLeftX = tableModel->index(topLeft.row(),0);
	float x = tableModel->data(topLeftX,Qt::DisplayRole).toFloat();

	QModelIndex topLeftY = tableModel->index(topLeft.row(),1);
	float y = tableModel->data(topLeftY, Qt::DisplayRole).toFloat();

	pointsModel->modifyPoint(topLeft.row(),QPointF(x,y));
}

void TrajectoryEditor::initMenuActions()
{
	initShowEditorAction();
}

void TrajectoryEditor::initShowEditorAction()
{
	ui->actionShowEditor->setCheckable(true);
	ui->actionShowEditor->setChecked(true);

    connect(ui->editorDockWidget, &QDockWidget::visibilityChanged, [this]{
		ui->actionShowEditor->blockSignals(true);
		ui->actionShowEditor->setChecked(!ui->editorDockWidget->isHidden());
		ui->actionShowEditor->blockSignals(false);
	});

    connect(ui->actionShowEditor, &QAction::changed, [this]{
		ui->actionShowEditor->blockSignals(true);
		ui->editorDockWidget->setHidden(!ui->editorDockWidget->isHidden());
		ui->actionShowEditor->blockSignals(false);
	});
}

void TrajectoryEditor::initChartView()
{
    QLineSeries* lineSeries = createLineSeries();

	QChart* chart = createChart(lineSeries);

    connect(pointsModel, &PointsModel::pointAppended, [lineSeries]{
		lineSeries->append(std::move(QPointF()));
	});

    connect(pointsModel, &PointsModel::pointModified, [lineSeries](uint pos, const QPointF& point){
		lineSeries->replace(pos,point);
	});

    connect(pointsModel, &PointsModel::pointRemoved, [lineSeries](uint pos){
		lineSeries->remove(pos);
	});

	ui->chartView->setChart(chart);
	ui->chartView->setRenderHint(QPainter::Antialiasing);
    ui->chartView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
}

QLineSeries *TrajectoryEditor::createLineSeries() const
{
	QLineSeries *lineSeries = new QLineSeries();
	lineSeries->setName("line");

	foreach(const QPointF& point, pointsModel->getPoints()){
		lineSeries->append(point.x(),point.y());
	}

	return lineSeries;
}

QChart* TrajectoryEditor::createChart(QLineSeries *lineSeries) const
{
	QChart* chart = new QChart();
	chart->addSeries(lineSeries);
	chart->legend()->hide();
	chart->setTitle(tr("Trajectory"));
	chart->createDefaultAxes();
	return chart;
}

void TrajectoryEditor::initEditor()
{
	initAddButton();
	initRemoveButton();
	initPointsTable();
}

void TrajectoryEditor::initAddButton()
{
    connect(ui->addPushButton, SIGNAL(pressed()), pointsModel, SLOT(appendPoint()));
}

void TrajectoryEditor::initRemoveButton()
{
    connect(ui->removePushButton, &QPushButton::pressed, [this]{
		QModelIndexList selectedIndexes = ui->pointsTableView->selectionModel()->selectedRows();
		if(!selectedIndexes.empty()){
			pointsModel->removePoint(selectedIndexes.first().row());
		}
	});
}

void TrajectoryEditor::initPointsTable()
{
	PointsTableModel* pointsTableModel = new PointsTableModel();

	pointsTableModel->initPoints(pointsModel->getPoints());

	ui->pointsTableView->setModel(pointsTableModel);
	ui->pointsTableView->setSelectionMode(QTableView::SingleSelection);
	ui->pointsTableView->setSelectionBehavior(QTableView::SelectRows);
    ui->pointsTableView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContentsOnFirstShow);

    connect(pointsModel, &PointsModel::pointAppended, [pointsTableModel]{
		pointsTableModel->appendPoint();
	});

    connect(pointsTableModel,
            SIGNAL(dataChanged(const QModelIndex&,const QModelIndex&)),
            SLOT(pointsTableModelDataChanged(const QModelIndex&,const QModelIndex&)));

    connect(pointsModel, &PointsModel::pointRemoved, [pointsTableModel](uint pos){
		pointsTableModel->removePoint(pos);
	});
}
