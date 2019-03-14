#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QString>
#include <QSizePolicy>
#include <QIntValidator>
#include <QListWidget>

#include <string>

#include "Model.h"
#include "Cell.h"

#include "SimulationCanvas.h"

class MainGUI : public QWidget
{
    Q_OBJECT
public:
    MainGUI(QWidget *parent = 0);
private:
    void initialRadioButton();
    void initialArrivalRateArea();
    void initialSimulationTimeArea();
    void initialSystemArea(); // for start save area
    void initialMainLayout();
    void connectSignals();
    QLabel *labelArrivalRate;
    QLabel *labelSimulationTime;
    QLabel *labelUnitms;
    QLabel *labelUnitArrivalRate;
    QLabel *labelUnitSimulationTime;
    QPushButton *btnStart;
    QPushButton *btnSaveConfig;
    QPushButton *btnLoadConfig;
    QRadioButton *rBtnMacrogNB;
    QRadioButton *rBtnFemtogNB;
    QRadioButton *rBtnFR1;
    QRadioButton *rBtnFR2;
    QRadioButton *rBtn4Beams;
    QRadioButton *rBtn8Beams;
    QRadioButton *rBtn64Beams;
    //QRadioButton *rBtnFormat0;
    //QRadioButton *rBtnFormat1;
    //QRadioButton *rBtnFormat2;
    //QRadioButton *rBtnFormat3;
    //QRadioButton *rBtnFormatA1;
    //QRadioButton *rBtnFormatA2;
    //QRadioButton *rBtnFormatA3;
    //QRadioButton *rBtnFormatB1;
    //QRadioButton *rBtnFormatB2;
    //QRadioButton *rBtnFormatB3;
    //QRadioButton *rBtnFormatB4;
    //QRadioButton *rBtnFormatC0;
    //QRadioButton *rBtnFormatC2;
    
    QListWidget *listPrachConfig;
    QGroupBox *groupgNBType;
    QGroupBox *groupFR;
    QGroupBox *groupBeams;
    //QGroupBox *groupPreambleFormat;
    QLineEdit *lEditArrivalRate;
    QLineEdit *lEditSimulationTime;
    QGridLayout *layoutSetting;
    QGridLayout *layoutMain;
    QHBoxLayout *layoutgNBType;
    QHBoxLayout *layoutFR;
    QHBoxLayout *layoutBeams;
    //QHBoxLayout *layoutPreambleFormat;
    QHBoxLayout *layoutArrivalRate;
    QHBoxLayout *layoutSimulationTime;
    QHBoxLayout *layoutSystem; // for button start, save...
    //QVBoxLayout *layoutPreambleFormatLeft;
    //QVBoxLayout *layoutPreambleFormatRight;
    QWidget *widgetSetting;
    SimulationCanvas *canvas; //fixed this
    QSizePolicy sp;

    Model *model;

    std::string sProjectName = "project";
    std::string sgNBType = "gNB Type";
    std::string sNumberOfBeams = "Number of SSB ";
    std::string sArrivalRate = "UE Arrival Rate: ";
    std::string sFR = "FR";
    //std::string sPreambleFormat = "Preamble Format";
    std::string sSimulationTime = "Simulation Time: ";
    std::string sMarcogNB = "Marco gNB";
    std::string sFemtogNB = "Femto gNB";
    std::string sFR1 = "FR1";
    std::string sFR2 = "FR2";
    std::string sBeam4 = "4";
    std::string sBeam8 = "8";
    std::string sBeam64 = "64";
    //std::string sFormat0 = "Format 0";
    //std::string sFormat1 = "Format 1";
    //std::string sFormat2 = "Format 2";
    //std::string sFormat3 = "Format 3";
    //std::string sFormatA1 = "Format A1";
    //std::string sFormatA2 = "Format A2";
    //std::string sFormatA3 = "Format A3";
    //std::string sFormatB1 = "Format B1";
    //std::string sFormatB2 = "Format B2";
    //std::string sFormatB3 = "Format B3";
    //std::string sFormatB4 = "Format B4";
    //std::string sFormatC0 = "Format C0";
    //std::string sFormatC2 = "Format C2";
    //std::string sBtnSet = "Set";
    std::string sPrachConfig16 = "Index:16; Format0; FR1; x:1,y:0; RA subframe: 1; time domain RAO:1";
    std::string sPrachConfig27 = "Index:27; Format0; FR1; x:1,y:0; RA subframe:0..9; time domain RAO: 1";
    std::string sPrachConfig101 = "Index:101; FormatA1; FR1; x:1,y:0; RA subframe: 1; time domain RAO: 12";
    std::string sPrachConfig106 = "Index:106; FormatA1; FR1; x:1,y:0; RA subframe:0..9; time domaint RAO: 12";
    std::string sUnitms = "ms";
    std::string sUnitArrivalRate = "per ms";
    std::string sUnitSimulationTime = "second(s)";
    std::string sBtnStart = "Start";
    std::string sBtnSaveConfig = "Save Config";
    std::string sBtnLoadConfig = "Load Config";
    int widthWindow = 515;
    int heightWindow = 700;
    unsigned int FR1 = 0;
    unsigned int FR2 = 1;
    unsigned int beams4 = 4;
    unsigned int beams8 = 8;
    unsigned int beams64 = 64;
    unsigned int iFR1 = 0;
    unsigned int iFR2 = 1;
private slots:
    void handleButtonStartClick();
    void handle4BeamsRadBtnClick();
    void handle8BeamsRadBtnClick();
    void handle64BeamsRadBtnClick();
    void handleMacroRadBtnClick();
    void handleFemtoRadBtnClick();
    void handleFR1RadBtnClick();
    void handleFR2RadBtnClick();
    void handleListPrachIndexChange(int selectedRow);
};
#endif

