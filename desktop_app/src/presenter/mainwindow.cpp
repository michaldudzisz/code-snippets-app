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

    ui->date_to_edit->setDate(QDate::currentDate());
    ui->date_to_edit->setTime(QTime::currentTime());
    ui->view_content->setReadOnly(true);

    set_date_text_color(ui->date_from_edit, ui->date_from_box->isChecked());
    set_date_text_color(ui->date_to_edit, ui->date_to_box->isChecked());

    connect(&worker_, &Worker::data_received, this, &MainWindow::handle_data);
    connect(&worker_, &Worker::communication_error, this, &MainWindow::handle_communication_error);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_find_button_clicked()
{
   QHash<QString, QString> map;


   QString title = ui->title_text->toPlainText();

   if (!title.isEmpty())
   {
       map.insert("title_subsequence", title);
   }

   QString lang = ui->langBox->currentText();

   if (lang != "all")
   {
       map.insert("lang", lang);
   }

   QString author = ui->author_text->toPlainText();

   if (!author.isEmpty())
   {
       map.insert("author_subsequence", author);
   }

   if (ui->date_from_box->isChecked())
   {
       QDateTime date_from = ui->date_from_edit->dateTime();
       qint64 int_date_from = date_from.toSecsSinceEpoch();
       QString string_date_from = QString::number(int_date_from);

       map.insert("created_from", string_date_from);
   }

   if (ui->date_to_box->isChecked())
   {
       QDateTime date_to = ui->date_to_edit->dateTime();
       qint64 int_date_to = date_to.toSecsSinceEpoch();
       QString string_date_to = QString::number(int_date_to);

       map.insert("created_to", string_date_to);
   }

   worker_.get(map);
}

void MainWindow::on_list_snippets_itemClicked(/*QListWidgetItem *item*/)
{
    int chosen = ui->list_snippets->currentRow();
    ui->view_content->setText(snippets_[chosen].content());
}

void MainWindow::on_new_button_clicked()
{
    AddSnippetWindow new_window;
    new_window.setModal(true);
    new_window.exec();
}

void MainWindow::show_snippets()
{
    ui->list_snippets->clear();

    for (auto& elem : snippets_)
    {
        ui->list_snippets->addItem(elem.title());
    }
}

void MainWindow::on_save_clicked()
{
    if (ui->list_snippets->currentRow() == -1)
    {
        QMessageBox::warning(this, "Error", "no snippet chosen");
        return;
    }

    QString file_name = QFileDialog::getSaveFileName(
                this,
                tr("save as"),
                "",
                tr("All Files(*)")
                );

    if (file_name.isEmpty())
    {
        return;
    }

    QFile file(file_name);

    if (!file.open(QIODevice::WriteOnly))
    {
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
    const QJsonArray json_array = json_document.array();

    try
    {
        snippets_.clear();
        for (const auto& json : json_array)
        {
            Snippet snip = Snippet::fromJson(json.toObject());
            snippets_.push_back(snip);
        }
        show_snippets();
    }
    catch(std::exception& e)
    {
        QMessageBox::information(this, "Error", e.what());
    }
}

void MainWindow::handle_communication_error(int status_code)
{
    QMessageBox::information(
                this,
                "Error with get",
                "Connection failed, http status code: " + QString::number(status_code)
                );
}

void MainWindow::on_date_from_box_stateChanged(int arg)
{
    set_date_text_color(ui->date_from_edit, arg);
}

void MainWindow::on_date_to_box_stateChanged(int arg)
{
    set_date_text_color(ui->date_to_edit, arg);
}

void MainWindow::set_date_text_color(QDateTimeEdit* widget, int arg)
{
    QPalette pal = widget->palette();

    if (arg)
    {
        pal.setColor(QPalette::Text, BLACK_);
        widget->setPalette(pal);
    }
    else
    {
        pal.setColor(QPalette::Text, GREY_);
        widget->setPalette(pal);
    }
}
