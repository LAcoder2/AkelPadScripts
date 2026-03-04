//Coder.js
var hWndEdit = AkelPad.GetEditWnd()
var oSys=AkelPad.SystemFunction()

//Возвращает массив из обозначений комментария назначенных для синтаксической темы рабочего окна
function GetSyntaxComments() {
    
    if (!hWndEdit) return
    
    var sSyntaxFile = getSyntaxFile(hWndEdit) // Получаем имя синтаксического файла для текущей вкладки
    if (!sSyntaxFile) return // Нет активной синтаксической темы

    // Получаем путь синтакс. файла
    var sCoderDir = AkelPad.GetAkelDir(4) + "\\Coder";
    var sFilePath = sCoderDir + "\\" + sSyntaxFile;
    
    // Читаем файл (флаг 0 - автоопределение кодировки)
    var sContent = AkelPad.ReadFile(sFilePath);
    if (!sContent) return

    var pos = sContent.indexOf("Quotes:")   // Ищем секцию Quotes:        
    if (pos > -1) {} else return null
    
    pos = sContent.indexOf("${COMM}", pos)  // Ищем маркер комментария ${COMM}
    if (pos > -1) {} else return null
    pos+=7
    
    pos = sContent.indexOf("\"", pos)+1       // Извлекаем строки в кавычках.
    var pos2 = sContent.indexOf("\"", pos+1)
    
    var arRes=[]
    arRes.push(sContent.slice(pos, pos2))        
    
    pos = sContent.indexOf("${COMM}", pos2+1)
    if (pos > -1){
        pos = sContent.indexOf("\"", pos+7)+1
        pos2 = sContent.indexOf("\"", pos+1)
        arRes.push(sContent.slice(pos, pos2))
        
        pos = sContent.indexOf("\"", pos2+1)+1
        pos2 = sContent.indexOf("\"", pos+1)
        arRes.push(sContent.slice(pos, pos2))
    }    
    return arRes
}
// Функция получения имени синтаксического файла
function getSyntaxFile(hWnd) {
    var lpSyntaxFile = AkelPad.MemAlloc(256 * 2)
    AkelPad.CallW("Coder::Settings", 16, hWnd, lpSyntaxFile, 256)
    var syntaxFile = AkelPad.MemRead(lpSyntaxFile, 1) // DT_UNICODE
    AkelPad.MemFree(lpSyntaxFile)
    return syntaxFile
}
// Добавление заданных отступов для каждой строчки текста

//AkelPad.Include("log.js")
//var s = normalizeSpaces(AkelPad.GetTextRange(950, 1219))
//PrintLog(addIndents(s, Space(10)))
//PrintLog(typeof re_rn)
var re_rn
function addIndents(sInp, sIndent){
    if(!re_rn) re_rn = /([\r\n]+)/gm
    return sInp.replace(re_rn, "$1" + sIndent)
}
var spaceData
function Space(cnt){
    if (!spaceData){
        spaceData = {
          spaceBuf: "",  
          bufLen: 0        
        }
    }
    with(spaceData){
        if (bufLen < cnt){
            var ar = Array(cnt-bufLen+1)
            spaceBuf += ar.join(" ")
            bufLen = cnt
        }
        
        return spaceBuf.substring(0, cnt)
    }
}
function getIndent(){
    var re 
    if (!re) re = /($\s*).*/
    var nSelStart = AkelPad.GetSelStart()
    var nLineStart = getLineStartPos(nSelStart)
    var sTxt = AkelPad.GetTextRange(nLineStart, nSelStart)
    return sTxt.replace(re, "$1")
}
// Возвращает текст с выровненными пробелами в коде, не затрагивая текстовые литералы и блоки комментариев
var normalizeSpacesData
function normalizeSpaces(sInp) {
    if(!normalizeSpacesData){
        normalizeSpacesData = {
          reBC: /\/\*([\s\S]*?)\*\//gm,
          reRe: /\/[\s\S]+\//gm,
          reC: /\/\//gm,
          reQ: /\\\"/gm,
          /* ^.*?"|".*?$|^.*?'|'.*?$  |^[\s\S]*?\x03\x04|\x01\x02[\s\S]*?$ */
          re1: /(\x01\x02[\s\S]*?\x03\x04|\x0d[\s\S]*?\x0e|\x07\x08.*?$|".*?"|'.*?')|\s*(===|==|!==|!=|\+=|-=|\*=|\/=|%=|>>>=|>>>|>>=|>>|>=|<<=|<<|<=|\|\||\|=|&&|&=|^=|[=\<\>\*\-+\/|&~\^])\s*/gm,
          re2: /(\S)\s*(\?)\s*(.*?)\s*(\:)\s*/gm,
          reQ2: /\x0b\x0c/gm,
          reC2: /\x07\x08/gm,
          reRe2: /_RE_\d+/gm, // /x0d([\S\s]+)x0e/ 
          reBC2: /\x01\x02([\s\S]*?)\x03\x04/gm
        }
    }
    var sOut, placeholders = Array(10), cnt = 0
    with(normalizeSpacesData){
      sOut = sInp.replace(reRe, function (match){  /* маскируем регекспы */
                                    placeholders[cnt] = match
                                    return "_RE_" + cnt++            
                                })
                 
      sOut = sOut.replace(reBC, "\x01\x02$1\x03\x04")   //маскируем блочные комментарии
      //PrintLog("sOut = " + sOut)
      //sOut = sOut.replace(reRe, "x0d$1x0e") 
      
      sOut = sOut.replace(reC, "\x07\x08")              // //...
      sOut = sOut.replace(reQ, "\x0b\x0c")              // ..\"..
      sOut = sOut.replace(re1, function (match1, match2, match3){ /* выравниваем пробелы */
                                  //PrintLog(match2)
                                  if(match2){
                                      return match2
                                  } else {
                                      return " " + match3 + " "
                                  }
                          })
      sOut = sOut.replace(re2, "$1 $2 $3 $4 ")          // (..)_(?)_(..)_(:)_..
          
      sOut = sOut.replace(reQ2, "\\\"")                 //убираем все маскировки
      sOut = sOut.replace(reC2, "\/\/")
      sOut = sOut.replace(reBC2, "\/\*$1\*\/")
      //PrintLog("sOut = " + sOut) 
      cnt = 0
      sOut = sOut.replace(reRe2, function (match){
                                     return placeholders[cnt++]
                                 }) 
      //sOut = sOut.replace(reRe2,"/\/$1\//")
      
    }
    return sOut
}
//Блокировка перерисовки окна
function StopRedraw(){
    AkelPad.SendMessage(hWndEdit, 11/*WM_SETREDRAW*/, false, 0)     
}
//Разблокировка перерисовки окна
function StartRedraw(){
    AkelPad.SendMessage(hWndEdit, 11, true, 0)
    oSys.Call("user32::InvalidateRect", hWndEdit, 0, true)
}
//Получение размера табулятора
function getTabSize(){
    if (AkelPad.GetArgValue("Local", false))
        return AkelPad.SendMessage(hWndEdit, 3239 /*AEM_GETTABSTOP*/, 0, 0);
    else
        return AkelPad.SendMessage(hMainWnd, 1223 /*AKD_GETFRAMEINFO*/, 52 /*FI_TABSTOPSIZE*/, 0);
}
//Получить начало линии из позиции
//function getLineStartPos(hWnd, nPos){    
//    var nLine = AkelPad.SendMessage(hWnd, 1078 /*EM_EXLINEFROMCHAR*/, 0, nPos)
//    return AkelPad.SendMessage(hWnd, 187 /*EM_LINEINDEX*/, nLine, 0)
//}

