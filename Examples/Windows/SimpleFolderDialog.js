// SimpleFolderDialog.js
// Простой диалог выбора папки с фиксированным размером
// При создании логики  окна и управляющих элементов был использован код скрипта FindReplaceFiles.js от KDJ
AkelPad.Include("log.js")
var oSys        = AkelPad.SystemFunction()
var hMainWnd    = AkelPad.GetMainWnd()
var hInstDLL    = AkelPad.GetInstanceDll()
var hGuiFont    = oSys.Call("Gdi32::GetStockObject", 17 /*DEFAULT_GUI_FONT*/)
var sClass      = "AkelPad::Scripts::" + WScript.ScriptName + "::" + hInstDLL
var hDlg

// Проверка на уже запущенный экземпляр
if (hDlg = oSys.Call("User32::FindWindowExW", 0, 0, sClass, 0)){
    SetForegroundWindow(hDlg)
    WScript.Quit()
}

// Размеры окна (фиксированные, в пикселях)
var nWndWidth  = 400
var nWndHeight = 150

// Идентификаторы элементов
var IDDIRG     = 2000
var IDDIRCB    = 2001
var IDBROWSEB  = 2002
var IDOKB      = 2003
var IDCANCELB  = 2004

// Массив описания элементов
var aDlg = []
aDlg[IDDIRG]    = {S:0x50000007, C:"BUTTON",   T:"Выберите папку"}
aDlg[IDDIRCB]   = {S:0x50210042, C:"COMBOBOX", T:""}
aDlg[IDBROWSEB] = {S:0x50010000, C:"BUTTON",   T:"Обзор..."}
aDlg[IDOKB]     = {S:0x50010000, C:"BUTTON",   T:"OK"}
aDlg[IDCANCELB] = {S:0x50010000, C:"BUTTON",   T:"Отмена"}

// Регистрация класса окна
AkelPad.WindowRegisterClass(sClass)

// Создание окна
hDlg = oSys.Call("User32::CreateWindowExW",
        0,               // dwExStyle
        sClass,          // lpClassName
        "Выбор папки",   // lpWindowName
        0x80CA0000,      // dwStyle: WS_POPUP|WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX
        200,             // x (позиция по центру экрана будет в ShowWindow)
        200,             // y
        nWndWidth,       // nWidth
        nWndHeight,      // nHeight
        hMainWnd,        // hWndParent
        0,               // hMenu
        hInstDLL,        // hInstance
        DialogCallback) // lpParam

// Показываем окно и запускаем цикл сообщений
oSys.Call("User32::ShowWindow", hDlg, 1 /*SW_SHOWNORMAL*/)
SetForegroundWindow(hDlg)
AkelPad.WindowGetMessage()

// Завершение скрипта после остановки обработки сообщений
AkelPad.WindowUnregisterClass(sClass)

