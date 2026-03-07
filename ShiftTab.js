AkelPad.Include("log.js")
AkelPad.Include("Coder.js")
var hWndEdit = AkelPad.GetEditWnd()

nTabSize = getTabSize()
sTab = Space(nTabSize)            
   
function main() {    
    var selStart = AkelPad.GetSelStart()
    var selEnd = AkelPad.GetSelEnd()

    // Проверяем, есть ли выделение
    if (selStart === selEnd) {
        processNoSelection(selStart)          // Выделения нет - проверяем 4 пробела перед курсором
    } else {
        processSelection(selStart, selEnd)    // Есть выделение - обрабатываем каждую строку
        //AkelPad.Command(4166)
    }
} 
main();

// Обработка случая без выделения
function processNoSelection(cursorPos) {
    var lineStartPos = getLineStartPos(cursorPos) // Получаем позицию начала текущей строки    
    
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
        PrintLog(e.description)
        StartRedraw()
    }    
}

// Обработка выделенного текста
function processSelection(selStart, selEnd) {
    var fstlineStartPos = getLineStartPos(selStart) // Получаем позицию начала первой строки выделения
    var endlineStartPos = getLineStartPos(selEnd)
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
        PrintLog(e.description)
      StartRedraw()
    }
}