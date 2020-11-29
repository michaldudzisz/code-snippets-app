#include <QApplication>
#include <QPushButton>

int main(int argc, char** argv) {
  QApplication app(argc, argv);
  QWidget window;
  window.resize(320,240);
  window.show();
  return app.exec();
}

