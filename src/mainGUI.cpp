#include "mainGUI.h"

// Constructor
// Initialize Model and UI
MainGUI::MainGUI(QWidget *parent):
    QWidget(parent){
    setWindowTitle(QString::fromStdString(sProjectName));
    resize(widthWindow, heightWindow);

    this->model = new Model();
   
    // canvas setting
    canvas = new SimulationCanvas(this, model);
    canvas->show();
    canvas->setStyleSheet("QWidget{background:white;}");
    canvas->setMinimumSize(widthWindow, heightWindow / 2);

    sp = canvas->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::MinimumExpanding);
    sp.setVerticalPolicy(QSizePolicy::Expanding);
    canvas->setSizePolicy(sp);

    initialRadioButton();
    initialSIBPeriodArea();
    initialArrivalRateArea();
    initialMainLayout();
}

// Initialize radio button 
void MainGUI::initialRadioButton(){
    // gNBType setting
    rBtnMarcogNB = new QRadioButton(QString::fromStdString(sMarcogNB), this);
    rBtnFemtogNB = new QRadioButton(QString::fromStdString(sFemtogNB), this);
    rBtnMarcogNB->setChecked(true);
    layoutgNBType = new QHBoxLayout;
    layoutgNBType->addWidget(rBtnMarcogNB);
    layoutgNBType->addWidget(rBtnFemtogNB);
    groupgNBType = new QGroupBox(QString::fromStdString(sgNBType), this);
    groupgNBType->setLayout(layoutgNBType);

    // FR setting
    rBtnFR1 = new QRadioButton(QString::fromStdString(sFR1), this);
    rBtnFR2 = new QRadioButton(QString::fromStdString(sFR2), this);
    rBtnFR1->setChecked(true);
    layoutFR = new QHBoxLayout;
    layoutFR->addWidget(rBtnFR1);
    layoutFR->addWidget(rBtnFR2);
    groupFR = new QGroupBox(QString::fromStdString(sFR), this);
    groupFR->setLayout(layoutFR);

    // Number of SSB setting 
    rBtn4Beams = new QRadioButton(QString::fromStdString(sBeam4), this);
    rBtn8Beams = new QRadioButton(QString::fromStdString(sBeam8), this);
    rBtn64Beams = new QRadioButton(QString::fromStdString(sBeam64), this);
    rBtn4Beams->setChecked(true);
    layoutBeams = new QHBoxLayout;
    layoutBeams->addWidget(rBtn4Beams);
    layoutBeams->addWidget(rBtn8Beams);
    layoutBeams->addWidget(rBtn64Beams);
    groupBeams = new QGroupBox(QString::fromStdString(sNumberOfBeams), this);
    groupBeams->setLayout(layoutBeams);

    // Preamble format setting
    rBtnFormat0 = new QRadioButton(QString::fromStdString(sFormat0), this);
    rBtnFormat1 = new QRadioButton(QString::fromStdString(sFormat1), this);
    rBtnFormat2 = new QRadioButton(QString::fromStdString(sFormat2), this);
    rBtnFormat3 = new QRadioButton(QString::fromStdString(sFormat3), this);
    rBtnFormatA1 = new QRadioButton(QString::fromStdString(sFormatA1), this);
    rBtnFormatA2 = new QRadioButton(QString::fromStdString(sFormatA2), this);
    rBtnFormatA3 = new QRadioButton(QString::fromStdString(sFormatA3), this);
    rBtnFormatB1 = new QRadioButton(QString::fromStdString(sFormatB1), this);
    rBtnFormatB2 = new QRadioButton(QString::fromStdString(sFormatB2), this);
    rBtnFormatB3 = new QRadioButton(QString::fromStdString(sFormatB3), this);
    rBtnFormatB4 = new QRadioButton(QString::fromStdString(sFormatB4), this);
    rBtnFormatC0 = new QRadioButton(QString::fromStdString(sFormatC0), this);
    rBtnFormatC2 = new QRadioButton(QString::fromStdString(sFormatC2), this);
    rBtnFormat0->setChecked(true);
    layoutPreambleFormat = new QHBoxLayout;
    layoutPreambleFormatLeft = new QVBoxLayout;
    layoutPreambleFormatRight = new QVBoxLayout;
    layoutPreambleFormatLeft->addWidget(rBtnFormat0);
    layoutPreambleFormatLeft->addWidget(rBtnFormat1);
    layoutPreambleFormatLeft->addWidget(rBtnFormat2);
    layoutPreambleFormatLeft->addWidget(rBtnFormat3);
    layoutPreambleFormatLeft->addWidget(rBtnFormatA1);
    layoutPreambleFormatLeft->addWidget(rBtnFormatA2);
    layoutPreambleFormatLeft->addWidget(rBtnFormatA3);
    layoutPreambleFormatRight->addWidget(rBtnFormatB1);
    layoutPreambleFormatRight->addWidget(rBtnFormatB2);
    layoutPreambleFormatRight->addWidget(rBtnFormatB3);
    layoutPreambleFormatRight->addWidget(rBtnFormatB4);
    layoutPreambleFormatRight->addWidget(rBtnFormatC0);
    layoutPreambleFormatRight->addWidget(rBtnFormatC2);
    layoutPreambleFormat->addLayout(layoutPreambleFormatLeft);
    layoutPreambleFormat->addLayout(layoutPreambleFormatRight);
    groupPreambleFormat = new QGroupBox(QString::fromStdString(sPreambleFormat), this);
    groupPreambleFormat->setLayout(layoutPreambleFormat);
}

