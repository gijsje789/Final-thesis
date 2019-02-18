// fileoperation.cpp - Implementation file for the FileOperation class.
// This class handles the appearance and functionality of the
// file menu. This will also take care of the writing to file.
// Date: 2019-02-12
// Created by: Gijs de Vries
#include "fileoperation.h"

FileOperation::FileOperation(QWidget *parent) : QWidget(parent)
{
    createGuiItems();
    createAndFillLayouts();

    connect(renameLast_pushButton, SIGNAL(clicked()), this, SLOT(renameLastFile()));
}

FileOperation::~FileOperation()
{
    closeOutputFile();
}

// #################### Private functions ####################
void FileOperation::createGuiItems()
{
    // Create input fields.
    fileName_label->setText("File name: ");
    fileName_lineEdit->setText("sensorData");
    renameLast_pushButton->setText("Rename last");
}

void FileOperation::createAndFillLayouts()
{
    // Fill the horizontal layout.
    hbox_main->addWidget(fileName_label);
    hbox_main->addWidget(fileName_lineEdit);
    hbox_main->addWidget(renameLast_pushButton);

    // Set main layout.
    this->setLayout(hbox_main);
}

void FileOperation::createNewOutputFile()
{
    // Create new file in an output folder which is one level up.
    QDateTime *datetime = new QDateTime;
    QString tempString = FILE_LOC
            + datetime->currentDateTime().toString("yyyyMMdd_hhmmss_")
            + fileName_lineEdit->text() + ".csv";
    outputFile = new QFile(tempString);
}

void FileOperation::openOutputFile()
{
    if (outputFile != nullptr) {
        if(outputFile->open(QIODevice::WriteOnly)) {
            qDebug() << outputFile->fileName() << "successfully opened.";
            lastFile = outputFile->fileName();
        }
    }
}
// #################### Signals ##########################
// #################### Public slots #####################
void FileOperation::startRecording()
{
    if (outputFile == nullptr)
        createNewOutputFile();

    if (!outputFile->isOpen())
        openOutputFile();

    if (outputFile->isWritable() && outputFile->isOpen())
        emit readyToRecord();
    else if (outputFile == nullptr)
        emit fileFailure("FERR-004");
    else if (!outputFile->isOpen())
        emit fileFailure("FERR-005");
    else if (!outputFile->isWritable())
        emit fileFailure("FERR-006");
    else
        emit fileFailure("FERR-999");
}

void FileOperation::writeToOutputFile(QString data)
{
    QByteArray byteArray = data.toLocal8Bit();
    if (outputFile != nullptr) {
        if (outputFile->isOpen()) {
            if (outputFile->isWritable()) {
                outputFile->write(byteArray);
            } else {
                emit fileFailure("FERR-003");
            }
        } else {
            emit fileFailure("FERR-002");
        }
    } else {
        emit fileFailure("FERR-001");
    }
}
// #################### Private slots ####################
void FileOperation::renameLastFile()
{
    if (temp) {
        closeOutputFile();
        temp = false;
    }
    else {
        createNewOutputFile();
        temp = true;
    }
}

void FileOperation::closeOutputFile()
{
    if (outputFile != nullptr) {
        if (outputFile->isOpen()) {
            qDebug() << "Closing file.";
            outputFile->close();
            outputFile = nullptr;
        }
        else {
            outputFile = nullptr;
        }
    }
}
