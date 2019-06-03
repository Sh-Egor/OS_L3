#include "touristbookmainwindow.h"


/*!
* Конструктор класса окна
*/
TouristBookMainWindow::TouristBookMainWindow(QWidget *parent, Qt::WindowFlags flags)
: QMainWindow(parent, flags)
{
    ui.setupUi(this);

    //готовим перевод кодировок
    c = QTextCodec::codecForLocale();

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    CreateProcessA("TouristBookServer.exe", nullptr, nullptr,nullptr, FALSE, CREATE_NEW_CONSOLE,nullptr, nullptr, &si, &pi);

    //подключаем виджеты
    connect(ui.BrowserView, SIGNAL(currentRowChanged(int)), this, SLOT(CurrentItemChanged(int))); //показ выбранной в браузере записи
    connect(ui.CountryBox, SIGNAL(currentIndexChanged(int)), this, SLOT(countryChanged(int))); //управление визовым флажком
    //connect(ui.GenerateButton, SIGNAL(clicked()), this, SLOT(GenerateExampleRecords())); //кнопка "Заполнить"
    connect(ui.CreateButton, SIGNAL(clicked()), this, SLOT(CreateRecord())); //кнопка "Создать"
    connect(ui.DeleteButton, SIGNAL(clicked()), this, SLOT(DeleteRecord())); //кнопка "Удалить"

    //подключение валидатора для строки места отдыха
    QValidator *val=new PlaceOfRestValidator(this);
    ui.RecreationPlaceEdit->setValidator(val);
    Sleep(500);

    while (1) {
        Sleep(1000);
        hPipe = CreateFileA("\\\\.\\pipe\\touristbookpipe\\", GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
        if (hPipe != INVALID_HANDLE_VALUE)
            break;


    }

    DWORD mode = PIPE_READMODE_MESSAGE | PIPE_WAIT;
    SetNamedPipeHandleState(hPipe, &mode, nullptr, nullptr);

    //создание новой БД и открытие файла
    db = new JourneyDatabase(hPipe);
    OpenFile();

    //настройка таймера автосохранения
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(AutoSave()));
    timer->start(5000);

    if (db->count() > 0)
        ui.BrowserView->setCurrentRow(0);

}

/*!
* Деструктор класса окна
*/
TouristBookMainWindow::~TouristBookMainWindow()
{

    //при закрытии окна уничтожаем БД
    if (db!=nullptr)
        delete db;

}


void TouristBookMainWindow::AutoSave()
{
    db->save();
    ui.autoSaveTime->setTime(QTime::currentTime());
}

/*!
* Обработчик события закрытия главного окна.
* При наличии несохраненных изменений предлагает их сохранить.
* \param [in] event указатель на класс-событие закрытия окна
*/
void TouristBookMainWindow::closeEvent(QCloseEvent *event)
{
    Save();
    DWORD read, written;
    queries query = _close;
    WriteFile(hPipe, &query, sizeof(query), &read, nullptr);
    bool s;
    ReadFile(hPipe, &s, sizeof(bool), &written, nullptr);
    CloseHandle(hPipe);
    event->accept();
}

