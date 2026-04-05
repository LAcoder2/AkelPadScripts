AkelPad.Include("log.js")
AkelPad.Include("MemHelp.js")

try{
    var nstp = -1
    var sTCBuf = Space(/*oTC.size()*/128 / 2)       // выделяем память для основной структуры AENTEXTCHANGE
    var sLDTBuf = Space(/*oLDt.size()*/48 / 2)      // выделяем память для ссылочной структуры AELINEDATA, 
                                                    // заполненную символом пробела, чтобы имитировать заполненность
    var oTC = makeAENTEXTCHANGEwrp(StrPtr(sTCBuf), 0, 2)
    nstp = 1
    
    PrintLog(oTC.crRichSel().cpMaxPtr() - oTC.pStruct())        // получаем смещение последнего элемента структуры
    oTC.crSel().ciMax().nCharInLineSet(752)                     // пишем простое значение в поле структуры
    PrintLog(oTC.crSel.ciMax.nCharInLine())                     // читаем это значение
    
    var s = "Привет Ворлд!"
    oTC.crSel.ciMax.lpLineSet(StrPtr(sLDTBuf))
    oTC.crSel.ciMax.lpLineRef().wpLineSet(StrPtr(s))            // пишем значение (указатель) в ссылочную структуру
                                                                // имитируя доступ к заполненной структуре
    PrintLog(oTC.crSel.ciMax.lpLineRef.wpLineRef())             // считываем ссылочное значение (строку wchar_t) из ссылочной структуры
    
}catch(e){
    PrintLog(e.message + " " + nstp)
    //PrintLog(nstp)
}
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
  AEHDOC docFrom;           // 20/12    Дескриптор документа. См. сообщение AEM_CREATEDOCUMENT.
} AENMHDR;                  // 28/16    Общий размер.*/
function makeAENMHDRwrp(pStruct, oStruct){
    return oStruct = makeStructWrapper(pStruct, oStruct, (_X64 ? 28 : 16), undefined, 
                                        "hwndFrom", 0, 2,
                                        "idFrom", (_X64 ? 8 : 4), 2,
                                        "code", (_X64 ? 16 : 8), 3,
                                        "docFrom", (_X64 ? 20 : 12), 2
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
  AECHARRANGE crSel;        // 28/16    Текущее выделение.
  AECHARINDEX ciCaret;      // 76/40    Позиция индекса символа курсора.
  DWORD dwType;             // 100/52   См. определения AETCT_*.
  BOOL bColumnSel;          // 104/56   Колоночное выделение.
  CHARRANGE64 crRichSel;    // 112/60   Текущее выделение (смещение RichEdit).
} AENTEXTCHANGE;            // 128/68   Общий размер.
*/
function makeAENTEXTCHANGEwrp(pStruct, oStruct, fullInit){
    return oStruct = makeStructWrapper(pStruct, oStruct, (_X64 ? 128 : 68)/*size*/, fullInit,
                                        "hdr", 0, 6, makeAENMHDRwrp,
                                        "crSel", (_X64 ? 28 : 16), 6, makeAECHARRANGEwrp,
                                        "ciCaret", (_X64 ? 76 : 40), 6, makeAECHARRANGEwrp,
                                        "dwType", (_X64 ? 100 : 52), 3, 
                                        "bColumnSel", (_X64 ? 104 : 56), 3,
                                        "crRichSel", (_X64 ? 112 : 60), 6, makeCHARRANGE64wrp
                                    )
} 