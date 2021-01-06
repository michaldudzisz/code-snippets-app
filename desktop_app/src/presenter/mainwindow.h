#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QListWidgetItem>
#include <../server/src/snippet.h>
#include "addsnippetwindow.h"
#include <src/communication/worker.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_find_button_clicked();
    void on_list_snippets_itemClicked(/*QListWidgetItem *item*/);
    void on_new_button_clicked(); 
    void on_save_clicked();
    void handle_data(QByteArray& byte_array);
    void on_date_from_box_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QVector<Snippet> snippets_;
    Worker worker_;
    void show_snippets();
    void data4tests();
    Snippet create_single_snippet();
};
#endif // MAINWINDOW_H
