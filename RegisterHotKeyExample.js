AkelPad.Include("log.js")
AkelPad.Include("MemHelp.js")
var hMainWnd=AkelPad.GetMainWnd()

testRegisterHotkey()
function testRegisterHotkey(){
    //RegisterHotkey("TabSwitch.js", GetHotkeyCode(9, true)) // регистрация обработчика Ctrl+Tab
    //RegisterHotkey("TabSwitch.js", 0)                      // разрегистрация обработчика
    //PrintLog(RegisterHotkey("Test3.js", 0))     
    PrintLog(RegisterHotkey("Test3.js", 593)) 
}
// Получить код клавиатурного сочетания. Пример:
// WScript.Echo(GetHotkeyCode(9, true)) //получение кода сочетания Ctrl + Tab
function GetHotkeyCode(keyCode, ctrl, shift, alt) {
    if (shift) keyCode |= 0x100
    if (ctrl)  keyCode |= 0x200
    if (alt)   keyCode |= 0x400
    return keyCode;
}
// Регистрация клавиатурного сочетания. Пример (назначение сочетания Ctrl + Q для скрипта TestHotkey.js):
// RegisterHotkey("TestHotKey.js", GetHotkeyCode("Q".charCodeAt(0), true)) //
// Является портом одноименной функции из исходных файлов плагина Scripts (Scripts.c)
function RegisterHotkey(wszScriptName, wHotkey){
//    try{
//    var nstep = 0
    var pfElement                           // Указатель на структуру функции плагина
    var wszHotkeyOwner = makeStrBuff(260)   // Имя владельца, если клавиша занята
    
    // Формируем полное имя функции для регистрации: "Scripts::Main::имя_скрипта"
    var wszPrefix = "Scripts::Main::"
    var wszFunction = wszPrefix + wszScriptName
      
    // Проверяем, не занята ли уже эта комбинация клавиш
    var nOwner = AkelPad.SendMessage(hMainWnd, 1338/*AKD_CHECKHOTKEY*/, wHotkey, wszHotkeyOwner.StrPtr())
    if (!nOwner){
        // Пытаемся найти уже зарегистрированную функцию с таким именем
        // if (pfElement = (PLUGINFUNCTION *)SendMessage(hMainWnd, AKD_DLLFINDW, (WPARAM)wszFunction, 0)) {
        if (pfElement = AkelPad.SendMessage(hMainWnd, 1331/*AKD_DLLFINDW*/, wszFunction.StrPtr(), 0)) { 
            // Функция уже существует - просто обновляем её горячую клавишу
            var opf = PLUGINFUNCTIONwrp(pfElement)      // Создаем объект-враппер структуры PLUGINFUNCTION
            //PrintLog("Замена сочетания")
            // Если клавиша сброшена (0) и функция не активна и не в автозагрузке то удаляем её из системы
			// if (!pfElement->wHotkey && !pfElement->bRunning && !pfElement->bAutoLoad)
			// SendMessage(hMainWnd, AKD_DLLDELETE, 0, (LPARAM)pfElement);
			if(!wHotkey && !opf.bRunning() && !opf.bAutoLoad()){
			    AkelPad.SendMessage(hMainWnd, 1335/*AKD_DLLDELETE*/, 0, pfElement)
			    // PrintLog("Удаление обработчика")
			} else opf.wHotkeySet(wHotkey)                  //pfElement->wHotkey = wHotkey;
        } else {
            // Функция не найдена - создаем новую, если есть клавиша для назначения
			if (wHotkey) {
			    var spa = makeStrBuff(16)                   // выделяем память под структуру PLUGINADDW, 32/2 - размер структуры (в x64)
			    var ppa = spa.StrPtr()
                var opa = PLUGINADDWwrp(ppa)            // Создаем объект-враппер структуры PLUGINADDW
			    // pa.pFunction = wszFunction;   
                opa.pFunctionSet(wszFunction.StrPtr())      // Имя функции
				// pa.wHotkey = wHotkey;  
                opa.wHotkeySet(wHotkey)                         
				// pa.PluginProc = HotkeyProc;   
                var HotkeyProc = GetHotkeyProc()            // callback-Функция-обработчик
                if (!HotkeyProc){
                    WScript.Echo("Не получен адрес HotkeyProc (внутреняя процедура обработки хоткеев плагина Scripts), \n" +
                                 "необходимой для регистарции клав. сочетаний!")
                    return false
                }
				opa.PluginProcSet(HotkeyProc)
				
				// Регистрируем новую функцию в ядре AkelPad
				// if (pfElement = (PLUGINFUNCTION *)SendMessage(hMainWnd, AKD_DLLADDW, 0, (LPARAM)&pa)) {
				if (pfElement = AkelPad.SendMessage(hMainWnd, 1334/*AKD_DLLADDW*/, 0, ppa)){
				    // PrintLog("Успешная регистрация новой функции в ядро AkelPad!")
				    // Устанавливаем параметр для обработчика - указатель на имя скрипта
					// lpParameter будет передан в HotkeyProc при нажатии
					// pfElement->lpParameter = pfElement->wszFunction + xstrlenW(wszPrefix)
					opf = PLUGINFUNCTIONwrp(pfElement)
					opf.lpParameterSet(opf.wszFunctionPtr() + wszPrefix.length * 2)
				}
			}
        }
        return true
    } else {
        var nLen = wszHotkeyOwner.indexOf("\0", 0)
        var sHotkeyOwner = wszHotkeyOwner.substr(0, nLen)
        if (wszFunction !== sHotkeyOwner) {
            WScript.Echo("Комбинация уже занята действием:\n" + sHotkeyOwner)
            return false
        } else 
            return true
    }
//    }catch(e){
//        PrintLog(e.description + "\n" + nstep)
//    }
}

