#include "mainGUI.h"
#include "include_log.h"

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
    initialPrachConfig();
    initialArrivalRateArea();
    initialSimulationTimeArea();
    initialDrawingButtonArea();
    initialNumberofPreambeArea();
    initialPreambleSCSArea();
    initialCellBandwithArea();
    initialArrivalPattern();
    initialTotalUEArea();
    initialSSBSCSArea();
    initialSystemArea();
    initialMainLayout();

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

void MainGUI::initialPrachConfig(){
    listPrachConfig = new QListWidget(this);
    int count = 0;
    listPrachConfig->insertItem(count++, QString::fromStdString(sPrachConfig16));
    listPrachConfig->insertItem(count++, QString::fromStdString(sPrachConfig19));
    listPrachConfig->insertItem(count++, QString::fromStdString(sPrachConfig22));
    listPrachConfig->insertItem(count++, QString::fromStdString(sPrachConfig25));
    listPrachConfig->insertItem(count++, QString::fromStdString(sPrachConfig27));
    listPrachConfig->insertItem(count++, QString::fromStdString(sPrachConfig101));
    listPrachConfig->insertItem(count++, QString::fromStdString(sPrachConfig106));
    listPrachConfig->setCurrentRow(0);
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

// configurate draw cell erase cell area
void MainGUI::initialDrawingButtonArea(){
    btnClear = new QPushButton(this);
    btnClear->setText(QString::fromStdString(sBtnClear));

    btnDrawCell = new QPushButton(this);
    btnDrawCell->setText(QString::fromStdString(sBtnDrawCell));
    btnDrawCell->setEnabled(false);

    layoutDrawing = new QHBoxLayout;
    layoutDrawing->addWidget(btnDrawCell);
    layoutDrawing->addWidget(btnClear);

}

// initialize number of preamble area
void MainGUI::initialNumberofPreambeArea(){
    labelNumberofRAPreamble = new QLabel(this);
    labelNumberofRAPreamble->setText(QString::fromStdString(sNumberofPreamble));
    lEditNumberofPreamble = new QLineEdit(this);
    lEditNumberofPreamble->setValidator(new QIntValidator(lEditNumberofPreamble));
    //lEditSimulationTime->setMaximumSize(50, 50);
    lEditNumberofPreamble->setAlignment(Qt::AlignRight);
    lEditNumberofPreamble->setText(QString::number(64));

    layoutNumberofPreamble = new QHBoxLayout;
    layoutNumberofPreamble->addWidget(labelNumberofRAPreamble);
    layoutNumberofPreamble->addWidget(lEditNumberofPreamble);
}

// initialize area for preamble SCS
void MainGUI::initialPreambleSCSArea(){
    labelPreambleSCS = new QLabel(this);
    labelPreambleSCS->setText(QString::fromStdString(sPreambleSCS));

    comboPreambleSCS = new QComboBox(this);
    comboPreambleSCS->setEditable(false);
    comboPreambleSCS->insertItem(0, QString::number(1.25));
    comboPreambleSCS->insertItem(1, QString::number(5));
    comboPreambleSCS->insertItem(2, QString::number(15));
    comboPreambleSCS->insertItem(3, QString::number(30));
    //sp = comboPreambleSCS->sizePolicy();
    //sp.setVerticalPolicy(QSizePolicy::Minimum);
    //comboPreambleSCS->setSizePolicy(sp);

    layoutPreambleSCS = new QHBoxLayout;
    //layoutPreambleSCS->setAlignment(Qt::AlignTop);
    layoutPreambleSCS->addWidget(labelPreambleSCS);
    layoutPreambleSCS->addWidget(comboPreambleSCS);
}

// initialize area for cell BW configuration
void MainGUI::initialCellBandwithArea(){
    labelCellBW = new QLabel(this);
    labelCellBW->setText(QString::fromStdString(sCellBW));
    labelCellBW->setMinimumSize(110, 30);
    labelCellBW->setMaximumSize(110, 30);
    sp = labelCellBW->sizePolicy();
    sp.setVerticalPolicy(QSizePolicy::Maximum);
    sp.setHorizontalPolicy(QSizePolicy::Minimum);
    labelCellBW->setSizePolicy(sp);

    labelBWUnit = new QLabel(this);
    labelBWUnit->setText(QString::fromStdString(sBWUnit));
    labelBWUnit->setMaximumSize(30, 50);
    sp = labelBWUnit->sizePolicy();
    sp.setVerticalPolicy(QSizePolicy::Preferred);
    sp.setHorizontalPolicy(QSizePolicy::Maximum);
    labelBWUnit->setSizePolicy(sp);

    comboCellBW = new QComboBox(this);
    comboCellBW->setEditable(false);
    comboCellBW->insertItem(0, QString::number(5));
    comboCellBW->insertItem(1, QString::number(10));
    comboCellBW->insertItem(2, QString::number(25));
    comboCellBW->insertItem(3, QString::number(50));
    comboCellBW->insertItem(4, QString::number(100));
    comboCellBW->insertItem(5, QString::number(200));
    comboCellBW->insertItem(6, QString::number(400));

    layoutCellBW = new QHBoxLayout;
    layoutCellBW->addWidget(labelCellBW);
    layoutCellBW->addWidget(comboCellBW);
    layoutCellBW->addWidget(labelBWUnit);
    
    labelCellBW->setVisible(false);
    labelBWUnit->setVisible(false);
    comboCellBW->setVisible(false);
}

// initialize area for arrival pattern
void MainGUI::initialArrivalPattern(){
    labelArrivalPattern = new QLabel(this);
    labelArrivalPattern->setText(QString::fromStdString(sArrivalPattern));

    comboArrivalPattern = new QComboBox(this);
    comboArrivalPattern->insertItem(0, "Uniform");
    comboArrivalPattern->insertItem(1, "Beta");
    comboArrivalPattern->setMinimumSize(130, 20);
    sp = comboArrivalPattern->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Minimum);
    comboArrivalPattern->setSizePolicy(sp);

    layoutArrivalPattern = new QHBoxLayout;
    layoutArrivalPattern->addWidget(labelArrivalPattern);
    layoutArrivalPattern->addWidget(comboArrivalPattern);
}

