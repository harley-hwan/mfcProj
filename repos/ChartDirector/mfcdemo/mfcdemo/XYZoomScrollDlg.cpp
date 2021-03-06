// xyzoomscrollDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "xyzoomscrollDlg.h"
#include "HotSpotDlg.h"
#include "chartdir.h"
#include <sstream>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
// Constructor
//
CXYZoomScrollDlg::CXYZoomScrollDlg(CWnd* pParent /*=NULL*/)
    : CDialog(IDD_XYZOOMSCROLL, pParent)
{
}

//
// Destructor
//
CXYZoomScrollDlg::~CXYZoomScrollDlg()
{
    delete m_ChartViewer.getChart();
    delete m_ViewPortControl.getChart();
}


void CXYZoomScrollDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_PointerPB, m_PointerPB);
    DDX_Control(pDX, IDC_ZoomBar, m_ZoomBar);
    DDX_Control(pDX, IDC_ChartViewer, m_ChartViewer);
    DDX_Control(pDX, IDC_ViewPortControl, m_ViewPortControl);
}

BEGIN_MESSAGE_MAP(CXYZoomScrollDlg, CDialog)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_PointerPB, OnPointerPB)
    ON_BN_CLICKED(IDC_ZoomInPB, OnZoomInPB)
    ON_BN_CLICKED(IDC_ZoomOutPB, OnZoomOutPB)
    ON_BN_CLICKED(IDC_SavePB, OnSavePB)
    ON_WM_HSCROLL()
    ON_BN_CLICKED(IDC_ChartViewer, OnChartViewerClick)
    ON_CONTROL(CVN_ViewPortChanged, IDC_ChartViewer, OnViewPortChanged)
    ON_CONTROL(CVN_MouseMovePlotArea, IDC_ChartViewer, OnMouseMovePlotArea)
END_MESSAGE_MAP()

//
// Initialization
//
BOOL CXYZoomScrollDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
   
    //
    // Initialize member variables
    //
    m_extBgColor = getDefaultBgColor();     // Default background color

    //
    // Initialize controls
    //

    // Load icons to mouse usage buttons
    loadButtonIcon(IDC_PointerPB, IDI_PointerPB, 100, 20);  
    loadButtonIcon(IDC_ZoomInPB, IDI_ZoomInPB, 100, 20);    
    loadButtonIcon(IDC_ZoomOutPB, IDI_ZoomOutPB, 100, 20);
    loadButtonIcon(IDC_SavePB, IDI_SavePB, 100, 20);  

    // Set Pointer pushbutton into clicked state
    m_PointerPB.SetCheck(1);

    // Initialize zoom bar
    m_ZoomBar.SetRange(1, 100);
    m_ZoomBar.SetPageSize(5);
    m_ZoomBar.SetTicFreq(10);

    // Set initial mouse usage for ChartViewer
    m_ChartViewer.setMouseUsage(Chart::MouseUsageScroll);
    m_ChartViewer.setScrollDirection(Chart::DirectionHorizontalVertical);
    m_ChartViewer.setZoomDirection(Chart::DirectionHorizontalVertical);
    
    // Enable mouse wheel zooming by setting the zoom ratio to 1.1 per wheel event
    m_ChartViewer.setMouseWheelZoomRatio(1.1);

    // Load the data
    loadData();

    // Trigger the ViewPortChanged event to draw the chart
    m_ChartViewer.updateViewPort(true, true);

    // Configure the CViewPortControl to use transparent black for region outside the viewport,
    // that is, to darken the outside region.
    m_ViewPortControl.setViewPortExternalColor(0x7f000000);
    m_ViewPortControl.setViewPortBorderColor(0x7fffffff);
    m_ViewPortControl.setSelectionBorderColor(0x7fffffff); 
    
    // Draw and display the full chart in the CViewPortControl
    drawFullChart(&m_ViewPortControl, &m_ChartViewer);

    // Bind the CChartViewer to the CViewPortControl
    m_ViewPortControl.setViewer(&m_ChartViewer);

    return TRUE;
}

//
// User clicks on the Scroll pushbutton
//
void CXYZoomScrollDlg::OnPointerPB() 
{
    m_ChartViewer.setMouseUsage(Chart::MouseUsageScroll);   
}

