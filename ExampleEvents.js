//var hMainWnd = AkelPad.GetMainWnd()
//var hWndEdit = AkelPad.GetEditWnd()
AkelPad.Include("WinEvents.js")
AkelPad.Include("Coder.js")
AkelPad.Include("log.js")
AkelPad.Include("MemHelp.js")
var oSys = AkelPad.SystemFunction()
 /*Уведомления AkelEdit (0x702 - 0x836 1794 - 2102)
//Уведомления об ошибках
//    #define AEN_ERRSPACE              (WM_USER + 1001)  //WScript.Echo(0x7E9)
//Уведомления окна
//    #define AEN_SETFOCUS              (WM_USER + 1026)  //0x802
//    #define AEN_KILLFOCUS             (WM_USER + 1027)  //0x803
//    #define AEN_HSCROLL               (WM_USER + 1028)  //0x804
//    #define AEN_VSCROLL               (WM_USER + 1029)  //0x805
//    #define AEN_SETRECT               (WM_USER + 1030)  //0x806
//    #define AEN_PAINT                 (WM_USER + 1031)  //0x807
//Уведомления о тексте
//    #define AEN_MAXTEXT               (WM_USER + 1050)  //0x81A  (1024+1050=2074)
//    #define AEN_PROGRESS              (WM_USER + 1051)  //0x81B
//    #define AEN_MODIFY                (WM_USER + 1052)  //0x81C
//    #define AEN_SELCHANGING           (WM_USER + 1053)  //0x81D
//    #define AEN_SELCHANGED            (WM_USER + 1054)  //0x81E
//    #define AEN_TEXTCHANGING          (WM_USER + 1055)  //0x81F
//    #define AEN_TEXTINSERTBEGIN       (WM_USER + 1056)  //0x820
//    #define AEN_TEXTINSERTEND         (WM_USER + 1057)  //0x821
//    #define AEN_TEXTDELETEBEGIN       (WM_USER + 1058)  //0x822
//    #define AEN_TEXTDELETEEND         (WM_USER + 1059)  //0x823
//    #define AEN_TEXTCHANGED           (WM_USER + 1060)  //0x824
//    #define AEN_POINT                 (WM_USER + 1061)  //0x825  
*/
// При повторном запуске останавливаем обработку событий  
if (!stopEvents())
    TestEvents()
var nModifiedLine   // номер последней модифицированной строки, которая обрабатывается после перехода курсора в другую строку
var oTC             // объект-враппер структуры AENTEXTCHANGE
function TestEvents(){ 
    //PrintLog("TestEvents")   
    try{
        nModifiedLine = -1
        PrintLog(1)
        oTC = AENTEXTCHANGEwrp()
        //oTI = AENTEXTINSERTwrp()
        startEvents(0x802/*AEN_SETFOCUS*/,          OnSetFocus,
                    0x81C/*AEN_MODIFY*/,            OnChangeModifySatus,
                    0x81D/*AEN_SELCHANGING*/,       OnSelChanging,
                    0x81E/*AEN_SELCHANGED*/,        OnSelChanged,
                    0x81F/*AEN_TEXTCHANGING*/,      OnTextChanging,
                    0x820/*AEN_TEXTINSERTBEGIN*/,   OnTextInsertBegin,
                    0x821/*AEN_TEXTINSERTEND*/,     OnTextInsertEnd,
                    0x822/*AEN_TEXTDELETEBEGIN*/,   OnTextDeleteBegin,
                    0x823/*AEN_TEXTDELETEEND*/,     OnTextDeleteEnd,
                    0x824/*AEN_TEXTCHANGED*/,       OnTextChanged)
    } catch(e){
        PrintLog('TestEvents error: \n' + e.message)
    }
}