// handle total number of ue area
void MainGUI::initialTotalUEArea(){
    labelTotalUE = new QLabel(this);
    labelTotalUE->setText(QString::fromStdString(sTotalUE));

    lEditTotalUE = new QLineEdit(this);
    lEditTotalUE->setValidator(new QIntValidator(lEditTotalUE));
    lEditTotalUE->setAlignment(Qt::AlignRight);
    lEditTotalUE->setText(QString::number(10000));

    labelTotalUE->setVisible(false);
    lEditTotalUE->setVisible(false);

    layoutTotalUE = new QHBoxLayout;
    layoutTotalUE->addWidget(labelTotalUE);
    layoutTotalUE->addWidget(lEditTotalUE);

    //layoutTotalUE->setVisible(false);
}

// handle ssb scs area
void MainGUI::initialSSBSCSArea(){
    labelSSBSCS = new QLabel(this);
    labelSSBSCS->setText(QString::fromStdString(sSSBSCS));

    labelUnitSCS = new QLabel(this);
    labelUnitSCS->setText(QString::fromStdString(sSCSUnit));

    comboSSBSCS = new QComboBox(this);
    comboSSBSCS->insertItem(0, "15");
    comboSSBSCS->insertItem(1, "30");
    comboSSBSCS->setMinimumSize(60, 20);
    sp = comboArrivalPattern->sizePolicy();
    sp.setHorizontalPolicy(QSizePolicy::Minimum);
    comboArrivalPattern->setSizePolicy(sp);

    layoutSSBSCS = new QHBoxLayout;
    layoutSSBSCS->addWidget(labelSSBSCS);
    layoutSSBSCS->addWidget(comboSSBSCS);
    layoutSSBSCS->addWidget(labelUnitSCS);
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
    layoutSetting->addLayout(layoutSSBSCS, 4, 0);
    layoutSetting->addLayout(layoutCellBW, 5, 0);
    layoutSetting->addLayout(layoutArrivalPattern, 5, 0);
    layoutSetting->addLayout(layoutArrivalRate, 6, 0);
    layoutSetting->addLayout(layoutTotalUE, 6, 0);
    layoutSetting->addLayout(layoutDrawing, 7, 0);
    layoutSetting->addWidget(listPrachConfig, 1, 1, 3, 1);
    layoutSetting->addLayout(layoutPreambleSCS, 4, 1);
    layoutSetting->addLayout(layoutNumberofPreamble, 5, 1);
    layoutSetting->addLayout(layoutSimulationTime, 6, 1);
    layoutSetting->addLayout(layoutSystem, 7, 1);

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

    connect(btnDrawCell, SIGNAL(clicked()), this, SLOT(handleButtonDrawCellClick()));
    connect(btnClear, SIGNAL(clicked()), this, SLOT(handleButtonClearClick()));
    connect(lEditNumberofPreamble, SIGNAL(textChanged(const QString&)), this, SLOT(handleNumberofPreambleChanged(const QString&)));
    connect(comboPreambleSCS, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(handlePreambleSCSChanged(const QString&)));
    connect(comboCellBW, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(handleCellBWChanged(const QString&)));
    connect(comboArrivalPattern, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(handleArrivalPatternChanged(const QString&)));
    connect(comboSSBSCS, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(handleSSBSCSChanged(const QString&)));
}

