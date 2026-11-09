#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Machine.h"

class QLabel;
class QLineEdit;
class QPlainTextEdit;
class QPushButton;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    Machine machine;
    QLineEdit *filePath;
    QLineEdit *startAddress;
    QLineEdit *regNumber;
    QLineEdit *regValue;
    QLineEdit *memAddress;
    QLineEdit *memValue;
    QLabel *pcLabel;
    QLabel *irLabel;
    QPlainTextEdit *registerView;
    QPlainTextEdit *memoryView;
    QPlainTextEdit *screenView;
    QPlainTextEdit *logView;

    void loadProgram();
    void editRegister();
    void editMemory();
    void runStep();
    void runAll();
    void resetMachine();
    void refreshViews();
    void addLog(const QString &message);
    int readHex(const QString &text, bool *ok);
};

#endif
