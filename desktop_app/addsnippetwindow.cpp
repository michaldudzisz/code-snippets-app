#include "addsnippetwindow.h"
#include "ui_addsnippetwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>
#include <server/src/snippet.h>
#include <server/src/too_long_content_exception.h>
#include <server/src/unsupported_language_exception.h>
#include <QDateTime>
#include <QJsonObject>

AddSnippetWindow::AddSnippetWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSnippetWindow)
{
    ui->setupUi(this);
}

AddSnippetWindow::~AddSnippetWindow()
{
    delete ui;
}

void AddSnippetWindow::on_browse_button_clicked()
{
    QString file_name = QFileDialog::getOpenFileName(this, "open a file", "");
    QFile file(file_name);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "title", "file not open");
    }

    QTextStream in (&file);
    QString text = in.readAll();
    qDebug() << text;
    ui->text_snippet->setPlainText(text);

    file.close();
}

void AddSnippetWindow::on_add_button_clicked()
{
    QString snippet_content = ui->text_snippet->toPlainText();
    QString snippet_title = ui->text_title->toPlainText();
    if (snippet_content.isEmpty()) {
        QMessageBox::warning(this, "title", "There is no text");
    }
    else if (snippet_title.isEmpty()) {
        QMessageBox::warning(this, "title", "There is no title");
    }
    else {
        try {
            Snippet new_snippet(
                        ui->text_author->toPlainText(),
                        ui->text_title->toPlainText(),
                        ui->lang_box->currentText(),
                        ui->text_snippet->toPlainText()
                        );
            QJsonObject snippet_json = new_snippet.toJson();

        } catch(TooLongContentException& e) {
            QMessageBox::warning(this, "title", "Text is too long");
        } catch(UnsupportedLanguageException& e) {
            QMessageBox::warning(this, "title", "Such language is not supported");
        }

        qDebug() << "ok";
    }
}
