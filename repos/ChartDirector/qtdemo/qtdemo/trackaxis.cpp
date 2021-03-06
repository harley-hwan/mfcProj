#include <QApplication>
#include "trackaxis.h"
#include <sstream>
#include <algorithm>


TrackAxis::TrackAxis(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Track Line with Axis Labels");

    // Create the QChartViewer and draw the chart
    m_ChartViewer = new QChartViewer(this);
    drawChart(m_ChartViewer);

    // Set the window to be of the same size as the chart
    setFixedSize(m_ChartViewer->width(), m_ChartViewer->height());

    // Set up the mouseMovePlotArea handler for drawing the track cursor
    connect(m_ChartViewer, SIGNAL(mouseMovePlotArea(QMouseEvent*)),
        SLOT(onMouseMovePlotArea(QMouseEvent*)));
}

TrackAxis::~TrackAxis()
{
    delete m_ChartViewer->getChart();
}

//
// Draw the chart and display it in the given viewer
//
void TrackAxis::drawChart(QChartViewer *viewer)
{
    // Data for the chart as 2 random data series
    RanSeries r(127);
    DoubleArray data0 = r.getSeries(180, 10, -1.5, 1.5);
    DoubleArray data1 = r.getSeries(180, 150, -15, 15);
    DoubleArray timeStamps = r.getDateSeries(180, Chart::chartTime(2011, 1, 1), 86400);

    // Create a XYChart object of size 670 x 400 pixels
    XYChart *c = new XYChart(670, 400);

    // Add a title to the chart using 18 pts Times New Roman Bold Italic font
    c->addTitle("Plasma Stabilizer Energy Usage", "Times New Roman Bold Italic", 18);

    // Set the plotarea at (50, 55) with width 100 pixels less than chart width, and height 90 pixels
    // less than chart height. Use a vertical gradient from light blue (f0f6ff) to sky blue (a0c0ff)
    // as background. Set border to transparent and grid lines to white (ffffff).
    c->setPlotArea(50, 55, c->getWidth() - 100, c->getHeight() - 90, c->linearGradientColor(0, 55, 0,
        c->getHeight() - 35, 0xf0f6ff, 0xa0c0ff), -1, Chart::Transparent, 0xffffff, 0xffffff);

    // Add a legend box at (50, 25) using horizontal layout. Use 10pts Arial Bold as font. Set the
    // background and border color to Transparent.
    c->addLegend(50, 25, false, "Arial Bold", 10)->setBackground(Chart::Transparent);

    // Set axis label style to 8pts Arial Bold
    c->xAxis()->setLabelStyle("Arial Bold", 8);
    c->yAxis()->setLabelStyle("Arial Bold", 8);
    c->yAxis2()->setLabelStyle("Arial Bold", 8);

    // Set the axis stem to transparent
    c->xAxis()->setColors(Chart::Transparent);
    c->yAxis()->setColors(Chart::Transparent);
    c->yAxis2()->setColors(Chart::Transparent);

    // Configure x-axis label format
    c->xAxis()->setMultiFormat(Chart::StartOfYearFilter(), "{value|mm/yyyy} ",
        Chart::StartOfMonthFilter(), "{value|mm}");

    // Add axis title using 10pts Arial Bold Italic font
    c->yAxis()->setTitle("Power Usage (Watt)", "Arial Bold Italic", 10);
    c->yAxis2()->setTitle("Effective Load (kg)", "Arial Bold Italic", 10);

    // Add a line layer to the chart using a line width of 2 pixels.
    LineLayer *layer = c->addLineLayer();
    layer->setLineWidth(2);

    // Add 2 data series to the line layer
    layer->setXData(timeStamps);
    layer->addDataSet(data0, 0xcc0000, "Power Usage");
    layer->addDataSet(data1, 0x008800, "Effective Load")->setUseYAxis2();

    // Set the chart image to the QChartViewer
    viewer->setChart(c);
}

//
// Draw track cursor when mouse is moving over plotarea
//
void TrackAxis::onMouseMovePlotArea(QMouseEvent *)
{
    trackLineAxis((XYChart *)m_ChartViewer->getChart(), m_ChartViewer->getPlotAreaMouseX());
    m_ChartViewer->updateDisplay();
    
    // Hide the track cursor when the mouse leaves the plot area
    m_ChartViewer->removeDynamicLayer("mouseLeavePlotArea");
}

