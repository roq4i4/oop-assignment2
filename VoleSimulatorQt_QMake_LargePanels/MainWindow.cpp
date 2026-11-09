#include "MainWindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>
#include <QTabWidget>
#include <QFrame>
#include <QSplitter>
#include <QFont>
#include <QRegularExpressionValidator>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("VOLE Simulator | Computer Architecture");
    resize(1450, 920);
    setMinimumSize(1050, 700);

    QWidget *central = new QWidget;
    setCentralWidget(central);
    QVBoxLayout *main = new QVBoxLayout(central);
    main->setContentsMargins(18, 14, 18, 16);
    main->setSpacing(10);

    // Header
    QHBoxLayout *header = new QHBoxLayout;
    QVBoxLayout *heading = new QVBoxLayout;
    QLabel *title = new QLabel("VOLE  <span style='color:#38bdf8'>SIMULATOR</span>");
    title->setObjectName("title");
    QLabel *subtitle = new QLabel("Load, execute and monitor your machine program");
    subtitle->setObjectName("subtitle");
    heading->addWidget(title);
    heading->addWidget(subtitle);
    header->addLayout(heading);
    header->addStretch();
    pcLabel = new QLabel("PC: 00"); pcLabel->setObjectName("statusValue");
    irLabel = new QLabel("IR: ----"); irLabel->setObjectName("statusValue");
    header->addWidget(pcLabel);
    header->addWidget(irLabel);
    main->addLayout(header);

    // Program loading row
    QGroupBox *loadBox = new QGroupBox("PROGRAM SETUP");
    QHBoxLayout *loadLayout = new QHBoxLayout(loadBox);
    filePath = new QLineEdit;
    filePath->setPlaceholderText("Choose a program file (.txt)");
    QPushButton *browse = new QPushButton("Browse");
    QPushButton *load = new QPushButton("Load Program");
    load->setObjectName("primary");
    startAddress = new QLineEdit("00");
    startAddress->setMaximumWidth(90);
    startAddress->setPlaceholderText("00");
    loadLayout->addWidget(new QLabel("Program file"));
    loadLayout->addWidget(filePath, 1);
    loadLayout->addWidget(browse);
    loadLayout->addSpacing(12);
    loadLayout->addWidget(new QLabel("Start address (HEX)"));
    loadLayout->addWidget(startAddress);
    loadLayout->addWidget(load);
    main->addWidget(loadBox);

    // Compact editing and execution controls
    QHBoxLayout *toolsRow = new QHBoxLayout;
    QGroupBox *editBox = new QGroupBox("MANUAL EDITING");
    QHBoxLayout *editLayout = new QHBoxLayout(editBox);
    regNumber = new QLineEdit; regNumber->setPlaceholderText("Register 0-F"); regNumber->setMaximumWidth(125);
    regValue = new QLineEdit; regValue->setPlaceholderText("Value 00-FF"); regValue->setMaximumWidth(125);
    QPushButton *setReg = new QPushButton("Set Register");
    memAddress = new QLineEdit; memAddress->setPlaceholderText("Address 00-FF"); memAddress->setMaximumWidth(140);
    memValue = new QLineEdit; memValue->setPlaceholderText("Value 00-FF"); memValue->setMaximumWidth(125);
    QPushButton *setMem = new QPushButton("Set Memory");
    editLayout->addWidget(regNumber);
    editLayout->addWidget(regValue);
    editLayout->addWidget(setReg);
    QFrame *divider = new QFrame; divider->setFrameShape(QFrame::VLine);
    editLayout->addWidget(divider);
    editLayout->addWidget(memAddress);
    editLayout->addWidget(memValue);
    editLayout->addWidget(setMem);
    toolsRow->addWidget(editBox, 3);

    QGroupBox *controlBox = new QGroupBox("EXECUTION");
    QHBoxLayout *control = new QHBoxLayout(controlBox);
    QPushButton *step = new QPushButton("Run One Step"); step->setObjectName("primary");
    QPushButton *run = new QPushButton("Run All"); run->setObjectName("success");
    QPushButton *reset = new QPushButton("Reset Machine"); reset->setObjectName("danger");
    control->addWidget(step);
    control->addWidget(run);
    control->addWidget(reset);
    toolsRow->addWidget(controlBox, 2);
    main->addLayout(toolsRow);

    // Main workspace: Memory gets most of the width. Registers stay visible.
    QSplitter *workspace = new QSplitter(Qt::Horizontal);
    workspace->setChildrenCollapsible(false);

    QGroupBox *memoryBox = new QGroupBox("MEMORY  |  256 ADDRESSES");
    QVBoxLayout *memoryLayout = new QVBoxLayout(memoryBox);
    memoryView = new QPlainTextEdit;
    memoryView->setReadOnly(true);
    memoryView->setLineWrapMode(QPlainTextEdit::NoWrap);
    memoryView->setPlaceholderText("Memory contents will appear here...");
    memoryView->setFont(QFont("Consolas", 11));
    memoryLayout->addWidget(memoryView);
    workspace->addWidget(memoryBox);

    QWidget *rightPanel = new QWidget;
    QVBoxLayout *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(8);

    QGroupBox *registerBox = new QGroupBox("REGISTERS  |  16 REGISTERS");
    QVBoxLayout *registerLayout = new QVBoxLayout(registerBox);
    registerView = new QPlainTextEdit;
    registerView->setReadOnly(true);
    registerView->setLineWrapMode(QPlainTextEdit::NoWrap);
    registerView->setFont(QFont("Consolas", 11));
    registerLayout->addWidget(registerView);
    rightLayout->addWidget(registerBox, 3);

    QTabWidget *tabs = new QTabWidget;
    screenView = new QPlainTextEdit;
    logView = new QPlainTextEdit;
    for (QPlainTextEdit *view : {screenView, logView}) {
        view->setReadOnly(true);
        view->setLineWrapMode(QPlainTextEdit::NoWrap);
        view->setFont(QFont("Consolas", 10));
    }
    tabs->addTab(screenView, "Screen Output");
    tabs->addTab(logView, "Activity Log");
    rightLayout->addWidget(tabs, 2);
    workspace->addWidget(rightPanel);
    workspace->setStretchFactor(0, 7);
    workspace->setStretchFactor(1, 3);
    workspace->setSizes({980, 420});
    main->addWidget(workspace, 1);

    connect(browse, &QPushButton::clicked, this, [this]() {
        QString path = QFileDialog::getOpenFileName(this, "Open program", QString(), "Text files (*.txt);;All files (*.*)");
        if (!path.isEmpty()) filePath->setText(path);
    });
    connect(load, &QPushButton::clicked, this, &MainWindow::loadProgram);
    connect(setReg, &QPushButton::clicked, this, &MainWindow::editRegister);
    connect(setMem, &QPushButton::clicked, this, &MainWindow::editMemory);
    connect(step, &QPushButton::clicked, this, &MainWindow::runStep);
    connect(run, &QPushButton::clicked, this, &MainWindow::runAll);
    connect(reset, &QPushButton::clicked, this, &MainWindow::resetMachine);

    setStyleSheet(R"(
        QWidget { background:#101827; color:#e5edf7; font-family:'Segoe UI'; font-size:13px; }
        QLabel#title { font-size:27px; font-weight:800; letter-spacing:1px; }
        QLabel#subtitle { color:#91a4bb; }
        QGroupBox { border:1px solid #2a3a50; border-radius:11px; margin-top:9px; padding:10px; font-weight:700; color:#7dd3fc; }
        QGroupBox::title { subcontrol-origin:margin; left:12px; padding:0 5px; }
        QLineEdit, QPlainTextEdit { background:#0b1220; border:1px solid #304158; border-radius:7px; padding:7px; selection-background-color:#0e7490; }
        QLineEdit:focus { border:1px solid #38bdf8; }
        QPushButton { background:#26364b; border:0; border-radius:8px; padding:9px 13px; font-weight:700; }
        QPushButton:hover { background:#344a63; }
        QPushButton#primary { background:#0369a1; } QPushButton#primary:hover { background:#0284c7; }
        QPushButton#success { background:#047857; } QPushButton#success:hover { background:#059669; }
        QPushButton#danger { background:#9f1239; } QPushButton#danger:hover { background:#be123c; }
        QLabel#statusValue { background:#17263a; border:1px solid #2c425b; border-radius:8px; padding:9px 17px; color:#7dd3fc; font-weight:700; }
        QTabWidget::pane { border:1px solid #2a3a50; border-radius:8px; }
        QTabBar::tab { background:#17263a; padding:9px 15px; margin-right:3px; border-top-left-radius:7px; border-top-right-radius:7px; }
        QTabBar::tab:selected { background:#075985; }
        QSplitter::handle { background:#26364b; width:5px; }
    )");

    refreshViews();
    addLog("Welcome. Select a program file to begin.");
}

int MainWindow::readHex(const QString &text, bool *ok)
{
    return text.trimmed().toInt(ok, 16);
}

void MainWindow::loadProgram()
{
    bool ok = false; int address = readHex(startAddress->text(), &ok);
    if (filePath->text().isEmpty() || !ok) { QMessageBox::warning(this, "Input needed", "Choose a program file and enter a valid hexadecimal start address."); return; }
    QString result = QString::fromStdString(machine.LoadProgram(filePath->text().toStdString(), address));
    addLog(result); refreshViews();
    if (!machine.IsProgramLoaded()) QMessageBox::warning(this, "Could not load program", result);
}

void MainWindow::editRegister()
{
    bool a=false,b=false; int reg=readHex(regNumber->text(),&a), value=readHex(regValue->text(),&b);
    if (!a || !b || reg<0 || reg>15 || value<0 || value>255) { QMessageBox::warning(this,"Invalid input","Register: 0-F, Value: 00-FF (hexadecimal)."); return; }
    machine.SetRegisterValue(reg,value); addLog("Register updated."); refreshViews();
}

void MainWindow::editMemory()
{
    bool a=false,b=false; int address=readHex(memAddress->text(),&a), value=readHex(memValue->text(),&b);
    if (!a || !b || address<0 || address>255 || value<0 || value>255) { QMessageBox::warning(this,"Invalid input","Address and value must be between 00 and FF (hexadecimal)."); return; }
    machine.SetMemoryValue(address,value); addLog("Memory updated."); refreshViews();
}

void MainWindow::runStep() { addLog(QString::fromStdString(machine.RunOneStep())); refreshViews(); }
void MainWindow::runAll() { addLog(QString::fromStdString(machine.RunAllSteps())); refreshViews(); }
void MainWindow::resetMachine() { machine.Reset(); addLog("Machine reset."); refreshViews(); }

void MainWindow::refreshViews()
{
    registerView->setPlainText(QString::fromStdString(machine.GetRegistersText()));
    memoryView->setPlainText(QString::fromStdString(machine.GetMemoryText()));
    screenView->setPlainText(QString::fromStdString(machine.GetScreenText()));
    pcLabel->setText("PC: " + QString::fromStdString(machine.GetPCText()));
    QString ir=QString::fromStdString(machine.GetIRText());
    irLabel->setText("IR: " + (ir.isEmpty() ? "----" : ir));
}
void MainWindow::addLog(const QString &message) { logView->appendPlainText("• " + message); }