//
// User clicks on the Zoom In pushbutton
//
void CXYZoomScrollDlg::OnZoomInPB() 
{
    m_ChartViewer.setMouseUsage(Chart::MouseUsageZoomIn);   
}

//
// User clicks on the Zoom Out pushbutton
//
void CXYZoomScrollDlg::OnZoomOutPB() 
{
    m_ChartViewer.setMouseUsage(Chart::MouseUsageZoomOut);  
}

//
// User clicks on the Save pushbutton
//
void CXYZoomScrollDlg::OnSavePB()
{
    // Supported formats = PNG, JPG, GIF, BMP, SVG and PDF
    TCHAR szFilters[]= _T("PNG (*.png)|*.png|JPG (*.jpg)|*.jpg|GIF (*.gif)|*.gif|")
        _T("BMP (*.bmp)|*.bmp|SVG (*.svg)|*.svg|PDF (*.pdf)|*.pdf||");

    // The standard CFileDialog
    CFileDialog fileDlg(FALSE, _T("png"), _T("chartdirector_demo"), OFN_HIDEREADONLY | 
        OFN_OVERWRITEPROMPT, szFilters);
    if(fileDlg.DoModal() != IDOK)
        return;

    // Save the chart
    CString path = fileDlg.GetPathName();
    BaseChart *c = m_ChartViewer.getChart();
    if (0 != c)
        c->makeChart(TCHARtoUTF8(path));
}

//
// The ViewPortChanged event handler. This event occurs if the user scrolls or zooms in or 
// out the chart by dragging or clicking on the chart. It can also be triggered by calling
// CChartViewer.updateViewPort and by the CViewPortControl.
//
void CXYZoomScrollDlg::OnViewPortChanged()
{
    // In addition to updating the chart, we may also need to update other controls that
    // changes based on the view port.
    updateControls(&m_ChartViewer);

    // Update the chart if necessary
    if (m_ChartViewer.needUpdateChart())
        drawChart(&m_ChartViewer);
    
    // Update the image map if necessary
    if (m_ChartViewer.needUpdateImageMap())
        updateImageMap(&m_ChartViewer);
}

//
// Draw track cursor when mouse is moving over plotarea, and update image map if necessary
//
void CXYZoomScrollDlg::OnMouseMovePlotArea()
{
    // Draw crosshair track cursor
    crossHair((XYChart *)m_ChartViewer.getChart(), m_ChartViewer.getPlotAreaMouseX(), 
        m_ChartViewer.getPlotAreaMouseY());
    m_ChartViewer.updateDisplay();

    // Hide the track cursor when the mouse leaves the plot area
    m_ChartViewer.removeDynamicLayer(CVN_MouseLeavePlotArea);

    // Update image map if necessary. If the mouse is still dragging, the chart is still 
    // updating and not confirmed, so there is no need to set up the image map.
    if (!m_ChartViewer.isMouseDragging())
        updateImageMap(&m_ChartViewer);
}

//
// User moves the Zoom slider control
//
void CXYZoomScrollDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
    if (nSBCode != SB_ENDSCROLL)
    {
        //
        // The slider is moving. Update the chart.
        //

        // Remember the center point
        double centerX = m_ChartViewer.getViewPortLeft() + 
            m_ChartViewer.getViewPortWidth() / 2;
        double centerY = m_ChartViewer.getViewPortTop() + 
            m_ChartViewer.getViewPortHeight() / 2;
            
        // Aspect ratio and zoom factor
        double aspectRatio = m_ChartViewer.getViewPortWidth() / 
            m_ChartViewer.getViewPortHeight();
        double zoomTo = ((double)m_ZoomBar.GetPos()) / m_ZoomBar.GetRangeMax();

        // Zoom by adjusting ViewPortWidth and ViewPortHeight while maintaining the aspect 
        // ratio
        m_ChartViewer.setViewPortWidth(zoomTo * ((aspectRatio < 1) ? 1 : aspectRatio));
        m_ChartViewer.setViewPortHeight(zoomTo * ((aspectRatio > 1) ? 1 : (1 / aspectRatio)));
        
        // Adjust ViewPortLeft and ViewPortTop to keep center point unchanged
        m_ChartViewer.setViewPortLeft(centerX - m_ChartViewer.getViewPortWidth() / 2);
        m_ChartViewer.setViewPortTop(centerY - m_ChartViewer.getViewPortHeight() / 2);
        
        // Update the chart image only, but no need to update the image map.
        m_ChartViewer.updateViewPort(true, false);
    }
        
    CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

