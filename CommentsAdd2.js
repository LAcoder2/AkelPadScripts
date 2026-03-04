//CommentsAdd2.js
with (AkelPad){
//    include("log.js")
    Include("Coder.js")
    var hMainWnd = GetMainWnd()
    var hWndEdit = GetEditWnd()

    var selStart = GetSelStart()
    var selEnd = GetSelEnd()    
    var selText = GetSelText()
    var lineStart = getLineStartPos(hWndEdit, selStart)
    
    var comms = GetSyntaxComments()
    if (comms === null || comms.length === 0){
        WScript.Echo("¬ синтаксической теме текущей вкладки отсутствуют обозначени€ комментариев!")
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

//ѕолучить начало линии из позиции
function getLineStartPos(hWnd, nPos){    
    var nLine = AkelPad.SendMessage(hWnd, 1078 /*EM_EXLINEFROMCHAR*/, 0, nPos)
    return AkelPad.SendMessage(hWnd, 187 /*EM_LINEINDEX*/, nLine, 0)
}

/*
arr1 = [1,2,3,4,5];
WScript.Echo(arr1.length)
arr1.pop()
WScript.Echo(arr1.length)

*/