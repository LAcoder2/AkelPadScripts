// Пример: диалог с ListBox и кнопкой

showListBoxDialog()
function showListBoxDialog() {
    var oSys = AkelPad.SystemFunction()
    var hMainWnd = AkelPad.GetMainWnd()
    var hInstDLL   = AkelPad.GetInstanceDll()
    var aItems = ["Элемент 1", "Элемент 2", "Элемент 3", "Элемент 4"]
    var nSelectedIndex = -1

    // 1. Регистрация класса окна (если нужно)
    var sClassName = "AkelPad::Scripts::ListBoxDialog"
    if (!AkelPad.WindowRegisterClass(sClassName)) {
        AkelPad.MessageBox(hMainWnd, "Не удалось зарегистрировать класс окна", "Ошибка", 16)
        return
    }

    // 2. Создание диалога
    var hWndDialog = oSys.Call(
        "user32::CreateWindowExW",
        0,                  // dwExStyle
        sClassName,         // lpClassName
        "Выбор элемента",   // lpWindowName
        0x90C80000,         // WS_POPUP | WS_CAPTION | WS_SYSMENU | WS_VISIBLE
        100, 100, 300, 250, // x, y, width, height
        hMainWnd,           // hWndParent
        0,                  // ID
        hInstDLL,           // hInstance
        DialogCallback      // Callback-функция
    )

    if (!hWndDialog) {
        AkelPad.MessageBox(hMainWnd, "Не удалось создать диалог", "Ошибка", 16)
        AkelPad.WindowUnregisterClass(sClassName)
        return
    }

    // 3. Запуск цикла обработки сообщений (для модального диалога)
    AkelPad.ScriptNoMutex(); // Разрешить выполнение других скриптов
    AkelPad.WindowGetMessage(); // Цикл сообщений

    // 4. Получение результата и очистка
    AkelPad.WindowUnregisterClass(sClassName)
    if (nSelectedIndex >= 0) {
        AkelPad.MessageBox(hMainWnd, "Выбрано: " + aItems[nSelectedIndex], "Результат", 64)
    }

    // --- Callback-функция для обработки сообщений диалога ---
    function DialogCallback(hWnd, uMsg, wParam, lParam) {
        switch (uMsg) {
        case 1: // WM_CREATE
            // Создание ListBox
            var hWndListBox = oSys.Call(
                "user32::CreateWindowExW",
                0x200,              // WS_EX_CLIENTEDGE
                "LISTBOX",          // lpClassName
                0,                  // lpWindowName
                0x50B00000,         // WS_VISIBLE | WS_CHILD | WS_VSCROLL | LBS_NOTIFY
                10, 10, 260, 180,   // x, y, width, height
                hWnd,               // hWndParent
                1001,               // ID
                hInstDLL,
                0
            )
            // Заполнение ListBox
            for (var i = 0; i < aItems.length; i++) {
                AkelPad.SendMessage(hWndListBox, 0x0180/*LB_ADDSTRING*/, 0, aItems[i])
            }

            // Создание кнопки "OK"
            oSys.Call("user32::CreateWindowExW",
                0,
                "BUTTON",
                "OK",
                0x50010001,         // WS_VISIBLE | WS_CHILD | WS_TABSTOP | BS_DEFPUSHBUTTON
                110, 200, 80, 30,   // x, y, width, height
                hWnd,
                1002,               // IDOK
                hInstDLL,
                0
            )
            break

        case 273: // WM_COMMAND
            var nCtrlId = wParam & 0xFFFF
            var nNotifyCode = (wParam >> 16) & 0xFFFF

            if (nCtrlId == 1001 && nNotifyCode == 1 /*LBN_SELCHANGE*/) {
                // Сохранение выбора при изменении выделения
                nSelectedIndex = AkelPad.SendMessage(hWndListBox, 0x0188 /*LB_GETCURSEL*/, 0, 0)
            }
            else if (nCtrlId == 1002) { // IDOK
                // Закрытие диалога
                oSys.Call("user32::DestroyWindow", hWnd)
            }
            break

        case 16: // WM_CLOSE
            oSys.Call("user32::DestroyWindow", hWnd)
            break

        case 2: // WM_DESTROY
            oSys.Call("user32::PostQuitMessage", 0)
            break
        }
        return 0
    }
}