#include "Editor.h"

#include <QtWidgets>
#include <QtGui>

Editor *Editor::open(QWidget *parent) {
  QString fileName = QFileDialog::getOpenFileName(parent, tr("Open"), ".");
  if (fileName.isEmpty()) {
    return 0;
  }
  return openFile(fileName, parent);
}

Editor *Editor::openFile(const QString &fileName, QWidget *parent) {
  Editor *editor = new Editor(parent);
  if (editor->readFile(fileName)) {
    editor->setCurrentFile(fileName);
    return editor;
  }
  else {
    delete editor;
    return 0;
  }
}

Editor::Editor(QWidget *parent /* = 0 */) : QTextEdit(parent) {
  action = new QAction(this);
  action->setCheckable(true);

  connect(action, SIGNAL(triggered()), this, SLOT(show()));
  connect(action, SIGNAL(triggered()), this, SLOT(setFocus()));

  isUntitled = true;

  connect(document(), SIGNAL(contentsChanged()), this, SLOT(documentWasModified()));
  setWindowIcon(QPixmap(":/images/documnet.png"));
  setWindowTitle("[*]");
  setAttribute(Qt::WA_DeleteOnClose);
}

bool Editor::save() {
  if (isUntitled) {
    return saveAs();
  }
  else {
    return saveFile(curFile);
  }
}

bool Editor::saveAs() {
  QString fileName = QFileDialog::getSaveFileName(this,
    tr("Save Spreadsheet"), tr("."),
    tr("Spreadsheet files (*.sp)"));
  if (fileName.isEmpty())
    return false;
  return saveFile(fileName);
}

void Editor::closeEvent(QCloseEvent * event) {
  if (okToContinue()) {
    event->accept();
  }
  else {
    event->ignore();
  }
}

void Editor::documentWasModified() {
  setWindowModified(true);
}

void Editor::newFile() {
  static int documentNumber = 1;
  curFile = tr("document%1.txt").arg(documentNumber);
  setWindowTitle(curFile + "[*]");
  action->setText(curFile);
  isUntitled = true;
  ++documentNumber;
}

bool Editor::okToContinue() {
  if (isWindowModified()) {
    int r = QMessageBox::warning(this, tr("Editor"),
      tr("The document has been modified.\n"
      "Do you want to save your changeds?"),
      QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if (r == QMessageBox::Yes) {
      return save();
    }
    else if (r == QMessageBox::Cancel) {
      return false;
    }
  }
  return true;
}

bool Editor::saveFile(const QString &fileName) {
  return false;
}

void Editor::setCurrentFile(const QString &fileName) {
  curFile = fileName;
  isUntitled = false;

  action->setText(strippedName(fileName));
  document()->setModified(false);
  setWindowTitle(strippedName(fileName) + "[*]");
  setWindowModified(false);
}

bool Editor::readFile(const QString &fileName) {
  return false;
}

bool Editor::writeFile(const QString &fileName) {
  return false;
}

QString Editor::strippedName(const QString &fullFileName) {
  return QFileInfo(fullFileName).fileName();
}

QSize Editor::sizeHint() const {
  return QSize(72 * fontMetrics().width('x'), 25 * fontMetrics().lineSpacing());
}