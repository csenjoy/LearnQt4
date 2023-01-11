#ifndef MDIEDITOR_EDITOR_H
#define MDIEDITOR_EDITOR_H

#include <QtWidgets/QTextEdit>

class Editor : public QTextEdit {
  Q_OBJECT
 public:
  static Editor *open(QWidget *parent);
  static Editor *openFile(const QString &filename, QWidget *parent = 0);

  Editor(QWidget *parent = 0);

  void newFile();
  bool save();
  bool saveAs();
  QSize sizeHint() const;
  QAction *windowMenuAction() const { return action; }
 //public signals:
 protected:
  void closeEvent(QCloseEvent * event) override;
 private slots:
  void documentWasModified();

 private:
  bool okToContinue();
  bool saveFile(const QString &fileName);
  void setCurrentFile(const QString &fileName);
  bool readFile(const QString &fileName);
  bool writeFile(const QString &fileName);
  QString strippedName(const QString &fullFileName);

  QString curFile;
  bool isUntitled;
  QAction *action;
};

#endif