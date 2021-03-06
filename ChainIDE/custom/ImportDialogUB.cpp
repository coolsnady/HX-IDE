#include "ImportDialogUB.h"
#include "ui_ImportDialogUB.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QRegExpValidator>
#include <QDebug>

#include "ChainIDE.h"
#include "ConvenientOp.h"
#include "datamanager/DataManagerUB.h"
#include "IDEUtil.h"

ImportDialogUB::ImportDialogUB(QWidget *parent) :
    MoveableDialog(parent),
    ui(new Ui::ImportDialogUB)
{
    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);

    ui->name->setPlaceholderText( tr("Beginning with letter,letters or numbers"));
    ui->name->setAttribute(Qt::WA_InputMethodEnabled, false);

    QRegExp regx("[a-z][a-z0-9]+$");
    QValidator *validator = new QRegExpValidator(regx, this);
    ui->name->setValidator( validator );

    QRegExp regxpass("[a-zA-Z0-9]+$");
    QValidator *validator1 = new QRegExpValidator(regxpass, this);
    ui->privatekey->setValidator( validator1 );

    ui->name->setFocus();
    connect(ChainIDE::getInstance(),&ChainIDE::jsonDataUpdated,this,&ImportDialogUB::jsonDataUpdated);

}

ImportDialogUB::~ImportDialogUB()
{
    delete ui;
}

void ImportDialogUB::on_okBtn_clicked()
{

    ChainIDE::getInstance()->postRPC( "import-import_key",
                                     IDEUtil::toJsonFormat( "importprivkey", QJsonArray() << ui->privatekey->text()<<ui->name->text()));

}

void ImportDialogUB::on_privatekey_returnPressed()
{
    on_okBtn_clicked();
}

void ImportDialogUB::on_closeBtn_clicked()
{
    close();
}

void ImportDialogUB::jsonDataUpdated(const QString &id, const QString &data)
{
    if("import-import_key" == id)
    {
        QJsonParseError json_error;
        QJsonDocument parse_doucment = QJsonDocument::fromJson(data.toLatin1(),&json_error);
        if(json_error.error != QJsonParseError::NoError || !parse_doucment.isObject())
        {
            qDebug()<<json_error.errorString();
            ConvenientOp::ShowSyncCommonDialog(json_error.errorString());
            close();
            return;
        }


        DataManagerUB::getInstance()->queryAccount();

        ConvenientOp::ShowSyncCommonDialog(data);
        close();

    }
}

void ImportDialogUB::on_cancelBtn_clicked()
{
    close();
}
