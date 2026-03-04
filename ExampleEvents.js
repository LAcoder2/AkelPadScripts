//var hMainWnd = AkelPad.GetMainWnd()
//var hWndEdit = AkelPad.GetEditWnd()
AkelPad.Include("WinEvents.js")
AkelPad.Include("Coder.js")

/* Уведомления AkelEdit (0x702-0x836 1794-2102)
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
var nModifiedLine // номер последней модифицированной строки, которая обрабатывается после перехода курсора в другую строку
function TestEvents(){ 
//    PrintLog("TestEvents")   
    nModifiedLine = -1
    startEvents(0x802/*AEN_SETFOCUS*/, OnSetFocus,
                0x81C/*AEN_MODIFY*/, OnChangeModifySatus,
                0x81D/*AEN_SELCHANGING*/, OnSelChanging,
                0x81E/*AEN_SELCHANGED*/, OnSelChanged,
                0x81F/*AEN_TEXTCHANGING*/, OnTextChanging,
                0x820/*AEN_TEXTINSERTBEGIN*/, OnTextInsertBegin,
                0x821/*AEN_TEXTINSERTEND*/, OnTextInsertEnd,
                0x822/*AEN_TEXTDELETEBEGIN*/, OnTextDeleteBegin,
                0x823/*AEN_TEXTDELETEEND*/, OnTextDeleteEnd,
                0x824/*AEN_TEXTCHANGED*/, OnTextChanged)
}

/* Описание структуры AENTEXTCHANGE и всех входящих в нее структур  
//    typedef struct {              //size 8/16
//      INT_PTR cpMin;
//      INT_PTR cpMax;
//    } CHARRANGE64;
//    typedef struct _AELINEDATA {   
//      struct _AELINEDATA *next;   //Указатель на следующую структуру AELINEDATA.
//      struct _AELINEDATA *prev;   //Указатель на предыдущую структуру AELINEDATA.
//      wchar_t *wpLine;            //Текст строки, заканчивающийся NULL-символом.
//      int nLineLen;               //Длина wpLine, не включая завершающий NULL-символ.
//      BYTE nLineBreak;            //Новая строка: AELB_EOF, AELB_R, AELB_N, AELB_RN, AELB_RRN или AELB_WRAP.
//      BYTE nLineFlags;            //Зарезервировано.
//      WORD nReserved;             //Зарезервировано.
//      int nLineWidth;             //Ширина строки в пикселях.
//      int nSelStart;              //Начальная позиция символа выделения в строке.
//      int nSelEnd;                //Конечная позиция символа выделения в строке.
//    } AELINEDATA;    
////  typedef struct _AECHARINDEX { //size 12/24
//      int nLine;                  //Номер строки в документе, начиная с нуля.
//      AELINEDATA *lpLine;         //Указатель на структуру AELINEDATA.
//      int nCharInLine;            //Позиция символа в строке.
//    } AECHARINDEX;
//    typedef struct {              //size 24/48
//      AECHARINDEX ciMin;          //Индекс первого символа в диапазоне.
//      AECHARINDEX ciMax;          //Индекс последнего символа в диапазоне.
//    } AECHARRANGE;
//    typedef struct {              //size 16/32
//      //Стандартный NMHDR         //size 12/24
//      HWND hwndFrom;
//      UINT_PTR idFrom;
//      UINT code;
//    
//      //Члены AkelEdit
//      AEHDOC docFrom;             //Дескриптор документа. См. сообщение AEM_CREATEDOCUMENT.
//    } AENMHDR;
//                                  //size 16+24+12+4+4+8=68 / 32+48+24+4+4+16=128 
//    typedef struct {         //size offset 
//      AENMHDR hdr;           //16/32    00  
//      AECHARRANGE crSel;     //24/48    16/32  Текущее выделение.
//      AECHARINDEX ciCaret;   //12/24    40/80  Позиция индекса символа курсора.
//      DWORD dwType;          // 04      52/104 См. определения AETCT_*.
//      BOOL bColumnSel;       // 04      58/108 Колоночное выделение.
//      CHARRANGE64 crRichSel; //08/16    62/112 Текущее выделение (смещение RichEdit).
//    } AENTEXTCHANGE;
*/

// ---------------------------------------------------------
// Функции - обработчики событий
// ---------------------------------------------------------
var nPrevSelStart, nPrevSelEnd, sPrevSelText//, nCurrentLine     

function OnSetFocus(lParam){
    PrintLog("OnSetFocus") 
    hWndEdit = AkelPad.GetEditWnd()  //Получаем хэндл текущего окна/вкладки
    
    if (getSyntaxFile(hWndEdit) === "js.coder"){
        PauseEventsFlag = false
        PrintLog("В этом окне JScript, включаем автоматическую обработку ввода")
    }else{ 
        PauseEventsFlag = true 
        PrintLog("В этом окне не  JScript, отключаем автоматическую обработку ввода") 
    }           
}
function OnChangeModifySatus(lParam) {PrintLog("AEN_MODIFY");} 
function OnSelChanging(lParam){/*PrintLog("Начало выделения");*/}   
function OnSelChanged(lParam){
    //PrintLog("Окончание выделения")
    var nLine = getLineFromChar(AkelPad.GetSelStart()) 
    if (nModifiedLine > -1){ 
        if(nModifiedLine !== nLine) {
            PrintLog("  Вы освободили измененную строку: " +  (nModifiedLine + 1))  //45fff fdfdfdfd 
            nModifiedLine = -1
        }
    }
}

function OnTextChanging(lParam){
    PrintLog("Перед изменением")
    with(AkelPad){
        var dwType = MemRead(_PtrAdd(lParam, dwTypeOff/*см. WitnEvents.js*/), 3/*DT_DWORD*/)          
//        var bColumnSel = MemRead(_PtrAdd(lParam, 108), 3/*DT_DWORD*/)     //флаг колоночного выделения777  
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
    
    switch (dwType){
      case 0x00000001: 
          PrintLog("  Замена выделения ")
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
      case 0x00002000: PrintLog("  Вставка текста при сбросе"); break
      case 0x00004000: PrintLog("  Отмена/Повтор для колоночного текста сгруппирована из действий на одной строке."); break 
    }  
}

function OnTextInsertBegin(lParam){PrintLog("Перед вставкой");}
function OnTextInsertEnd(lParam){              //111fszzfsz g
    PrintLog("После вставки")    
    var nCurSelStart = AkelPad.GetSelStart()
    var sInsText = AkelPad.GetTextRange(nPrevSelStart, nCurSelStart)
    if (sPrevSelText.length)
        PrintLog("  Вы заменили \"" + sPrevSelText + "\" на \"" + sInsText +"\"")
    else       
        PrintLog("  Вы вставили \"" + sInsText +"\"") 
    
}
function OnTextDeleteBegin(lParam){PrintLog("Перед удалением");}
function OnTextDeleteEnd(lParam){
    PrintLog("После удаления")
    PrintLog("  Вы удалили: \"" + sPrevSelText)
}

function OnTextChanged(lParam){
    PrintLog("После изменения \n\n")
    var nLine = getLineFromChar(AkelPad.GetSelStart()) 
    if (nModifiedLine !== nLine) nModifiedLine = nLine   //запоминаем модифицированную строку для ее постобработки
}

// --------------------------------------------------------- 
// Вспомогательные функции
// ---------------------------------------------------------
function getLineFromChar(nPos){
    return AkelPad.SendMessage(hWndEdit, 1078 /*EM_EXLINEFROMCHAR*/, 0, nPos) 
}