#include <QFileDialog>
#include <QNetworkInterface>
#include "optionsform.h"
#include "settings.h"
#include "global.h"
#include "HotkeyEditor.h"
#include "mainwindow.h"

void OptionsForm::appendIpInformation() {
    QList<QHostAddress> list = QNetworkInterface::allAddresses();
    ui.ipLabel->setText("Possible ip addresses of this PC are:\n");

    for(int nIter=0; nIter<list.count(); nIter++)

    {
        if(!list[nIter].isLoopback() && list[nIter].protocol() == QAbstractSocket::IPv4Protocol) {
            ui.ipLabel->setText(ui.ipLabel->text() + list[nIter].toString() + "\n");
        }
    }
}


OptionsForm::OptionsForm(QWidget *parent) : QDialog(parent)
{
	keys = new Keys(this);

	ui.setupUi(this);
	ui.customServerTab->setVisible(false);

    //------------------- Remote ------------------------
    ui.remoteEnable->setChecked(Settings::Instance()->remoteEnable());
    ui.remotePassword->setText(Settings::Instance()->remotePassword());
    ui.remotePort->setText(QString::number( Settings::Instance()->remotePort() ));

	//------------------- Custom server ------------------------
	ui.customServerUrl->setText(Settings::Instance()->customServerUrl());
	ui.customServerQuality->setValue(Settings::Instance()->customServerQuality());
	ui.customServerDirectLink->setChecked(Settings::Instance()->customServerDirectLink());


	//------------------- Hot key editor ------------------------
    hotkeyEditor = new HotkeyEditor(this);
	ui.horizontalLayout->addWidget(hotkeyEditor);
	hotkeyEditor->setPlainText(Settings::Instance()->hotkeyTxt());
	hotkeyEditor->setHotkey(Settings::Instance()->hotkey());
	hotkeyEditor->setMod(Settings::Instance()->hotkeyMod());

	setFixedSize(width(), height());

	ui.autorun->setChecked(Settings::Instance()->autorun());
	ui.askBeforeSend->setChecked(Settings::Instance()->askBeforeSend());

	ui.defaultUploader->addItem("Save to file");
	ui.defaultUploader->addItem("Upload to bsvi.ru");
	ui.defaultUploader->addItem("Upload to custom server");

	QString aa = Settings::Instance()->defaultUploader();
	int index = ui.defaultUploader->findText(aa);
	if ( index != -1 ) ui.defaultUploader->setCurrentIndex(index);

	ui.chooseSaveToFilePath->setText(Settings::Instance()->saveToFilePath());
	ui.saveToFileQuality->setValue(Settings::Instance()->saveToFileQuality());

	ui.checkUpdates->setChecked(Settings::Instance()->checkUpdates());

	ui.showDrawingMenu->setChecked(Settings::Instance()->showMenuByDefault());
	ui.doubleClickDrawing->setChecked(Settings::Instance()->doubleClickDrawing());


	connect(ui.chooseSaveToFilePath, SIGNAL(clicked()), this, SLOT(chooseSaveToFilePath()));

    appendIpInformation();
}

OptionsForm::~OptionsForm()
{
	delete keys;
}


void OptionsForm::accept()
{
	Settings::Instance()->setAutorun(ui.autorun->checkState());
	Settings::Instance()->setAskBeforeSend(ui.askBeforeSend->checkState());
	Settings::Instance()->setDefaultUploader(ui.defaultUploader->currentText());
	Settings::Instance()->setSaveToFilePath(ui.chooseSaveToFilePath->text());
	Settings::Instance()->setSaveToFileQuality(ui.saveToFileQuality->value());
	Settings::Instance()->setCheckUpdates(ui.checkUpdates->checkState());
	Settings::Instance()->setShowMenuByDefault(ui.showDrawingMenu->checkState());
	Settings::Instance()->setDoubleClickDrawing(ui.doubleClickDrawing->checkState());
    Settings::Instance()->setHotkeyTxt(hotkeyEditor->toPlainText());
    Settings::Instance()->setHotkey(hotkeyEditor->hotkey());
    Settings::Instance()->setHotkeyMod(hotkeyEditor->mod());

	//------------------- Custom server ------------------------
	Settings::Instance()->setCustomServerUrl(ui.customServerUrl->text());
	Settings::Instance()->setCustomServerQuality(ui.customServerQuality->value());
	Settings::Instance()->setCustomServerDirectLink(ui.customServerDirectLink->isChecked());

    //------------------- Remote ------------------------
    Settings::Instance()->setRemoteEnable(ui.remoteEnable->checkState());
    Settings::Instance()->setRemotePassword(ui.remotePassword->text());
    Settings::Instance()->setRemotePort( ui.remotePort->text().toInt() );

    MainWindow::Instance()->initialize();
    done(1);
}

void OptionsForm::reject()
{
	done(0);
}


void OptionsForm::chooseSaveToFilePath()
{
	QFileDialog fileDlg; 
	fileDlg.setOption(QFileDialog::ShowDirsOnly, true); 
	fileDlg.setFileMode(QFileDialog::Directory);
	if (fileDlg.exec())
	{
		ui.chooseSaveToFilePath->setText(fileDlg.selectedFiles()[0]);
	}
}