//function normalizeSpaces(sInp) {
//    try{
//    if(!normalizeSpacesData){
//        normalizeSpacesData = {
//            reBC: /\/\*([\s\S]*?)\*\//gm,
//            reC: /\/\//gm,
//            reQ: /\\\"/gm,
//            re1: /(\x01\x02[\s\S]*?\x03\x04|\x07\x08.*?$|".*?"|'.*?')|\s*(===|==|!==|!=|\+=|-=|\*=|\/=|%=|>>>=|>>>|>>=|>>|>=|<<=|<<|<=|\|\||\|=|&&|&=|^=|[=\<\>\*\-+\/|&~\^])\s*/gm,
//            re2: /(\S)\s*(\?)\s*(.*?)\s*(\:)\s*/gm,
//            reQ2: /\x0b\x0c/gm,
//            reC2: /\x07\x08/gm,
//            reBC2: /\x01\x02([\s\S]*?)\x03\x04/gm
//        }
//    }
//    with(normalizeSpacesData){
//      var sOut
//      var blBC = reBC.test(sInp)                        // /*...*/
//      if(blBC){sOut = sInp.replace(reBC, "\x01\x02$1\x03\x04");} else sOut = sInp 
//      var blC = reC.test(sOut)
//      if(blC){sOut = sOut.replace(reC, "\x07\x08");}      // //...
//      var blQ = reQ.test(sOut)
//      if(blQ){sOut = sOut.replace(reQ, "\x0b\x0c");}      // ..\"..
//      
//      bl1 = re1.test(sOut)
//      if(bl1){
//          sOut = sOut.replace(re1, 
//                              function (match1, match2, match3){
//                                  //PrintLog(match2)
//                                  if(match2){
//                                      return match2
//                                  } else {
//                                      return " " + match3 + " "
//                                  }
//                              })
//      }
//      bl2 = re2.test(sOut)
//      if(bl2){sOut = sOut.replace(re2, "$1 $2 $3 $4 ");}      // (..)_(?)_(..)_(:)_..
//      PrintLog(blBC.toString()+blC+blQ+bl1+bl2)    
//      if(blQ){sOut = sOut.replace(reQ2, "\\\"");}
//      if(blC){sOut = sOut.replace(reC2, "\/\/");}
//      if(blBC){sOut = sOut.replace(reBC2, "\/\*$1\*\/");}
//    }
//    }catch(e){
//         PrintLog(e.description())
//    }
//    return sOut;
//}

/*
arr1 = [1,2,3,4,5];
WScript.Echo(arr1.length)
arr1.pop()
WScript.Echo(arr1.length)

*/