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
    initialArrivalRateArea();
    initialSimulationTimeArea();
    initialSystemArea();
    initialMainLayout();

    listPrachConfig = new QListWidget(this);
    layoutSetting->addWidget(listPrachConfig, 1, 1, 3, 1);
    listPrachConfig->insertItem(0, QString::fromStdString(sPrachConfig16));
    listPrachConfig->insertItem(1, QString::fromStdString(sPrachConfig27));
    listPrachConfig->insertItem(2, QString::fromStdString(sPrachConfig101));
    listPrachConfig->insertItem(3, QString::fromStdString(sPrachConfig106));
    listPrachConfig->setCurrentRow(0);

    connectSignals();
}

// Initialize radio button 
void MainGUI::initialRadioButton(){
    // gNBType setting
    rBtnMacrogNB = new QRadioButton(QString::fromStdString(sMarcogNB), this);
    rBtnFemtogNB = new QRadioButton(QString::fromStdString(sFemtogNB), this);
    rBtnMacrogNB->setChecked(true);
    layoutgNBType = new QHBoxLayout;
    layoutgNBType->addWidget(rBtnMacrogNB);
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
    //lEditArrivalRate->setMaximumSize(50, 50);
    lEditArrivalRate->setValidator(new QIntValidator(lEditArrivalRate));
    lEditArrivalRate->setText(QString::number(10));
    lEditArrivalRate->setAlignment(Qt::AlignRight);
    //sp = lEditArrivalRate->sizePolicy();
    //sp.setVerticalPolicy(QSizePolicy::Preferred);
    //sp.setHorizontalPolicy(QSizePolicy::Maximum);
    //lEditArrivalRate->setSizePolicy(sp);

    // Arrival rate area setting
    layoutArrivalRate = new QHBoxLayout;
    layoutArrivalRate->addWidget(labelArrivalRate);
    layoutArrivalRate->addWidget(lEditArrivalRate);
    layoutArrivalRate->addWidget(labelUnitArrivalRate);
}

// configuration simulation time Area
void MainGUI::initialSimulationTimeArea(){
    // Label setting
    labelSimulationTime = new QLabel(this);
    labelUnitSimulationTime = new QLabel(this);

    labelSimulationTime->setText(QString::fromStdString(sSimulationTime));
    //labelSimulationTime->setMinimumSize(200, 20);
    labelUnitSimulationTime->setText(QString::fromStdString(sUnitSimulationTime));

    // LineEdit setting
    lEditSimulationTime = new QLineEdit(this);
    lEditSimulationTime->setValidator(new QIntValidator(lEditSimulationTime));
    //lEditSimulationTime->setMaximumSize(50, 50);
    lEditSimulationTime->setAlignment(Qt::AlignRight);
    //sp = lEditSimulationTime->sizePolicy();
    //sp.setVerticalPolicy(QSizePolicy::Preferred);
    //sp.setHorizontalPolicy(QSizePolicy::Maximum);
    //lEditSimulationTime->setSizePolicy(sp);

    // Simulation time area setting
    layoutSimulationTime = new QHBoxLayout;
    layoutSimulationTime->addWidget(labelSimulationTime);
    layoutSimulationTime->addWidget(lEditSimulationTime);
    layoutSimulationTime->addWidget(labelUnitSimulationTime);
}

// initial area for button start or load, save config area
void MainGUI::initialSystemArea(){
    // initialize load config button
    btnLoadConfig = new QPushButton(this);
    btnLoadConfig->setText(QString::fromStdString(sBtnLoadConfig));

    // initialize save config button
    btnSaveConfig = new QPushButton(this);
    btnSaveConfig->setText(QString::fromStdString(sBtnSaveConfig));
    
    // initialize start button
    btnStart = new QPushButton(this);
    btnStart->setText(QString::fromStdString(sBtnStart));
    btnStart->setMaximumSize(50, 50);
    sp = btnStart->sizePolicy();
    sp.setVerticalPolicy(QSizePolicy::Preferred);
    sp.setHorizontalPolicy(QSizePolicy::Maximum);
    btnStart->setSizePolicy(sp);

    // initialize system layout for button start, save, load area
    layoutSystem = new QHBoxLayout;
    layoutSystem->addWidget(btnLoadConfig);
    layoutSystem->addWidget(btnSaveConfig);
    layoutSystem->addWidget(btnStart);
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
    //layoutSetting->addWidget(groupPreambleFormat, 1, 1, 3, 1);
    layoutSetting->addLayout(layoutSimulationTime, 4, 0);
    layoutSetting->addLayout(layoutArrivalRate, 4, 1);
    layoutSetting->addLayout(layoutSystem, 5, 1);

    // Main Area Setting
    layoutMain = new QGridLayout(this);
    layoutMain->addWidget(canvas, 1, 0);
    layoutMain->addWidget(widgetSetting, 2, 0);
}

