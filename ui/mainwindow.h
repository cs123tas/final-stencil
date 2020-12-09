#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <memory>
#include <QMainWindow>
#include "shaderevolution/ShaderEvolutionManager.h"


class SupportCanvas3D;
class ShaderEvolutionManager;

namespace Ui {
    class MainWindow;
}

/**
 * @class MainWindow
 *
 * The main graphical user interface class (GUI class) for our application.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void fileOpen(QString file);

protected:

    // Overridden from QWidget. Handles the window close event.
    virtual void closeEvent(QCloseEvent *e);
    void signalSettingsChanged(); //We could have done this with signals and slots; not a priority now

private slots:
    void on_mutateButton_clicked();

    void on_renderShadersButton_clicked();

    void on_usePointLightsForShaders_stateChanged(int arg1);

    void on_useLightingForShaders_stateChanged(int arg1);


    void on_mainTabWidget_currentChanged(int index);

    void on_renderLTreesbutton_clicked();

    void on_angleStochasticity_stateChanged(int arg1);

    void on_generateLSystemTree_clicked();

    void on_lSystemType_currentIndexChanged(int index);

    void on_recursiveDepth_sliderMoved(int position);

    void on_lengthStochasticity_stateChanged(int arg1);

    void on_leaves_stateChanged(int arg1);

private:
    // Auto-generated by Qt. DO NOT RENAME!
    Ui::MainWindow *ui;

    SupportCanvas3D *m_canvas3D;
    ShaderEvolutionManager *SEManager;

};

#endif // MAINWINDOW_H
