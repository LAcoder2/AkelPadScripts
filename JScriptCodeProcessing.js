//var hMainWnd = AkelPad.GetMainWnd()
//var hWndEdit = AkelPad.GetEditWnd()
AkelPad.Include("WinEvents.js")
AkelPad.Include("Coder.js")
var AP = AkelPad

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
 / /    #define AEN_TEXTINSERTBEGIN       (WM_USER + 1056)  / / 0x820
//    #define AEN_TEXTINSERTEND         (WM_USER + 1057)  //0x821
//    #define AEN_TEXTDELETEBEGIN       (WM_USER + 1058)  //0x822
//    #define AEN_TEXTDELETEEND         (WM_USER + 1059)  //0x823
//    #define AEN_TEXTCHANGED           (WM_USER + 1060)  //0x824
//    #define AEN_POINT                 (WM_USER + 1061)  //0x825  
*/
// При повторном запуске останавливаем обработку событий 
if (!stopEvents())
    startProcessing()
var nModifiedLine, EventsOn // номер последней модифицированной строки, которая обрабатывается после перехода курсора в другую строку
function startProcessing(){ 
    nModifiedLine =  -1
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
//    48 (AECHARRANGE crSel) + ptrSz(AELINEDATA *lpLine) + ptrsz * 2 (wchar_t *wpLine)
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
var nPrevSelStart, nPrevSelEnd, sPrevSelText, IsInsert, IsMove, IsTabPressed, IsEnterPressed, bColumnSel //, nCurrentLine

function OnSetFocus(lParam){
    //PrintLog("OnSetFocus") 
    nModifiedLine = -1 //забываем про последнюю модифицированную строку
    hWndEdit = AkelPad.GetEditWnd()
    if (getSyntaxFile(hWndEdit) === "js.coder"){
        PauseEventsFlag = false
        //PrintLog("В этом окне JScript, включаем автоматическую обработку ввода")
    }else{ 
        PauseEventsFlag = true 
        //PrintLog("В этом окне не  JScript, отключаем автоматическую обработку ввода") 
    }   
//      
//    
//    hSubClassMain = AkelPad.WindowSubClass(1/*WSC_MAINPROC*/, MainCallback, WM_NOTIFY)
//    if (hSubClassFrame) hSubClassFrame = AkelPad.WindowSubClass(3/*WSC_FRAMEPROC*/, EditCallback, WM_NOTIFY)     
}
function OnChangeModifySatus(lParam) {/*PrintLog("AEN_MODIFY");*/} 
function OnSelChanging(lParam){
    /*PrintLog("Начало выделения");*/
    if (oSys.Call("user32::GetAsyncKeyState", 9)) 
        if (!IsTabPressed) IsTabPressed = true
    else
        if (IsTabPressed) IsTabPressed = false
    //if (oSys.Call("user32::GetAsyncKeyState", 0xd/*VK_RETURN*/)) IsEnterPressed = true
}
var sLine2
function OnSelChanged(lParam){
    //PrintLog("Окончание выделения")
    if (IsTabPressed) {
        if(!IsInsert) IsTabPressed = false 
        return
    }    
    if (nModifiedLine > -1){ 
        try{
            // Запоминаем текущее выделение
            var nSelStart = AkelPad.GetSelStart()
            var nSelEnd = AkelPad.GetSelEnd()
            
            var nCurLine = getLineFromChar(nSelStart) 
            if(nModifiedLine !== nCurLine) {
                //PrintLog("Начинаем обработку модифицированной строки " + nModifiedLine)
                var nBgnPos = AkelPad.SendMessage(hWndEdit, 187 /*EM_LINEINDEX*/, nModifiedLine, 0)
                var nEndPos = nBgnPos + AkelPad.SendMessage(hWndEdit, 193 /*EM_LINELENGTH*/, nBgnPos, 0)
                var sLine = AkelPad.GetTextRange(nBgnPos, nEndPos)
                if (/\S{3,}/.test(sLine)){                  
                    var nDif = sLine.length  
                    sLine = normalizeSpaces(sLine) 
                    //PrintLog(sLine)
                    nDif = sLine.length - nDif
                    
                    PauseEventsFlag = true
                    StopRedraw() // Отключаем перерисовку 
                    
                    if(IsEnterPressed){
                        IsEnterPressed = false
                        //PrintLog("IsEnterPressed " + sLine.charAt(sLine.length - 1))
                        //if (sLine.charAt(sLine.length - 1) === "{"){
                        if (AkelPad.GetTextRange(nPrevSelStart -1 , nPrevSelStart) === "{"){
                            var nIndent = sLine.search(/\S/)
                            //PrintLog("nIndent = " + nIndent)
                            if (nIndent === -1) nIndent = 0
                            var sIndent = Space(nIndent)
                            var nTabSize = getTabSize()
                            var sRBraket = "}"
                            if (AkelPad.GetTextRange(nSelStart, nSelStart + 1) === sRBraket) sRBraket = ""  
                            //PrintLog("sIndent = |" + sIndent + "|\nsRBraket = " + sRBraket)
                            sLine += "\r" + Space(nIndent + nTabSize * 2) + "\r" + sIndent + sRBraket
                            //PrintLog("sLine =\n" + sLine.replace(/ /g, "_"))
                            nEndPos = nSelStart
                            nSelStart += nDif + nTabSize * 2
                            //PrintLog("nSelEnd = " + nSelEnd + "\n nSelStart = " + nSelStart)
                            nSelEnd = nSelStart
                        }
                    }else{
                        if(nCurLine > nModifiedLine) {
                            nSelStart += nDif  
                            nSelEnd += nDif    
                        }
                    }
                    
                    //DoEvents()
                    AkelPad.SetSel(nBgnPos, nEndPos)
                    //DoEvents()
                    WScript.Sleep(100)
                    AkelPad.ReplaceSel(sLine)
                    //DoEvents()
                    AkelPad.SetSel(nSelStart, nSelEnd)
                    
                    StartRedraw() //Разблокируем перерисовку
                    PauseEventsFlag = false                 
                }
                nModifiedLine = -1
            }
        }catch(e){
            StartRedraw()
            PauseEventsFlag = true            
            PrintLog("Ошибка в OnSelChanged: " + e.description)
        }                                     
    }
}

function OnTextChanging(lParam){
    //PrintLog("Перед изменением")
    if (oSys.Call("user32::GetAsyncKeyState", 0xd/*VK_RETURN*/)) IsEnterPressed = true
    with(AkelPad){
        var dwType = MemRead(_PtrAdd(lParam, dwTypeOff/*см. WitnEvents.js*/), 3/*DT_DWORD*/)          
        bColumnSel = MemRead(_PtrAdd(lParam, 108), 3/*DT_DWORD*/)     //флаг колоночного выделения777  
//        var crRichSelMin = MemRead(_PtrAdd(lParam, 112), 2/*DT_QWORD*/)   
//        var crRichSelMax = MemRead(_PtrAdd(lParam, 112+8), 2/*DT_QWORD*/)               
        nPrevSelStart = GetSelStart()
        if (bColumnSel) nPrevSelEnd = GetSelEnd() 
        //48 (AECHARRANGE crSel) + ptrSz(AELINEDATA *lpLine) + ptrsz * 2 (wchar_t *wpLine)
        //sPrevSelText = GetSelText()
        //pLineData = AkelPad.MemRead(_PtrAdd(lParam, 32 + ptrSz * 4), 2 /*DT_QWORD*/)
//        var ptrSz = (_X64) ? 8 : 4
//        var ciCaretOff = (_X64) ? 80 : 40
//        pLineData = AkelPad.MemRead(_PtrAdd(lParam, ciCaretOff + ptrSz), 2 /*DT_QWORD*/)
//        pwpLine = AkelPad.MemRead(_PtrAdd(pLineData, ptrSz * 2), 2)
//        if (typeof(pwpLine) ==="number"){
//            PrintLog(pwpLine)
//        }         
//        var sLine = AkelPad.MemRead(pwpLine, 1 /*DT_UNICODE*/)
//        PrintLog("sLine = \n" + sLine)
    }
    var nCurLine = getLineFromChar(nPrevSelStart)
    if (nModifiedLine !== nCurLine) nModifiedLine = nCurLine    
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
//    PrintLog("dwType = 0x" + (dwType).toString(16))
    switch (dwType){
      case 0x00000001: /*PrintLog("  Замена выделения ");*/IsInsert = true; break 
      //case 0x00000002: PrintLog("  Добавление текста"); break
      //case 0x00000004: PrintLog("  Установка текста"); break
      //case 0x00000008: PrintLog("  Потоковый ввод"); break
      //case 0x00000010: PrintLog("  Отправка AEM_SETWORDWRAP"); break
      //case 0x00000020: PrintLog("  Отмена действия"); break
      //case 0x00000040: PrintLog("  Повтор действия"); break
      //case 0x00000080: PrintLog("  Вырезание"); break
      //case 0x00000100: PrintLog("  Вставка символа "); break
      case 0x00000200: /*PrintLog("  Нажатие VK_RETURN");*/IsEnterPressed = true; break
      //case 0x00000400: PrintLog("  Нажатие VK_BACK"); break
      //case 0x00000800: PrintLog("  Нажатие VK_DELETE"); break
      //case 0x00001000: PrintLog("  Удаление текста при перетаскивании"); break
      case 0x00002000: /*PrintLog("  Вставка текста при сбросе")*/IsMove = true; break
      //case 0x00004000: PrintLog("  Отмена/Повтор для колоночного текста сгруппирована из действий на одной строке."); break 
    }  
}

function OnTextInsertBegin(lParam){/*PrintLog("Перед вставкой");*/}
function OnTextInsertEnd(lParam){              //111fszzfsz g
    //PrintLog("После вставки")                                       //!!!!!!!!!!!!!!!!!!1  
    //if (!IsInsert) {return;} else IsInsert = false
//    if (sPrevSelText.length)
//        PrintLog("  Вы заменили \"" + sPrevSelText + "\" на \"" + sInsText +"\"")
//    else       
//        PrintLog("  Вы вставили \"" + sInsText +"\"") 
//    var nCurSelStart = AkelPad.GetSelStart()
//    var sTmp = AkelPad.GetTextRange(nPrevSelStart, nCurSelStart)
//    if (!/\S/.test(sTmp)) return
//        
//    var nPrevLine = getLineFromChar(nPrevSelStart)
//    var nCurLine = getLineFromChar(nCurSelStart)
//    if(nPrevLine !== nCurLine){ 
//        //nModifiedLine = -1
//        PauseEventsFlag = true
//        StopRedraw()
//        
//        var nStartPos = AkelPad.SendMessage(hWndEdit, 187 /*EM_LINEINDEX*/, nPrevLine, 0)
//        var nEndPos = AkelPad.SendMessage(hWndEdit, 187 /*EM_LINEINDEX*/, nCurLine, 0) + 2
//        
//        AkelPad.SetSel(nStartPos, nEndPos)           // Получаем строки, захватываемые вставленным текстом) за исключением 
//        var sInsText = AkelPad.GetSelText()          // последней, в которую устанавливается курсор после вставки
//        var nPrevLen = sInsText.length
//        
//        sInsText = normalizeSpaces(sInsText)         // нормализуем пробелы
//        var sIndent = Space(nPrevSelStart - nStartPos)
//        var sInsText = addIndents(sInsText, sIndent) // добавляем отступы
//                
//        AkelPad.ReplaceSel(sInsText)                 // Вставляем в редактор обработанный текст
//        
//        nCurSelStart += sInsText.length - nPrevLen   // Восстанавливаем положение курсора с учетом изменившейся длины нормализованного текста
//        AkelPad.SetSel(nCurSelStart, nCurSelStart)
//        
//        StartRedraw()
//        PauseEventsFlag = false
//    }
}

function OnTextDeleteBegin(lParam){/*PrintLog("Перед удалением");*/}
function OnTextDeleteEnd(lParam){
//    PrintLog("После удаления")
//    PrintLog("  Вы удалили: \"" + sPrevSelText)
}

function OnTextChanged(lParam){
//    PrintLog("После изменения \n\n")
    if (IsTabPressed) {
       IsTabPressed = false
       return
    }
    var nCurSelStart = AkelPad.GetSelStart()
    var nCurLine = getLineFromChar(nCurSelStart) 
    if(nModifiedLine !== nCurLine){
        nModifiedLine = nCurLine  // запоминаем модифицированную строку для ее постобработки fff
    }/*else{
        if (!IsEnterPressed) {
        } else {
            IsEnterPressed = false        
            PrintLog("Сброс флага IsEnterPressed")
        }
    }*/
    
    try{        
        if(IsInsert){
            IsInsert = false
            if(bColumnSel){  // обработка вставки скопированного колоночного выделения
                bColumnSel = 0
                
            }else{
                var nPrevLine = getLineFromChar(nPrevSelStart)
                //PrintLog(nPrevLine + " " + nCurLine)
                if(nPrevLine !== nCurLine){     //проверяем больше ли размер вставленного текста чем 1 строка
                    var nStartPos = AkelPad.SendMessage(hWndEdit, 187 /*EM_LINEINDEX*/, nPrevLine, 0)
                    var nEndPos = AkelPad.SendMessage(hWndEdit, 187 /*EM_LINEINDEX*/, nCurLine, 0) 
                    nEndPos += AkelPad.SendMessage(hWndEdit, 193 /*EM_LINELENGTH*/, nEndPos, 0)
                    //Проверяем, если были вставлены только пробельные символы, то не обрабатываем их
                    if (!/\S{3,}/.test(AkelPad.GetTextRange(nPrevSelStart, nCurSelStart))) return 
                    PrintLog("Обрабатываем вставку")
                    PauseEventsFlag = true
                    StopRedraw()
                    //var re = new RegExp("^(?!\\s{16})\\s{1,15}");
                    
                    var sModifText = AkelPad.GetTextRange(nStartPos, nEndPos) // Получаем строки, захватываемые вставленным текстом) за исключением
    //                PrintLog("nCurLine = " + nCurLine)
    //                PrintLog("sModifText = \n" + sModifText)
                    var nPrevLen = sModifText.length               // последней, в которую устанавливается курсор после вставки
                    var nIndentLen = nPrevSelStart - nStartPos
                    if (nIndentLen > 0){
                        arRows = sModifText.split(/[\r\n]+/) 
                        var re = /\S/
                        var off = arRows[0].search(re)
                        //PrintLog("off1 = " + off)
                        if (off > -1) nIndentLen = off
                        off = undefined
                        for(var i = 1; i < arRows.length; ++arRows){
                            off2 = arRows[i].search(re)
                            if (off === undefined){
                                off = off2
                                if (arRows[0].search(/[\{\[(]\s*$/) > -1) off -= getTabSize()
                                if (off <= 0) break
                            }else{
                                if(Off > off2) Off = off2
                            }                            
                        } 
                        //if(off < 0) off = 0
                        //PrintLog("off = " + off)
                        nIndentLen -= off
                        //PrintLog("nIndentLen = " + nIndentLen)
                        if(nIndentLen > 0){
                            sIndent = Space(nIndentLen)
                            //PrintLog("sIndent = |" + sIndent + "|")
                            re = /([\r\n]+)/gm
                            sModifText = sModifText.replace(re, "$1" + sIndent)
                            //PrintLog("sModifText = " + sModifText)
                        }else if(nIndentLen < 0){
                            //RegExp("^(?!\\s{16})\\s{1,15}")
                            //re = new RegExp("([\r\n]+) {" + -nIndentLen + "}", "g")
                            re = new RegExp("([\r\n]+) {" + -nIndentLen + "}", "gm")
                            //PrintLog("re = " + re)
                            sModifText = sModifText.replace(re, "$1")
                            //PrintLog("sModifText = \n" + sModifText)
                        }
                        //sModifText = addIndents(sModifText, sIndent)    // добавляем отступы
                    }
                    var m = sModifText.match(/[\r\n]+[^\r\n]*$/)
                    var sLastRow = m[0]
                    sModifText = sModifText.substring(0, m.index)
                    /*PrintLog("sLastRow = \n" + sLastRow)
                    PrintLog("sModifText = \n" + sModifText)*/
                    
                    sModifText = normalizeSpaces(sModifText) + sLastRow // выравниваем пробелы
                    AkelPad.SetSel(nStartPos, nEndPos)
                    AkelPad.ReplaceSel(sModifText)                      // Вставляем в редактор обработанный текст
                    nCurSelStart += sModifText.length - nPrevLen        // Восстанавливаем положение курсора с учетом изменившейся длины нормализованного текста
                    AkelPad.SetSel(nCurSelStart, nCurSelStart)
                    
                    StartRedraw()
                    PauseEventsFlag = false
                }
            }
        } else if (IsMove){
            IsMove = false
            var nCurSelEnd = AkelPad.GetSelEnd()
            var nStartPos = getLineStartPos(nCurSelStart)
            var nEndPos = getLineEndPos(nCurSelEnd)
            var sModifText = AkelPad.GetTextRange(nStartPos, nEndPos)
            
            //Проверяем, если были только пробельные символы, то не обрабатываем их
            if (!/\S{3,}/.test(sModifText)) return 
            
            PauseEventsFlag = true
            StopRedraw()
            //var re = new RegExp("^(?!\\s{16})\\s{1,15}");
                      
            var nPrevLen = sModifText.length
            
            sModifText = normalizeSpaces(sModifText)      // нормализуем пробелы
    //        var sIndent = Space(nPrevSelStart - nStartPos)
    //        var sModifText = addIndents(sModifText, sIndent) // добавляем отступы
            
            AkelPad.SetSel(nStartPos, nEndPos)        
            AkelPad.ReplaceSel(sModifText)                // Вставляем в редактор обработанный текст
            
            nCurSelEnd += sModifText.length - nPrevLen    // Восстанавливаем положение курсора с учетом изменившейся длины нормализованного текста
            AkelPad.SetSel(nCurSelStart, nCurSelEnd)
            
            StartRedraw()
            PauseEventsFlag = false
        
        }
    }catch(e){
        PrintLog("Ошибка в OnTextChanged: " + e.description)
        StartRedraw()
        PauseEventsFlag = false
    }
}

// ---------------------------------------------------------
// Вспомогательные функции
// ---------------------------------------------------------
function getLineFromChar(nPos){
    return AkelPad.SendMessage(hWndEdit, 1078 /*EM_EXLINEFROMCHAR*/, 0, nPos)
}
//Аналог Space() в VBS. Получение строки, заданной длины, заполненной пробелами
//var spaceData
//function Space(cnt){
//    if (!spaceData){
//        spaceData = {
//          spaceBuf: "",  
//          bufLen: 0        
//        }
//    }
//    with(spaceData){
//        if (bufLen < cnt){
//            var ar = Array(cnt-bufLen+1)
//            spaceBuf += ar.join(" ")
//            bufLen = cnt
//        }
//        
//        return spaceBuf.substring(0, cnt)
//    }
//}
//typedef struct tagMSG {
//  HWND   hwnd;      // [0x00] размер: 4/8 байт (зависит от разрядности)
//  UINT   message;   // [0x04/0x08] размер: 4 байта
//  WPARAM wParam;    // [0x08/0x0C] размер: 4/8 байт (зависит от разрядности)
//  LPARAM lParam;    // [0x0C/0x10] размер: 4/8 байт (зависит от разрядности)
//  DWORD  time;      // [0x10/0x18] размер: 4 байта
//  POINT  pt;        // [0x14/0x1C] размер: 8 байт (2 x 4 байта)
//  DWORD  lPrivate;  // [0x1C/0x24] размер: 4 байта
//} MSG;              // Общий размер: 0x20 (32) / 0x28 (40) байт

//AkelPad.Include("log.js"); var oSys=AkelPad.SystemFunction(); test_DoEvents(1, 700)
function test_DoEvents(num, interval){
    var tmStart = new Date()
    var dif = 0
    if (num) {test_DoEvents(0, 1000)} else {DoEvents(); WScript.Sleep(300)}
    //while(!oSys.Call("user32::GetAsyncKeyState", 9)){
    while(dif < 10000){
        DoEvents()
        WScript.Sleep(interval)
        PrintLog(num)
        dif = new Date() - tmStart
    }
    PrintLog("Оконочание цикла " + num)
}   
var sMsgBuf, pMSG, pwParam
function DoEvents(){
    if (pMSG){
    } else {
        var sMsgBuf = new Array(21).join("\0")  // 40 bytes
        pMSG = AkelPad.MemStrPtr(sMsgBuf)
        pwParam = _PtrAdd(pMSG, 0x0C)
    }
    
    var result 
    while(oSys.Call("user32::PeekMessageW", pMSG, 0, 0, 0, 0/*PM_NOREMOVE*/)){
        result = oSys.Call("user32::GetMessageW", pMSG, 0, 0, 0)
        if(result === 0){  // WM_QUIT             
            //var wParam = AkelPad.MemRead(_PtrAdd(pMSG, 0x0C), 2 /*DT_QWORD*/)
            var wParam = AkelPad.MemRead(pwParam, 2 /*DT_QWORD*/)
            
            oSys.Call("user32::PostQuitMessage", wParam)
            break
        } else if (result === -1){
            // Handle errors/exit application, etc. 
            PrintLog("DoEvents: Handle errors/exit application, etc. !!!")
        } else {
            oSys.Call("user32::TranslateMessage", pMSG)
            oSys.Call("user32::DispatchMessage", pMSG)
        }  
    } 
    //PrintLog(_PtrAdd(pMSG, 0x0c) + "    " + pMSG + 0x0c)
}
//AkelPad.Include("log.js"); ptrTest()
function ptrTest(){
    var sMSG = "Hellow World and all!" 
    //var pMSG = AkelPad.MemStrPtr(sMSG)
    //var pwParam = _PtrAdd(pMSG, 0x0C)
    var wParam = AkelPad.MemRead(_PtrAdd(AkelPad.MemStrPtr(sMSG), 0x0C), 2 /*DT_QWORD*/)
    PrintLog(wParam)  // должно быть 9007628758548594 
}   
//Результат test_DoEvents (плохой, не работает так как надо):
//0
//0
//0
//0
//0
//0
//0
//0
//0
//0
//Оконочание цикла 0
//1
//Оконочание цикла 1

//void DoEvents()
//{
//    MSG msg;
//    BOOL result;
//    while ( ::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE ) )
//    {
//        result = ::GetMessage(&msg, NULL, 0, 0);
//        if (result == 0) // WM_QUIT
//        {
//            ::PostQuitMessage(msg.wParam);
//            break;
//        }
//        else if (result == -1)
//        {
//             // Handle errors/exit application, etc.
//        }
//        else
//        {
//            ::TranslateMessage(&msg);
//            :: DispatchMessage(&msg);
//        }
//    }
//}