//
// Draw track line with axis labels
//
void TrackAxis::trackLineAxis(XYChart *c, int mouseX)
{
    // Clear the current dynamic layer and get the DrawArea object to draw on it.
    DrawArea *d = c->initDynamicLayer();

    // The plot area object
    PlotArea *plotArea = c->getPlotArea();

    // Get the data x-value that is nearest to the mouse, and find its pixel coordinate.
    double xValue = c->getNearestXValue(mouseX);
    int xCoor = c->getXCoor(xValue);

    // The vertical track line is drawn up to the highest data point (the point with smallest
    // y-coordinate). We need to iterate all datasets in all layers to determine where it is.
    int minY = plotArea->getBottomY();

    // Iterate through all layers to find the highest data point
    for(int i = 0; i < c->getLayerCount(); ++i) {
        Layer *layer = c->getLayerByZ(i);

        // The data array index of the x-value
        int xIndex = layer->getXIndexOf(xValue);

        // Iterate through all the data sets in the layer
        for(int j = 0; j < layer->getDataSetCount(); ++j) {
            DataSet *dataSet = layer->getDataSetByZ(j);

            double dataPoint = dataSet->getPosition(xIndex);
            if ((dataPoint != Chart::NoValue) && (dataSet->getDataColor() != (int)Chart::Transparent))
                minY = (std::min)(minY, c->getYCoor(dataPoint, dataSet->getUseYAxis()));
        }
    }

    // Draw a vertical track line at the x-position up to the highest data point.
    d->vline((std::max)(minY, plotArea->getTopY()), plotArea->getBottomY() + 6, xCoor,
        d->dashLineColor(0x000000, 0x0101));

    // Draw a label on the x-axis to show the track line position
    std::ostringstream xlabel;
    xlabel << "<*font,bgColor=000000*> " << c->xAxis()->getFormattedLabel(xValue, "mmm dd, yyyy")
        << " <*/font*>";
    TTFText *t = d->text(xlabel.str().c_str(), "Arial Bold", 8);
    t->draw(xCoor, plotArea->getBottomY() + 6, 0xffffff, Chart::Top);
    t->destroy();

    // Iterate through all layers to build the legend array
    for(int i = 0; i < c->getLayerCount(); ++i) {
        Layer *layer = c->getLayerByZ(i);

        // The data array index of the x-value
        int xIndex = layer->getXIndexOf(xValue);

        // Iterate through all the data sets in the layer
        for(int j = 0; j < layer->getDataSetCount(); ++j) {
            DataSet *dataSet = layer->getDataSetByZ(j);

            // The positional value, axis binding, pixel coordinate and color of the data point.
            double dataPoint = dataSet->getPosition(xIndex);
            Axis *yAxis = dataSet->getUseYAxis();
            int yCoor = c->getYCoor(dataPoint, yAxis);
            int color = dataSet->getDataColor();

            // Draw the axis label only for visible data points of named data sets
            if ((dataPoint != Chart::NoValue) && (color != (int)Chart::Transparent) && (yCoor >=
                plotArea->getTopY()) && (yCoor <= plotArea->getBottomY())) {
                // The axis label consists of 3 parts - a track dot for the data point, an axis label,
                // and a line joining the track dot to the axis label.

                // Draw the line first. The end point of the line at the axis label side depends on
                // whether the label is at the left or right side of the axis (that is, on whether the
                // axis is on the left or right side of the plot area).
                int xPos = yAxis->getX() + ((yAxis->getAlignment() == Chart::Left) ? -4 : 4);
                d->hline(xCoor, xPos, yCoor, d->dashLineColor(color, 0x0101));

                // Draw the track dot
                d->circle(xCoor, yCoor, 4, 4, color, color);

                // Draw the axis label. If the axis is on the left side of the plot area, the labels
                // should right aligned to the axis, and vice versa.
                std::ostringstream axisLabel;
                axisLabel << "<*font,bgColor=" << std::hex << color << "*> "
                    << c->formatValue(dataPoint, "{value|P4}")	<< " <*/font*>";
                t = d->text(axisLabel.str().c_str(), "Arial Bold", 8);
                t->draw(xPos, yCoor, 0xffffff,
                    ((yAxis->getAlignment() == Chart::Left) ? Chart::Right : Chart::Left));
                t->destroy();
            }
        }
    }
}
