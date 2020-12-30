#ifndef ADDSNIPPETWINDOW_H
#define ADDSNIPPETWINDOW_H

#include <QDialog>

namespace Ui {
class AddSnippetWindow;
}

class AddSnippetWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AddSnippetWindow(QWidget *parent = nullptr);
    ~AddSnippetWindow();

private slots:
    void on_browse_button_clicked();
    void on_add_button_clicked();

private:
    Ui::AddSnippetWindow *ui;
};

#endif // ADDSNIPPETWINDOW_H
