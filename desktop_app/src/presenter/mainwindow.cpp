#include "mainwindow.h"
#include "addsnippetwindow.h"
#include <../view/ui_mainwindow.h>
#include <../server/src/snippet.h>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <exception>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //data4tests();
    connect(&worker_, &Worker::data_received, this, &MainWindow::handle_data);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_find_button_clicked()
{
    QString query = ui->form_query->toPlainText();
   // ui->list_snippets->addItem(query);
   show_snippets();
   //worker_.get("http://127.0.0.1:8000/app");

   QString title;
   QString lang;
   worker_.get(title, lang);

   QJsonObject data = create_single_snippet().toJson();

  // worker_.post("http://127.0.0.1:8000/app", QJsonDocument(data).toJson());

   Snippet snip = create_single_snippet();
   worker_.post(snip);
   qDebug() << "size: " + QString::number(snippets_.size());
}

void MainWindow::on_list_snippets_itemClicked(/*QListWidgetItem *item*/)
{
    //qDebug() << ui->list_snippets->currentRow();
    int chosen = ui->list_snippets->currentRow();
   // qDebug() << chosen;
    ui->view_content->setText(snippets_[chosen].content());
}

void MainWindow::on_new_button_clicked()
{
    AddSnippetWindow* new_window = new AddSnippetWindow(this);
    new_window->show();
}

void MainWindow::show_snippets()
{
    ui->list_snippets->clear();

    for (auto& elem : snippets_) {
        ui->list_snippets->addItem(elem.title());
    }
}

void MainWindow::on_save_clicked()
{
    if (ui->list_snippets->currentRow() == -1) {
        QMessageBox::warning(this, "Error", "no snippet chosen");
        return;
    }

    QString file_name = QFileDialog::getSaveFileName(
                this,
                tr("save as"),
                "",
                tr("All Files(*)")
                );

    if (file_name.isEmpty()) {
        return;
    }

    QFile file(file_name);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Unable to open file"),
            file.errorString());
        return;
    }

    QTextStream out(&file);
    int chosen = ui->list_snippets->currentRow();
    out << snippets_[chosen].content();
    file.flush();
    file.close();
}

void MainWindow::handle_data(QByteArray& byte_array)
{
    QJsonDocument json_document = QJsonDocument::fromJson(byte_array);
    QJsonArray json_array = json_document.array();

    try {
        snippets_.clear();
        for (auto json : json_array) {
            Snippet snip = Snippet::fromJson(json.toObject());
            snippets_.push_back(snip);
            qInfo() << json.toString();
        }
        show_snippets();
    } catch(std::exception& e) {
        QMessageBox::information(this, "Error", e.what());
    }

    //Snippet snip = Snippet::fromJson(json_object);
   // qInfo() << json_document.isArray();

    qInfo() << "komnukiacja miedzy klasami powiodla sie";
}

Snippet MainWindow::create_single_snippet() {
    Snippet snip;
    snip.setLang("c++");
    snip.setAuthor("ja");
    QString content = QString::number(5) + ", essa";
    snip.setContent(content);
    snip.setTitle("ok");
    return snip;
}

void MainWindow::data4tests() {
    for(int i = 0; i < 10; ++i) {
        Snippet snip;
        snip.setLang("c++");
        snip.setAuthor("ja");
        QString content = QString::number(i) + ", essa";
        snip.setContent(content);
        snip.setTitle("ok");
        snippets_.push_back(snip);
        //qDebug() << content;
    }
}
