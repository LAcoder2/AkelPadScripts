//CommentsAdd2.js
with (AkelPad){
//    include("log.js")
    Include("Coder.js")
    var hMainWnd = GetMainWnd()
    var hWndEdit = GetEditWnd()

    var selStart = GetSelStart()
    var selEnd = GetSelEnd()    
    var selText = GetSelText()
    var lineStart = getLineStartPos(selStart)
    
    var comms = GetSyntaxComments()
    if (comms === null || comms.length === 0){
        WScript.Echo("В синтаксической теме текущей вкладки отсутствуют обозначения комментариев!")
        WScript.Quit()
    }
      
    if (lineStart !== selStart){        
        if(selStart !== selEnd && comms.length === 3){
            selText = comms[1] + selText + comms[2]
            ReplaceSel(selText)
            SetSel(selStart, selStart+selText.length)
        } else {
            SetSel(lineStart, lineStart)
            ReplaceSel(comms[0])
            sleStart+=2
            var commLen = comms[0].length
            SetSel(selStart + commLen, selEnd + commLen)
        }        
    }else{
        var lines = selText.split("\r") 
        var n = 0
        if(lines[lines.length-1].length === 0){
            lines.pop()
            SetSel(selStart, selEnd-1) 
            n = 1
        }
        selText = comms[0]+lines.join("\n"+comms[0])
        ReplaceSel(selText)
        
        SetSel(selStart, selStart + selText.length + n)         
    }
}
