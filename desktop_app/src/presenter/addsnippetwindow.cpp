#include "addsnippetwindow.h"
#include <../view/ui_addsnippetwindow.h>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include "../model/snippet.h"
#include "../model/too_long_content_exception.h"
#include "../model/unsupported_language_exception.h"
#include <QDateTime>
#include <QJsonObject>
#include "../communication/worker.h"


AddSnippetWindow::AddSnippetWindow(QWidget *parent) :
    QDialog(parent),
    ui_(new Ui::AddSnippetWindow)
{
    ui_->setupUi(this);

    connect(&worker_, &Worker::communication_error, this, &AddSnippetWindow::handle_communication_error);
}


AddSnippetWindow::~AddSnippetWindow()
{
    delete ui_;
}


void AddSnippetWindow::on_browse_button_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "open a file", "");
    QFile file(file_name);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "title", "file not open");
    }

    QTextStream in (&file);
    QString text = in.readAll();
    ui_->text_snippet->setPlainText(text);

    file.close();
}


void AddSnippetWindow::on_add_button_clicked()
{ 
    if (!check_if_filled())
    {
        return;
    }

    try
    {
        Snippet new_snippet(
                    ui_->text_author->toPlainText(),
                    ui_->text_title->toPlainText(),
                    ui_->lang_box->currentText(),
                    ui_->text_snippet->toPlainText()
                    );

        worker_.post(new_snippet);
        ui_->text_author->clear();
        ui_->text_title->clear();
        ui_->text_snippet->clear();

    }
    catch(TooLongContentException& e)
    {
        QMessageBox::warning(this, "title", "Text is too long");
    }
    catch(UnsupportedLanguageException& e)
    {
        QMessageBox::warning(this, "title", "Such language is not supported");
    }
}

void AddSnippetWindow::handle_communication_error(int status_code)
{
    QMessageBox::information(
                this,
                "Error with post",
                "Connection failed, http status code: " + QString::number(status_code)
                );
}

bool AddSnippetWindow::check_if_filled()
{
    if (ui_->text_snippet->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, "error", "There is no text");
        return false;
    }
    if (ui_->text_title->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, "error", "There is no title");
        return false;
    }
    if (ui_->text_author->toPlainText().isEmpty())
    {
        QMessageBox::warning(this, "error", "There is no author");
        return false;
    }
    return true;
}
