#ifndef OPTIONSFORM_H
#define OPTIONSFORM_H

#include <QDialog>
#include "keys.h"
#include "ui_optionsform.h"

class HotkeyEditor;

class OptionsForm : public QDialog
{
	Q_OBJECT

	Keys *keys;
public:
	OptionsForm(QWidget *parent);
	~OptionsForm();

private:
	Ui::OptionsForm ui;
	void StartWithWindows(bool start);
    HotkeyEditor *hotkeyEditor;
    void appendIpInformation();

public slots:
	void accept();
	void reject();

private slots:
    void chooseSaveToFilePath();
};

#endif // OPTIONSFORM_H