/*!
* Функция проверяет наличие несохраненных изменений и предлагает их сохранить.
* Если пользователь согласен, сохраняет.
* Вызывать когда нужно спросить у пользователя разрешение на закрытие окна и т.д.
* \return true - можно продолжать, false - отменить операцию
*/
bool TouristBookMainWindow::CanForget()
{
    //если у нас нету БД или нет несохраненных изменений
    if (db == nullptr || !db->isModified())
    {
        //можно продолжать
        return true;
    }

    //спрашиваем
    QMessageBox::StandardButton btn = QMessageBox::question(this, c->toUnicode("Справочник туриста"), \
        c->toUnicode("Вы хотите сохранить изменения? \n При продолжении действия они будут потеряны!"), \
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    //в зависимости от выбранной кнопки
    switch (btn)
    {
    case QMessageBox::Yes:  //"Да"
        Save();      //сохраняем
        return true; //можно продолжать

    case QMessageBox::No: //"Нет"
        return true; //можно продолжать

    case QMessageBox::Cancel: //"Отмена"
        return false;  //отменить дейстиве

    default: //какая-то непонятная кнопка?!
        return false; //лучше отменим

    }

}


/*!
* Функция показывает сохраненные значения текущей записи в виджетах
* \param [in] curr индекс записи в базе данных
*/
void TouristBookMainWindow::ShowValues(int curr)
{
    //берем текущую запись браузера
    QListWidgetItem *item = ui.BrowserView->currentItem();

    //достаем из нее ID
    int currID = ui.BrowserView->currentItem()->data(Qt::UserRole).toInt(); //ID текущей записи

    Journey toShow;
    toShow.data = db->record(currID); //запись в БД, которую мы выводим
    //db->record(currID, toShow); //достаем ее из БД

    //ниже присваиваем виджетам окна значения из текущей записи в базе данных
    ui.KindOfRecreationBox->setCurrentIndex(toShow.data.kindOfRecreationIndex); //вид отдыха

    ui.CountryBox->setCurrentIndex(toShow.data.countryIndex); //страна
    countryChanged(toShow.data.countryIndex); //настраиваем соответствующий флажок о визе

    ui.RecreationPlaceEdit->setText(toShow.data.recreationPlace); //место отдыха
    ui.TicketCost->setValue(toShow.data.ticketCost); //цена
    ui.Duration->setValue(toShow.data.duration); //длительность
    ui.VisaCheckBox->setChecked(toShow.data.NeedVisa); //виза

}

/*!
* Слот, показывающий выбранную в браузере запись
* \param [in] row индекс выбранной строчки браузера
*/
void TouristBookMainWindow::CurrentItemChanged(int row)
{
    //если работа слота запрещена, выйти
    if (blocked)
    {
        return;
    }

    // если это корректный индекс записи
    if (row >= 0)
    {
        current = row;    //выставляем текущий индекс в БД
        ui.BrowserView->setCurrentRow(current); // и в браузере
        ShowValues(current);  //выводим на экран содержимое записи
    }
    else
    {
        //если поступил сигнал об отсутствии записей и данное действие не запрещено
        //выключаем кнопку "Удалить" и поля ввода
        ChangeWidgetsMode(NO_RECORDS);
    }
}

/*!
* Слот, реагирующий на смену фокуса и автоматически сохраняющий введенные данные
* \param [in] old указатель на виджет, потерявший фокус
* \param [in] new указатель на виджет, получивший фокус
*/
void TouristBookMainWindow::focusChanged(QWidget* old, QWidget* now)
{

    //сравниваем old и каждый из наших виджетов
    if (old == ui.KindOfRecreationBox)
    {
        //сохраняем индекс вида отдыха
        ui.BrowserView->currentItem()->data(Qt::UserRole);
        int newIndex = db->update(ui.BrowserView->currentItem()->data(Qt::UserRole).toInt(), "kind", QString::number(ui.KindOfRecreationBox->currentIndex()));
        //обновляем и перемещаем эту запись в браузере
        UpdateBrowser(newIndex);
    }

    else if (old == ui.CountryBox)
    {
        //сохраняем индекс страны
        int newIndex = db->update(ui.BrowserView->currentItem()->data(Qt::UserRole).toInt(), "country", QString::number(ui.CountryBox->currentIndex()));
        //обновляем и перемещаем эту запись в браузере
        UpdateBrowser(newIndex);
    }

    else if (old == ui.RecreationPlaceEdit)
    {
        //сохраняем место отдыха и проверяем на корректность
        if (ui.RecreationPlaceEdit->hasAcceptableInput())
        {
            //если место отдыха корректно, сохраняем его в БД
            int newIndex = db->update(ui.BrowserView->currentItem()->data(Qt::UserRole).toInt(), "place", ui.RecreationPlaceEdit->text());
            //обновляем запись в браузере
            UpdateBrowser(newIndex);
        }
        else
        {
            //если некорректно, выдаем сообщение об ошибке
            // если не изменилось, нет смысла выводить сообщение
            if (placeOld != ui.RecreationPlaceEdit->text())
            {
                QMessageBox::warning(this, c->toUnicode("Ошибка"), c->toUnicode("Место отдыха должно быть с большой буквы. Не сохранено!"));
            }
            ui.RecreationPlaceEdit->setFocus(); //возвращаем фокус на поле ввода обратно
        }
        //сохраняем текст в переменную placeOld
        //для проверки на факт изменения ввода
        placeOld = ui.RecreationPlaceEdit->text();
    }

    else if (old == ui.TicketCost)
    {
        //стоимость билета
        int newIndex = db->update(ui.BrowserView->currentItem()->data(Qt::UserRole).toInt(), "cost", QString::number(ui.TicketCost->value()));
        //обновляем запись в браузере
        UpdateBrowser(newIndex);
    }

    else if (old == ui.Duration)
    {
        //длительность отдыха
        db->update(ui.BrowserView->currentItem()->data(Qt::UserRole).toInt(), "duration", QString::number(ui.Duration->value()));
    }

    else if (old == ui.VisaCheckBox)
    {
        //нужна ли виза
        db->update(ui.BrowserView->currentItem()->data(Qt::UserRole).toInt(), "visaflag", QString::number((int)ui.VisaCheckBox->isChecked()));
    }

}

/*!
* Слот, реагирующий на смену текущей страны. Активирует или деактивирует визовый флажок.
* \param [in] index индекс текущей страны
*/
void TouristBookMainWindow::countryChanged(int index)
{
    //если Россия - виза не нужна
    //Россия под индексом 0
    if (index == 0)
    {
        //сбрасываем и выключаем флажок
        ui.VisaCheckBox->setChecked(false);
        db->update(ui.BrowserView->currentItem()->data(Qt::UserRole).toInt(), "visaflag", nullptr);
        ui.VisaCheckBox->setEnabled(false);
    }
    else
    {
        //для других стран может понадобиться
        //включаем флажок обратно
        ui.VisaCheckBox->setEnabled(true);
    }
}

/*!
* Слот, добавляющий 10 тестовых записей (кнопка "Заполнить").
*/
void TouristBookMainWindow::GenerateExampleRecords()
{

    Journey examples[10] =  //10 записей-образцов
    {
        { 2, 0, c->toUnicode("Москва"), 5555  , 7, false },
        { 1, 1, c->toUnicode("Сухуми"), 6666, 4, false },
        { 0, 2, c->toUnicode("Сочи"), 9999, 6, true },
        { 7, 1, c->toUnicode("Анапа"), 8888, 31, false },
        { 4, 3, c->toUnicode("Шарм-Аль-Шейх"), 4444, 15, true },
        { 3, 0, c->toUnicode("Припять"), 3333, 7, false },
        { 5, 1, c->toUnicode("Стамбул"), 6565, 18, false },
        { 4, 3, c->toUnicode("Каир"), 6767, 2, true },
        { 4, 0, c->toUnicode("Анталья"), 88888, 9, false },
        { 4, 2, c->toUnicode("Анкара"), 7777, 3, false }

    };

    //цикл добавляет все записи из массива выше в браузер и БД
    for (int i = 0; i < 10; i++)
    {
        newRecordData recordData = db->append(examples[i].data);
        examples[i].data.ID = recordData.new_id;
        AddToBrowser(examples[i], recordData.pos);
    }

    //переходим в режим работы с записями (выключаем "Заполнить")
    ChangeWidgetsMode(HAS_RECORDS);

    //делаем текущей первую запись
    ui.BrowserView->setCurrentRow(0);

}

/*!
* Слот, создающий (из записи по умолчанию) и показывающий на экране новую запись (кнопка "Создать").
*/
void TouristBookMainWindow::CreateRecord()
{

    ChangeWidgetsMode(HAS_RECORDS); //разблокируем элементы управления

    Journey def; //запись "по умолчанию"
    newRecordData recordData = db->append(def.data);

    current = recordData.pos;  //добавляем запись по умолчанию в БД
    def.data.ID = recordData.new_id;

    AddToBrowser(def, current); //добавляем в браузер


    blocked = true; //блокируем работу слота CurrentItemChanged
    ui.BrowserView->setCurrentRow(current); //делаем текущей
    ShowValues(current); //выводим значения
    blocked = false; //разблокируем слот обратно

}

/*!
* Слот, удаляющий текущую запись и переходящий к другой (кнопка "Удалить").
*/
void TouristBookMainWindow::DeleteRecord()
{
    int positionToDelete = current; //запоминаем позицию удаляемого элемента
                                    //current может быть изменено каким-либо другим слотом!

    //достаем ID и удаляем текущую запись из БД
    db->remove(ui.BrowserView->currentItem()->data(Qt::UserRole).toInt());

    //убираем эту запись из браузера
    QListWidgetItem *item = ui.BrowserView->takeItem(current);
    delete item;

    //если удаляем последний элемент, текущим становится предыдущий
    if (positionToDelete == db->count())
    {
        positionToDelete--;
    }

    current = positionToDelete;   //возвращаем current на место

    ui.BrowserView->setCurrentRow(current); // делаем ее активной в браузере

    //если есть хоть одна запись
    if (current != -1)
    {
        //выводим ее на экран
        ShowValues(current);
    }

}

/*!
* Функция обновляет текст и местоположение в браузере измененной записи
*/
void TouristBookMainWindow::UpdateBrowser(int newIndex)
{
    blocked = true; //блокируем деактивацию виджетов (глюки при 1 записи)

    QListWidgetItem *item = ui.BrowserView->takeItem(current); //убираем текущую запись из браузера
    int UpdatingID = item->data(Qt::UserRole).toInt();  //запоминаем ее ID
    delete item;                                        //уничтожаем запись

    //берем запись из БД
    Journey temp;
    temp.data = db->record(UpdatingID);
    //db->record(UpdatingID, temp);

    AddToBrowser(temp, newIndex); //добавляем в браузер

    //делаем текущей в классе и браузере
    current = newIndex;
    ui.BrowserView->setCurrentRow(current);

    ShowValues(current); //выводим на экран

    blocked = false; //разблокируем обратно

}

/*!
* Переключает режимы "редактирование", "приглашение на добавление новых записей", "отсутствие БД"
* \param [in] status текущий режим. true - редактирование, false - добавление
*/
void TouristBookMainWindow::ChangeWidgetsMode(widgetsState status)
{

    // вкл/выкл кнопки сохранения
    ui.Save->setEnabled(status != NO_DB);
    ui.SaveAs->setEnabled(status != NO_DB);

    //конпка "Создать запись"
    ui.CreateButton->setEnabled(status != NO_DB);

    //вкл/выкл "Заполнить"
    //ui.GenerateButton->setEnabled(status == NO_RECORDS);

    //вкл/выкл кнопку удаления
    ui.DeleteButton->setEnabled(status == HAS_RECORDS);

    //вкл/выкл. виджеты ввода данных
    ui.RecordBox->setEnabled(status == HAS_RECORDS);


}

/*!
* Вставляет запись в браузер
* \param [in] record ссылка на экземпляр класса-записи
* \param [in] index индекс для вставки
*/
void TouristBookMainWindow::AddToBrowser(const Journey &record, int index)
{
    //создаем на основе записи текст для ее отображения в браузере
    QString browserText = GenerateBrowserText(record);

    //создаем новый элемент с заданным текстом и вставляем его в браузер на положенное место
    QListWidgetItem *newItem = new QListWidgetItem;
    newItem->setText(browserText);
    newItem->setData(Qt::UserRole, record.data.ID);  //присваиваем полю браузера ID
    ui.BrowserView->insertItem(index, newItem);
}

/*!
* Функция генерирует строку для показа в браузере на основании переданной записи
* \param [in] record ссылка на экземпляр класса Journey - запись в БД
* \return сгенерированная строка
*/
QString TouristBookMainWindow::GenerateBrowserText(const Journey &record) const
{
    //формат: "вид отдыха место стоимость"

    QString divider; //разделитель между

    //если длина текста с местом отдыха больше 12
    //подбираем соответствующее кол-во табов
    if (record.data.recreationPlace.length() > 12)
    {
        divider = "\t";
    }
    else
    {
        divider = "\t\t";
    }

    //формируем текст для записи
    QString browserText = ui.KindOfRecreationBox->itemText(record.data.kindOfRecreationIndex) + "\t\t";
    browserText += record.data.recreationPlace + divider + QString::number(record.data.ticketCost);

    return browserText;
}

/*!
* Слот, сохраняющий текущую БД в файл. (пункт "Сохранить")
*/
void TouristBookMainWindow::Save()
{
    //сохраняем
    if (!db->save())
    {
        //если не получилось, выводим сообщение об ошибке
        QMessageBox::critical(this, c->toUnicode("Ошибка"), c->toUnicode("Ошибка сохранения файла!"));
    }
}


/*!
* Слот, открывающий новый файл и загружающий из него БД (пункт "Открыть...")
*/
void TouristBookMainWindow::OpenFile()
{

    ChangeWidgetsMode(NO_RECORDS); //включаем нужные виджеты

    // загружаем данные в БД
    if (!db->load())
    {
        //если неудача, сообщение об ошибке и закрытие окна
        QMessageBox::critical(this, c->toUnicode("Ошибка"), c->toUnicode("Ошибка открытия файла!"));
        this->close();
        return;
    }

    ui.BrowserView->clear();  //очищаем браузер

    browserItemData *arr = new browserItemData[db->count()];
     //берем сведения для заполнения браузера
    int size = db->records(arr); //индекс в браузере текущей записи

    // пока есть записи в БД, добавляем их в браузер
    for (int i = 0; i < size; i++)
    {
        Journey tempRecord; // временная запись
        browserItemData tempStruct = arr[i];  //берем структуру с информацией

        // заполняем временную запись
        tempRecord.data.kindOfRecreationIndex = tempStruct.kindIndex;
        tempRecord.data.recreationPlace = tempStruct.place;
        tempRecord.data.ticketCost = tempStruct.cost;
        tempRecord.data.ID = tempStruct.ID;

        //передаем ее функции формирования поля в браузере
        AddToBrowser(tempRecord, i);

    }

    delete[] arr;

    //если файл был не пустой, включаем виджеты
    if (size > 0)
    {
        ChangeWidgetsMode(HAS_RECORDS);
    }

}
