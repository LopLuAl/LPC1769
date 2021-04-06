#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

#include <QQueue>

#include <QSerialPort>
#include <QSerialPortInfo>

#include <QList>
#include <QMap>

#include <QPointer>

#include <QDateTime>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QSerialPort *m_port;
    QLabel *m_status_bytes_recibidos;
    QString Portname;
    int m_cant_bytes_recibidos;
    int m_cant_bytes_enviados;
    void EnumerarPuertos();

public:

    bool m_init;

public:
    void ActualizarEstadoConexion();

    void CerrarPuerto();

    bool Conectado();
    void NoConectadoError();
    void UpdateBytesTotales();

    void UpdateTodo();

    void EnviarComando(QString comando);

    void UpdateTabs();

    QByteArray m_datos_recibidos;

    void ProcesarComandos();
    void ProcesarComando(QString comando);

private slots:
    void onDatosRecibidos();

    void on_button_connect_clicked();

    void on_comboBox_puertos_currentIndexChanged(int index);

    void on_dialAntebrazo_valueChanged(int value);

    void on_dialBase_valueChanged(int value);

    void on_dialBrazo_valueChanged(int value);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_pressed();

    void on_pushButton_2_pressed();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
