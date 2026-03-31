//test_makeStructWrapper()
function test_makeStructWrapper(){
    AkelPad.Include("log.js")
    
    var st = makeStructWrapper(0/*struct pointer*/, 
                               "name", 0, 1, 7, /*name, offset, type, [length]*/
                               "age", 14, 4,
                               "speciality", 18, 1, 8)
    st.size = 34
    
    var sDat = "Сергей \x23 Электрик"
    PrintLog(sDat.length * 2)
        
    st.pStruct = AkelPad.MemStrPtr(sDat)
    PrintLog(st.name() + "\n" +
             st.age() + "\n" +
             st.speciality())
    st.ageSet(st.age() + 1)
    PrintLog(st.age()) 
    
    PrintLog(StrPtr(sDat)) 
    PrintLog(st.agePtr() + "\n" +
             st.specialityPtr())
}

function makeStructWrapper(pStruct){
    var nstp = 0
    try{
    var oStruct = {pStruct: pStruct}
    
    for (var i = 3; i < arguments.length; i += 3){
        var fieldName = arguments[i-2]
        var nOffset = arguments[i-1]
        var nType = arguments[i]
        
        if (nType === 6){
            var fnGetWrp = arguments[++i]
            nstp = 1
            //oStruct[fieldName] = fieldSubStruct1(nOffset, fnGetWrp)
            oStruct[fieldName] = fieldSubStruct2(nOffset, fnGetWrp, oStruct, fieldName)
            nstp = 2
        } else {
            var nLength
            if (nType === 1 || nType === 0) 
                nLength = arguments[++i]
            else
                nLength = -1
            nstp = 3    
            oStruct[fieldName] = fieldRead(nOffset, nType, nLength)             // прочитать значение поля
            oStruct[fieldName + "Set"] = fieldWrite(nOffset, nType, nLength)    // записать значение
            oStruct[fieldName + "Ptr"] = fieldPtr(nOffset)                      // получить указатель поля
            nstp = 4
        }
    }
    }catch(e){
        PrintLog('Ошибка в makeStructWrapper()\n' + e.description + " " + nstp)
    }
    return oStruct
    
    function fieldSubStruct1(nOffset, fnGetWrp){ //v1
        var oSubStruct
        return function (){
            if (this.pStruct){
                var pSubStruct = this.pStruct + nOffset
                if (!oSubStruct) 
                    oSubStruct = fnGetWrp(pSubStruct)
                else if(oSubStruct.pStruct !== pSubStruct) 
                    oSubStruct.pStruct = pSubStruct
                return oSubStruct
            }
        }
    }
    function fieldSubStruct2(nOffset, fnGetWrp, oParentStruct, fieldName){ v2
//        try{
        var oSubStruct = oParentStruct[fieldName] = function (){
            if (this.pStruct){
                var pSubStruct = this.pStruct + nOffset
                //PrintLog('12345 ' + typeof oSubStruct)
                if (!oSubStruct.pStruct) 
   /*oSubStruct = */fnGetWrp(pSubStruct, oSubStruct)  
                else if(oSubStruct.pStruct !== pSubStruct) 
                    oSubStruct.pStruct = pSubStruct
                return oSubStruct
            }
        }
            return oSubStruct
//        } catch(e) {
//            PrintLog('Ошибка в fieldSubStruct' + e.description) 
//        }
    }
    function fieldRead(nOffset, nType, nLength){
        return function (nType2, nLength2){
            if (this.pStruct)
                return AkelPad.MemRead(_PtrAdd(this.pStruct, nOffset), 
                                        nType2 === undefined ? nType : nType2, 
                                        !nLength2 ? nLength : nLength2)
        }
    }
    function fieldWrite(nOffset, nType, nLength){
        return function (vData, nType2, nLength2){
            if (this.pStruct)
                AkelPad.MemCopy(_PtrAdd(this.pStruct, nOffset), vData, 
                                nType2 === undefined ? nType : nType2, 
                                !nLength2 ? nLength : nLength2)
        }
    }
    function fieldPtr(nOffset){
        return function (){
            return this.pStruct + nOffset
        }
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
    var StrBuf = "";  // сохраняется между вызовами
    return function(nLen) {
        if (StrBuf.length < nLen) {
            StrBuf = Array(nLen + 1).join("\0");
        }
        return StrBuf.substr(0, nLen);
    };
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