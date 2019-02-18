#include "maincontrols.h"

MainControls::MainControls(QWidget *parent) : QWidget(parent)
{
    createGuiItems();
    createAndFillLayouts();

    connect(record_pushButton, SIGNAL(pressed()), this, SLOT(recordButtonPressed()));
}

// ################### Private methods ######################
void MainControls::createGuiItems()
{
    // Create the widgets.
    init_pushButton->setText("Initialise set-up");
    init_label->setText("Status: idle");

    record_pushButton->setText("Record experiment");
    record_label->setText("Not recording");
}

void MainControls::createAndFillLayouts()
{
    // Fill the layouts.
    init_hbox->addWidget(init_pushButton);
    init_hbox->addWidget(init_label);

    record_hbox->addWidget(record_pushButton);
    record_hbox->addWidget(record_label);

    // Fill the main layout.
    main_vbox->addLayout(init_hbox);
    main_vbox->addLayout(record_hbox);

    // Set the main layout.
    this->setLayout(main_vbox);
}

// #################### Signals #########################
// #################### Public slots ####################
void MainControls::recordingReady()
{
    record_label->setText("Recording");
}

void MainControls::recordingFail(QString message)
{
    record_label->setText("Error: " + message);
}
// #################### Private slots ###################
void MainControls::recordButtonPressed()
{
    emit startRecording();
}