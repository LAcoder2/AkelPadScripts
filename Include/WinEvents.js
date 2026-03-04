var hMainWnd = AkelPad.GetMainWnd()
var hWndEdit = AkelPad.GetEditWnd()
AkelPad.Include("log.js") 
var WM_NOTIFY = 0x4E
var dwTypeOff = _X64 ? 104 : 52            
var hSubClassMain
var hSubClassFrame
var EventPool
var PauseEventsFlag
//var minMsg = 0x805 
//var maxMsg = 0

// Остановка скрипта при повторном запуске 
//stopEvents() 
function stopEvents(){
    var hScript = AkelPad.ScriptHandle(WScript.ScriptName, 3 /*SH_FINDSCRIPT*/)
    if (AkelPad.ScriptHandle(hScript, 13 /*SH_GETMESSAGELOOP*/)){                   // Скрипт уже работает.      
        PrintLog("Останавливаем очередь сообщений")                                 // Логируем и закрываем.
        AkelPad.ScriptHandle(hScript, 33 /*SH_CLOSESCRIPT*/)
        // Повторно запущенный скрипт останавливает очередь сообщений в предыдущей запущенной копии и останавливается сам)
        if (hScript !== AkelPad.ScriptHandle(0, 2 /*SH_THISSCRIPT*/)){
            PrintLog("Остановка очереди сообщений из другой копии скрипта")
        }
        if (hSubClassFrame) AkelPad.WindowUnsubClass(3); hSubClassFrame = 0
        if (hSubClassMain) AkelPad.WindowUnsubClass(1); hSubClassMain = 0
        return true        
    }
//    return undefined // по умолчанию       
}

function startEvents(){
    PrintLog("startEvents")
    //PauseEventsFlag = false
    EventPool = Array(2200)       //инициализируем массив функций-событий      
    for (var i = 0; i < arguments.length; i += 2){     
        EventPool[arguments[i]] = arguments[i+1]    
    }
    
    PrintLog("Запуск скрипта. Начинаем подклассирование...")
    //Подклассируем ГЛАВНОЕ окно (для режима SDI и глобальных событий)
    hSubClassMain = AkelPad.WindowSubClass(1/*WSC_MAINPROC*/, MainCallback, WM_NOTIFY)
    if (hSubClassMain)
        PrintLog("Успешно: MainCallback подключен (WSC_MAINPROC)")         
    else
        PrintLog("Ошибка: MainCallback не подключен")
    
    //Подклассируем Фрейм/окно (для режимов MDI/PMDI)
    hSubClassFrame = AkelPad.WindowSubClass(3/*WSC_FRAMEPROC*/, EditCallback, WM_NOTIFY)  
    if (hSubClassFrame)
        PrintLog("Успешно: EditCallback подключен (WSC_FRAMEPROC)")
    else        
        PrintLog("Ошибка: EditCallback не подключен")
    
    if (hSubClassMain){
        AkelPad.ScriptNoMutex()               // Разрешаем работу других скриптов и разблокируем поток d _
        
        PrintLog("Скрипт перешел в резидентный режим. Ожидание событий...\n")        
        AkelPad.WindowGetMessage()            // Запускаем цикл обработки сообщений
                                              // Сюда попадаем только при выходе
        if (hSubClassFrame) AkelPad.WindowUnsubClass(3); hSubClassFrame = 0
        if (hSubClassMain) AkelPad.WindowUnsubClass(1); hSubClassMain = 0
        PrintLog("Подкласирование отключено")
    }
}

// ---------------------------------------------------------
// Обработчик сообщений главного окна (SDI Mode)
// ---------------------------------------------------------
function MainCallback(hWnd, uMsg, wParam, lParam){
    //PrintLog("MainCallback")
    //var hWndEdit2 = AkelPad.GetEditWnd() 
    //PrintLog(hWndEdit + " " + hWndEdit2)
    //ProcessEvent(hSubClassMain, hWnd, uMsg, wParam, lParam)  
        
    return 0;
}
// ---------------------------------------------------------
// Обработчик сообщений окна редактора (MDI/PMDI Mode)  
// ---------------------------------------------------------
function EditCallback(hWnd, uMsg, wParam, lParam){
    //PrintLog("EditCallback") 
    ProcessEvent(hSubClassFrame, hWnd, wParam, lParam)
    
    return 0
}

// ---------------------------------------------------------
// Основная логика обработки событий 
// ---------------------------------------------------------
function ProcessEvent(hSubClass, hWnd, wParam, lParam){
    //PrintLog("ProcessEvent")
    // Считываем код события из структуры NMHDR
    // NMHDR: hwndFrom (ptr), idFrom (ptr), code (int)    
    var nCode = AkelPad.MemRead(_PtrAdd(lParam, _X64 ? 16 : 8), 3 /*DT_DWORD*/); // code находится по смещению sizeof(ptr)*2
    
    //PrintLog("nCode = " + nCode)
    //if (nCode < -1) PrintLog("!!!nCode = " + nCode)  
    if (PauseEventsFlag)
        if (nCode !== 0x802/*AEN_SETFOCUS*/) return 
        
    var fnEvent = EventPool[nCode]
    if(fnEvent){
        fnEvent(lParam)                 //выполняем функцию-событие     
        
        AkelPad.WindowNextProc(hSubClass, hWnd, uMsg, wParam, lParam)
        AkelPad.WindowNoNextProc(hSubClass)
    }   
}

// ---------------------------------------------------------
// Вспомогательные функции
// ---------------------------------------------------------
function getLineStartPos(hWnd, nPos){    
    var nLine = AkelPad.SendMessage(hWnd, 1078 /*EM_EXLINEFROMCHAR*/, 0, nPos)
    return AkelPad.SendMessage(hWnd, 187 /*EM_LINEINDEX*/, nLine, 0)  
}
function getLineText(hWnd, nPos){
    var nLine = AkelPad.SendMessage(hWnd, 1078 /*EM_EXLINEFROMCHAR*/, 0, nPos)
    var nLineStart = AkelPad.SendMessage(hWnd, 187 /*EM_LINEINDEX*/, nLine, 0)
    var nLineLength = AkelPad.SendMessage(hWnd, 193 /*EM_LINELENGTH*/, nLineStart, 0)
    return AkelPad.GetTextRange(nLineStart, nLineStart + nLineLength - 1)
}   
