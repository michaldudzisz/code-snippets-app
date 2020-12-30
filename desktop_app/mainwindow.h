#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <server/src/snippet.h>
#include <addsnippetwindow.h>

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

private:
    Ui::MainWindow *ui;
    AddSnippetWindow* add_snippet_window;
    QVector<Snippet> snippets_;
    void show_snippets();
    void data4tests();
};
#endif // MAINWINDOW_H
