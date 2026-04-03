//test_makeStructWrapper()
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
    st.ageSet(st.age() + 1)
    PrintLog(st.age()) 
    
    PrintLog(StrPtr(sDat)) 
    PrintLog(st.agePtr() + "\n" +
             st.specialityPtr())
}
// Функция создания объекта-враппера структуры, упрощающего работу со структурами данных
// pStruct - указатель структуры
// oStruct - объект-враппер структуры
// nSize - размер структуры
// fullInit - флаг инициализации всех свойств объекта, соответствующих полям основной структуры, являющимися (суб-)структурами
// если fullInit = true, то все свойства, соответствующие дочерним структурам, и их свойства, соотв. их дочерним структурам любой вложенности будут инициализированы
// если fullInit = false, то все свойства, соотв. дочерним структурам будут первоначально иметь значение - функцию инициализации
function makeStructWrapper(pStruct, oStruct, nSize, fullInit){
        if (!oStruct) oStruct = {}
        var nCountSubStructs = 0
        var nCountInit = 0
        var arSubStructs = [] //массив для хранения данных (и контроля) полей проинициализированных дочерних структур
        var nMaxCount = 0
        
        // Инициализация свойств, отвечающих за поля структуры
        for (var i = 6; i < arguments.length; i += 3){
            var fieldName = arguments[i-2]
            var nOffset = arguments[i-1]
            var nType = arguments[i]
            
            oStruct[fieldName + "Ptr"] = fieldPtr(nOffset)                          // получить указатель поля
            if (nType === 6){
                nCountSubStructs += 2
                if (nMaxCount < nCountSubStructs) {
                    nMaxCount += 10
                    arSubStructs.realloc(nMaxCount)
                }
                var fnGetWrp = arguments[++i]
                var fnSubStructInit = fieldSubStruct(nOffset, fnGetWrp, fieldName)
                oStruct[fieldName] = !fullInit ? fnSubStructInit : fnSubStructInit()
            } else {
                var nLength
                if (nType === 1 || nType === 0) 
                    nLength = arguments[++i]
                else
                    nLength = -1
                oStruct[fieldName] = fieldRead(nOffset, nType, nLength)             // прочитать значение поля
                //PrintLog(fieldName + " " + typeof oStruct[fieldName])
                oStruct[fieldName + "Set"] = fieldWrite(nOffset, nType, nLength)    // записать значение
            }
        }
        if (nCountSubStructs) arSubStructs.realloc(nCountSubStructs) 
        
        // Инициализация дефолтных свойств
        oStruct.pStruct = function(){return pStruct}
        oStruct.pStructSet = function(pNewStruct){
            //здесь можно добавить проверку на числовое значение pNewStruct (защита от идиотизма)
            pStruct = pNewStruct                        //меняем указатель основной структуры
            var fn_pSubStructSet, nOffset
            if (pStruct){
                for(var i = 0; i < nCountInit;){        //меняем указатели в каждом проинициализированном объекте дочерней структуры
                    fn_pSubStructSet = arSubStructs[i++]
                    nOffset = arSubStructs[i++]
                    fn_pSubStructSet(pStruct + nOffset) 
                }
            } else {
                for(var i = 0; i < nCountInit; i += 2){
                    fn_pSubStructSet = arSubStructs[i]
                    fn_pSubStructSet(0)                 //обнуляем указатели в объектах дочерних структур
                }
            }            
            return pStruct
        }
        oStruct.size = function(){return nSize}
        
    return oStruct
    
    function fieldSubStruct(nOffset, fnGetWrp, fieldName){  //v2
//        try{
        return function (){ // "ленивая" инициализации объекта субструктуры
            //if(pStruct){ 
            var oSubStruct = oStruct[fieldName] = function (){
                if (pStruct) return oSubStruct
                /*else*/ errorNullPointer()
            }
            fnGetWrp(pStruct + nOffset, oSubStruct, fullInit)
            arSubStructs[nCountInit++] = oSubStruct.pStructSet
            arSubStructs[nCountInit++] = nOffset
            oSubStruct.pStructSet = function (){
                throw new Error("Нельзя изменить указатель дочерней структуры!")
            }
            return oSubStruct
            //}
            ///*else*/ errorNullPointer()
        }
//        } catch(e) {
//            PrintLog('Ошибка в fieldSubStruct' + e.description) 
//        }
    }    
    function fieldRead(nOffset, nType, nLength){
        return function(nType2, nLength2){
            if (pStruct)
                return AkelPad.MemRead(_PtrAdd(pStruct, nOffset), 
                                        nType2 === undefined ? nType : nType2, 
                                        !nLength2 ? nLength : nLength2)
            errorNullPointer()
        }
    }
    function fieldWrite(nOffset, nType, nLength){
        return function(vData, nType2, nLength2){
            if (pStruct){
                AkelPad.MemCopy(_PtrAdd(pStruct, nOffset), vData, 
                                nType2 === undefined ? nType : nType2, 
                                !nLength2 ? nLength : nLength2)
                return vData
            }
            errorNullPointer()
        }
    }
    function fieldPtr(nOffset){
        return function(){
            if (pStruct) return pStruct + nOffset
            errorNullPointer()
        }
    }
    function errorNullPointer(){
        throw new Error("Указатель основной структуры равен нулю!")
    }
}

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
    var StrBuf = ""         // буфер сохраняется между вызовами
    return function(nLen) {
        if (StrBuf.length < nLen) {
            StrBuf = Array(nLen + 1).join("\0")
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
    //return this
}
Array.prototype.padEnd = function(lenadd, value){   // добавить lenadd элементов в конец
    if(lenadd > 0)
        this[this.length + lenadd - 1] = value
}
Array.prototype.rightDelete = function (lendel){
   this.splice(-lendel, lendel)
}
//function MyClass() {
//    // Возвращаем функцию, которая будет "методом по умолчанию"
//    var defaultMethod = function(param) {
//        return "Результат: " + param;
//    };
//    
//    // Добавляем другие методы как свойства
//    defaultMethod.otherMethod = function() {
//        return "Другой метод";
//    };
//    
//    return defaultMethod;
//}
//
//var obj = MyClass();
////WScript.Echo(obj("тест"));        // "Результат: тест"
//WScript.Echo(obj());  // "Другой метод"

//function testLock(){
//        function fnCreate(){
//            var ptr
//            return [
//                       function ptrGet(){return ptr},    
//                       function ptrSet(newptr){ptr = newptr}
//                   ]
//        }
//        var fnAr = fnCreate()
//        ptrGet = fnAr[0]
//        ptrSet = fnAr[1]
//        
//        ptrSet(123)
//        PrintLog(ptrGet())
//        ptrSet(22222)
//        PrintLog(ptrGet())
//}