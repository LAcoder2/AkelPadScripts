// Модуль MemHelp.js (AkelPad-WSH-JScript) для секции "Include"
// (c) testuser2 2026
// Версия: 1 - 04/2026
// Описание: различные функции и объекты, урощающими работу с памятью и структурами в JScript
// https://github.com/LAcoder2/AkelPadScripts/blob/main/Include/MemHelp.js

// Функция создания объекта-враппера структуры, упрощающего работу со структурами данных
// pStruct  - указатель структуры
// oStruct  - объект-враппер структуры, если нужно использовать уже существующий объект/функцию
// nSize    - размер структуры
// fullInit - флаг инициализации всех свойств объекта, соответствующих полям основной структуры, являющимися (суб-)структурами
// если fullInit === 1, - все свойства, соответствующие дочерним структурам, и их свойства, соотв. их дочерним структурам любой вложенности будут инициализированы
// если fullInit > 1,   - дополнительно будут инициализированы все референсные структуры первого уровня вложенности равного fullInit
// если !fullInit,      - ни чего не будет инициализировано заранее, а только при первом обращении.
function makeStructWrapper(pStruct, oStruct, nSize, fullInit){
        if (!oStruct) oStruct = {}
        if (!fullInit) fullInit = 0
        var nCountSubStructs = 0
        var nCountInit = 0
        var nMaxCount = 0
        var arSubStructs = [] // массив для хранения данных (и контроля) полей проинициализированных дочерних структур
        //var dictRefs = {}
        var fnGetWrp
        
        //--Инициализация свойств, отвечающих за поля структуры--//
        for (var i = 6; i < arguments.length; i += 3){
            var fieldName = arguments[i-2]
            var nOffset = arguments[i-1]
            var nType = arguments[i]
            
            if (nType === 6){                   // структура, вложенная в основную структуру
                nCountSubStructs += 2
                if (nMaxCount < nCountSubStructs) {
                    nMaxCount += 10
                    arSubStructs.realloc(nMaxCount)
                }
                fnGetWrp = arguments[++i]
                var fnSubStructInit = fieldSubStruct(nOffset, fnGetWrp, fieldName)
                oStruct[fieldName] = !fullInit ? fnSubStructInit : fnSubStructInit()
                
            } else if (nType === 9){            // указатель на структуру
                oStruct[fieldName] = fieldRead(nOffset, 2, nLength)             
                oStruct[fieldName + "Set"] = fieldWrite(nOffset, 2, nLength)    
                fnGetWrp = arguments[++i]
                var fldNmRef = fieldName + "Ref"
                //oStruct[fldNmRef] = fieldRefStruct(nOffset, fnGetWrp, fldNmRef)      // v1 объекты референсных структур всегда инициализируются отложенно 
                var fnRefStructInit = fieldRefStruct(nOffset, fnGetWrp, fldNmRef)    // v2 реф-структуры также инициализируются, до уровня вложенности, соответствующего параметру fullInit
                oStruct[fldNmRef] = (fullInit < 2 || !pStruct) ? fnRefStructInit : fnRefStructInit()
            
            } else {
                var nLength = (nType === 1 || nType === 0) ? arguments[++i] : -1    // Строки Unicode и Ansi, включенные в структуру
                
                if (nType === 7 || nType === 8){                                    // указатель строки char*/wchar_t
                    oStruct[fieldName + "Ref"] = fieldReadRef(nOffset, nType - 7, nLength) // прочитать значение по ссылке (DT_ANSI 1/DT_UNICODE)
                    nType = 2 
                }
                oStruct[fieldName] = fieldRead(nOffset, nType, nLength)             // прочитать значение поля
                oStruct[fieldName + "Set"] = fieldWrite(nOffset, nType, nLength)    // записать значение
            }
            oStruct[fieldName + "Ptr"] = fieldPtr(nOffset)                          // получить указатель поля
        }
        if (nCountSubStructs) arSubStructs.realloc(nCountSubStructs) 
        
        //--Инициализация дефолтных свойств--//
        oStruct.pStruct = function(){return pStruct}
        oStruct.pStructSet = function(pNewStruct){
            //if (isInteger(pNewStruct) && pNewStruct > 0){} else errorNoPointer()
            if (pStruct !== pNewStruct) {
                pStruct = pNewStruct                        //меняем указатель основной структуры
                var fn_pSubStructSet
                if (pStruct){
                    for(var i = 0; i < nCountInit;){        //меняем указатели в каждом проинициализированном объекте дочерней структуры
                        fn_pSubStructSet = arSubStructs[i++]
                        var nOffset = arSubStructs[i++]
                        fn_pSubStructSet(pStruct + nOffset) 
                    }
                } else {
                    for(var i = 0; i < nCountInit; i += 2){
                        fn_pSubStructSet = arSubStructs[i]
                        fn_pSubStructSet(0)                 //обнуляем указатели в объектах дочерних структур
                    }
                } 
            }           
            return pStruct
        }
        oStruct.size = function(){return nSize}
        
    return oStruct
    
    //--Функции для инициализации полей - структур--//
    function fieldSubStruct(nOffset, fnGetWrp, fieldName){      // "ленивая" инициализация объекта вложенной структуры
        return function (){                                     
            if(pStruct || fullInit){ 
                var oSubStruct = oStruct[fieldName] = function (){
                    if (pStruct) return oSubStruct
                    errorNullPointer()
                }
                fnGetWrp((pStruct ? pStruct + nOffset : 0), oSubStruct, fullInit)
                arSubStructs[nCountInit++] = oSubStruct.pStructSet // забираем у объекта вложенной структуры ручку pStructSet()
                arSubStructs[nCountInit++] = nOffset
                oSubStruct.pStructSet = function (){               // бьем по рукам, чтобы не пытались..
                    throw new Error("Нельзя изменить указатель дочерней структуры!")
                }
                return oSubStruct
            }
            //errorNullPointer()
        }
    } 
    function fieldRefStruct(nOffset, fnGetWrp, fieldName){      // "ленивая" инициализация ссылочной структуры
        return function fnRefStructInit(){                      
            //PrintLog('Попытка инициализации ' + pStruct)
            if (pStruct){
                var fn_pStructSet
                var pSubStruct = AkelPad.MemRead(pStruct + nOffset, 2)
                if (pSubStruct){
                    //PrintLog('Инициализация ссылочной структуры')
                    var oRefStruct = oStruct[fieldName] = function (){
                        if (pStruct){
                        if (pSubStruct = AkelPad.MemRead(pStruct + nOffset, 2)) {
                            // Возвращает объект референсной структуры, только если указатель не равен нулю
                            fn_pStructSet(pSubStruct)  
                            return oRefStruct
                        }
                        }
                        errorNullPointer()
                    }
                    fnGetWrp(pSubStruct, oRefStruct, fullInit - 1)
                    fn_pStructSet = oRefStruct.pStructSet       // забираем у ссылочной структуры метод pStructSet() 
                    oRefStruct.pStructSet = function (){
                        throw new Error("Нельзя изменить указатель референсной структуры!")
                    }
                    return oRefStruct
                }
            } return fnRefStructInit // При неудачной попытке инициализации, функция возвращает саму себя
        }
    }
    
    //--Функции для инициализации полей базовых типов (числа, строки)--//   
    function fieldRead(nOffset, nType, nLength){    // чтение из поля структуры базового типа
        return function(nType2, nLength2){
            if (pStruct)
                return AkelPad.MemRead(pStruct + nOffset, 
                                        nType2 === undefined ? nType : nType2, 
                                        !nLength2 ? nLength : nLength2)
            errorNullPointer()
        }
    }
    function fieldWrite(nOffset, nType, nLength){   // запись в поле структуры базовых типов
        return function(vData, nType2, nLength2){
            if (pStruct){
                AkelPad.MemCopy(pStruct + nOffset, vData, 
                                nType2 === undefined ? nType : nType2, 
                                !nLength2 ? nLength : nLength2)
                return vData
            }
            errorNullPointer()
        }
    }
    function fieldReadRef(nOffset, nType, nLength){ // разименование строк и др. базовых типов
        return function(nType2, nLength2){
            if (pStruct)
                var pValue = AkelPad.MemRead(pStruct + nOffset, 2)
                if (pValue){
                    return AkelPad.MemRead(pValue, 
                                           (!isInteger(nType2)   || nType2   < 0) ? nType   : nType2, 
                                           (!isInteger(nLength2) || nLength2 < 0) ? nLength : nLength2)
                }                                   // при pValue = 0 вернет undefined
            errorNullPointer()
        }
    }
    function fieldPtr(nOffset){                     // получение указателя поля структуры
        return function(){
            if (pStruct) return pStruct + nOffset
            errorNullPointer()
        }
    }
    function errorNullPointer(){                    // ошибка при pStruct = 0
        throw new Error("Указатель основной структуры равен нулю!")
    }
    function errorNoPointer(){                      
        throw new Error("Значение не соответствует типу указателя!")
    }
}

