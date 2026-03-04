// http://akelpad.sourceforge.net/forum/viewtopic.php?p=1653#1653
// Description(1033): Decommented text or block of text
// 	variants comments see included CommentsExt.js
// Description(1049): Раскомментирование строки или текстового блока
// Version: 3.9 (2014.12.06)
// Author: VladSh
// 
// Usage:
// 	1. By Hotkeys-plugin: proposed to use a keyboard shortcut in Scripts-plugin box: Ctrl + \
// 	2. With arguments:
// 		• smbStart - start symbols for declose
// 		• smbEnd - end symbols for declose
// 		Example: -"Убрать кавычки «_|_»" Call("Scripts::Main", 1, "CommentsDel.js", `-smbStart="«" -smbEnd="»"`)
AkelPad.ScriptNoMutex()

if (! AkelPad.Include("CommentsExt.js")) WScript.Quit();
if (! AkelPad.Include("selCompleteLine.js")) WScript.Quit();

if (WScript.Arguments.length) {
	cBlockOpen = AkelPad.GetArgValue("smbStart", "");
	cBlockClose = AkelPad.GetArgValue("smbEnd", "");
}
else {
	if (! AkelPad.Include("CoderFunctions.js")) WScript.Quit();
	setComments(GetSyntaxAliasExtension());
}

oCh.run();

function process() {
	var bSimple = false;
	var nCaretPos = AkelPad.GetSelEnd();
	var pSelText = "";
	
	if (cSimple != null) {
		//Проверка: строчный или блочный комментарий
		oCh.setCompleteLineText();
		
		if (oCh.Text.indexOf(cSimple) != -1)			//работа со СТРОЧНЫМИ комментариями
		{
			pSelText = oCh.Text;		//запоминаем для корректировки позиции курсора на количество убранных комментариев
			
			var arrText = oCh.Text.split(pBreak);
			for (var nLine = 0; nLine < arrText.length; nLine++)
				arrText[nLine] = arrText[nLine].replace(cSimple, "");
			oCh.Text = arrText.join(pBreak);
			
			nCaretPos -= (pSelText.length - oCh.Text.length);
			if (nCaretPos < oCh.rResult[0]) nCaretPos = oCh.rResult[0];	//когда каретка изначально стоит прямо на комментарии вводим коррективы..
			bSimple = true;
		}
	}
	
	if (!bSimple && cBlockOpen) {			//работа с БЛОЧНЫМ комментарием
		oCh.rResult = getRangebyBorders(nCaretPos, nCaretPos, cBlockOpen, cBlockClose, true);
		if (oCh.rResult == null)
			quitIsNotComment();		//если хоть какая-то часть коммента не найдена, значит неверно установлена каретка
		
		oCh.Text = getTextbyRange(oCh.rResult);
		
		oCh.Text = oCh.Text.substr(cBlockOpen.length, oCh.Text.length - cBlockOpen.length - cBlockClose.length - (oCh.Text.charAt(oCh.Text.length) == pBreak));		//берём строку без переднего и заднего комментов; последняя часть в скобках - захват перевода строки в многострочных комментариях
		
		if (oCh.Text.indexOf(cBlockOpen) != -1 || (oCh.Text.indexOf(cBlockClose) != -1))
			quitIsNotComment();		//если внутри текста найден противоположный коммент, считаем что неверно установлена каретка
		
		pSelText = oCh.Text;		//запоминаем для корректировки позиции курсора на количество съедаемых вначале переводов строк
		//продолжение корректировки текста: гасим ненужные переводы строк
		oCh.Text = oStr.ltrim(oCh.Text, pBreak);
		nCaretPos -= (cBlockOpen.length + (pSelText.length - oCh.Text.length));		//вычисляем здесь, т.к. для сдвига каретки нужна только верхняя часть: размер открывающего коммента и возможный перевод строки
		oCh.Text = oStr.rtrim(oCh.Text, pBreak);
	}
	
	oCh.setSelCaret(nCaretPos);
}

function quitIsNotComment() {
	AkelPad.MessageBox(AkelPad.GetEditWnd(), "Курсор установлен не в строке, где есть комментарий, либо за пределами блока комментария.", WScript.ScriptName, 64 /*MB_INFORMATION*/);
	WScript.Quit();
}