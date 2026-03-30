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

function makeStructWrapper(){
    var obj = {"pStruct": arguments[0]}
    for (var i = 3; i < arguments.length; i += 3){
        var fieldName = arguments[i-2]
        var nOffset = arguments[i-1]
        var nType = arguments[i]
        if (nType === 6){
            var fnGetWrp = arguments[++i]
            obj[fieldName] = fieldStruct(nOffset, fnGetWrp, fieldName)
        } else {
            var nLength
            if (nType === 1 || nType === 0) 
                nLength = arguments[++i]
            else
                nLength = -1
                
            obj[fieldName] = fieldRead(nOffset, nType, nLength)             // прочитать значение поля
            obj[fieldName + "Set"] = fieldWrite(nOffset, nType, nLength)    // записать значение
            obj[fieldName + "Ptr"] = fieldPtr(nOffset)                      // получить указатель поля
        }
    }
    return obj
    
    function fieldStruct(nOffset, fnGetWrp, fieldName){
        var oWrp
        return function (){
            if (this.pStruct){
                var pStruct = this.pStruct + nOffset
                if (!oWrp || oWrp.pStruct !== pStruct) oWrp = fnGetWrp(pStruct)
                //this[fieldName] = oWrp
                return oWrp
            }
        }
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
function shallowCopyObject(objInp){
    var objOut = {}
    for(var key in objInp){
        objOut[key] = objInp[key]
    }
    return objOut
}
function StrPtr(sVar){return AkelPad.MemStrPtr(sVar)}

String.prototype.StrPtr = function(){
    return AkelPad.MemStrPtr(this.toString())
}