// аналоги SysAllocString/Len/ByteLen
function AllocString(pwStr, nLength){
    if(!nLength) nLength = -1
    return AkelPad.MemRead(pwStr, 1/*DT_UNICODE*/, nLength)
}
var AllocStringW = AllocString
function AllocStringA(paStr, nLength){
    if(!nLength) nLength = -1
    return AkelPad.MemRead(paStr, 0/*DT_ANSI*/, nLength)
}
// Создание строки, заполненной нулями заданного размера (nLen)
// предназначено для безопасного выделения памяти
// WScript.Echo(makeStrBuff(10).length)
function makeStrBuff(nLen){
    var StrBuf = ""         
    return (makeStrBuff = function(nLen) {
        if (StrBuf.length < nLen) {
            StrBuf = Array(nLen + 1).join("\0")
        }
        return StrBuf.substr(0, nLen);
    })(nLen)
}
// AkelPad.Include("log.js"); PrintLog("|" + Space(10) + "|"); PrintLog("|" + Space(5) + "|")
// Создание строки, заполненной пробелами
// Аналог Space() в VB
function Space(nLen) {
    var StrBuf = ""         
    Space = function(nLen){
        if (StrBuf.length < nLen) {
            StrBuf = Array(nLen + 1).join(" ")
        }
        return StrBuf.substr(0, nLen)
    }
    return Space(nLen)
}
//Поверхностное копирование объекта
function shallowCopyObject(objInp, objOut){
    if (!objOut) objOut = new Object()
    for(var key in objInp){
        objOut[key] = objInp[key]
    }
    return objOut
}
function StrPtr(sVar){return AkelPad.MemStrPtr(sVar)}

