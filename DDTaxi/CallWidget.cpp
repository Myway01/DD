#include "CallWidget.h"
#include "ui_CallWidget.h"

#include <QMessageBox>

CallWidget::CallWidget(QWidget *parent) :
    QWidget(parent),
  ui(new Ui::CallWidget)
{
  ui->setupUi(this);
  map_view = new QWebEngineView(this);
  mapconn = new MapConn(map_view);
  this->ui->gridLayout_map->addWidget(map_view);
  QWebEnginePage *page = map_view->page();

  connect(page, &QWebEnginePage::featurePermissionRequested,
          [this, page](const QUrl &securityOrigin, QWebEnginePage::Feature feature) {
      if (feature != QWebEnginePage::Geolocation)
          return;

      QMessageBox msgBox(this);
      msgBox.setText(tr("%1 wants to know your location").arg(securityOrigin.host()));
      msgBox.setInformativeText(tr("Do you want to send your current location to this website?"));
      msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
      msgBox.setDefaultButton(QMessageBox::Yes);

      if (msgBox.exec() == QMessageBox::Yes) {
          page->setFeaturePermission(
              securityOrigin, feature, QWebEnginePage::PermissionGrantedByUser);
      } else {
          page->setFeaturePermission(
              securityOrigin, feature, QWebEnginePage::PermissionDeniedByUser);
      }
  });
  page->load(QUrl(QStringLiteral("qrc:/new/map/rsc/test-4.html")));
}

CallWidget::~CallWidget()
{
    delete ui;
}

void CallWidget::on_pushButton_call_clicked()
{
    emit mapconn->sendText("Hello, I'm Qt!");
}