/* Описание структуры AENTEXTCHANGE и всех входящих в нее структур  
typedef struct {            // смещения (x64/x86)
  INT_PTR cpMin;            // 0/0      Минимальное смещение.
  INT_PTR cpMax;            // 8/4      Максимальное смещение.
} CHARRANGE64;              // 16/8     Общий размер.
typedef struct {            // смещения (x64/x86)
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
} AELINEDATA;               // 48/32    Общий размер.
typedef struct {            // смещения (x64/x86)
  int nLine;                // 0/0      Номер строки в документе, начиная с нуля.
  AELINEDATA *lpLine;       // 8/4      Указатель на структуру AELINEDATA.
  int nCharInLine;          // 16/8     Позиция символа в строке.
} AECHARINDEX;              // 24/12    Общий размер.
typedef struct {            // смещения (x64/x86)
  AECHARINDEX ciMin;        // 0/0      Индекс первого символа в диапазоне.
  AECHARINDEX ciMax;        // 24/12    Индекс последнего символа в диапазоне.
} AECHARRANGE;              // 48/24    Общий размер.
typedef struct {            // смещения (x64/x86)
  HWND hwndFrom;            // 0/0      Дескриптор окна‑источника.
  UINT_PTR idFrom;          // 8/4      Идентификатор источника.
  UINT code;                // 16/8     Код уведомления.
  AEHDOC docFrom;           // 20/12    Дескриптор документа. См. сообщение AEM_CREATEDOCUMENT.
} AENMHDR;                  // 28/16    Общий размер.
typedef struct {            // смещения (x64/x86)
  AENMHDR hdr;              // 0/0      Стандартный NMHDR.
  AECHARRANGE crSel;        // 28/16    Текущее выделение.
  AECHARINDEX ciCaret;      // 76/40    Позиция индекса символа курсора.
  DWORD dwType;             // 100/52   См. определения AETCT_*.
  BOOL bColumnSel;          // 104/56   Колоночное выделение.
  CHARRANGE64 crRichSel;    // 112/60   Текущее выделение (смещение RichEdit).
} AENTEXTCHANGE;            // 128/68   Общий размер.
*/

// ---------------------------------------------------------
// Функции - обработчики событий
// ---------------------------------------------------------
var nPrevSelStart, nPrevSelEnd, sPrevSelText, InsertFlag, MoveFlag, DeleteFlag //, nCurrentLine     

function OnSetFocus(lParam){
    //PrintLog("OnSetFocus") 
    hWndEdit = AkelPad.GetEditWnd()  //Получаем хэндл текущего окна/вкладки
    
    if (getSyntaxFile(hWndEdit) === "js.coder"){
        PauseEventsFlag = false
        PrintLog("В этом окне JScript, включаем автоматическую обработку ввода")
    }else{ 
        PauseEventsFlag = true 
        PrintLog("В этом окне не  JScript, отключаем автоматическую обработку ввода") 
    }           
}
function OnChangeModifySatus(lParam) {
    //PrintLog("AEN_MODIFY")
} 
function OnSelChanging(lParam){
    /*PrintLog("Начало выделения");*/
}   
function OnSelChanged(lParam){
    //PrintLog("Окончание выделения")
    return
    var nLine = getLineFromChar(AkelPad.GetSelStart()) 
    if (nModifiedLine > -1){ 
        if(nModifiedLine !== nLine) {
            PrintLog("  Вы освободили измененную строку: " +  (nModifiedLine + 1))  //45fff fdfdfdfd 
            nModifiedLine = -1
        }
    }
}

function OnTextChanging(lParam){
    //PrintLog("Перед изменением")
    return
    oTC.pStructSet(lParam)
    var dwType = oTC.dwType()
    var bColumnSel = oTC.bColumnSel()
    with(AkelPad){
        //var dwType = MemRead(_PtrAdd(lParam, dwTypeOff/*см. WitnEvents.js*/), 3/*DT_DWORD*/)          
        //var bColumnSel = MemRead(_PtrAdd(lParam, 108), 3/*DT_DWORD*/)     //флаг колоночного выделения  
//        var crRichSelMin = MemRead(_PtrAdd(lParam, 112), 2/*DT_QWORD*/)   
//        var crRichSelMax = MemRead(_PtrAdd(lParam, 112+8), 2/*DT_QWORD*/)                
        nPrevSelStart = GetSelStart()
        sPrevSelText = GetSelText()
    }
        
/* Описание флагов dwType (AETCT..)                      
        #define AETCT_REPLACESEL        0x00000001  //Замена выделения. 
        #define AETCT_APPENDTEXT        0x00000002  //Добавление текста.
        #define AETCT_SETTEXT           0x00000004  //Установка текста.
        #define AETCT_STREAMIN          0x00000008  //Потоковый ввод.
        #define AETCT_WRAP              0x00000010  //Отправка AEM_SETWORDWRAP.
        #define AETCT_UNDO              0x00000020  //Отмена действия.
        #define AETCT_REDO              0x00000040  //Повтор действия.
        #define AETCT_CUT               0x00000080  //Вырезание.
        #define AETCT_CHAR              0x00000100  //Вставка символа.
        #define AETCT_KEYRETURN         0x00000200  //Нажатие VK_RETURN.
        #define AETCT_KEYBACKSPACE      0x00000400  //Нажатие VK_BACK.
        #define AETCT_KEYDELETE         0x00000800  //Нажатие VK_DELETE.
        #define AETCT_DRAGDELETE        0x00001000  //Удаление текста при перетаскивании.
        #define AETCT_DROPINSERT        0x00002000  //Вставка текста при сбросе. 
        #define AETCT_COLUMNGROUP       0x00004000  //Отмена/Повтор для колоночного текста сгруппирована из действий на одной строке.
*/                   
    PrintLog("dwType = 0x" + (dwType).toString(16)) 
    if (bColumnSel) PrintLog("Используется колоночное выделение")
    switch (dwType){
      case 0x00000001: 
          PrintLog("  Замена выделения ")
          InsertFlag = true
          //PrintLog("  \"" + sPrevSelText + "\"")
          break 
      case 0x00000002: PrintLog("  Добавление текста"); break
      case 0x00000004: PrintLog("  Установка текста"); break
      case 0x00000008: PrintLog("  Потоковый ввод"); break
      case 0x00000010: PrintLog("  Отправка AEM_SETWORDWRAP"); break
      case 0x00000020: PrintLog("  Отмена действия"); break
      case 0x00000040: PrintLog("  Повтор действия"); break
      case 0x00000080: PrintLog("  Вырезание"); break
      case 0x00000100: PrintLog("  Вставка символа "); break
      case 0x00000200: PrintLog("  Нажатие VK_RETURN"); break
      case 0x00000400: PrintLog("  Нажатие VK_BACK"); break
      case 0x00000800: PrintLog("  Нажатие VK_DELETE"); break
      case 0x00001000: PrintLog("  Удаление текста при перетаскивании"); break
      case 0x00002000: 
          PrintLog("  Вставка текста при сбросе (перетаскивание текста мышью drag drop)")
          MoveFlag = true
          break
      case 0x00004000: PrintLog("  Отмена/Повтор для колоночного текста сгруппирована из действий на одной строке."); break 
    }  
}