// Configuration SIB Period Area
void MainGUI::initialSIBPeriodArea(){
    // Label Setting
    labelSIBPeriod = new QLabel(this);
    labelUnitms = new QLabel(this);

    labelSIBPeriod->setText(QString::fromStdString(sSIBPeriod));
    labelUnitms->setText(QString::fromStdString(sUnitms));

    // LineEdit Setting
    lEditSIBPeriod = new QLineEdit(this);

    // PushButton Setting
    btnSIBPeriod = new QPushButton(this);
    btnSIBPeriod->setText(QString::fromStdString(sBtnSet));
    btnSIBPeriod->setMaximumSize(50, 50);
    sp = btnSIBPeriod->sizePolicy();
    sp.setVerticalPolicy(QSizePolicy::Preferred);
    sp.setHorizontalPolicy(QSizePolicy::Maximum);
    btnSIBPeriod->setSizePolicy(sp);

    // SIBPeriod area setting
    layoutSIBPeriod = new QHBoxLayout;
    layoutSIBPeriod->addWidget(labelSIBPeriod);
    layoutSIBPeriod->addWidget(lEditSIBPeriod);
    layoutSIBPeriod->addWidget(labelUnitms);
    layoutSIBPeriod->addWidget(btnSIBPeriod);
}

// configuration ArrivalRate Area
void MainGUI::initialArrivalRateArea(){
    // Label setting
    labelArrivalRate = new QLabel(this);
    labelUnitArrivalRate = new QLabel(this);

    labelArrivalRate->setText(QString::fromStdString(sArrivalRate));
    labelUnitArrivalRate->setText(QString::fromStdString(sUnitArrivalRate));

    // LineEdit setting
    lEditArrivalRate = new QLineEdit(this);

    // PushButton setting
    btnArrivalRate = new QPushButton(this);
    btnArrivalRate->setText(QString::fromStdString(sBtnSet));
    btnArrivalRate->setMaximumSize(50, 50);
    sp = btnArrivalRate->sizePolicy();
    sp.setVerticalPolicy(QSizePolicy::Preferred);
    sp.setHorizontalPolicy(QSizePolicy::Maximum);
    btnArrivalRate->setSizePolicy(sp);

    // Arrival rate area setting
    layoutArrivalRate = new QHBoxLayout;
    layoutArrivalRate->addWidget(labelArrivalRate);
    layoutArrivalRate->addWidget(lEditArrivalRate);
    layoutArrivalRate->addWidget(labelUnitArrivalRate);
    layoutArrivalRate->addWidget(btnArrivalRate);
}

// Configuration Main Layout
void MainGUI::initialMainLayout(){
    // Configuration area setting
    widgetSetting = new QWidget(this);
    widgetSetting->setMaximumSize(widthWindow, heightWindow / 2);
    
    sp = widgetSetting->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Maximum);
    sp.setVerticalPolicy(QSizePolicy::Fixed);
    widgetSetting->setSizePolicy(sp);

    layoutSetting = new QGridLayout(widgetSetting);
    layoutSetting->addWidget(groupFR, 1, 0);
    layoutSetting->addWidget(groupgNBType, 2, 0);
    layoutSetting->addWidget(groupBeams, 3, 0);
    layoutSetting->addWidget(groupPreambleFormat, 1, 1, 3, 1);
    layoutSetting->addLayout(layoutSIBPeriod, 4, 0);
    layoutSetting->addLayout(layoutArrivalRate, 4, 1);

    // Main Area Setting
    layoutMain = new QGridLayout(this);
    layoutMain->addWidget(canvas, 1, 0);
    layoutMain->addWidget(widgetSetting, 2, 0);
}
