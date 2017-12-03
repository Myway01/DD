#include "CallWidget.h"
#include "ui_CallWidget.h"

CallWidget::CallWidget(QWidget *parent) :
    QWidget(parent),
  ui(new Ui::CallWidget)
{
  ui->setupUi(this);
  connect(ui->webView_map->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
              this, SLOT(populateJavaScriptWindowObject()));
}

CallWidget::~CallWidget()
{
    if(ui->webView_map != NULL)
    {
        delete ui->webView_map;
        ui->webView_map = NULL;
    }
    QWebSettings::globalSettings()->clearMemoryCaches();
    delete ui;
}

void CallWidget::on_pushButton_call_clicked()
{
    ui->webView_map->page()->mainFrame()->evaluateJavaScript(QString("Qttest(\"%1\")").arg("hello, I'm Qt!"));
}

void CallWidget::populateJavaScriptWindowObject(){
    ui->webView_map->page()->mainFrame()->addToJavaScriptWindowObject("Extractor", this);
}
