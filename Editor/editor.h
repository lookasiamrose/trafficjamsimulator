#ifndef EDITOR_H
#define EDITOR_H

#include "types.h"
#include "config.h"
#include <QWidget>

class Editor : public QWidget
{
    Q_OBJECT
public:
    explicit Editor(QWidget *parent = 0, int _iNodeId = 0);
private:
    int iNodeId;
    NodeSettings nodeSettings;

private slots:
    void slSave();
    void slReload();
    void slEditLight();
    void slEditOrder();
    void slClose();
};

#endif // EDITOR_H
