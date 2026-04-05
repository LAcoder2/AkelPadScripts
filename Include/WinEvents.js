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
    //PrintLog("startEvents")
    //PauseEventsFlag = false
    EventPool = Array(2200)       //инициализируем массив функций-событий      
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
function makeAELINEDATAwrp(pStruct, oStruct, fullInit){
    return oStruct = makeStructWrapper(pStruct, oStruct, (_X64 ? 48 : 32), fullInit, 
                                        "next", 0, 9, makeAELINEDATAwrp,
                                        "prev", (_X64 ? 8 : 4), 9, makeAELINEDATAwrp,
                                        "wpLine", (_X64 ? 16 : 8), 8,
                                        "nLineLen", (_X64 ? 24 : 12), 3,  
                                        "nLineBreak", (_X64 ? 28 : 16), 5,
                                        "nLineFlags", (_X64 ? 29 : 17), 5,
                                        "nReserved", (_X64 ? 30 : 18), 4,
                                        "nLineWidth", (_X64 ? 32 : 20), 3,
                                        "nSelStart", (_X64 ? 36 : 24), 3,
                                        "nSelEnd", (_X64 ? 40 : 28), 3
                                    )
} 
/*typedef struct {            // смещения (x64/x86)
  int nLine;                // 0/0      Номер строки в документе, начиная с нуля.
  AELINEDATA *lpLine;       // 8/4      Указатель на структуру AELINEDATA.
  int nCharInLine;          // 16/8     Позиция символа в строке.
} AECHARINDEX;              // 24/12    Общий размер.*/
function makeAECHARINDEXwrp(pStruct, oStruct, fullInit){
    return oStruct = makeStructWrapper(pStruct, oStruct, (_X64 ? 24 : 12), fullInit, 
                                        "nLine", 0, 3,
                                        "lpLine", (_X64 ? 8 : 4), 9, makeAELINEDATAwrp,
                                        "nCharInLine", (_X64 ? 16 : 8), 3
                                    )
} 
/*typedef struct {            // смещения (x64/x86)
  AECHARINDEX ciMin;        // 0/0      Индекс первого символа в диапазоне.
  AECHARINDEX ciMax;        // 24/12    Индекс последнего символа в диапазоне.
} AECHARRANGE;              // 48/24    Общий размер.*/
function makeAECHARRANGEwrp(pStruct, oStruct, fullInit){
    return oStruct = makeStructWrapper(pStruct, oStruct, (_X64 ? 48 : 24), fullInit, 
                                        "ciMin", 0, 6, makeAECHARINDEXwrp,
                                        "ciMax", (_X64 ? 24 : 12), 6, makeAECHARINDEXwrp
                                    )
} 
/*typedef struct {            // смещения (x64/x86)
  HWND hwndFrom;            // 0/0      Дескриптор окна‑источника.
  UINT_PTR idFrom;          // 8/4      Идентификатор источника.
  UINT code;                // 16/8     Код уведомления.
  AEHDOC docFrom;           // 24/12    Дескриптор документа. См. сообщение AEM_CREATEDOCUMENT.
} AENMHDR;                  // 32/16    Общий размер.*/
function makeAENMHDRwrp(pStruct, oStruct){
    return oStruct = makeStructWrapper(pStruct, oStruct, (_X64 ? 32 : 16), undefined, 
                                        "hwndFrom", 0, 2,
                                        "idFrom", (_X64 ? 8 : 4), 2,
                                        "code", (_X64 ? 16 : 8), 3,
                                        "docFrom", (_X64 ? 24 : 12), 2
                                    )
} 
/*typedef struct {            // смещения (x64/x86)
  INT_PTR cpMin;            // 0/0      Минимальное смещение.
  INT_PTR cpMax;            // 8/4      Максимальное смещение.
} CHARRANGE64;              // 16/8     Общий размер.*/
function makeCHARRANGE64wrp(pStruct, oStruct){
    return oStruct = makeStructWrapper(pStruct, oStruct, (_X64 ? 16 : 8)/*size*/, undefined, 
                                        "cpMin", 0, 2,
                                        "cpMax", (_X64 ? 8 : 4), 2
                                    )
} 
/*typedef struct {            // смещения (x64/x86)
  AENMHDR hdr;              // 0/0      Стандартный NMHDR.
  AECHARRANGE crSel;        // 32/16    Текущее выделение.
  AECHARINDEX ciCaret;      // 80/40    Позиция индекса символа курсора.
  DWORD dwType;             // 104/52   См. определения AETCT_*.
  BOOL bColumnSel;          // 108/56   Колоночное выделение.
  CHARRANGE64 crRichSel;    // 112/60   Текущее выделение (смещение RichEdit).
} AENTEXTCHANGE;            // 128/68   Общий размер.
*/
function makeAENTEXTCHANGEwrp(pStruct, oStruct, fullInit){
    return oStruct = makeStructWrapper(pStruct, oStruct, (_X64 ? 128 : 68)/*size*/, fullInit,
                                        "hdr", 0, 6, makeAENMHDRwrp,
                                        "crSel", (_X64 ? 32 : 16), 6, makeAECHARRANGEwrp,
                                        "ciCaret", (_X64 ? 80 : 40), 6, makeAECHARRANGEwrp,
                                        "dwType", (_X64 ? 104 : 52), 3, 
                                        "bColumnSel", (_X64 ? 108 : 56), 3,
                                        "crRichSel", (_X64 ? 112 : 60), 6, makeCHARRANGE64wrp
                                    )
} 

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
function makeAENTEXTINSERTwrp(pStruct, oStruct, fullInit){
    return oStruct = makeStructWrapper(pStruct, oStruct, (_X64 ? 208 : 108)/*size*/, fullInit,
                                        "hdr", 0, 6, makeAENMHDRwrp,
                                        "crSel", (_X64 ? 32 : 16), 6, makeAECHARRANGEwrp,
                                        "ciCaret", (_X64 ? 80 : 40), 6, makeAECHARINDEXwrp,
                                        "dwType", (_X64 ? 104 : 52), 3,
                                        "wpText", (_X64 ? 112 : 56), 8,  // указатель на wchar_t строку
                                        "dwTextLen", (_X64 ? 120 : 60), 2, // UINT_PTR - указатель/размер
                                        "nNewLine", (_X64 ? 128 : 64), 3,
                                        "bColumnSel", (_X64 ? 132 : 68), 3,
                                        "dwInsertFlags", (_X64 ? 136 : 72), 3,
                                        "crAkelRange", (_X64 ? 144 : 76), 6, makeAECHARRANGEwrp,
                                        "crRichRange", (_X64 ? 192 : 100), 6, makeCHARRANGE64wrp
                                    )
}