// var hMainWnd = AkelPad.GetMainWnd(); AkelPad.Include("log.js"); AkelPad.Include("MemHelp.js"); testGetHotkeyProc()
function testGetHotkeyProc(){
    PrintLog(GetHotkeyProc(9))
    PrintLog(GetHotkeyProc(521))
    PrintLog(GetHotkeyProc(587))
    PrintLog(GetHotkeyProc(265))
}
function GetHotkeyProc(wHotkey){
    if(!wHotkey) wHotkey = 265 // Shift + Tab
    var wszHotkeyOwner = makeStrBuff(260) // Имя процедуры, назначенной на клавишу
    var pwszHotkeyOwner = StrPtr(wszHotkeyOwner)
    if (AkelPad.SendMessage(hMainWnd, 1338/*AKD_CHECKHOTKEY*/, wHotkey, pwszHotkeyOwner)){
        var pfElement = AkelPad.SendMessage(hMainWnd, 1331/*AKD_DLLFINDW*/, pwszHotkeyOwner, 0)
        if (pfElement) return PLUGINFUNCTIONwrp(pfElement).PluginProc() 
    } 
}

/*typedef struct {            // смещения (x64/x86) 
  const wchar_t *pFunction;   // 0/0      Function name, format "Plugin::Function".
  WORD wHotkey;               // 8/4      Function hotkey. See HKM_GETHOTKEY message return value (MSDN).
  BOOL bAutoLoad;             // 12/8     TRUE  if function has autoload flag.
                              //            FALSE if function has no autoload flag.
  PLUGINPROC PluginProc;      // 16/12    Function procedure.
  void *lpParameter;          // 24/16    Procedure parameter.
} PLUGINADDW;                 // 32/20    Общий размер*/  
// Создание объекта-враппера структуры PLUGINADDW
function PLUGINADDWwrp(pStruct, oStruct, fullInit){
    var aOffsets = (_X64)?[32,8,12,16,24]:[20,4,8,12,16]
    var aDataFields = ['pFunction', 8,
                       'wHotkey', 4,
                       'bAutoLoad', 3,
                       'PluginProc', 2,
                       'lpParameter', 2]
    return (PLUGINADDWwrp = function (pStruct, oStruct, fullInit){
        return makeStructWrapper(pStruct, oStruct, fullInit, aOffsets, aDataFields)
    })(pStruct, oStruct, fullInit)
}
//function PLUGINADDWwrp(pStruct, oStruct){
//    return oStruct = makeStructWrapper(pStruct, oStruct, (_X64 ? 32 : 20), 0, 
//                            "pFunction", 0, 2,
//                            "wHotkey", (_X64 ? 8 : 4), 4,  
//                            "bAutoLoad", (_X64 ? 12 : 8), 3,
//                            "PluginProc", (_X64 ? 16 : 12), 2,
//                            "lpParameter", (_X64 ? 24 : 16), 2)
//} 
/*typedef struct {      
    struct _PLUGINFUNCTION *next;     // 0 : 0      — указатель на следующий элемент в списке
    struct _PLUGINFUNCTION *prev;     // 8 : 4      — указатель на предыдущий элемент в списке
    const BYTE *pFunction;            // 16 : 8     — указатель на имя функции
                                      //                  Формат: "Plugin::Function"
                                      //                  const char *pFunction      если bOldWindows == TRUE
                                      //                  const wchar_t *pFunction   если bOldWindows == FALSE
    char szFunction[MAX_PATH];        // 24 : 12    — имя функции в ANSI кодировке (260 байт)
    wchar_t wszFunction[MAX_PATH];    // 284 : 272  — имя функции в Unicode кодировке (520 байт)
                                      //                  Максимум MAX_PATH символов (обычно 260)
    int nFunctionLen;                 // 804 : 792  — длина имени функции в символах
    WORD wHotkey;                     // 808 : 796  — горячая клавиша функции
                                      //                  Формат: старший байт = флаги модификаторов (HOTKEYF_*)
                                      //                  младший байт = виртуальный код клавиши (VK_*)
                                      //                  См. документацию по HKM_GETHOTKEY в MSDN
    BOOL bAutoLoad;                   // 812 : 800  — флаг автозагрузки функции
                                      //                  TRUE  — функция загружается автоматически при старте
                                      //                  FALSE — функция не загружается автоматически
    BOOL bRunning;                    // 816 : 804  — флаг выполнения функции
                                      //                  TRUE  — функция выполняется в данный момент
                                      //                  FALSE — функция не выполняется
    PLUGINPROC PluginProc;            // 824 : 808  — указатель на функцию-обработчик
                                      //                  Прототип: BOOL CALLBACK PluginProc(void *lpParameter, LPARAM lParam, DWORD dwSupport)
    void *lpParameter;                // 832 : 812  — пользовательские данные для обработчика
                                      //                  В случае Scripts плагина: указатель на имя скрипта
    int nRefCount;                    // 840 : 816  — счётчик ссылок (внутреннее использование)
                                      //                  Используется для управления временем жизни структуры
} PLUGINFUNCTION;                     // 848 : 820  — размер структуры (820/848 байт)*/
// Создание объекта-враппера структуры PLUGINFUNCTION
function PLUGINFUNCTIONwrp(pStruct, oStruct, fullInit){
    var aOffsets = (_X64)?[848,8,16,24,284,804,808,812,816,824,832,840]:[820,4,8,12,272,792,796,800,804,808,812,816]
    var aDataFields = ['next', 9, PLUGINFUNCTIONwrp,
                       'prev', 9, PLUGINFUNCTIONwrp,
                       'pFunction', 2,
                       'szFunction', 0, -1, /*MAX_PATH = 260*/
                       'wszFunction', 1, -1, /*MAX_PATH = 260*/
                       'nFunctionLen', 3,
                       'wHotkey', 4,
                       'bAutoLoad', 3,
                       'bRunning', 3,
                       'PluginProc', 2,
                       'lpParameter', 2,
                       'nRefCount', 3]
    return (PLUGINFUNCTIONwrp = function (pStruct, oStruct, fullInit){
        return makeStructWrapper(pStruct, oStruct, fullInit, aOffsets, aDataFields)
    })(pStruct, oStruct, fullInit)
}
//function PLUGINFUNCTIONwrp(pStruct, oStruct){
//    return oStruct = makeStructWrapper(pStruct, oStruct, (_X64 ? 0x350 : 0x334), 0, 
//                                /*"next", 0, 2,
//                                "prev", (_X64 ? 8 : 4), 2,*/
//                                "wszFunction", (_X64 ? 284 : 272), 1, -1,
//                                "wHotkey", (_X64 ? 808 : 796), 4,  
//                                "bAutoLoad", (_X64 ? 812 : 800), 3,
//                                "bRunning", (_X64 ? 816 : 804), 3,
//                                "PluginProc", (_X64 ? 824 : 808), 2,
//                                "lpParameter", (_X64 ? 832 : 812), 2)
//} 

//testtest(); WScript.Quit()
function testtest(){
    var wszHotkeyOwner = makeStrBuff(260) // Имя владельца, если клавиша занята
    var wHotkey = 593
    // Формируем полное имя функции для регистрации: "Scripts::Main::имя_скрипта"
    var wszPrefix = "Scripts::Main::"
    //var wszFunction = wszPrefix + wszScriptName
    
    //Проверяем, не занята ли уже эта комбинация клавиш
    var nOwner = AkelPad.SendMessage(hMainWnd, 1338/*AKD_CHECKHOTKEY*/, wHotkey, wszHotkeyOwner.StrPtr())
    if (!nOwner) return
    var pfElement = AkelPad.SendMessage(hMainWnd, 1331/*AKD_DLLFINDW*/, wszHotkeyOwner.StrPtr(), 0)
    var opf = PLUGINFUNCTIONwrp(pfElement) 
//    try{
    var pnext
    PrintLog(opf.PluginProc())
    
    while(pnext = opf.prev()){
       opf.pStruct = pnext
       PrintLog(opf.PluginProc())
    }
//    }catch(e){
//        PrintLog(e.description)
//        //PrintLog(opf)
//    }
}