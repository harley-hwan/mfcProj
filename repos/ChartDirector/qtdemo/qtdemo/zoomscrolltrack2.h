#ifndef ZOOMSCROLLTRACK2_H
#define ZOOMSCROLLTRACK2_H

#include <QDialog>
#include <QDateEdit>
#include <QScrollBar>
#include <QDateTime>
#include <QCheckBox>
#include <QButtonGroup>
#include "qchartviewer.h"

class ZoomScrollTrack2 : public QDialog {
    Q_OBJECT
public:
    ZoomScrollTrack2(QWidget *parent = 0);
    ~ZoomScrollTrack2();

private:
    //
    // Data arrays for the scrollable / zoomable chart.
    // - In this demo, we just use a RanTable object to generate random data for the chart.
    //
    RanSeries *m_ranSeries;
    DoubleArray m_timeStamps;
    DoubleArray m_dataSeriesA;
    DoubleArray m_dataSeriesB;
    DoubleArray m_dataSeriesC;

    QButtonGroup *mouseUsage;
    QDateEdit *m_StartDate;
    QDateEdit *m_EndDate;
    QScrollBar *m_HScrollBar;
    QChartViewer *m_ChartViewer;
    QCheckBox* m_AlphaCB;
    QCheckBox* m_BetaCB;
    QCheckBox* m_GammaCB;

    void loadData();                                // Load data into data arrays
    void initChartViewer(QChartViewer *viewer);     // Initialize the QChartViewer
    void drawChart(QChartViewer *viewer);           // Draw chart
    void trackLineLabel(XYChart *c, int mouseX);    // Draw Track Cursor
    void updateControls(QChartViewer *viewer);      // Update other controls

private slots:
    void onSelectDataSeries();
    void onStartDateChanged(QDateTime date);
    void onEndDateChanged(QDateTime date);
    void onHScrollBarChanged(int value);
    void onMouseUsageChanged(QAbstractButton *b);
    void onViewPortChanged();
    void onMouseMovePlotArea(QMouseEvent *event);
};

#endif // ZOOMSCROLLTRACK2_H