// handle start button click event
void MainGUI::handleButtonStartClick(){
    SPDLOG_TRACE("start button click");
    model->setSimulationTime(lEditSimulationTime->text().toInt());
    if(model->getArrivalMode() == ArrivalMode::Uniform)
        model->setArrivalRate(lEditArrivalRate->text().toInt());
    else
        model->setTotalUE(lEditTotalUE->text().toInt());
    model->startSimulation();
}

// handle radio button 4 beams click event
void MainGUI::handle4BeamsRadBtnClick(){
    SPDLOG_TRACE("4 beams\n");
    model->setnBeams(beams4);
}

// handle radio button 8 beams click event
void MainGUI::handle8BeamsRadBtnClick(){
    SPDLOG_TRACE("8 beams\n");
    model->setnBeams(beams8);
}

// handle radio button 64 beams click event
void MainGUI::handle64BeamsRadBtnClick(){
    SPDLOG_TRACE("64 beams\n");
    model->setnBeams(beams64);
}

// handle radio button marco click event
void MainGUI::handleMacroRadBtnClick(){
    SPDLOG_TRACE("Macro gNB selected\n");
    model->setCellType(celltype::Macro);
}

// handle radio button femto click event
void MainGUI::handleFemtoRadBtnClick(){
    SPDLOG_TRACE("Femto gNB selected\n");
    model->setCellType(celltype::Femto);
}

// handle FR1 radio button click event
void MainGUI::handleFR1RadBtnClick(){
    SPDLOG_TRACE("FR1 selected\n");
    if(model->getFR() == 1){
        comboPreambleSCS->removeItem(1);
        comboPreambleSCS->removeItem(0);
        comboPreambleSCS->insertItem(0, QString::number(1.25));
        comboPreambleSCS->insertItem(1, QString::number(5));
        comboPreambleSCS->insertItem(2, QString::number(15));
        comboPreambleSCS->insertItem(3, QString::number(30));
        comboPreambleSCS->setCurrentIndex(0);

        comboSSBSCS->removeItem(1);
        comboSSBSCS->removeItem(0);
        comboSSBSCS->insertItem(0, QString::number(15));
        comboSSBSCS->insertItem(1, QString::number(30));
        comboSSBSCS->setCurrentIndex(0);
    }
    model->setFR(iFR1);
}