String.prototype.StrPtr = function(){
    return AkelPad.MemStrPtr(this.toString())
}
Array.prototype.realloc = function(newlen) {
    if (newlen < this.length) 
        this.splice(newlen, this.length - newlen)   // Укорачиваем: удаляем лишние элементы
    else if (newlen > this.length)                  // Удлиняем: добавляем undefined элементы
        this[newlen - 1] = undefined                // автоматически расширит массив
    return this
}
Array.prototype.padEnd = function(lenadd, value){   // добавить lenadd элементов в конец
    if(lenadd > 0)
        this[this.length + lenadd - 1] = value
    return this
}
Array.prototype.rightDelete = function(lendel){
   this.splice(-lendel, lendel)
   return this
}
Array.prototype.leftDelete = function(lendel){
   this.splice(0, lendel)
   return this
}
// проверка любого значения (строка, объект, булево и т.д.) на соответствие целому числу
function isInteger(vData){
    return Math.floor(vData) === vData
}

// test_makeStructWrapper()
function test_makeStructWrapper(){
    AkelPad.Include("log.js")
    
    var st = makeStructWrapper(0/*struct pointer*/, 0, 34, false,
                               "name", 0, 1, 7, /*name, offset, type, [length]*/
                               "age", 14, 4,
                               "speciality", 18, 1, 8)
    PrintLog("Size = " + st.size())
    
    var sDat = "Сергей \x23 Электрик"
    PrintLog(sDat.length * 2)
        
    st.pStructSet(AkelPad.MemStrPtr(sDat))
    PrintLog(st.name() + "\n" +
             st.age() + "\n" +
             st.speciality())
    
    PrintLog(st.ageSet(st.age() + 1))
    
    //PrintLog(st.specialityPtr()) 
    PrintLog((st.agePtr() - st.pStruct()) + "\n" +
             (st.specialityPtr() - st.pStruct()))
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

/* Описание структуры AENTEXTCHANGE и всех входящих в нее структур  
//  typedef struct _AECHARINDEX { //size 12/24
      int nLine;                  //Номер строки в документе, начиная с нуля.
      AELINEDATA *lpLine;         //Указатель на структуру AELINEDATA.
      int nCharInLine;            //Позиция символа в строке.
    } AECHARINDEX;
    typedef struct {              //size 8/16
      INT_PTR cpMin;
      INT_PTR cpMax;
    } CHARRANGE64;
    typedef struct {              //size 24/48
      AECHARINDEX ciMin;          //Индекс первого символа в диапазоне.
      AECHARINDEX ciMax;          //Индекс последнего символа в диапазоне.
    } AECHARRANGE;
    typedef struct {         //size offset 
      AENMHDR hdr;           //16/32    00  
      AECHARRANGE crSel;     //24/48    16/32  Текущее выделение.
      AECHARINDEX ciCaret;   //12/24    40/80  Позиция индекса символа курсора.
      DWORD dwType;          // 04      52/104 См. определения AETCT_*.
      BOOL bColumnSel;       // 04      58/108 Колоночное выделение.
      CHARRANGE64 crRichSel; //08/16    62/112 Текущее выделение (смещение RichEdit).
    } AENTEXTCHANGE;
    typedef struct _AELINEDATA {   
      struct _AELINEDATA *next;   //Указатель на следующую структуру AELINEDATA.
      struct _AELINEDATA *prev;   //Указатель на предыдущую структуру AELINEDATA.
      wchar_t *wpLine;            //Текст строки, заканчивающийся NULL-символом.
      int nLineLen;               //Длина wpLine, не включая завершающий NULL-символ.
      BYTE nLineBreak;            //Новая строка: AELB_EOF, AELB_R, AELB_N, AELB_RN, AELB_RRN или AELB_WRAP.
      BYTE nLineFlags;            //Зарезервировано.
      WORD nReserved;             //Зарезервировано.
      int nLineWidth;             //Ширина строки в пикселях.
      int nSelStart;              //Начальная позиция символа выделения в строке.
      int nSelEnd;                //Конечная позиция символа выделения в строке.
    } AELINEDATA;    
    typedef struct {              //size 16/32
      //Стандартный NMHDR         //size 12/24
      HWND hwndFrom;
      UINT_PTR idFrom;
      UINT code;
    
      //Члены AkelEdit
      AEHDOC docFrom;             //Дескриптор документа. См. сообщение AEM_CREATEDOCUMENT.
    } AENMHDR;
    48 (AECHARRANGE crSel) + ptrSz(AELINEDATA *lpLine) + ptrsz * 2 (wchar_t *wpLine)
                                  //size 16+24+12+4+4+8=68 / 32+48+24+4+4+16=128 
*/

//AkelPad.Include("MemHelp.js"); 
test_getStructsMetadata()
function test_getStructsMetadata(){
    AkelPad.Include("log.js")
    var sText = AkelPad.GetTextRange(13850, 16286)
    //PrintLog(sText); WScript.Quit()
    var oStructures = getStructsMetadata(sText)
    
    //PrintLog(oStructures)
}
function getStructsMetadata(sText){
    var DT_ANSI         = 0
    var DT_UNICODE      = 1
    var DT_QWORD        = 2
    var DT_PTR          = DT_QWORD
    var DT_DWORD        = 3
    var DT_WORD         = 4
    var DT_BYTE         = 5
    var DT_STRUCT       = 6
    var DT_PTR_ANSI     = 7
    var DT_PTR_UNICODE  = 8
    var DT_PTR_STRUCT   = 9
    var reStruct = /typedef\s+struct(\s+[_\w]+)?\s*\{(.*?)\}\s*(\w+)/g
    var typeFlags = [0, DT_BYTE, DT_WORD, 0, DT_DWORD, 0, 0, 0, DT_QWORD]
    //Данные для getStructData()
    var ptrFlag = 0 //-1 
        // Standard C/C++ Types
        // Windows Data Types (based on https://learn.microsoft.com/en-us/windows/win32/winprog/windows-data-types)
        // AkelEdit Types from AkelEdit.h
    var dictTypeSizes = {
        "char": 1, "short": 2, "int": 4, "long": 4, "long long": 8, "float": 4, "double": 8, "long double": 8, "wchar_t": 2, "bool": 1, "void": ptrFlag,
        "APIENTRY": ptrFlag, "ATOM": 2, "BOOL": 4, "BOOLEAN": 1, "BYTE": 1, "CALLBACK": ptrFlag, "CCHAR": 1, "CHAR": 1, "COLORREF": 4, "CONST": ptrFlag, "DWORD": 4, "DWORDLONG": 8, "DWORD_PTR": ptrFlag, "DWORD32": 4, "DWORD64": 8, "FLOAT": 4, "HACCEL": ptrFlag, "HALF_PTR": (_X64 ? 4 : 2), "HANDLE": ptrFlag, "HBITMAP": ptrFlag, "HBRUSH": ptrFlag, "HCOLORSPACE": ptrFlag, "HCONV": ptrFlag, "HCONVLIST": ptrFlag, "HCURSOR": ptrFlag, "HDC": ptrFlag, "HDDEDATA": ptrFlag, "HDESK": ptrFlag, "HDROP": ptrFlag, "HDWP": ptrFlag, "HENHMETAFILE": ptrFlag, "HFILE": 4, "HFONT": ptrFlag, "HGDIOBJ": ptrFlag, "HGLOBAL": ptrFlag, "HHOOK": ptrFlag, "HICON": ptrFlag, "HINSTANCE": ptrFlag, "HKEY": ptrFlag, "HKL": ptrFlag, "HLOCAL": ptrFlag, "HMENU": ptrFlag, "HMETAFILE": ptrFlag, "HMODULE": ptrFlag, "HMONITOR": ptrFlag, "HPALETTE": ptrFlag, "HPEN": ptrFlag, "HRESULT": 4, "HRGN": ptrFlag, "HRSRC": ptrFlag, "HSZ": ptrFlag, "HWINSTA": ptrFlag, "HWND": ptrFlag, "INT": 4, "INT_PTR": ptrFlag, "INT8": 1, "INT16": 2, "INT32": 4, "INT64": 8, "LANGID": 2, "LCID": 4, "LCTYPE": 4, "LGRPID": 4, "LONG": 4, "LONGLONG": 8, "LONG_PTR": ptrFlag, "LONG32": 4, "LONG64": 8, "LPARAM": ptrFlag, "LPBOOL": ptrFlag, "LPBYTE": ptrFlag, "LPCOLORREF": ptrFlag, "LPCSTR": ptrFlag, "LPCTSTR": ptrFlag, "LPCVOID": ptrFlag, "LPCWSTR": ptrFlag, "LPDWORD": ptrFlag, "LPHANDLE": ptrFlag, "LPINT": ptrFlag, "LPLONG": ptrFlag, "LPSTR": ptrFlag, "LPTSTR": ptrFlag, "LPVOID": ptrFlag, "LPWORD": ptrFlag, "LPWSTR": ptrFlag, "LRESULT": ptrFlag, "PBOOL": ptrFlag, "PBOOLEAN": ptrFlag, "PBYTE": ptrFlag, "PCHAR": ptrFlag, "PCSTR": ptrFlag, "PCTSTR": ptrFlag, "PCWSTR": ptrFlag, "PDWORD": ptrFlag, "PDWORDLONG": ptrFlag, "PDWORD_PTR": ptrFlag, "PDWORD32": ptrFlag, "PDWORD64": ptrFlag, "PFLOAT": ptrFlag, "PHALF_PTR": ptrFlag, "PHANDLE": ptrFlag, "PHKEY": ptrFlag, "PINT": ptrFlag, "PINT_PTR": ptrFlag, "PINT8": ptrFlag, "PINT16": ptrFlag, "PINT32": ptrFlag, "PINT64": ptrFlag, "PLCID": ptrFlag, "PLONG": ptrFlag, "PLONGLONG": ptrFlag, "PLONG_PTR": ptrFlag, "PLONG32": ptrFlag, "PLONG64": ptrFlag, "POINTER_32": ptrFlag, "POINTER_64": ptrFlag, "POINTER_SIGNED": ptrFlag, "POINTER_UNSIGNED": ptrFlag, "PSHORT": ptrFlag, "PSIZE_T": ptrFlag, "PSSIZE_T": ptrFlag, "PSTR": ptrFlag, "PTBYTE": ptrFlag, "PTCHAR": ptrFlag, "PTSTR": ptrFlag, "PUCHAR": ptrFlag, "PUHALF_PTR": ptrFlag, "PUINT": ptrFlag, "PUINT_PTR": ptrFlag, "PUINT8": ptrFlag, "PUINT16": ptrFlag, "PUINT32": ptrFlag, "PUINT64": ptrFlag, "PULONG": ptrFlag, "PULONGLONG": ptrFlag, "PULONG_PTR": ptrFlag, "PULONG32": ptrFlag, "PULONG64": ptrFlag, "PUSHORT": ptrFlag, "PVOID": ptrFlag, "PWCHAR": ptrFlag, "PWORD": ptrFlag, "PWSTR": ptrFlag, "QWORD": 8, "SC_HANDLE": ptrFlag, "SC_LOCK": ptrFlag, "SERVICE_STATUS_HANDLE": ptrFlag, "SHORT": 2, "SIZE_T": ptrFlag, "SSIZE_T": ptrFlag, "TBYTE": 1, "TCHAR": 2, "UCHAR": 1, "UHALF_PTR": (_X64 ? 4 : 2), "UINT": 4, "UINT_PTR": ptrFlag, "UINT8": 1, "UINT16": 2, "UINT32": 4, "UINT64": 8, "ULONG": 4, "ULONGLONG": 8, "ULONG_PTR": ptrFlag, "ULONG32": 4, "ULONG64": 8, "UNICODE_STRING": ptrFlag, "USHORT": 2, "USN": 8, "VOID": ptrFlag, "WCHAR": 2, "WINAPI": ptrFlag, "WORD": 2, "WPARAM": ptrFlag,
        "AEHDOC": ptrFlag, "AEHPRINT": ptrFlag, "AEHTHEME": ptrFlag, "AEHDELIMITER": ptrFlag, "AEHWORD": ptrFlag, "AEHQUOTE": ptrFlag, "AEHMARKTEXT": ptrFlag, "AEHMARKRANGE": ptrFlag, "HSTACK": ptrFlag, "AEEditProc": ptrFlag, "AEStreamCallback": ptrFlag, "AEGetHighLightCallback": ptrFlag, "AEPaintCallback": ptrFlag
    }            
    //var re1 = /^\s*(struct\s+_)?(\w+)\s+(\*\s*)?(\w+)/gm
    
    getStructsMetadata = function (sText){      
        var oStructs = {}
        var match
        while (match = reStruct.exec(sText)){
            var structName = match[3]
            if (!structName) {WScript.Echo("Не определено имя структуры!"); WScript.Quit();}
            (oStructs[structName] = {}).name = structName
            oStructs[structName].fieldsText = match[2]        
        }
        for(structName in oStructs){
            var oStructData = oStructs[structName]
            if(!oStructData.size64) getStructData(oStructData)
            PrintLog(oStructData)
        }
        return oStructs
         
        function getStructData(oStructData){
        //    try {            
            /*0 - char(Ansi)   флаги типов
            1 - wchar_t (Ubicode)
            2 - QWORD
            3 - DWORD
            4 - WORD
            5 - BYTE
            6 - Struct
            7 - *char
            8 - *wchar_t
            9 = pStruct*/            
            //getStructData = function(oStructData){
            var structName = oStructData.name
            var sFields = oStructData.fieldsText
            var arOffsets32 = Array(5)
            var arOffsets64 = Array(5)                    
            var maxCount = 5
            var fieldCount = 0
            
            var typeSize, typeSize64, typeSize32, offset64 = 0, offset32 = 0, maxAlignSize64 = 1, maxAlignSize32 = 1
            var match, structFlag, typeFlag, oStructData2
            var reField = /^\s*(struct\s+_)?(\w+)\s+(\*\s*)?(\w+)/gm
            while (match = reField.exec(sFields)){
                var typeName = match[2]                    
                var fieldName = match[4]
                
                if (match[3]) { // match[3] === '*'
                    //typeName += '*'       // значимость этой строчки под вопросом
                    if (oStructs[typeName])
                        typeFlag = DT_PTR_STRUCT
                    else if (typeName === 'char')
                        typeFlag = DT_PTR_ANSI
                    else if (typeName === 'wchar_t')                                
                        typeFlag = DT_PTR_UNICODE    
                    else
                        typeFlag = DT_PTR 
                    typeSize = ptrFlag      // значимость этой строчки под вопросом
                    typeSize32 = 4
                    typeSize64 = 8
                }else{                        
                    typeSize = dictTypeSizes[typeName]
                    
                    switch (typeSize){
                    case ptrFlag:
                        if (oStructs[typeName])
                            typeFlag = DT_PTR_STRUCT
                        else 
                            typeFlag = DT_PTR
                        typeSize32 = 4
                        typeSize64 = 8
                        break
                    case undefined:
                        oStructData2 = oStructs[typeName]                             
                        if (oStructData2){
                            //PrintLog('offset64 = ' + offset64)
                            if (!(typeSize32 = oStructData2.size32)){
                                //WScript.Echo("Рекурсивный вызов: " + typeName)
                                //PrintLog(fieldCount)
                                getStructData(oStructData2)
                                //PrintLog('offset64 = ' + offset64); WScript.Quit()
                                //PrintLog(fieldCount)
                                typeSize32 = oStructData2.size32                                    
                            } 
                            typeSize64 = oStructData2.size64
                        }else{
                            WScript.Echo("Отсутствуют данные по типу данных\n" + typeName); WScript.Quit()
                        }
                        typeFlag = DT_STRUCT
                        structFlag = true
                        break
                    default:
                        if (typeSize === 1) 
                            typeFlag = (typeName === 'char') ? DT_ANSI : DT_BYTE                                    
                        else if(typeSize === 2)
                            typeFlag = (typeName === 'wchar_t') ? DT_UNICODE : DT_WORD                                
                        else
                            typeFlag = typeFlags[typeSize] // 5 - 3 соответствует DT_BYTE, DT_WORD, DT_DWORD
                        
                        typeSize32 = typeSize64 = typeSize
                        break
                    } 
                } 
                
                if (maxCount < fieldCount) {
                    maxCount += 10
                    arOffsets32.realloc(maxCount)
                    arOffsets64.realloc(maxCount)
                }                        
                //PrintLog(fieldName + ' ' + typeName + ' ' + typeFlag)
                oStructData[fieldName] = [typeName, typeFlag]
                if(!structFlag){
                    arOffsets32[fieldCount] = offset32 = alignOffset(offset32, typeSize32)
                    arOffsets64[fieldCount] = offset64 = alignOffset(offset64, typeSize64)                        
                    if (maxAlignSize32 < 4) 
                        if (maxAlignSize32 < typeSize32) maxAlignSize32 = typeSize32
                    if (maxAlignSize64 < 8) 
                        if (maxAlignSize64 < typeSize64) maxAlignSize64 = typeSize64
                    offset32 += typeSize32 
                    offset64 += typeSize64 
                } else {
                    structFlag = false
                    arOffsets32[fieldCount] = offset32 = alignOffset(offset32, oStructData2.alignSize32)
                    arOffsets64[fieldCount] = offset64 = alignOffset(offset64, oStructData2.alignSize64)                        
                    //oStructData[fieldName] = [typeName, size32, size64]
                    if (maxAlignSize32 < 4){ 
                        if (maxAlignSize32 < oStructData2.alignSize32) maxAlignSize32 = oStructData2.alignSize32
                    }
                    if (maxAlignSize64 < 8){ 
                        if (maxAlignSize64 < oStructData2.alignSize64) maxAlignSize64 = oStructData2.alignSize64
                    }
                    offset32 += oStructData2.size32 
                    offset64 += oStructData2.size64
                }
                fieldCount++
            }
            oStructData.offsets32 = arOffsets32.realloc(fieldCount)
            oStructData.offsets64 = arOffsets64.realloc(fieldCount)                    
            oStructData.size32 = alignOffset(offset32, maxAlignSize32)
            oStructData.size64 = alignOffset(offset64, maxAlignSize64)
            oStructData.alignSize32 = maxAlignSize32
            oStructData.alignSize64 = maxAlignSize64
            return oStructData
            //}
            //return getStructData(oStructData)
        //    }catch (e){
        //        PrintLog(e.message)
        //    }
        }
    }
    return getStructsMetadata(sText)
}
//WScript.Echo(alignOffset(20, 8))
function alignOffset(nOffset, nTypeSize) {
    //return Math.ceil((nOffset + 1) / nTypeSize) * nTypeSize;
    //return ((((nOffset - 1) / nTypeSize)|0) + 1) * nTypeSize
    return ((nOffset + nTypeSize - 1) & ~(nTypeSize - 1))
}