//
// User clicks on the CChartViewer
//
void CXYZoomScrollDlg::OnChartViewerClick()
{
    ImageMapHandler *handler = m_ChartViewer.getImageMapHandler();
    if (0 != handler)
    {
        //
        // Query the ImageMapHandler to see if the mouse is on a clickable hot spot. We 
        // consider the hot spot as clickable if its href ("path") parameter is not empty.
        //
        const char *path = handler->getValue("path");
        if ((0 != path) && (0 != *path))
        {
            // In this sample code, we just show all hot spot parameters.
            CHotSpotDlg hs;
            hs.SetData(handler);
            hs.DoModal();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// CXYZoomScrollDlg methods

//
// Load the data
//
void CXYZoomScrollDlg::loadData()
{
    //
    // For simplicity, in this demo, we just use hard coded data. 
    //
    double X0[] = {10, 15, 6, -12, 14, -8, 13, -3, 16, 12, 10.5, -7, 3, -10, -5, 2, 5};
    double Y0[] = {130, 150, 80, 110, -110, -105, -130, -15, -170, 125,  125, 60, 25, 150,
        150, 15, 120};
    double X1[] = {6, 7, -4, 3.5, 7, 8, -9, -10, -12, 11, 8, -3, -2, 8, 4, -15, 15};
    double Y1[] = {65, -40, -40, 45, -70, -80, 80, 10, -100, 105, 60, 50, 20, 170, -25, 
        50, 75};
    double X2[] = {-10, -12, 11, 8, 6, 12, -4, 3.5, 7, 8, -9, 3, -13, 16, -7.5, -10, -15};
    double Y2[] = {65, -80, -40, 45, -70, -80, 80, 90, -100, 105, 60, -75, -150, -40, 120, 
        -50, -30};

    dataX0.assign(X0, X0 + sizeof(X0) / sizeof(*X0));
    dataY0.assign(Y0, Y0 + sizeof(Y0) / sizeof(*Y0));
    dataX1.assign(X1, X1 + sizeof(X1) / sizeof(*X1));
    dataY1.assign(Y1, Y1 + sizeof(Y1) / sizeof(*Y1));
    dataX2.assign(X2, X2 + sizeof(X2) / sizeof(*X2));
    dataY2.assign(Y2, Y2 + sizeof(Y2) / sizeof(*Y2));
}

//
// Draw the chart and display it in the given viewer
//
void CXYZoomScrollDlg::drawChart(CChartViewer *viewer)
{               
    // Create an XYChart object 500 x 480 pixels in size, with the same background color
    // as the container
    XYChart *c = new XYChart(500, 480, m_extBgColor);

    // Set the plotarea at (50, 40) and of size 400 x 400 pixels. Use light grey (c0c0c0)
    // horizontal and vertical grid lines. Set 4 quadrant coloring, where the colors of 
    // the quadrants alternate between lighter and deeper grey (dddddd/eeeeee). 
    c->setPlotArea(50, 40, 400, 400, -1, -1, -1, 0xc0c0c0, 0xc0c0c0
        )->set4QBgColor(0xdddddd, 0xeeeeee, 0xdddddd, 0xeeeeee, 0x000000);

    // Enable clipping mode to clip the part of the data that is outside the plot area.
    c->setClipping();

    // Set 4 quadrant mode, with both x and y axes symetrical around the origin
    c->setAxisAtOrigin(Chart::XYAxisAtOrigin, Chart::XAxisSymmetric + Chart::YAxisSymmetric);

    // Add a legend box at (450, 40) (top right corner of the chart) with vertical layout
    // and 8 pts Arial Bold font. Set the background color to semi-transparent grey.
    LegendBox *legendBox = c->addLegend(450, 40, true, "Arial Bold", 8);
    legendBox->setAlignment(Chart::TopRight);
    legendBox->setBackground(0x40dddddd);

    // Add a titles to axes
    c->xAxis()->setTitle("Alpha Index");
    c->yAxis()->setTitle("Beta Index");

    // Set axes width to 2 pixels
    c->xAxis()->setWidth(2);
    c->yAxis()->setWidth(2);

    // The default ChartDirector settings has a denser y-axis grid spacing and less-dense
    // x-axis grid spacing. In this demo, we want the tick spacing to be symmetrical.
    // We use around 50 pixels between major ticks and 25 pixels between minor ticks.
    c->xAxis()->setTickDensity(50, 25);
    c->yAxis()->setTickDensity(50, 25);

    //
    // In this example, we represent the data by scatter points. If you want to represent
    // the data by somethings else (lines, bars, areas, floating boxes, etc), just modify
    // the code below to use the layer type of your choice. 
    //

    // Add scatter layer, using 11 pixels red (ff33333) X shape symbols
    c->addScatterLayer(vectorToArray(dataX0), vectorToArray(dataY0), "Group A", 
        Chart::Cross2Shape(), 11, 0xff3333);

    // Add scatter layer, using 11 pixels green (33ff33) circle symbols
    c->addScatterLayer(vectorToArray(dataX1), vectorToArray(dataY1), "Group B", 
        Chart::CircleShape, 11,  0x33ff33);

    // Add scatter layer, using 11 pixels blue (3333ff) triangle symbols
    c->addScatterLayer(vectorToArray(dataX2), vectorToArray(dataY2), "Group C", 
        Chart::TriangleSymbol, 11, 0x3333ff);

    // In this example, we have not explicitly configured the full x and y range. In this case, 
    // the first time syncLinearAxisWithViewPort is called, ChartDirector will auto-scale the axis
    // and assume the resulting range is the full range. In subsequent calls, ChartDirector will 
    // set the axis range based on the view port and the full range.
    viewer->syncLinearAxisWithViewPort("x", c->xAxis());
    viewer->syncLinearAxisWithViewPort("y", c->yAxis());
        
    // We need to update the track line too. If the mouse is moving on the chart (eg. if 
    // the user drags the mouse on the chart to scroll it), the track line will be updated
    // in the MouseMovePlotArea event. Otherwise, we need to update the track line here.
    if ((!viewer->isInMouseMoveEvent()) && viewer->isMouseOnPlotArea())
        crossHair(c, viewer->getPlotAreaMouseX(), viewer->getPlotAreaMouseY());

    // Set the chart image to the WinChartViewer
    delete viewer->getChart();
    viewer->setChart(c);
}

//
// Draw the full thumbnail chart and display it in the given CViewPortControl
//
void CXYZoomScrollDlg::drawFullChart(CViewPortControl *vpc, CChartViewer *viewer)
{
    // Create an XYChart object 110 x 110 pixels in size
    XYChart *c = new XYChart(110, 110);

    // Set the plotarea to cover the entire chart. Disable grid lines by setting their colors
    // to transparent. Set 4 quadrant coloring, where the colors of the quadrants alternate 
    // between lighter and deeper grey (dddddd/eeeeee). 
    c->setPlotArea(0, 0, c->getWidth() - 1, c->getHeight() - 1, -1, -1, -1, Chart::Transparent, 
        Chart::Transparent)->set4QBgColor(0xdddddd, 0xeeeeee, 0xdddddd, 0xeeeeee, 0x000000);

    // Set 4 quadrant mode, with both x and y axes symetrical around the origin
    c->setAxisAtOrigin(Chart::XYAxisAtOrigin, Chart::XAxisSymmetric + Chart::YAxisSymmetric);

    // The x and y axis scales reflect the full range of the view port
    c->xAxis()->setLinearScale(viewer->getValueAtViewPort("x", 0), viewer->getValueAtViewPort(
        "x", 1), Chart::NoValue);
    c->yAxis()->setLinearScale(viewer->getValueAtViewPort("y", 0), viewer->getValueAtViewPort(
        "y", 1), Chart::NoValue);

    // Add scatter layer, using 3 pixels red (ff33333) X shape symbols
    c->addScatterLayer(vectorToArray(dataX0), vectorToArray(dataY0), "", Chart::Cross2Shape(),
        3, 0xff3333, 0xff3333);

    // Add scatter layer, using 3 pixels green (33ff33) circle symbols
    c->addScatterLayer(vectorToArray(dataX1), vectorToArray(dataY1), "", Chart::CircleShape,
        3, 0x33ff33, 0x33ff33);

    // Add scatter layer, using 3 pixels blue (3333ff) triangle symbols
    c->addScatterLayer(vectorToArray(dataX2), vectorToArray(dataY2), "", Chart::TriangleSymbol,
        3, 0x3333ff, 0x3333ff);

    // Set the chart image to the WinChartViewer
    vpc->setChart(c);
}

//
// Draw cross hair cursor with axis labels
//
void CXYZoomScrollDlg::crossHair(XYChart *c, int mouseX, int mouseY)
{
    // Clear the current dynamic layer and get the DrawArea object to draw on it.
    DrawArea *d = c->initDynamicLayer();

    // The plot area object
    PlotArea *plotArea = c->getPlotArea();

    // Draw a vertical line and a horizontal line as the cross hair
    d->vline(plotArea->getTopY(), plotArea->getBottomY(), mouseX, d->dashLineColor(0x000000, 0x0101));
    d->hline(plotArea->getLeftX(), plotArea->getRightX(), mouseY, d->dashLineColor(0x000000, 0x0101));

    // Draw y-axis label
    std::ostringstream ylabel;
    ylabel << "<*block,bgColor=FFFFDD,margin=3,edgeColor=000000*>" << c->formatValue(c->getYValue(
        mouseY, c->yAxis()), "{value|P4}") << "<*/*>";
    TTFText *t = d->text(ylabel.str().c_str(), "Arial Bold", 8);
    t->draw(plotArea->getLeftX() - 5, mouseY, 0x000000, Chart::Right);
    t->destroy();

    // Draw x-axis label
    std::ostringstream xlabel;
    xlabel << "<*block,bgColor=FFFFDD,margin=3,edgeColor=000000*>" << c->formatValue(c->getXValue(
        mouseX), "{value|P4}") << "<*/*>";
    t = d->text(xlabel.str().c_str(), "Arial Bold", 8);
    t->draw(mouseX, plotArea->getBottomY() + 5, 0x000000, Chart::Top);
    t->destroy();
}

//
// Update the image map
//
void CXYZoomScrollDlg::updateImageMap(CChartViewer *viewer)
{
    if (0 == viewer->getImageMapHandler())
    {
        // no existing image map - creates a new one
        viewer->setImageMap(viewer->getChart()->getHTMLImageMap("clickable", "",
                "title='[{dataSetName}] Alpha = {x}, Beta = {value}'"));
    }
}

//
// Update other controls that may be affected by the viewport.
//
void CXYZoomScrollDlg::updateControls(CChartViewer *viewer)
{
    //
    // Update the Zoom slider to reflect the current zoom level of the view port
    //
    double smallerSide = viewer->getViewPortWidth() > viewer->getViewPortHeight() 
        ? viewer->getViewPortHeight() : viewer->getViewPortWidth();
    m_ZoomBar.SetPos((int)(smallerSide * m_ZoomBar.GetRangeMax() + 0.5));
}

/////////////////////////////////////////////////////////////////////////////
// General utilities

//
// Get the default background color
//
int CXYZoomScrollDlg::getDefaultBgColor()
{
    LOGBRUSH LogBrush; 
    HBRUSH hBrush = (HBRUSH)SendMessage(WM_CTLCOLORDLG, (WPARAM)CClientDC(this).m_hDC, (LPARAM)m_hWnd); 
    ::GetObject(hBrush, (int)sizeof(LOGBRUSH), &LogBrush); 
    int ret = LogBrush.lbColor;
    return ((ret & 0xff) << 16) | (ret & 0xff00) | ((ret & 0xff0000) >> 16);
}

//
// Load an icon resource into a button
//
void CXYZoomScrollDlg::loadButtonIcon(int buttonId, int iconId, int width, int height)
{
    // Resize the icon to match the screen DPI for high DPI support
    HDC screen = ::GetDC(0);
    double scaleFactor = GetDeviceCaps(screen, LOGPIXELSX) / 96.0;
    ::ReleaseDC(0, screen);
    width = (int)(width * scaleFactor + 0.5);
    height = (int)(height * scaleFactor + 0.5);

    GetDlgItem(buttonId)->SendMessage(BM_SETIMAGE, IMAGE_ICON, (LPARAM)::LoadImage(
        AfxGetResourceHandle(), MAKEINTRESOURCE(iconId), IMAGE_ICON, width, height, LR_DEFAULTCOLOR));
}

//
// Convert std::vector to a DoubleArray
//
DoubleArray CXYZoomScrollDlg::vectorToArray(std::vector<double> &v)
{
    return (v.size() == 0) ? DoubleArray() : DoubleArray(&(v[0]), (int)v.size());
}