// handle FR2 radio button click event
void MainGUI::handleFR2RadBtnClick(){
    SPDLOG_TRACE("FR2 selected\n");
    if(model->getFR() == 0){
        comboPreambleSCS->removeItem(3);
        comboPreambleSCS->removeItem(2);
        comboPreambleSCS->removeItem(1);
        comboPreambleSCS->removeItem(0);
        comboPreambleSCS->insertItem(0, QString::number(60));
        comboPreambleSCS->insertItem(1, QString::number(120));
        comboPreambleSCS->setCurrentIndex(0);

        comboSSBSCS->removeItem(1);
        comboSSBSCS->removeItem(0);
        comboSSBSCS->insertItem(0, QString::number(120));
        comboSSBSCS->insertItem(1, QString::number(240));
        comboSSBSCS->setCurrentIndex(0);
    }
    model->setFR(iFR2);
}

// handle prach configuration index list widget select row change event
void MainGUI::handleListPrachIndexChange(int selectedRow){
    model->setPrachConfigIndex(listPrachConfig->item(selectedRow)->text().toStdString());
}

// handle button draw cell click
void MainGUI::handleButtonDrawCellClick(){
    model->setDrawMode(DrawMode::DrawCell);
    btnClear->setEnabled(true);
    btnDrawCell->setEnabled(false);
}

// handle button clear click
void MainGUI::handleButtonClearClick(){
    model->setDrawMode(DrawMode::EraseCell);
    btnDrawCell->setEnabled(true);
    btnClear->setEnabled(false);
}

// handle lineedit number of preamble changed
void MainGUI::handleNumberofPreambleChanged(const QString& text){
    model->setNPreambles(text.toInt());
}

// handle preamble scs changed
void MainGUI::handlePreambleSCSChanged(const QString& text){
    model->setPreambleSCS(text.toDouble());
}

// handle cell BW changed
void MainGUI::handleCellBWChanged(const QString& text){
    model->setCellBW(text.toInt());
}

// handle arrival pattern changed
void MainGUI::handleArrivalPatternChanged(const QString& text){
    //SPDLOG_INFO("{0}", text.fromStdString());
    if(!text.toStdString().compare("Uniform")){
        model->setArrivalMode(ArrivalMode::Uniform);
        labelArrivalRate->setVisible(true);
        labelUnitArrivalRate->setVisible(true);
        lEditArrivalRate->setVisible(true);
        labelTotalUE->setVisible(false);
        lEditTotalUE->setVisible(false);
    }
    else{
        model->setArrivalMode(ArrivalMode::Beta);
        labelArrivalRate->setVisible(false);
        labelUnitArrivalRate->setVisible(false);
        lEditArrivalRate->setVisible(false);
        labelTotalUE->setVisible(true);
        lEditTotalUE->setVisible(true);
    }
}

// handle ssb scs changed
void MainGUI::handleSSBSCSChanged(const QString& text){
    model->setSSBSCS(text.toInt());
}

// destructor
MainGUI::~MainGUI(){
    delete model;
    delete layoutMain;
    delete layoutArrivalRate;
    delete layoutSimulationTime;
    delete layoutSSBSCS;
    delete layoutTotalUE;
    delete layoutCellBW;
    delete layoutArrivalPattern;
    delete layoutPreambleSCS;
    delete layoutNumberofPreamble;
    delete layoutDrawing;
    delete layoutSystem;
    delete layoutSetting;
    delete layoutgNBType;
    delete layoutFR;
    delete layoutBeams;
    delete labelArrivalRate;
    delete labelSimulationTime;
    delete labelUnitArrivalRate;
    delete labelUnitSimulationTime;
    delete labelNumberofRAPreamble;
    delete labelPreambleSCS;
    delete labelCellBW;
    delete labelBWUnit;
    delete labelArrivalPattern;
    delete labelTotalUE;
    delete labelSSBSCS;
    delete labelUnitSCS;
    delete comboPreambleSCS;
    delete comboCellBW;
    delete comboArrivalPattern;
    delete comboSSBSCS;
    delete btnStart;
    delete btnSaveConfig;
    delete btnLoadConfig;
    delete btnClear;
    delete btnDrawCell;
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
    delete lEditNumberofPreamble;
    delete lEditTotalUE;
    delete widgetSetting;
    delete canvas;
}