// connect all singals
void MainGUI::connectSignals(){
    connect(btnStart, SIGNAL(clicked()), this, SLOT(handleButtonStartClick()));
    connect(rBtn4Beams, SIGNAL(clicked()), this, SLOT(handle4BeamsRadBtnClick()));
    connect(rBtn8Beams, SIGNAL(clicked()), this, SLOT(handle8BeamsRadBtnClick()));
    connect(rBtn64Beams, SIGNAL(clicked()), this, SLOT(handle64BeamsRadBtnClick()));
    connect(rBtnMacrogNB, SIGNAL(clicked()), this, SLOT(handleMacroRadBtnClick()));
    connect(rBtnFemtogNB, SIGNAL(clicked()), this, SLOT(handleFemtoRadBtnClick()));
    connect(rBtnFR1, SIGNAL(clicked()), this, SLOT(handleFR1RadBtnClick()));
    connect(rBtnFR2, SIGNAL(clicked()), this, SLOT(handleFR2RadBtnClick()));
    connect(listPrachConfig, SIGNAL(currentRowChanged(int)), this, SLOT(handleListPrachIndexChange(int)));
}

// handle start button click event
void MainGUI::handleButtonStartClick(){
    printf("start button click\n");
    model->setSimulationTime(lEditSimulationTime->text().toInt());
    model->setArrivalRate(lEditArrivalRate->text().toInt());
    model->startSimulation();
}

// handle radio button 4 beams click event
void MainGUI::handle4BeamsRadBtnClick(){
    printf("4 beams\n");
    model->setnBeams(beams4);
}

// handle radio button 8 beams click event
void MainGUI::handle8BeamsRadBtnClick(){
    printf("8 beams\n");
    model->setnBeams(beams8);
}

// handle radio button 64 beams click event
void MainGUI::handle64BeamsRadBtnClick(){
    printf("64 beams\n");
    model->setnBeams(beams64);
}

// handle radio button marco click event
void MainGUI::handleMacroRadBtnClick(){
    printf("Macro gNB selected\n");
    model->setCellType(celltype::Macro);
}

// handle radio button femto click event
void MainGUI::handleFemtoRadBtnClick(){
    printf("Femto gNB selected\n");
    model->setCellType(celltype::Femto);
}

// handle FR1 radio button click event
void MainGUI::handleFR1RadBtnClick(){
    printf("FR1 selected\n");
    model->setFR(iFR1);
}

// handle FR2 radio button click event
void MainGUI::handleFR2RadBtnClick(){
    printf("FR2 selected\n");
    model->setFR(iFR2);
}

// handle prach configuration index list widget select row change event
void MainGUI::handleListPrachIndexChange(int selectedRow){
    model->setPrachConfigIndex(listPrachConfig->item(selectedRow)->text().toStdString());
}

// destructor
MainGUI::~MainGUI(){
    delete model;
    delete layoutMain;
    delete layoutArrivalRate;
    delete layoutSimulationTime;
    delete layoutSystem;
    delete layoutSetting;
    delete layoutgNBType;
    delete layoutFR;
    delete layoutBeams;
    delete labelArrivalRate;
    delete labelSimulationTime;
    delete labelUnitArrivalRate;
    delete labelUnitSimulationTime;
    delete btnStart;
    delete btnSaveConfig;
    delete btnLoadConfig;
    delete rBtnMacrogNB;
    delete rBtnFemtogNB;
    delete rBtnFR1;
    delete rBtnFR2;
    delete rBtn4Beams;
    delete rBtn8Beams;
    delete rBtn64Beams;
    delete listPrachConfig;
    delete groupgNBType;
    delete groupFR;
    delete groupBeams;
    delete lEditArrivalRate;
    delete lEditSimulationTime;
    delete widgetSetting;
    delete canvas;
}
