#ifndef TOURISTBOOKMAINWINDOW_H
#define TOURISTBOOKMAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QString>
#include <QtWidgets/QMessageBox>
#include <QTextCodec>
#include <QtWidgets\QFileDialog>
#include <QKeyEvent>
#include <QTimer>
#include "ui_touristbookmainwindow.h"
#include "journey.h"
#include "placeofrestvalidator.h"
#include "JourneyDatabase.h"

//коды состояний активности виджетов в окне
enum widgetsState
{
    NO_DB = 0,       //отсутствует БД
    NO_RECORDS = 1,  //пустая БД
    HAS_RECORDS = 2  //есть записи
};

 class TouristBookMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    /*!
    * Конструктор класса окна
    */
    TouristBookMainWindow(QWidget *parent = nullptr, Qt::WindowFlags flags = nullptr);

    /*!
    * Деструктор класса окна
    */
    ~TouristBookMainWindow();

    /*!
    * Переключает режимы "редактирование", "приглашение на добавление новых записей", "отсутствие БД"
    * \param [in] status текущий режим. true - редактирование, false - добавление
    */
    void ChangeWidgetsMode(widgetsState status);

    /*!
    * Функция обновляет текст и местоположение в браузере измененной записи
    */
    void UpdateBrowser(int newIndex);

    /*!
    * Вставляет запись в браузер
    * \param [in] record ссылка на экземпляр класса-записи
    * \param [in] index индекс для вставки
    */
    void AddToBrowser(const Journey &record, int index);

    /*!
    * Функция показывает сохраненные значения текущей записи в виджетах
    * \param [in] curr индекс записи в базе данных
    */
    void ShowValues(int curr);

    /*!
    * Функция генерирует строку для показа в браузере на основании переданной записи
    * \param [in] record ссылка на экземпляр класса Journey - запись в БД
    * \return сгенерированная строка
    */
    QString GenerateBrowserText(const Journey &record) const;

    /*!
    * Функция проверяет наличие несохраненных изменений и предлагает их сохранить.
    * Если пользователь согласен, сохраняет.
    * Вызывать когда нужно спросить у пользователя разрешение на закрытие окна и т.д.
    * \return true - можно продолжать, false - отменить операцию
    */
    bool CanForget();

    /*!
    * Обработчик события закрытия главного окна.
    * При наличии несохраненных изменений предлагает их сохранить.
    * \param [in] event указатель на класс-событие закрытия окна
    */
    void closeEvent(QCloseEvent *event);

private:
    Ui::TouristBookMainWindowClass ui;

    JourneyDatabase* db = nullptr; //база данных, с которой сейчас работаем

    int current = -1; //индекс текущей показываемой записи

    QTextCodec* c; //класс для настройки кодировок

    bool blocked = false; // флаг запрета выключения элементов управления

    QString placeOld; //старое место отдыха. для определения факта изменения введенного текста

    //QString fileName; //имя и путь к текущуму файлу

    QTimer *timer;

    HANDLE hPipe;

private slots:
    /*!
    * Слот, реагирующий на смену фокуса и автоматически сохраняющий введенные данные
    * \param [in] old указатель на виджет, потерявший фокус
    * \param [in] new указатель на виджет, получивший фокус
    */
    void focusChanged(QWidget* old, QWidget* now);

    /*!
    * Слот, реагирующий на смену текущей страны. Активирует или деактивирует визовый флажок.
    * \param [in] index индекс текущей страны
    */
    void countryChanged(int index);

    /*!
    * Слот, добавляющий 10 тестовых записей (кнопка "Заполнить").
    */
    void GenerateExampleRecords();

    /*!
    * Слот, показывающий выбранную в браузере запись
    * \param [in] row индекс выбранной строчки браузера
    */
    void CurrentItemChanged(int row);

    /*!
    * Слот, создающий (из записи по умолчанию) и показывающий на экране новую запись (кнопка "Создать").
    */
    void CreateRecord();

    /*!
    * Слот, удаляющий текущую запись и переходящий к другой (кнопка "Удалить").
    */
    void DeleteRecord();

    /*!
    * Слот, сохраняющий текущую БД в файл. (пункт "Сохранить")
    */
    void Save();

    /*!
    * Слот, открывающий новый файл и загружающий из него БД (пункт "Открыть...")
    */
    void OpenFile();

    void AutoSave();



};

#endif // TOURISTBOOKMAINWINDOW_H
