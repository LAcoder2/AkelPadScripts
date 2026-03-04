var args = WScript.Arguments
if (args.length === 0){
} else {
    switch (args(0)){
      case "ClearLog": ClearLog()
    }
}
//test()
function test(){
    var arr = [1.55, 222, 333]
    PrintLog(arr)     
    var obj = {opt1:"value1", opt2:"value2", opt3:"value4"}
    PrintLog(obj)    
    try{
        var i = unExisted
    }catch(err){
        PrintLog(err)
    }     
}
function ClearLog(){
    PrintLog("", 0)
}
//Вывод значения переменной value в окно лога
//append = 0 - очистка лога, вывод с первой строки/1 - вывод в этой же строке/2 - вывод с новой строки
//alias = ".js" - назначение окну лога синтаксический стиль .js
function PrintLog(value, append, alias) { 
    var strValue;
    // Преобразуем значение в строку в зависимости от его типа
    switch (typeof value) { 
    case "string":
        strValue = value;
        break;
    case "number":
        strValue = value.toString();
        break;
    case "boolean":
        strValue = value.toString();
        break;
    case "undefined":
        strValue = "undefined";
        break;
    case "object":
        if (value === null) {
            strValue = "null";
        } else if (value instanceof Array) { 
            //strValue = value.toString()
            strValue = "[\n  " + value.join(",\n  ") + "\n]"
        } else if (value instanceof Error) {
            strValue = "Error: " + value.message;
        } else {
            strValue = "{"
            for(key in value) {
                strValue += "\n  " + key + ": " + value[key]
            } 
            strValue += "\n}"
        }
        break;
    case "function":
        strValue = "[function " + (value.name || "anonymous") + "]";
        break;
    default:
        strValue = String(value);
    }
    
    // Выводим в лог с новой строки (режим добавления 2)
    // Параметр 4 = MT_LOADFONT (использовать шрифт редактора) + MT_NOCRLF (обработка переноса)
    //Call("Log::Output", 4, "TEXT", TEXTLEN, APPEND, CODEPAGE, "ALIAS")   
    if(append === undefined) append = 2
    AkelPad.Call("Log::Output", 4, strValue, -1, append, 0, alias);
}

/*
AkelPad.Include("log.js")
PrintLog("AkelPad.Call()", 1) //",2, ".js")
*/