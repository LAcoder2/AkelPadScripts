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
    PrintLog('stopEvents')
    var hScript = AkelPad.ScriptHandle(WScript.ScriptName, 3 /*SH_FINDSCRIPT*/)
    if (AkelPad.ScriptHandle(hScript, 13 /*SH_GETMESSAGELOOP*/)){                   // Скрипт уже работает.      
        //PrintLog("Останавливаем очередь сообщений")                                 // Логируем и закрываем.
        AkelPad.ScriptHandle(hScript, 33 /*SH_CLOSESCRIPT*/)
        // Повторно запущенный скрипт останавливает очередь сообщений в предыдущей запущенной копии и останавливается сам)
        if (hScript !== AkelPad.ScriptHandle(0, 2 /*SH_THISSCRIPT*/)){
            //PrintLog("Остановка очереди сообщений из другой копии скрипта")
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
    EventPool = []       // массив функций-событий      
    for (var i = 0; i < arguments.length; i += 2){     
        EventPool[arguments[i]] = arguments[i+1]    
    }
    
    //PrintLog("Запуск скрипта. Начинаем подклассирование...")
    //Подклассируем ГЛАВНОЕ окно (для режима SDI и глобальных событий)
    hSubClassMain = AkelPad.WindowSubClass(1/*WSC_MAINPROC*/, MainCallback, WM_NOTIFY)
    /*if (hSubClassMain)
        PrintLog("Успешно: MainCallback подключен (WSC_MAINPROC)")         
    else
        PrintLog("Ошибка: MainCallback не подключен")*/
    
    //Подклассируем Фрейм/окно (для режимов MDI/PMDI)
    hSubClassFrame = AkelPad.WindowSubClass(3/*WSC_FRAMEPROC*/, EditCallback, WM_NOTIFY)  
    /*if (hSubClassFrame)
        PrintLog("Успешно: EditCallback подключен (WSC_FRAMEPROC)")
    else        
        PrintLog("Ошибка: EditCallback не подключен")*/
    
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

// Функции инициализации врапперов структур
/*typedef struct {            // смещения (x64/x86)
  struct _AELINEDATA *next; // 0/0      Указатель на следующую структуру AELINEDATA.
  struct _AELINEDATA *prev; // 8/4      Указатель на предыдущую структуру AELINEDATA.
  wchar_t *wpLine;          // 16/8     Текст строки, заканчивающийся NULL‑символом.
  int nLineLen;             // 24/12    Длина wpLine, не включая завершающий NULL‑символ.
  BYTE nLineBreak;          // 28/16    Новая строка: AELB_EOF, AELB_R, AELB_N, AELB_RN, AELB_RRN или AELB_WRAP.
  BYTE nLineFlags;          // 29/17    Зарезервировано.
  WORD nReserved;           // 30/18    Зарезервировано.
  int nLineWidth;           // 32/20    Ширина строки в пикселях.
  int nSelStart;            // 36/24    Начальная позиция символа выделения в строке.
  int nSelEnd;              // 40/28    Конечная позиция символа выделения в строке.
} AELINEDATA;               // 48/32    Общий размер.*/
 
/*typedef struct {            // смещения (x64/x86)
  int nLine;                // 0/0      Номер строки в документе, начиная с нуля.
  AELINEDATA *lpLine;       // 8/4      Указатель на структуру AELINEDATA.
  int nCharInLine;          // 16/8     Позиция символа в строке.
} AECHARINDEX;              // 24/12    Общий размер.*/

/*typedef struct {            // смещения (x64/x86)
  AECHARINDEX ciMin;        // 0/0      Индекс первого символа в диапазоне.
  AECHARINDEX ciMax;        // 24/12    Индекс последнего символа в диапазоне.
} AECHARRANGE;              // 48/24    Общий размер.*/

/*typedef struct {            // смещения (x64/x86)
  HWND hwndFrom;            // 0/0      Дескриптор окна‑источника.
  UINT_PTR idFrom;          // 8/4      Идентификатор источника.
  UINT code;                // 16/8     Код уведомления.
  AEHDOC docFrom;           // 24/12    Дескриптор документа. См. сообщение AEM_CREATEDOCUMENT.
} AENMHDR;                  // 32/16    Общий размер.*/

/*typedef struct {            // смещения (x64/x86)
  INT_PTR cpMin;            // 0/0      Минимальное смещение.
  INT_PTR cpMax;            // 8/4      Максимальное смещение.
} CHARRANGE64;              // 16/8     Общий размер.*/

/*typedef struct {            // смещения (x64/x86)
  AENMHDR hdr;              // 0/0      Стандартный NMHDR.
  AECHARRANGE crSel;        // 32/16    Текущее выделение.
  AECHARINDEX ciCaret;      // 80/40    Позиция индекса символа курсора.
  DWORD dwType;             // 104/52   См. определения AETCT_*.
  BOOL bColumnSel;          // 108/56   Колоночное выделение.
  CHARRANGE64 crRichSel;    // 112/60   Текущее выделение (смещение RichEdit).
} AENTEXTCHANGE;            // 128/68   Общий размер.
*/

/*typedef struct {            // смещения (x64/x86)
  AENMHDR hdr;              // 0/0      Стандартный NMHDR.
  AECHARRANGE crSel;        // 32/16    Зарезервировано. (выравнивание на 8 байт после 28 байт)
  AECHARINDEX ciCaret;      // 80/40    Зарезервировано. (28+48=76, выравнивание до 80)
  DWORD dwType;             // 104/52   См. определения AETCT_*. (80+24=104)
  const wchar_t *wpText;    // 112/56   Текст для вставки. (104+4=108, выравнивание до 112)
  UINT_PTR dwTextLen;       // 120/60   Длина текста.
  int nNewLine;             // 128/64   См. определения AELB_*. (120+8=128)
  BOOL bColumnSel;          // 132/68   Колоночное выделение.
  DWORD dwInsertFlags;      // 136/72   См. определения AEINST_*.
  AECHARRANGE crAkelRange;  // 144/76   Позиция вставки текста или диапазон после вставки. (136+4=140, выравнивание до 144)
  CHARRANGE64 crRichRange;  // 192/100  Позиция вставки или диапазон после вставки (смещение RichEdit). (144+48=192)
} AENTEXTINSERT;            // 208/108  Общий размер.*/
