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
var makeStrBuff = (function() {
    var StrBuf = ""         
    return function(nLen) {
        if (StrBuf.length < nLen) {
            StrBuf = Array(nLen + 1).join("\0")
        }
        return StrBuf.substr(0, nLen);
    }
})()
// Создание строки, заполненной пробелами
// Аналог Space() в VB
var Space = (function() {
    var StrBuf = ""         
    return function(nLen) {
        if (StrBuf.length < nLen) {
            StrBuf = Array(nLen + 1).join(" ")
        }
        return StrBuf.substr(0, nLen);
    }
})()
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