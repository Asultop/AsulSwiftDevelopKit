#ifndef T_EXAMPLE_H
#define T_EXAMPLE_H

#include <QWidget>
#include <qtmetamacros.h>
#include "../SystemKit/BaseScrollPage.h"
#include "../CTL_AsulComboBox/AsulComboBox.h"
class T_Example : public BaseScrollPage
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit T_Example(QWidget *parent = nullptr);

signals:

};

#endif // T_EXAMPLE_H
