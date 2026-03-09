//Coder.js
var hMainWnd = AkelPad.GetMainWnd()
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
    
    pos = sContent.indexOf("\"", pos) + 1       // Извлекаем строки в кавычках.
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
//Аналог Space() в VBS. Получение строки, заданной длины, заполненной пробелами
//testSpace()
//function testSpace(){
//    AkelPad.Include("log.js")
//    PrintLog("|" + Space(0) + "|")
//}
var spaceData
function Space(cnt){
    if (!spaceData){
        spaceData = {
          spaceBuf: "          ",  
          bufLen: 10 /*начальный размер пробельного буфера*/       
        }
    } 
    
    with(spaceData){
        if (bufLen < cnt){
            var ar = Array(cnt+1)
            spaceBuf = ar.join(" ")
            bufLen = cnt
        }
        
        return spaceBuf.substr(0, cnt)
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
            reRE: /([^\w*])(\/[\s\S]*?[^\\]\/)(?=[gmi]*[^\w*]*)/g, // /../     
            reC1: /(\/\/.*?(?=[\r\n]+|$)|\/\*[\s\S]*?\*\/)/g,         // /*..*/|//..  
            reC2: /^[\s\S]*?\*\/|\/\*[\s\S]*?$/g,                   // ..*/|/*.. 
            re1: /(".*?[^\\]"|'.*?[^\\]'| -{1,2}\w|-{1,2}\w|\w--|\+\+\w|\w\+\+)|\s*(===|!==|==|!=|\+=|-=|\*=|\/=|%=|>>>=|>>>|>>=|>>|>=|<<=|<<|<=|\|\||\|=|&&|&=|^=|[=\<\>\*\-+\/|&~\^])\s*/g,
            re2: /(\S)\s*(\?)\s*(.*?)\s*(\:)\s*/g,                  // (..)_(?)_(..)_(:)_..
            re0: /__PH_\d+_/g
        }
    }
    var placeholders = {}, counter = 0
    with(normalizeSpacesData){
      var ph   //Маскировка подстрок, не входящих в обработку
      var sOut = sInp
      //if(reC1.test(sInp))
          sOut = sOut.replace(reC1, function (match){
                                          ph = "__PH_" + counter++ + "_"
                                          placeholders[ph] = match
                                          return ph
                                  })
      //PrintLog("sOut = " + sOut + "\n ")
      //if(reRE.test(sOut))
          sOut = sOut.replace(reRE, function (match, match1, match2){
                                        ph = "__PH_" + counter++ + "_"
                                        placeholders[ph] = match2
                                        return match1 + ph
                                  })
      //PrintLog("sOut = " + sOut + "\n ")
      //if(reC2.test(sOut))
          sOut = sOut.replace(reC2, function (match){
                                      ph = "__PH_" + counter++ + "_"
                                      placeholders[ph] = match
                                      return ph
                              })
      //PrintLog("sOut = " + sOut + "\n ")
      //Выравнивание пробелов
      //if(re1.test(sOut))
          sOut = sOut.replace(re1, function (match, match1, match2){
                                      if(match1){
                                          return match1
                                      } else {
                                          return " " + match2 + " "
                                      }
                             })
      //if(re2.test(sOut))
          sOut = sOut.replace(re2, "$1 $2 $3 $4 ")            // (..)_(?)_(..)_(:)_..
        //PrintLog("sOut = " + sOut + "\n ")
        
      //Восстанавливаем маскированные подстроки    
      if(isObjectNoEmpty(placeholders))
          sOut = sOut.replace(re0, function (match){
                                      return placeholders[match]
                             })
    }
    return sOut
}

function isObjectNoEmpty(obj){
    for(var key in obj) return true
    return false
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
function getLineStartPos(nPos){    
    var nLine = AkelPad.SendMessage(hWndEdit, 1078 /*EM_EXLINEFROMCHAR*/, 0, nPos)
    return AkelPad.SendMessage(hWndEdit, 187 /*EM_LINEINDEX*/, nLine, 0)
}
function getLineEndPos(nPos){
    var nLine = AkelPad.SendMessage(hWndEdit, 1078 /*EM_EXLINEFROMCHAR*/, 0, nPos)
    var nLineStart = AkelPad.SendMessage(hWndEdit, 187 /*EM_LINEINDEX*/, nLine, 0)
    var nLineLength = AkelPad.SendMessage(hWndEdit, 193 /*EM_LINELENGTH*/, nLineStart, 0)
    return nLineStart + nLineLength
}
function getLineText(nPos){
    var nLine = AkelPad.SendMessage(hWndEdit, 1078 /*EM_EXLINEFROMCHAR*/, 0, nPos)
    var nLineStart = AkelPad.SendMessage(hWndEdit, 187 /*EM_LINEINDEX*/, nLine, 0)
    var nLineLength = AkelPad.SendMessage(hWndEdit, 193 /*EM_LINELENGTH*/, nLineStart, 0)
    return AkelPad.GetTextRange(nLineStart, nLineStart + nLineLength - 1)
}   