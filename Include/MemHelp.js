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
// AkelPad.Include("log.js")

function makeStructWrapper(pStruct, oStruct, fullInit, aOffsets, aDataFields){
        if (!oStruct) oStruct = {}
        if (!fullInit) fullInit = 0
        var nCountSubStructs = 0
        var nCountInit = 0
        var nMaxCount = 0
        var arSubStructs = [] // массив для хранения данных (и контроля) полей проинициализированных дочерних структур
        //var dictRefs = {}
        var nSize = aOffsets[0]
        
        //--Инициализация свойств, отвечающих за поля структуры--//
        var fnWrpMaker, nOffset = 0, offIter = 0        
        for (var i = 0; i < aDataFields.length - 2;){
            var fieldName = aDataFields[i++]
            var nType = aDataFields[i++]
            
            if (nType === 6){                   // структура, вложенная в основную структуру
                nCountSubStructs += 2
                if (nMaxCount < nCountSubStructs) {
                    nMaxCount += 10
                    arSubStructs.realloc(nMaxCount)
                }
                fnWrpMaker = aDataFields[i++]
                var fnSubStructInit = fieldSubStruct(nOffset, fnWrpMaker, fieldName)
                oStruct[fieldName] = !fullInit ? fnSubStructInit : fnSubStructInit()
                
            } else if (nType === 9){            // указатель на структуру
                oStruct[fieldName] = fieldRead(nOffset, 2, nLength)             
                oStruct[fieldName + "Set"] = fieldWrite(nOffset, 2, nLength)    
                fnWrpMaker = aDataFields[i++]
                var fldNmRef = fieldName + "Ref"
                //oStruct[fldNmRef] = fieldRefStruct(nOffset, fnWrpMaker, fldNmRef)      // v1 объекты референсных структур всегда инициализируются отложенно 
                var fnRefStructInit = fieldRefStruct(nOffset, fnWrpMaker, fldNmRef)    // v2 реф-структуры также инициализируются, до уровня вложенности, соответствующего параметру fullInit
                oStruct[fldNmRef] = ((fullInit < 2) || !pStruct) ? fnRefStructInit : fnRefStructInit()
            
            } else {
                var nLength = (nType === 1 || nType === 0) ? aDataFields[i++] : -1    // Строки Unicode и Ansi, включенные в структуру
                
                if (nType === 7 || nType === 8){                                    // указатель строки char*/wchar_t
                    oStruct[fieldName + "Ref"] = fieldReadRef(nOffset, nType - 7, nLength) // прочитать значение по ссылке (DT_ANSI 1/DT_UNICODE)
                    nType = 2 
                }
                oStruct[fieldName] = fieldRead(nOffset, nType, nLength)             // прочитать значение поля
                oStruct[fieldName + "Set"] = fieldWrite(nOffset, nType, nLength)    // записать значение
            }
            oStruct[fieldName + "Ptr"] = fieldPtr(nOffset)                          // получить указатель поля
            nOffset = aOffsets[++offIter]
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
    function fieldSubStruct(nOffset, fnWrpMaker, fieldName){      // "ленивая" инициализация объекта вложенной структуры
        return function (){                                     
            if(pStruct || fullInit){ 
                var oSubStruct = oStruct[fieldName] = function (){
                    if (pStruct) return oSubStruct
                    errorNullPointer()
                }
                fnWrpMaker((pStruct ? pStruct + nOffset : 0), oSubStruct, fullInit)
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
    function fieldRefStruct(nOffset, fnWrpMaker, fieldName){      // "ленивая" инициализация ссылочной структуры
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
                    fnWrpMaker(pSubStruct, oRefStruct, fullInit - 1)
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

//test_makeStructWrapper() // Простой тест структур
function test_makeStructWrapper(){
    AkelPad.Include("log.js")
    
    // makeStructWrapper(pStruct, oStruct, fullInit, aOffsets, aDataFields)
    var st = makeStructWrapper(0, 0, 0, [34,14,18]/*size, offsets*/,
                               ["name", 1, 6, /*name, type, [length]*/
                               "age", 4,
                               "speciality", 1, 8])
    PrintLog("Size = " + st.size())
    
    var sDat = "Сергей \x23 Электрик"
    //PrintLog(sDat.length * 2)
        
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
    } AECHARINDEX;                123
//    typedef struct {              //size 8/16
//      INT_PTR cpMin;
//      INT_PTR cpMax;
//    } CHARRANGE64;
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
    } AENTEXTCHANGE; //safadsads kljlkj asdf 
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
//test_getStructsMetadata()
function test_getStructsMetadata(){
    //AkelPad.Include("log.js")
    var sText = AkelPad.GetTextRange(14123, 16566)
    
    var oStructures = getStructsMetadata(sText)
    
    //PrintLog(oStructures)
}
//test_makeStructWrapperFunctions()
function test_makeStructWrapperFunctions(){
    AkelPad.Include("log.js")
    if (AkelPad.IsInclude()) WScript.Quit()
    var aWrpFnList = makeStructWrapperFunctions()
    for(var i = 0; i < aWrpFnList; ++i){
        PrintLog(aWrpFnList(i))
    }
}
// Создание JS-функций - фабрик объектов-врапперов структур
// Функция парсит текст (sText) ищет там определения C-структур и на основе полученных данных из них создает функции-фабрики для JS
// Если пустой аргумент sText, nj функция парсит выделенный текст активной вкладки
// если ни чего не выделено, парсится вся страница
function makeStructWrapperFunctions(sText){    
    //AkelPad.Include("log.js")
    //if (AkelPad.IsInclude()) return
    try{
        if (!sText){
            var selStart = AkelPad.GetSelStart()
            var selEnd = AkelPad.GetSelEnd()
            if (selStart === selEnd) {selStart = 0; selEnd = -1}    // если ни чего не выбрано будет обработан весь текст активной вкладки
            sText = AkelPad.GetTextRange(selStart, selEnd)      // получаем текст     
        }
        var oStopList = getExistedStructWrappersList(sText)     // ищем уже имеющиеся функции-врапперы в тексте (sText)
        var oIncludList = getAllIncludes(sText), fileName
        for(fileName in oIncludList){                           // продолжаем искать в инклюдах, найденных текстах, 
            getExistedStructWrappersList(oIncludList[fileName], oStopList) //и инклюдах, найденных в самих инклюдах (рекурсивно)
        }
        var oStructs = getStructsMetadata(sText, 0, oStopList)  // получаем данные о структурах из текста (sText)
        
        var structName
        var aOut = [], maxCnt = -1, i = 0
        for(structName in oStructs){
            var oStruct = oStructs[structName]
            delete oStruct.fieldsText; delete oStruct.name; delete oStruct.alignSize32; delete oStruct.alignSize64
            var offsets32 = oStruct.offsets32; delete oStruct.offsets32
            var offsets64 = oStruct.offsets64; delete oStruct.offsets64
            offsets32[0] = oStruct.size32; delete oStruct.size32
            offsets64[0] = oStruct.size64; delete oStruct.size64
            //offsets32.splice(0, 1); offsets64.splice(0, 1)           
            /*function AENTEXTCHANGEwrp(pStruct, oStruct, fullInit){
                var aOffsets = (_X64)?[128,32,80,104,108,112]:[68,16,40,52,56,60]
                var aDataFields = ["hdr", 6, AENMHDRwrp,
                                   "crSel", 6 ,AECHARRANGEwrp,
                                   "ciCaret", 6, AECHARRANGEwrp,
                                   "dwType", 3, 
                                   "bColumnSel", 3,
                                   "crRichSel", 6, CHARRANGE64wrp]
                return (AENTEXTCHANGEwrp = function (pStruct, oStruct, fullInit){
                    return makeStructWrapper(pStruct, oStruct, fullInit, aOffsets, aDataFields)
                })(pStruct, oStruct, fullInit)
            } */ 
            var funName = structName + 'wrp'
            var sFunc = 
            'function ' + funName + '(pStruct, oStruct, fullInit){\n' + 
            '    var aOffsets = (_X64)?[' + offsets64.join(',') + ']:[' + offsets32.join(',') + ']\n'+
            "    var aDataFields = ["
            var sFields = ""
            for (fieldName in oStruct){
                var aField = oStruct[fieldName]
                var typeName = aField[0]
                var typeFlag = aField[1]
                var arLen = aField[2]
                sFields += "                       '" + fieldName + "', " + typeFlag
                if(typeFlag === 6 || typeFlag === 9)
                    sFields += ", " + typeName + "wrp"
                else if (typeFlag === 0 || typeFlag === 1) 
                    sFields += ", -1"
                
                sFields += (!arLen) ? ",\n" : ', /*' + arLen + ' = ' + aField[3] + '*/\n'            
            }
            
            sFunc += sFields.slice(23, -2) + "]\n" +
            "    return (" + funName + " = function (pStruct, oStruct, fullInit){\n" +
            "        return makeStructWrapper(pStruct, oStruct, fullInit, aOffsets, aDataFields)\n" +
            "    })(pStruct, oStruct, fullInit)\n}"
            if (maxCnt < i){ 
                maxCnt += 10
                aOut.realloc(maxCnt)
            }
            PrintLog(sFunc)//; WScript.Quit()
            aOut[i++] = sFunc
        }
        aOut.realloc(i)
        return aOut            
    }catch(e){
        PrintLog(e.message)
    }
}
// получение списка имен структур, для которых уже имеются функции вида "function STRUCT_NAMEwrp("
function getExistedStructWrappersList(sText, oWrpFnList){
    //AkelPad.GetAkelDir
    reWrpFn = /^function (\w+)(?:wrp\()/g //function STRUCT_NAMEwrp(
    if (!oWrpFnList) oWrpFnList = {}
    var match
    while(match = reWrpFn.exec(sText)){
        var structName = match[1]
        if (!oWrpFnList[structName]) oWrpFnList[structName] = true
    }
    return oWrpFnList
}
/*(function test_getAllIncludes(){
    AkelPad.Include("log.js")
    try{
        var sText = AkelPad.GetTextRange(0, -1)
        
        var oIncludList = getAllIncludes(sText) 
        
        //PrintLog(oIncludList)
    }catch(e){
        PrintLog('testgetAllIncludes: ' + e.message)
    }
    
})()*/
// получение списка всех подключаемых файлов и их контента
// скрипт просматривает только верхнюю часть (1е 50 строк)
function getAllIncludes(sText, oIncludList){
    //try{
    if (!oIncludList) oIncludList = {}
    var includePath = AkelPad.GetAkelDir(6 /*ADTYPE_INCLUDE*/) + "\\"
    var reHeadText = /(^.*?[\r\n]+){50}/gm    
    var reInclude = /(\/\/.*?[\r\n]{1,2}|\/\*.*?\*\/)|(AkelPad\.Include\("(\w+\.js)"\))/g
    
    var match = reHeadText.exec(sText)
    if (match) sText = match[0] // берем только верхние 50 строк в которых с бОльшей вероятностью прописаны все инклюды
    //PrintLog('sText.length = ' + sText.length)
    
    while(match = reInclude.exec(sText)){
        var fileName = match[3]
        if (fileName){
            //PrintLog(fileName)
            if (!oIncludList[fileName]){ // исключаем повторную обработку одного и того же инклюда
                var fileText = AkelPad.ReadFile(includePath + fileName)
                oIncludList[fileName] = fileText
                getAllIncludes(fileText, oIncludList)
            }
        }
    }
    return oIncludList
//    } catch(e){
//        PrintLog('getAllIncludes: ' + e.message)
//    }
}
// Поиск определений C-структур и сбор из них всех данных об этих структурах в словарь объектов с данными
function getStructsMetadata(sText, oStructs, oStopList){
    var reStruct = /(\/[\/\*])?\s*typedef\s+struct(\s+[_\w]+)?\s*\{(.*?)\}\s*(\w+)(.*?[\r\n]+)?/g
    //Данные для getStructData()
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
    var MAX_PATH = 260
    var typeFlags = [0, DT_BYTE, DT_WORD, 0, DT_DWORD, 0, 0, 0, DT_QWORD]
    var ptrFlag = 0 //-1 
    var dictTypeSizes = {
        // Standard C/C++ Types
        "char": 1, "short": 2, "int": 4, "long": 4, "long long": 8, "float": 4, "double": 8, "long double": 8, "wchar_t": 2, "bool": 1, "void": ptrFlag,
        // Windows Data Types (based on https://learn.microsoft.com/en-us/windows/win32/winprog/windows-data-types)
        "APIENTRY": ptrFlag, "ATOM": 2, "BOOL": 4, "BOOLEAN": 1, "BYTE": 1, "CALLBACK": ptrFlag, "CCHAR": 1, "CHAR": 1, "COLORREF": 4, "CONST": ptrFlag, "DWORD": 4, "DWORDLONG": 8, "DWORD_PTR": ptrFlag, "DWORD32": 4, "DWORD64": 8, "FLOAT": 4, "HACCEL": ptrFlag, "HALF_PTR": (_X64 ? 4 : 2), "HANDLE": ptrFlag, "HBITMAP": ptrFlag, "HBRUSH": ptrFlag, "HCOLORSPACE": ptrFlag, "HCONV": ptrFlag, "HCONVLIST": ptrFlag, "HCURSOR": ptrFlag, "HDC": ptrFlag, "HDDEDATA": ptrFlag, "HDESK": ptrFlag, "HDROP": ptrFlag, "HDWP": ptrFlag, "HENHMETAFILE": ptrFlag, "HFILE": 4, "HFONT": ptrFlag, "HGDIOBJ": ptrFlag, "HGLOBAL": ptrFlag, "HHOOK": ptrFlag, "HICON": ptrFlag, "HINSTANCE": ptrFlag, "HKEY": ptrFlag, "HKL": ptrFlag, "HLOCAL": ptrFlag, "HMENU": ptrFlag, "HMETAFILE": ptrFlag, "HMODULE": ptrFlag, "HMONITOR": ptrFlag, "HPALETTE": ptrFlag, "HPEN": ptrFlag, "HRESULT": 4, "HRGN": ptrFlag, "HRSRC": ptrFlag, "HSZ": ptrFlag, "HWINSTA": ptrFlag, "HWND": ptrFlag, "INT": 4, "INT_PTR": ptrFlag, "INT8": 1, "INT16": 2, "INT32": 4, "INT64": 8, "LANGID": 2, "LCID": 4, "LCTYPE": 4, "LGRPID": 4, "LONG": 4, "LONGLONG": 8, "LONG_PTR": ptrFlag, "LONG32": 4, "LONG64": 8, "LPARAM": ptrFlag, "LPBOOL": ptrFlag, "LPBYTE": ptrFlag, "LPCOLORREF": ptrFlag, "LPCSTR": ptrFlag, "LPCTSTR": ptrFlag, "LPCVOID": ptrFlag, "LPCWSTR": ptrFlag, "LPDWORD": ptrFlag, "LPHANDLE": ptrFlag, "LPINT": ptrFlag, "LPLONG": ptrFlag, "LPSTR": ptrFlag, "LPTSTR": ptrFlag, "LPVOID": ptrFlag, "LPWORD": ptrFlag, "LPWSTR": ptrFlag, "LRESULT": ptrFlag, "PBOOL": ptrFlag, "PBOOLEAN": ptrFlag, "PBYTE": ptrFlag, "PCHAR": ptrFlag, "PCSTR": ptrFlag, "PCTSTR": ptrFlag, "PCWSTR": ptrFlag, "PDWORD": ptrFlag, "PDWORDLONG": ptrFlag, "PDWORD_PTR": ptrFlag, "PDWORD32": ptrFlag, "PDWORD64": ptrFlag, "PFLOAT": ptrFlag, "PHALF_PTR": ptrFlag, "PHANDLE": ptrFlag, "PHKEY": ptrFlag, "PINT": ptrFlag, "PINT_PTR": ptrFlag, "PINT8": ptrFlag, "PINT16": ptrFlag, "PINT32": ptrFlag, "PINT64": ptrFlag, "PLCID": ptrFlag, "PLONG": ptrFlag, "PLONGLONG": ptrFlag, "PLONG_PTR": ptrFlag, "PLONG32": ptrFlag, "PLONG64": ptrFlag, "POINTER_32": ptrFlag, "POINTER_64": ptrFlag, "POINTER_SIGNED": ptrFlag, "POINTER_UNSIGNED": ptrFlag, "PSHORT": ptrFlag, "PSIZE_T": ptrFlag, "PSSIZE_T": ptrFlag, "PSTR": ptrFlag, "PTBYTE": ptrFlag, "PTCHAR": ptrFlag, "PTSTR": ptrFlag, "PUCHAR": ptrFlag, "PUHALF_PTR": ptrFlag, "PUINT": ptrFlag, "PUINT_PTR": ptrFlag, "PUINT8": ptrFlag, "PUINT16": ptrFlag, "PUINT32": ptrFlag, "PUINT64": ptrFlag, "PULONG": ptrFlag, "PULONGLONG": ptrFlag, "PULONG_PTR": ptrFlag, "PULONG32": ptrFlag, "PULONG64": ptrFlag, "PUSHORT": ptrFlag, "PVOID": ptrFlag, "PWCHAR": ptrFlag, "PWORD": ptrFlag, "PWSTR": ptrFlag, "QWORD": 8, "SC_HANDLE": ptrFlag, "SC_LOCK": ptrFlag, "SERVICE_STATUS_HANDLE": ptrFlag, "SHORT": 2, "SIZE_T": ptrFlag, "SSIZE_T": ptrFlag, "TBYTE": 1, "TCHAR": 2, "UCHAR": 1, "UHALF_PTR": (_X64 ? 4 : 2), "UINT": 4, "UINT_PTR": ptrFlag, "UINT8": 1, "UINT16": 2, "UINT32": 4, "UINT64": 8, "ULONG": 4, "ULONGLONG": 8, "ULONG_PTR": ptrFlag, "ULONG32": 4, "ULONG64": 8, "UNICODE_STRING": ptrFlag, "USHORT": 2, "USN": 8, "VOID": ptrFlag, "WCHAR": 2, "WINAPI": ptrFlag, "WORD": 2, "WPARAM": ptrFlag,
        // AkelEdit Types from AkelEdit.h
        "AEHDOC": ptrFlag, "AEHPRINT": ptrFlag, "AEHTHEME": ptrFlag, "AEHDELIMITER": ptrFlag, "AEHWORD": ptrFlag, "AEHQUOTE": ptrFlag, "AEHMARKTEXT": ptrFlag, "AEHMARKRANGE": ptrFlag, "HSTACK": ptrFlag, "AEEditProc": ptrFlag, "AEStreamCallback": ptrFlag, "AEGetHighLightCallback": ptrFlag, "AEPaintCallback": ptrFlag, "PLUGINPROC": ptrFlag
    } 
    var reFieldBas = /(struct\s+_)?(\w+)\s+(\*\s*)?(\w+)(\[(\w+)\])?;/gm    //^(\/\/)?\s*   
    
    getStructsMetadata = function (sText, oStructs, oStopList){      
        if (!oStructs) oStructs = {}
        if (!oStopList) oStopList = {}
        var match
        while (match = reStruct.exec(sText)){
            //PrintLog(match[0])
            var structName = match[4]
            //PrintLog(structName)
            if (!structName) {WScript.Echo("Не определено имя структуры!"); WScript.Quit();}
            if (!oStructs[structName]){         // отсекаем повторные определения структуры
            if (!oStopList[structName])     // отсекаем имена структур из стоплиста
                oStructs[structName] = {name: structName, fieldsText: match[3]} 
            }       
        }
        for(structName in oStructs){
            var oStructData = oStructs[structName]
            if(!oStructData.size64) 
                getStructData(oStructData, reFieldBas)
            //PrintLog(oStructData)
        }
        return oStructs
                 
        function getStructData(oStructData, reField){
            try {            
            var structName = oStructData.name
            var sFields = oStructData.fieldsText
            var arOffsets32 = Array(5)
            var arOffsets64 = Array(5)                    
            var maxCount = 5
            var fieldCount = 0
            
            var typeSize, typeSize64, typeSize32, offset64 = 0, offset32 = 0, maxAlignSize64 = 1, maxAlignSize32 = 1
            var match, structFlag, typeFlag, oStructData2
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
                            if (!(typeSize32 = oStructData2.size32)){  // если oStructs[typeName] не обработана                              
                                //WScript.Echo("Рекурсивный вызов")
                                getStructData(oStructData2, new RegExp(reFieldBas))                                
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
                
                var sArLen = match[6]
                if (!sArLen){
                    oStructData[fieldName] = [typeName, typeFlag]               // !!!!!!!
                    nArLen = 1
                } else {
                    //PrintLog('sArLen = ' + sArLen) //#################!!!!!!!!!!!!!!!!!!#########
                    try {
                        nArLen = eval(sArLen)
                    } catch(e) {
                        PrintLog(e.message)
                        WScript.Echo("Не известно значение " + sArLen + "!\n" + 
                            "Добавьте соответствующую переменную/константу с таким именем \n" +
                            "чтобы правильно посчитать смещения структуры " + oStructData.name)
                        WScript.Quit()
                    }
                    
                    oStructData[fieldName] = [typeName, typeFlag, sArLen, nArLen]
                    
                }
                
                if (maxCount < fieldCount) {
                    maxCount += 10
                    arOffsets32.realloc(maxCount)
                    arOffsets64.realloc(maxCount)
                }                                      
                if(!structFlag){
                    arOffsets32[fieldCount] = offset32 = alignOffset(offset32, typeSize32)
                    arOffsets64[fieldCount] = offset64 = alignOffset(offset64, typeSize64)                        
                    if (maxAlignSize32 < 4) 
                        if (maxAlignSize32 < typeSize32) maxAlignSize32 = typeSize32
                    if (maxAlignSize64 < 8) 
                        if (maxAlignSize64 < typeSize64) maxAlignSize64 = typeSize64
                    offset32 += typeSize32 * nArLen
                    offset64 += typeSize64 * nArLen
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
                    offset32 += oStructData2.size32 * nArLen
                    offset64 += oStructData2.size64 * nArLen
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
            }catch (e){
                PrintLog(e.message)
            }
        }    
    }
    return getStructsMetadata(sText, oStructs, oStopList)        
}
//WScript.Echo(alignOffset(20, 8))
function alignOffset(nOffset, nTypeSize) {
    //return Math.ceil((nOffset + 1) / nTypeSize) * nTypeSize;
    //return ((((nOffset - 1) / nTypeSize)|0) + 1) * nTypeSize
    return ((nOffset + nTypeSize - 1) & ~(nTypeSize - 1))
}