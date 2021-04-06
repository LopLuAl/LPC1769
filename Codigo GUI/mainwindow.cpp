#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QByteArray>

#include <QTimer>

#define LOG_MAXCOUNT    500

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_port(NULL), m_cant_bytes_recibidos(0),
    m_cant_bytes_enviados(0), ui(new Ui::MainWindow)
{
    m_init = true;

    ui->setupUi(this);

    UpdateTabs();

    Portname = "";
    EnumerarPuertos();
    ActualizarEstadoConexion();

    //Inicializar panel de la status bar
    m_status_bytes_recibidos = new QLabel;
    ui->statusBar->addWidget(m_status_bytes_recibidos);

    UpdateBytesTotales();

    m_init = false;
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_port;
}

void MainWindow::UpdateTabs()
{
    bool enable = Conectado();

    ui->tabWidget->setTabEnabled(1, enable);  // hago que siempre arranque en la pestaña de conexión

    ui->tab_estado_general->setDisabled(!enable);
}

void MainWindow::EnumerarPuertos()
{
    ui->comboBox_puertos->clear();

    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();

    for (int i = 0; i < ports.size(); i++)
        ui->comboBox_puertos->addItem(ports.at(i).portName(), ports.at(i).portName());
}

void MainWindow::on_button_connect_clicked()
{
    if (!m_port)  // si no está conectado....me quiero conectar
    {
        m_port = new QSerialPort(Portname);
        m_port->setBaudRate(QSerialPort::Baud115200);
        m_port->setFlowControl(QSerialPort::NoFlowControl);
        m_port->setParity(QSerialPort::NoParity);
        m_port->setDataBits(QSerialPort::Data8);
        m_port->setStopBits(QSerialPort::OneStop);

        if(!m_port->open(QIODevice::ReadWrite))
        {
            QMessageBox::critical(this,"Error","No se puede abrir el puerto "+m_port->portName());
            CerrarPuerto();
        }
        else
        {
            //Conectamos las señales que nos interesen
            connect(m_port, SIGNAL(readyRead()), this, SLOT(onDatosRecibidos()));
            ui->tabWidget->setCurrentIndex(1);
        }
    }
    else    // me quiero desconectar
        CerrarPuerto();

    ActualizarEstadoConexion();
    UpdateTabs();
}

void MainWindow::CerrarPuerto()
{
    m_port->close();
    delete m_port;
    m_port = NULL;
}

void MainWindow::ActualizarEstadoConexion()
{
    if (Conectado())
    {
        ui->edit_estado->setStyleSheet("font-weight: bold; color: black; background-color: lightgreen;");
        ui->edit_estado->setText("CONECTADO");
        ui->button_connect->setText("Desconectar");
    }
    else
    {
        ui->edit_estado->setStyleSheet("font-weight: normal; color: white; background-color: red;");
        ui->edit_estado->setText("Desconectado");
        ui->button_connect->setText("Conectar");
    }
}


bool MainWindow::Conectado()
{
    return m_port && m_port->isOpen();
}

void MainWindow::NoConectadoError()
{
    if (!m_init)
        QMessageBox::warning(this, QString::fromUtf8("Error de conexión"), "No conectado");
}
/* --------------------------------------------------------------- -*/
void MainWindow::onDatosRecibidos()
{
    QByteArray bytes;
    QString aux;
    int cant = m_port->bytesAvailable();
    bytes.resize(cant);

    m_port->read(bytes.data(), bytes.size());

    m_datos_recibidos += bytes;

    m_cant_bytes_recibidos += cant;

    UpdateBytesTotales();

}



void MainWindow::on_comboBox_puertos_currentIndexChanged(int index)
{
    Portname = ui->comboBox_puertos->itemData(index).toString();   //recupero la data del item de indice index
}



void MainWindow::EnviarComando(QString comando)
{
    QByteArray send = (comando).toLatin1();
    //Controlar si en modo socket o rs232
    qDebug() << comando;

    m_port->write(send);

    ui->list_log_enviados->addItem(comando);

    ui->list_log_enviados->setCurrentRow(ui->list_log_enviados->count()-1);

    //ui->list_log_enviados->scrollTo(ui->list_log_enviados->item(ui->list_log_enviados->count()-1));

    if(ui->list_log_enviados->count() > LOG_MAXCOUNT)
        for(int i=0;i<LOG_MAXCOUNT/5;i++)
            delete ui->list_log_enviados->takeItem(i);


    m_cant_bytes_enviados += send.size();
}

QString FijarAnchoString(QString str, int ancho)
{
    if (str.size() == ancho)
        return str;
    else if (str.size() > ancho)
        return str.mid(0, ancho);
    else
        while (str.size() < ancho)
            str += ' ';

    return str;
}

void MainWindow::UpdateBytesTotales()
{
    m_status_bytes_recibidos->setText(QString::number(m_cant_bytes_recibidos)
                 + " byte(s) recibidos, " + QString::number(m_cant_bytes_enviados)
                 + " byte(s) enviados.");
}

void MainWindow::on_dialAntebrazo_valueChanged(int value)
{
    ui->lineAntebrazo->setText(QString::number(value));
    QString cmd;
    if(value < 10)          cmd = "00"+QString::number(value);
    else if(value > 99)     cmd = QString::number(value);
    else                    cmd = "0"+QString::number(value);
    EnviarComando("$3"+cmd+"#");
}

void MainWindow::on_dialBase_valueChanged(int value)
{
    ui->lineBase->setText(QString::number(value));
    QString cmd;
    if(value < 10)          cmd = "00"+QString::number(value);
    else if(value > 99)     cmd = QString::number(value);
    else                    cmd = "0"+QString::number(value);
    EnviarComando("$4"+cmd+"#");
}

void MainWindow::on_dialBrazo_valueChanged(int value)
{
    ui->lineEdit->setText(QString::number(value));
    QString cmd;
    if(value < 10)          cmd = "00"+QString::number(value);
    else if(value > 99)     cmd = QString::number(value);
    else                    cmd = "0"+QString::number(value);
    EnviarComando("$2"+cmd+"#");
}

void MainWindow::on_pushButton_2_clicked()
{
    EnviarComando("$1002#");
}

void MainWindow::on_pushButton_2_pressed()
{
    EnviarComando("$1001#");
}

void MainWindow::on_pushButton_clicked()
{
    EnviarComando("$1002#");
}

void MainWindow::on_pushButton_pressed()
{
    EnviarComando("$1000#");
}
