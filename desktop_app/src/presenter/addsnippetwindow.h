#ifndef ADDSNIPPETWINDOW_H
#define ADDSNIPPETWINDOW_H

#include <QDialog>
#include "../communication/worker.h"

namespace Ui {
class AddSnippetWindow;
}

/** brief Class managing window responsible for creating and sending snippets
 * User interface is defined in view/addsnippetwindow.ui file
 */

class AddSnippetWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddSnippetWindow(QWidget *parent = nullptr);
    ~AddSnippetWindow();

private slots:
    void on_browse_button_clicked();
    void on_add_button_clicked();
    void handle_communication_error(int status_code);

private:
    Ui::AddSnippetWindow *ui;
    Worker worker_;
    bool check_if_filled();

};

#endif // ADDSNIPPETWINDOW_H
