#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QListWidgetItem>
#include <../server/src/snippet.h>
#include "addsnippetwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    data4tests();
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

}

void MainWindow::on_list_snippets_itemClicked(/*QListWidgetItem *item*/)
{
    //qDebug() << ui->list_snippets->currentRow();
    int chosen = ui->list_snippets->currentRow();
    ui->view_content->setText(snippets_[chosen].content());
}

void MainWindow::on_new_button_clicked()
{
    AddSnippetWindow* new_window = new AddSnippetWindow(this);
    new_window->show();
}

void MainWindow::show_snippets()
{
    for (auto& elem : snippets_) {
        ui->list_snippets->addItem(elem.title());
    }
}

void MainWindow::on_save_clicked()
{
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
