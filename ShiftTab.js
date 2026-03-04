//AkelPad.ScriptNoMutex()
AkelPad.Include("Coder.js")
AkelPad.Include("log.js")
var hMainWnd=AkelPad.GetMainWnd()
var hWndEdit = AkelPad.GetEditWnd()
nTabSize = getTabSize()
sTab = Space(nTabSize)            

function main() {    
    var selStart = AkelPad.GetSelStart()
    var selEnd = AkelPad.GetSelEnd()

    // Проверяем, есть ли выделение
    if (selStart === selEnd) {
        processNoSelection(hWndEdit, selStart)          // Выделения нет - проверяем 4 пробела перед курсором
    } else {
        processSelection(hWndEdit, selStart, selEnd)    // Есть выделение - обрабатываем каждую строку
        //AkelPad.Command(4166)
    }
} 
main();

// Обработка случая без выделения
function processNoSelection(hWndEdit, cursorPos) {
    var lineStartPos = getLineStartPos(hWndEdit, cursorPos) // Получаем позицию начала текущей строки    
    
    cursorPos2 = cursorPos - lineStartPos
    
    if (cursorPos2 > 0) {} else retrun 
    
    var off = cursorPos2 % nTabSize                                // получаем необходимую длину смещения строки перед курсором, если в ней есть пробелы
    if (!off) off = nTabSize
    
    var offChars = AkelPad.GetTextRange(cursorPos - off, cursorPos) // получаем символы смещения
    
    try {
        StopRedraw()
        if (/^\s+$/.test(offChars)) {                           // проверяем являтся ли символы смещения пробелами
            AkelPad.SetSel(cursorPos - off, cursorPos)          // Удаляем символы смещения
            AkelPad.ReplaceSel("")        
        } else if (/\s+$/.test(offChars)) {                     // проверяем есть ли пробелы справа
            off = 0
            for (var i = offChars.length-2; i > 0 ; --i) {      // ищем непробельный символ
                if (offChars.charAt(i) !== " ") break
                ++off
            }
            AkelPad.SetSel(cursorPos - off, cursorPos)          // Удаляем прбелы до непробельного символа (оставляя один пробел)
            AkelPad.ReplaceSel("")
        }
        StartRedraw()
    }catch (e){
        StartRedraw()
    }    
}

// Обработка выделенного текста
function processSelection(hWndEdit, selStart, selEnd) {
    var fstlineStartPos = getLineStartPos(hWndEdit, selStart) // Получаем позицию начала первой строки выделения
    var endlineStartPos = getLineStartPos(hWndEdit, selEnd)
    var lastLineEndPos = endlineStartPos + AkelPad.SendMessage(hWndEdit, 193 /*EM_LINELENGTH*/, endlineStartPos, 0)
    
    var sText = AkelPad.GetTextRange(fstlineStartPos, lastLineEndPos) // Получаем строки, которые затрагивает выделение   
    var nPrevLen = sText.length
    var re = new RegExp("^(\\/\\/|)(" + sTab + ")", "gm")
    sText = sText.replace(re, "$1")
    
    try{
      StopRedraw()
        AkelPad.SetSel(fstlineStartPos, lastLineEndPos)         // Заменяем выделенный текст на смещенный
        AkelPad.ReplaceSel(sText)
        
        lastLineEndPos-=(nPrevLen - sText.length)
        AkelPad.SetSel(fstlineStartPos, lastLineEndPos)               // восстанавливаем выделение с учетом смещения
      StartRedraw()
    }catch(e){
      StartRedraw()
    }
}
//function processSelection(hWndEdit, selStart, selEnd) {
//    var fstlineStartPos = getLineStartPos(hWndEdit, selStart); // Получаем позицию начала первой строки выделения
//    var lastLineEndPos = selEnd + AkelPad.SendMessage(hWnd, 193 /*EM_LINELENGTH*/, selEnd, 0)
//    var selectedLines = AkelPad.GetTextRange(fstlineStartPos, lastLineEndPos) // Получаем строки, которые затрагивает выделение   
//    //var lines = selectedLines.split("\r")           // Разделяем на строки
//    var re = /$(\/\/)?(\s+)/gm
//    var off
//    var selEnd2 = selEnd
//    
//    // Обрабатываем первую строку   
//    var sLine = lines[0]
//    if (sLine.length > 0) {
//        if (sLine.length < nTabSize) {
//            off = sLine.length 
//        } else {            
//            off = nTabSize
//        }
//        if (/^\s+$/.test(sLine.substring(0, off))) {
//            lines[0] = sLine.substring(off)         // Удаляем символы смещения
//            selStart -= off
//            if (selStart < fstlineStartPos) {
//                selStart = fstlineStartPos
//            }
//            selEnd2 -= off
//        }
//    }
//    // Обрабатываем остальные строки
//    for (var i = 1; i < lines.length; i++) {
//        sLine = lines[i]
//        if (sLine.length > 0) {
//            if (sLine.length < nTabSize) off = sLine.length; else off = nTabSize
//            if (/^\s+$/.test(sLine.substring(0, off))) {
//                lines[i] = sLine.substring(off)     // Удаляем символы смещения
//                selEnd2 -= off
//            }
//        }
//    }
//    
//    var newText = lines.join("\r");                 // Соединяем строки обратно
//    
//    AkelPad.SetSel(fstlineStartPos, selEnd)         // Заменяем выделенный текст на смещенный
//    AkelPad.ReplaceSel(newText)
//    
//    AkelPad.SetSel(selStart, selEnd2)               // восстанавливаем выделение с учетом смещения
//    // AkelPad.SetSel(fstlineStartPos, selEnd2)     // вариант с полным выделением первой строки (классический)  
//}

// Получаем позицию начала текущей строки
function getLineStartPos(hWnd, nPos){    
    var nLine = AkelPad.SendMessage(hWnd, 1078 /*EM_EXLINEFROMCHAR*/, 0, nPos)
    return AkelPad.SendMessage(hWnd, 187 /*EM_LINEINDEX*/, nLine, 0)
}