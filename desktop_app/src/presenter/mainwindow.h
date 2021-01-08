#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QListWidgetItem>
#include <QDateTimeEdit>
#include <../server/src/snippet.h>
#include "addsnippetwindow.h"
#include <src/communication/worker.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/** @brief Class managing the main window. 
 * User interface is defined in view/mainwindow.ui files
 */

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
    void handle_communication_error(int status_code);
    void on_date_from_box_stateChanged(int arg);
    void on_date_to_box_stateChanged(int arg);

private:
    const QColor GREY_{140,140,140};
    const QColor BLACK_{0,0,0};

    Ui::MainWindow *ui;
    QVector<Snippet> snippets_;
    Worker worker_;
    void show_snippets();
    void set_date_text_color(QDateTimeEdit* widget, int arg);
};
#endif // MAINWINDOW_H
