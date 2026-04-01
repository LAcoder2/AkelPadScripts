AkelPad.Include("log.js")
AkelPad.Include("MemHelp.js")

/*typedef struct {            // смещения (x64/x86)
  AENMHDR hdr;              // 0/0      Стандартный NMHDR.
  AECHARRANGE crSel;        // 28/16    Текущее выделение.
  AECHARINDEX ciCaret;      // 76/40    Позиция индекса символа курсора.
  DWORD dwType;             // 100/52   См. определения AETCT_*.
  BOOL bColumnSel;          // 104/56   Колоночное выделение.
  CHARRANGE64 crRichSel;    // 112/60   Текущее выделение (смещение RichEdit).
} AENTEXTCHANGE;            // 128/68   Общий размер.
*/
try{
    var nstp = -1
    var oTC = makeAENTEXTCHANGEwrp()
    //PrintLog(oTC)
    nstp = 1
    var sBuf = makeStrBuff(oTC.size / 2)
    nstp = 2
    oTC.pStructSet(sBuf.StrPtr())
//    oTC.crRichSel().cpMaxSet(55544)
//    PrintLog(oTC.crRichSel().cpMax())
//    PrintLog(oTC.crRichSel().cpMaxPtr() - oTC.pStruct)
//    oTC.crSel().ciMax().nCharInLineSet(752)
//    PrintLog(oTC.crSel().ciMax().nCharInLine())
    var s = "Какая-то строка"
    //PrintLog(typeof oTC.crSel().ciMax())
    //PrintLog(typeof oTC.crSel.ciMax)
    PrintLog(typeof oTC.crSel().ciMax())
    with(oTC.crSel.ciMax){
        lpLineSet(s.StrPtr())
        PrintLog(AllocString(lpLine()))
    }
}catch(e){
    PrintLog(e.description + " " + nstp)
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
var oAELINEDATAwrp
function makeAELINEDATAwrp(pStruct, oStruct){
    if(!oAELINEDATAwrp)
        oAELINEDATAwrp = makeStructWrapper(0, 
                                "next", 0, 2,
                                "prev", (_X64 ? 8 : 4), 2,
                                "wpLine", (_X64 ? 16 : 8), 2,
                                "nLineLen", (_X64 ? 24 : 12), 3,  
                                "nLineBreak", (_X64 ? 28 : 16), 5,
                                "nLineFlags", (_X64 ? 29 : 17), 5,
                                "nReserved", (_X64 ? 30 : 18), 4,
                                "nLineWidth", (_X64 ? 32 : 20), 3,
                                "nSelStart", (_X64 ? 36 : 24), 3,
                                "nSelEnd", (_X64 ? 40 : 28), 3
                            )
    oStruct = shallowCopyObject(oAELINEDATAwrp, oStruct) 
    if (pStruct) oStruct.pStructSet(pStruct) 
    oStruct.size = _X64 ? 48 : 32     
    return oStruct                                           
} 
/*typedef struct {            // смещения (x64/x86)
  int nLine;                // 0/0      Номер строки в документе, начиная с нуля.
  AELINEDATA *lpLine;       // 8/4      Указатель на структуру AELINEDATA.
  int nCharInLine;          // 16/8     Позиция символа в строке.
} AECHARINDEX;              // 24/12    Общий размер.*/
var oAECHARINDEXwrp
function makeAECHARINDEXwrp(pStruct, oStruct){
    if(!oAECHARINDEXwrp)
        oAECHARINDEXwrp = makeStructWrapper(0, 
                                "nLine", 0, 3,
                                "lpLine", (_X64 ? 8 : 4), 2,
                                "nCharInLine", (_X64 ? 16 : 8), 3
                            )
    oStruct = shallowCopyObject(oAECHARINDEXwrp, oStruct) 
    if (pStruct) oStruct.pStructSet(pStruct) 
    oStruct.size = _X64 ? 24 : 12     
    return oStruct                                           
} 
/*typedef struct {            // смещения (x64/x86)
  AECHARINDEX ciMin;        // 0/0      Индекс первого символа в диапазоне.
  AECHARINDEX ciMax;        // 24/12    Индекс последнего символа в диапазоне.
} AECHARRANGE;              // 48/24    Общий размер.*/
var oAECHARRANGEwrp
function makeAECHARRANGEwrp(pStruct, oStruct){
    if(!oAECHARRANGEwrp)
        oAECHARRANGEwrp = makeStructWrapper(0, 
                                "ciMin", 0, 6, makeAECHARINDEXwrp,
                                "ciMax", (_X64 ? 24 : 12), 6, makeAECHARINDEXwrp
                            )
    oStruct = shallowCopyObject(oAECHARRANGEwrp, oStruct) 
    if (pStruct) oStruct.pStructSet(pStruct)
    oStruct.size = _X64 ? 48 : 24     
    return oStruct                                           
} 
/*typedef struct {            // смещения (x64/x86)
  HWND hwndFrom;            // 0/0      Дескриптор окна‑источника.
  UINT_PTR idFrom;          // 8/4      Идентификатор источника.
  UINT code;                // 16/8     Код уведомления.
  AEHDOC docFrom;           // 20/12    Дескриптор документа. См. сообщение AEM_CREATEDOCUMENT.
} AENMHDR;                  // 28/16    Общий размер.*/
var oAENMHDRwrp
function makeAENMHDRwrp(pStruct, oStruct){
    if(!oAENMHDRwrp)
        oAENMHDRwrp = makeStructWrapper(0, 
                                "hwndFrom", 0, 2,
                                "idFrom", (_X64 ? 8 : 4), 2,
                                "code", (_X64 ? 16 : 8), 3,
                                "docFrom", (_X64 ? 20 : 12), 2
                            )
    oStruct = shallowCopyObject(oAENMHDRwrp, oStruct) 
    if (pStruct) oStruct.pStructSet(pStruct) 
    oStruct.size = _X64 ? 28 : 16     
    return oStruct                                           
} 
/*typedef struct {            // смещения (x64/x86)
  INT_PTR cpMin;            // 0/0      Минимальное смещение.
  INT_PTR cpMax;            // 8/4      Максимальное смещение.
} CHARRANGE64;              // 16/8     Общий размер.*/
var oCHARRANGE64wrp
function makeCHARRANGE64wrp(pStruct, oStruct){
    if(!oCHARRANGE64wrp)
        oCHARRANGE64wrp = makeStructWrapper(0, 
                                "cpMin", 0, 2,
                                "cpMax", (_X64 ? 8 : 4), 2
                            )
    oStruct = shallowCopyObject(oCHARRANGE64wrp, oStruct) 
    if (pStruct) oStruct.pStructSet(pStruct)
    oStruct.size = _X64 ? 16 : 8     
    return oStruct                                           
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
var oAENTEXTCHANGEwrp
function makeAENTEXTCHANGEwrp(pStruct, oStruct){
    //PrintLog('makeAENTEXTCHANGEwrp')
    if(!oAENTEXTCHANGEwrp)
        oAENTEXTCHANGEwrp = makeStructWrapper(0, 
                                "hdr", 0, 6, makeAENMHDRwrp,
                                "crSel", (_X64 ? 28 : 16), 6, makeAECHARRANGEwrp,
                                "ciCaret", (_X64 ? 76 : 40), 6, makeAECHARRANGEwrp,
                                "dwType", (_X64 ? 100 : 52), 3, 
                                "bColumnSel", (_X64 ? 104 : 56), 3,
                                "crRichSel", (_X64 ? 112 : 60), 6, makeCHARRANGE64wrp
                            )
    oStruct = shallowCopyObject(oAENTEXTCHANGEwrp, oStruct)
    if (pStruct) 
        oStruct.pStructSet(pStruct)
    oStruct.size = _X64 ? 128 : 68     
    return oStruct                                           
} 