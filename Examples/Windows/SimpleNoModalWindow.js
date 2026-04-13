// DeepSeek готовое немодальное окошко с одной кнопкой.
// SimpleNoModalWindow.js
// Простое немодальное окно с одной кнопкой
var oSys       = AkelPad.SystemFunction()
var hMainWnd   = AkelPad.GetMainWnd()
var hInstDLL   = AkelPad.GetInstanceDll()
var hGuiFont   = oSys.Call("Gdi32::GetStockObject", 17 /*DEFAULT_GUI_FONT*/)

var sClass     = "AkelPad::Scripts::" + WScript.ScriptName + "::" + hInstDLL
var hDlg

// Проверка на уже запущенный экземпляр
if (hDlg = oSys.Call("User32::FindWindowExW", 0, 0, sClass, 0)){
    SetForegroundWindow(hDlg)
    WScript.Quit()
}

// Идентификатор кнопки
var IDMYBUTTON = 1001
// Размеры кнопки
var nBtnWidth  = 100
var nBtnHeight = 30
var nBtnX = 20
var nBtnY = 30
// Размеры окна (немного больше кнопки + отступы)
var nWndWidth  = nBtnWidth + 40;  // +40 пикселей на отступы по бокам
var nWndHeight = nBtnHeight + 60; // +60 пикселей на заголовок и отступы
var nWndX = 300
var nWndY = 300

// Регистрация класса окна
AkelPad.WindowRegisterClass(sClass)

// Создание окна
hDlg = oSys.Call("User32::CreateWindowExW",
                0,               // dwExStyle
                sClass,          // lpClassName
                "Моё окно",      // lpWindowName
                0x80CA0000,      // dwStyle: WS_POPUP|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX
                nWndX,           // x
                nWndY,           // y
                nWndWidth,       // nWidth
                nWndHeight,      // nHeight
                hMainWnd,        // hWndParent
                0,               // hMenu
                hInstDLL,        // hInstance
                DialogCallback)  // lpParam

// Показываем окно
oSys.Call("User32::ShowWindow", hDlg, 1 /*SW_SHOWNORMAL*/)
SetForegroundWindow(hDlg)

// Запускаем цикл сообщений (немодальное окно требует этого)
AkelPad.WindowGetMessage()

// Окончание обработки сообщений и завершение скрипта
AkelPad.WindowUnregisterClass(sClass)

// ------------------------------------------------------------
// Функция обработки сообщений
// ------------------------------------------------------------
function DialogCallback(hWnd, uMsg, wParam, lParam){
    switch (uMsg){
    case 1: /*WM_CREATE*/
        // Создаем кнопку
        var hBtn = oSys.Call("User32::CreateWindowExW",
                                0,                    // dwExStyle
                                "BUTTON",             // lpClassName
                                "Нажми меня",         // lpWindowName
                                0x50010000,           // dwStyle: WS_VISIBLE|WS_CHILD|WS_TABSTOP
                                nBtnX,                // x (20px от левого края)
                                nBtnY,                // y (30px от верхнего края под заголовком)
                                nBtnWidth,            // nWidth
                                nBtnHeight,           // nHeight
                                hWnd,                 // hWndParent
                                IDMYBUTTON,           // ID
                                hInstDLL,             // hInstance
                                0)                    // lpParam
        // Устанавливаем шрифт
        SendMessage(hBtn, 48 /*WM_SETFONT*/, hGuiFont, true)        
        break
    case 273: /*WM_COMMAND*/
        var nID = LoWord(wParam)

        if (nID == IDMYBUTTON)
            AkelPad.MessageBox(hWnd, "Кнопка нажата!", "Информация", 0)
        else if (nID == 2 /*IDCANCEL*/) // Закрытие по ESC
            PostMessage(hWnd, 16 /*WM_CLOSE*/, 0, 0)        
        break
    case 16: /*WM_CLOSE*/
        oSys.Call("User32::DestroyWindow", hWnd)        
        break
    case 2: /*WM_DESTROY*/
        oSys.Call("User32::PostQuitMessage", 0)
        break
    }

    return 0
}

// ------------------------------------------------------------
// Вспомогательные функции
// ------------------------------------------------------------
function LoWord(nParam){
    return (nParam & 0xFFFF)
}

function HiWord(nParam){
    return ((nParam >> 16) & 0xFFFF)
}

function SendMessage(hWnd, uMsg, wParam, lParam){
    return AkelPad.SendMessage(hWnd, uMsg, wParam, lParam)
}

function PostMessage(hWnd, uMsg, wParam, lParam){
    return oSys.Call("User32::PostMessageW", hWnd, uMsg, wParam, lParam)
}

function SetForegroundWindow(hWnd){
    if (oSys.Call("User32::IsIconic", hWnd))
        oSys.Call("User32::ShowWindow", hWnd, 9 /*SW_RESTORE*/)
    oSys.Call("User32::SetForegroundWindow", hWnd)
}