// ------------------------------------------------------------
// Функция обработки сообщений
// ------------------------------------------------------------
function DialogCallback(hWnd, uMsg, wParam, lParam) {
    var nID, nCode
    var nX = 10, nY = 30, nW, nH

    switch(uMsg){
    case 1: // WM_CREATE
        // Создание всех элементов
        for (var i = 2000; i < aDlg.length; ++i){
            aDlg[i].HWND = oSys.Call("User32::CreateWindowExW",
                aDlg[i].ES, aDlg[i].C, aDlg[i].T, aDlg[i].S,
                0, 0, 0, 0, hWnd, i, hInstDLL, 0)

            SendMessage(aDlg[i].HWND, 48 /*WM_SETFONT*/, hGuiFont, true)
        }

        // Настройка комбобокса
        SendMessage(aDlg[IDDIRCB].HWND, 0x0141 /*CB_LIMITTEXT*/, 256, 0)
        SendMessage(aDlg[IDDIRCB].HWND, 0x0143 /*CB_ADDSTRING*/, 0, "C:\\")
        SendMessage(aDlg[IDDIRCB].HWND, 0x0143 /*CB_ADDSTRING*/, 0, "D:\\")
        SendMessage(aDlg[IDDIRCB].HWND, 0x014E /*CB_SETCURSEL*/, 0, 0)
        
        // Установка начального текста
        SetWindowText(aDlg[IDDIRCB].HWND, "C:\\")
        
        oSys.Call("User32::SetWindowPos", aDlg[IDDIRG].HWND, 0,
            10, 10, 380, 60, 0x0114 /*SWP_NOCOPYBITS|SWP_NOACTIVATE|SWP_NOZORDER*/)

        oSys.Call("User32::SetWindowPos", aDlg[IDDIRCB].HWND, 0,
            20, 30, 250, 200, 0x0114)

        oSys.Call("User32::SetWindowPos", aDlg[IDBROWSEB].HWND, 0,
            280, 30, 100, 23, 0x0114)

        oSys.Call("User32::SetWindowPos", aDlg[IDOKB].HWND, 0,
            200, 80, 80, 23, 0x0114)

        oSys.Call("User32::SetWindowPos", aDlg[IDCANCELB].HWND, 0,
            290, 80, 80, 23, 0x0114)
        break

    case 273: // WM_COMMAND
        nID   = LoWord(wParam)
        //nCode = HiWord(wParam)

        switch(nID){
        case IDBROWSEB:
            // Здесь можно вызвать BrowseForFolder
            AkelPad.MessageBox(hWnd, "Будет открыт диалог выбора папки", "Info", 0)
            break
        case IDOKB:
            var sPath = GetWindowText(aDlg[IDDIRCB].HWND)
            AkelPad.MessageBox(hWnd, "Выбрано: " + sPath, "Результат", 0)
            PostMessage(hWnd, 16 /*WM_CLOSE*/, 0, 0)
            break
        case IDCANCELB:
            PostMessage(hWnd, 16 /*WM_CLOSE*/, 0, 0)
            break
        case 2: //IDCANCEL
            PostMessage(hWnd, 16 /*WM_CLOSE*/, 0, 0)
            break
        }
        break

    case 16: // WM_CLOSE
        oSys.Call("User32::DestroyWindow", hWnd)
        break

    case 2: // WM_DESTROY
        oSys.Call("User32::PostQuitMessage", 0)
        break
    }
    
    return 0
}

// ------------------------------------------------------------
// Вспомогательные функции
// ------------------------------------------------------------
function LoWord(nParam) {
    return (nParam & 0xFFFF)
}
function HiWord(nParam) {
    return ((nParam >> 16) & 0xFFFF)
}
function SendMessage(hWnd, uMsg, wParam, lParam) {
    return AkelPad.SendMessage(hWnd, uMsg, wParam, lParam)
}
function PostMessage(hWnd, uMsg, wParam, lParam) {
    return oSys.Call("User32::PostMessageW", hWnd, uMsg, wParam, lParam)
}
function SetForegroundWindow(hWnd) {
    if (oSys.Call("User32::IsIconic", hWnd))
        oSys.Call("User32::ShowWindow", hWnd, 9 /*SW_RESTORE*/)
    oSys.Call("User32::SetForegroundWindow", hWnd)
}
//function GetWindowText(hWnd) {
//    var lpBuffer = AkelPad.MemAlloc(512)
//    oSys.Call("User32::GetWindowTextW", hWnd, lpBuffer, 256)
//    var sText = AkelPad.MemRead(lpBuffer, 1 /*DT_UNICODE*/)
//    AkelPad.MemFree(lpBuffer)
//    return sText
//}
// 
function GetWindowText(hWnd) {
    var sBuf = Array(257).join('\0') 
    var pBuf = AkelPad.MemStrPtr(sBuf)
    return (GetWindowText = function(hWnd){
        oSys.Call("User32::GetWindowTextW", hWnd, pBuf, 256)
        return AkelPad.MemRead(pBuf, 1 /*DT_UNICODE*/)
    })(hWnd)
}
function SetWindowText(hWnd, sText) {
    oSys.Call("User32::SetWindowTextW", hWnd, sText)
}