function OnTextInsertBegin(lParam){
    return
    try{
    PrintLog("Перед вставкой")
    oTI.pStructSet(lParam)
    PrintLog('Текст для вставки. \n    ' + '|' + oTI.wpTextRef() + '|')
    PrintLog('Позиция вставки текста или диапазон после вставки. \n    ' + oTI.crAkelRange().ciMin().nCharInLine())
    } catch(e){
        PrintLog(e.message)
    }
}
function OnTextInsertEnd(lParam){              
    try {        
        oTI = AENTEXTINSERTwrp()                            // предварительная инициализация данных функции
        oBI = BLOCKINFOwrp()
        return (OnTextInsertEnd = function (lParam){
            oTI.pStructSet(lParam)
            if (oTI.dwType() === 0x100/*AETCT_CHAR*/){      // Введен один символ
                if (oTI.wpTextRef(4/*DT_WORD*/) === 46){    // Это точка
                    //PrintLog('Вы вставили точку!')
                    
                }
            }
        })(lParam)    
    } catch(e) {
        PrintLog('OnTextInsertEnd error: \n' + e.description)
    }
}
//PrintLog("После вставки")     
/*//        var nCurSelStart = AkelPad.GetSelStart()
//        PrintLog(nPrevSelStart + " " + nCurSelStart)
//        if (InsertFlag){
//            var sInsText = AkelPad.GetTextRange(nPrevSelStart, nCurSelStart)
//            if (sPrevSelText.length)
//                PrintLog("  Вы заменили \n\"" + sPrevSelText + "\" на \"" + sInsText +"\"")
//            else       
//                PrintLog("  Вы вставили \n\"" + sInsText +"\"")
//            InsertFlag = false     
////        }else if(MoveFlag){
////            sInsText = AkelPad.GetSelText()
////            PrintLog(sInsText.length)
////            PrintLog("  Вы переместили \"" + sPrevSelText + "\"")
////            MoveFlag = false
//        }
*/

function OnTextDeleteBegin(lParam){    
    //PrintLog("Перед удалением")
    return
    DeleteFlag = true
}
function OnTextDeleteEnd(lParam){
    //PrintLog("После удаления")
    return
    PrintLog("  Удалено: \n\"" + sPrevSelText + "\"")
}

function OnTextChanged(lParam){
    //PrintLog("После изменения \n ")
    return
    var nLine = getLineFromChar(AkelPad.GetSelStart()) 
    if(MoveFlag){
          var sMovedText = AkelPad.GetSelText()
          if(DeleteFlag)
              PrintLog("  Вы переместили перетаскиванием\n\"" + sMovedText + "\"")
          else
              PrintLog("  Вы скопировали перетаскиванием\n\"" + sMovedText + "\"")
          
          MoveFlag = false
    }else if (nModifiedLine !== nLine) {
        nModifiedLine = nLine   //запоминаем модифицированную строку для ее постобработки
    }
    
    if (DeleteFlag) DeleteFlag = false
}

// --------------------------------------------------------- 
// Вспомогательные функции
// ---------------------------------------------------------
function getLineFromChar(nPos){
    return AkelPad.SendMessage(hWndEdit, 1078 /*EM_EXLINEFROMCHAR*/, 0, nPos) 
}
