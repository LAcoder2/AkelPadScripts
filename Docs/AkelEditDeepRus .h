#ifndef __AKELEDIT_H__
#define __AKELEDIT_H__


//// Включаемые файлы

#include <richedit.h>
#include <shellapi.h>


//// Определения

#define AES_AKELEDITA            "AkelEditA"
#define AES_AKELEDITA_UNICODE   L"AkelEditA"
#define AES_AKELEDITW_ANSI       "AkelEditW"
#define AES_AKELEDITW           L"AkelEditW"
#define AES_RICHEDIT20A          "RichEdit20A"
#define AES_RICHEDIT20A_UNICODE L"RichEdit20A"
#define AES_RICHEDIT20W_ANSI     "RichEdit20W"
#define AES_RICHEDIT20W         L"RichEdit20W"

//AEM_CONTROLCLASS
#define AECLASS_AKELEDIT        1
#define AECLASS_RICHEDIT        2

//Стили окна
#ifndef ES_MULTILINE
  #define ES_MULTILINE        0x00000004  //См. AECO_MULTILINE.
#endif
#ifndef ES_NOHIDESEL
  #define ES_NOHIDESEL        0x00000100  //См. AECO_NOHIDESEL.
#endif
#ifndef ES_READONLY
  #define ES_READONLY         0x00000800  //См. AECO_READONLY.
#endif
#ifndef ES_WANTRETURN
  #define ES_WANTRETURN       0x00001000  //См. AECO_WANTRETURN.
#endif
#ifndef ES_DISABLENOSCROLL
  #define ES_DISABLENOSCROLL  0x00002000  //См. AECO_DISABLENOSCROLL.
#endif
#define ES_GLOBALUNDO         0x00004000  //Использовать кучу процесса для Undo/Redo вместо кучи окна. Требуется для AEM_DETACHUNDO и AEM_ATTACHUNDO.
                                          //Совместимость: определено так же, как ES_SUNKEN.
#define ES_HEAPSERIALIZE      0x00008000  //Взаимное исключение будет использоваться, когда функции кучи выделяют и освобождают память из кучи окна. Сериализация доступа к куче позволяет двум или более потокам одновременно выделять и освобождать память из одной кучи.
                                          //Совместимость: определено так же, как ES_SAVESEL.

//Строки
#define AES_WORDDELIMITERSW     L" \t\n'`\"\\|[](){}<>,.;:+-=~!@#$%^&*/?\0\0"
#define AES_WRAPDELIMITERSW     L" \t\0\0"
#define AES_URLLEFTDELIMITERSW  L" \t\n'`\"(<{[=\0\0"
#define AES_URLRIGHTDELIMITERSW L" \t\n'`\")>}]\0\0"
#define AES_URLPREFIXESW        L"http:\0https:\0www.\0ftp:\0file:\0mailto:\0\0"

//Флаги AEM_SETEVENTMASK
#define AENM_SCROLL             0x00000001  //Отправляет уведомления AEN_HSCROLL и AEN_VSCROLL.
#define AENM_PAINT              0x00000002  //Отправляет уведомления AEN_PAINT.
#define AENM_MAXTEXT            0x00000010  //Не использовать. Только для внутреннего кода.
#define AENM_PROGRESS           0x00000020  //Отправляет уведомления AEN_PROGRESS.
#define AENM_MODIFY             0x00000040  //Отправляет уведомления AEN_MODIFY.
#define AENM_SELCHANGE          0x00000080  //Отправляет уведомления AEN_SELCHANGING и AEN_SELCHANGED.
#define AENM_TEXTCHANGE         0x00000100  //Отправляет уведомления AEN_TEXTCHANGING и AEN_TEXTCHANGED.
#define AENM_TEXTINSERT         0x00000200  //Отправляет уведомления AEN_TEXTINSERTBEGIN и AEN_TEXTINSERTEND.
#define AENM_TEXTDELETE         0x00000400  //Отправляет уведомления AEN_TEXTDELETEBEGIN и AEN_TEXTDELETEEND.
#define AENM_POINT              0x00000800  //Отправляет уведомления AEN_POINT.
#define AENM_DROPFILES          0x00010000  //Отправляет уведомления AEN_DROPFILES.
#define AENM_DRAGDROP           0x00020000  //Отправляет уведомления AEN_DROPSOURCE и AEN_DROPTARGET.
#define AENM_LINK               0x00040000  //Отправляет уведомления AEN_LINK.
#define AENM_MARKER             0x00080000  //Отправляет уведомления AEN_MARKER.

//Типы AEN_SELCHANGING и AEN_SELCHANGED
#define AESCT_REPLACESEL        0x00000001  //Замена выделения.
#define AESCT_APPENDTEXT        0x00000002  //Добавление текста.
#define AESCT_SETTEXT           0x00000004  //Установка текста.
#define AESCT_STREAMIN          0x00000008  //Потоковый ввод.
#define AESCT_WRAP              0x00000010  //Отправка AEM_SETWORDWRAP.
#define AESCT_UNDO              0x00000020  //Отмена действия.
#define AESCT_REDO              0x00000040  //Повтор действия.
#define AESCT_CUT               0x00000080  //Вырезание.
#define AESCT_CHAR              0x00000100  //Вставка символа.
#define AESCT_KEYRETURN         0x00000200  //Нажатие VK_RETURN.
#define AESCT_KEYBACKSPACE      0x00000400  //Нажатие VK_BACK.
#define AESCT_KEYDELETE         0x00000800  //Нажатие VK_DELETE.
#define AESCT_DRAGDELETE        0x00001000  //Удаление текста при перетаскивании.
#define AESCT_DROPINSERT        0x00002000  //Вставка текста при сбросе.

#define AESCT_MOUSESINGLECLK    0x00100000  //Одиночный щелчок мыши.
#define AESCT_MOUSEDOUBLECLK    0x00200000  //Двойной щелчок мыши.
#define AESCT_MOUSETRIPLECLK    0x00400000  //Тройной щелчок мыши.
#define AESCT_MOUSECAPTURE      0x00800000  //Мышь сделала непустое выделение.
#define AESCT_MOUSELEFTMARGIN   0x01000000  //Действие мыши на левом поле.
#define AESCT_KEYBOARD          0x02000000  //Выделение изменено клавиатурой.
#define AESCT_SETSELMESSAGE     0x04000000  //Отправка AEM_EXSETSEL, AEM_SETSEL, EM_SETSEL, EM_EXSETSEL.
#define AESCT_UPDATESELECTION   0x08000000  //Выделение обновлено.
#define AESCT_IME               0x10000000  //Редактор методов ввода (IME).

//Типы AEN_TEXTCHANGING, AEN_TEXTINSERTBEGIN, AEN_TEXTINSERTEND, AEN_TEXTDELETEBEGIN, AEN_TEXTDELETEEND и AEN_TEXTCHANGED
#define AETCT_REPLACESEL        0x00000001  //Замена выделения.
#define AETCT_APPENDTEXT        0x00000002  //Добавление текста.
#define AETCT_SETTEXT           0x00000004  //Установка текста.
#define AETCT_STREAMIN          0x00000008  //Потоковый ввод.
#define AETCT_WRAP              0x00000010  //Отправка AEM_SETWORDWRAP.
#define AETCT_UNDO              0x00000020  //Отмена действия.
#define AETCT_REDO              0x00000040  //Повтор действия.
#define AETCT_CUT               0x00000080  //Вырезание.
#define AETCT_CHAR              0x00000100  //Вставка символа.
#define AETCT_KEYRETURN         0x00000200  //Нажатие VK_RETURN.
#define AETCT_KEYBACKSPACE      0x00000400  //Нажатие VK_BACK.
#define AETCT_KEYDELETE         0x00000800  //Нажатие VK_DELETE.
#define AETCT_DRAGDELETE        0x00001000  //Удаление текста при перетаскивании.
#define AETCT_DROPINSERT        0x00002000  //Вставка текста при сбросе.
#define AETCT_COLUMNGROUP       0x00004000  //Отмена/Повтор для колоночного текста сгруппирована из действий на одной строке.

//Типы AEN_TEXTCHANGED
#define AETCT_NONE              0x00100000  //Текст не изменен.
#define AETCT_DELETEALL         0x00200000  //Указывает, что из-за действия AETCT_* был изменен весь текст.

//Флаги вставки текста
#define AEINST_LOCKUNDO          0x00000001
#define AEINST_LOCKSCROLL        0x00000002
#define AEINST_LOCKUPDATEHSCROLL 0x00000004
#define AEINST_LOCKUPDATEVSCROLL 0x00000008
#define AEINST_LOCKUPDATECARET   0x00000010
#define AEINST_LOCKUPDATETEXT    0x00000020
#define AEINST_LOCKUPDATEALL    (AEINST_LOCKUPDATEHSCROLL |\
                                 AEINST_LOCKUPDATEVSCROLL |\
                                 AEINST_LOCKUPDATECARET   |\
                                 AEINST_LOCKUPDATETEXT)

//Флаги удаления текста
#define AEDELT_LOCKUNDO          0x00000001
#define AEDELT_LOCKSCROLL        0x00000002
#define AEDELT_LOCKUPDATEHSCROLL 0x00000004
#define AEDELT_LOCKUPDATEVSCROLL 0x00000008
#define AEDELT_LOCKUPDATECARET   0x00000010
#define AEDELT_LOCKUPDATETEXT    0x00000020
#define AEDELT_SAVECOLUMNSEL     0x00000040
#define AEDELT_LOCKUPDATEALL    (AEDELT_LOCKUPDATEHSCROLL |\
                                 AEDELT_LOCKUPDATEVSCROLL |\
                                 AEDELT_LOCKUPDATECARET   |\
                                 AEDELT_LOCKUPDATETEXT)

//Типы AEN_POINT
#define AEPTT_SETTEXT           0x00000001  //Весь текст документа был изменен. Все точки сброшены на первый символ.
#define AEPTT_STREAMIN          0x00000002  //Весь текст документа был изменен. Все точки сброшены на первый символ.
#define AEPTT_INSERT            0x00000004  //Операция вставки.
#define AEPTT_DELETE            0x00000008  //Операция удаления.

//Флаги AEPOINT
#define AEPTF_MODIFY        0x00000002  //Если установлено, текст в области (AEPOINT.ciPoint + AEPOINT.nPointLen) был изменен.
#define AEPTF_INSERT        0x00000004  //Если установлено, индекс AEPOINT.nPointLen был увеличен. Дополнительно к флагу AEPTF_MODIFY.
#define AEPTF_DELETE        0x00000008  //Если установлено, индекс AEPOINT.nPointLen был уменьшен. Дополнительно к флагу AEPTF_MODIFY.
#define AEPTF_NOTIFYDELETE  0x00000010  //Не использовать. Только для внутреннего кода.
#define AEPTF_NOTIFYINSERT  0x00000020  //Не использовать. Только для внутреннего кода.
#define AEPTF_VALIDLINE     0x00000040  //Не использовать. Только для внутреннего кода.
#define AEPTF_WRAPMOVESET   0x00000080  //Не использовать. Только для внутреннего кода.
#define AEPTF_FOLD          0x00000100  //Если установлено, индекс AEPOINT.ciPoint используется в свернутой области (фолде). AEPOINT.dwUserData - указатель на структуру AEFOLD.
#define AEPTF_WRAPMOVE      0x00000200  //Если установлено, переместить точку на следующую строку, если она находится в месте переноса.
#define AEPTF_MOVEOFFSET    0x00001000  //Если установлено, AEPOINT.nPointOffset был изменен.
#define AEPTF_MOVELINE      0x00002000  //Если установлено, AEPOINT.ciPoint.nLine был изменен.

//Значение смещения символа AEPOINT
#define AEPTO_IGNORE    -1  //Смещение символа RichEdit не используется в AEPOINT.
#define AEPTO_CALC      -2  //Смещение символа RichEdit будет вычислено автоматически при AEM_ADDPOINT.

//Типы AEM_GETFOLDCOUNT
#define AEFC_ALL              0  //Все фолды.
#define AEFC_COLLAPSED        1  //Свернутые фолды.
#define AEFC_COLORED          2  //Окрашенные фолды.
#define AEFC_WITHID           3  //Фолды с ID.
#define AEFC_WITHTHEME        4  //Фолды с темой подсветки.

//Флаги AEM_COLLAPSELINE и AEM_COLLAPSEFOLD
#define AECF_EXPAND           0x00000000  //Развернуть фолд (по умолчанию).
#define AECF_COLLAPSE         0x00000001  //Свернуть фолд.
#define AECF_RECURSE          0x00000002  //Рекурсивная обработка со всеми дочерними элементами.
#define AECF_NOUPDATE         0x00000004  //Не обновлять прокрутку и выделение.
#define AECF_NOCARETCORRECT   0x00000008  //Если курсор находится в свернутом фолде, не перемещать его на начало фолда.

//Действия AEN_DROPTARGET
#define AEDT_TARGETENTER        1  //Вход в окно-цель.
#define AEDT_TARGETOVER         2  //Перемещение над окном-целью.
#define AEDT_TARGETLEAVE        3  //Выход из окна-цели.
#define AEDT_TARGETDROP         4  //Сброс данных в окно-цель.

//Действия AEN_DROPSOURCE
#define AEDS_SOURCEBEGIN        1  //Начало перетаскивания выделения.
#define AEDS_SOURCEEND          2  //Конец перетаскивания выделения. Перед удалением выделения.
#define AEDS_SOURCEDONE         3  //Конец операции перетаскивания. То же, что и EN_DRAGDROPDONE.

//Тип AEN_PROGRESS
#define AEPGS_SETTEXT           0x00000001  //Установка текста.
#define AEPGS_WRAPTEXT          0x00000002  //Перенос текста.
#define AEPGS_STREAMIN          0x00000004  //Получение потокового текста.

//Тип AEN_PAINT
#define AEPNT_BEGIN             0x00000001  //Отправляется перед началом рисования, действителен только член AENPAINT.hDC.
#define AEPNT_END               0x00000002  //Отправляется перед очисткой ресурсов рисования.
#define AEPNT_DRAWLINE          0x00000004  //Отправляется перед рисованием строки. Используется только в обратном вызове, см. AEM_PAINTCALLBACK.

//Флаги AEM_SETOPTIONS
                                                  // Стили окна:
#define AECO_READONLY                 0x00000001  //Установить режим только для чтения. Можно использовать стиль окна ES_READONLY.
#define AECO_DISABLENOSCROLL          0x00000002  //Отключает полосы прокрутки вместо их скрытия, когда они не нужны. Можно использовать стиль окна ES_DISABLENOSCROLL.
#define AECO_NOHIDESEL                0x00000004  //Если не указать этот стиль, выделение скрывается, когда элемент управления теряет фокус ввода, и инвертируется, когда получает фокус ввода. Можно использовать стиль окна ES_NOHIDESEL.
#define AECO_WANTRETURN               0x00000008  //Если не указать этот стиль, нажатие клавиши ENTER имеет тот же эффект, что и нажатие кнопки по умолчанию в диалоговом окне. Можно использовать стиль окна ES_WANTRETURN.
#define AECO_MULTILINE                0x00000010  //Обозначает многострочный элемент редактирования. По умолчанию - однострочный. Можно использовать стиль окна ES_MULTILINE.
                                                  // Другое:
#define AECO_DETAILEDUNDO             0x00000020  //Элемент управления сохраняет любое действие ввода как новое действие в очереди отмены.
#define AECO_PASTESELECTCOLUMN        0x00000040  //Выделяет вставленный текст в колоночном режиме.
#define AECO_DISABLEDRAG              0x00000080  //Отключает перетаскивание текста OLE.
#define AECO_DISABLEDROP              0x00000100  //Отключает сброс текста OLE.
#define AECO_CARETOUTEDGE             0x00000200  //Разрешить перемещение курсора за край строки.
#define AECO_ACTIVECOLUMN             0x00000400  //Рисовать вертикальную линию курсора.
#define AECO_ACTIVELINE               0x00000800  //Рисовать активную строку.
#define AECO_ACTIVELINEBORDER         0x00001000  //Рисовать границу активной строки.
#define AECO_ALTLINEBORDER            0x00002000  //Рисовать границу чередующихся строк.
#define AECO_NONEWLINEDRAW            0x00004000  //Запрещает рисовать выделение символа новой строки как пробел.
#define AECO_ENTIRENEWLINEDRAW        0x00008000  //Рисовать выделение новой строки до правого края.
#define AECO_NONEWLINEMOUSESELECT     0x00010000  //Тройной щелчок и щелчок на левом поле выделяют только содержимое строки без символа новой строки.
#define AECO_LBUTTONUPCONTINUECAPTURE 0x00020000  //После сообщения WM_LBUTTONUP операции захвата не останавливаются.
#define AECO_RBUTTONDOWNMOVECARET     0x00040000  //Сообщение WM_RBUTTONDOWN перемещает курсор в позицию щелчка.
#define AECO_MBUTTONDOWNNOSCROLL      0x00080000  //Нет прокрутки после сообщения WM_MBUTTONDOWN.
#define AECO_SELUNWRAPLINE            0x00100000  //Выделение строки мышью выделяет всю перенесенную строку.
#define AECO_NOMARGINSEL              0x00200000  //Отключает выделение строки на левом поле с помощью мыши.
#define AECO_NOMARKERMOVE             0x00400000  //Отключает изменение позиции маркера столбца с помощью мыши и клавиши shift.
#define AECO_NOMARKERAFTERLASTLINE    0x00800000  //Отключает рисование маркера после последней строки.
#define AECO_VSCROLLBYLINE            0x01000000  //Единица вертикальной прокрутки - строка (по умолчанию - пиксель).
#define AECO_NOSCROLLDELETEALL        0x02000000  //Отключает прокрутку к курсору, когда операции отмены/повтора заменяют весь текст.
#define AECO_NOSCROLLSELECTALL        0x04000000  //Отключает прокрутку к курсору, когда выделен весь текст.
#define AECO_NOCOLUMNPASTEHOTKEY      0x08000000  //Отключает Alt+V для колоночной вставки.
#define AECO_DISABLEBEEP              0x10000000  //Отключает звуковой сигнал, когда происходит недопустимое действие.
#define AECO_NODCBUFFER               0x20000000  //Не использовать буферизацию вывода контекста устройства в AE_Paint. Вызывает мерцание окна редактирования.
#define AECO_PAINTGROUP               0x40000000  //Рисовать текст группами символов (по умолчанию символ за символом).
                                                  //С этим флагом некоторые программы распознавания текста могут заработать, принтер может печатать быстрее, но выделенные символы и комбинированные символы юникода могут отображаться иначе, и редактирование таких символов может стать неудобным.

//Флаги AEM_EXSETOPTIONS
#define AECOE_DETECTURL               0x00000001  //Включает обнаружение и подсветку URL-адресов элементом редактирования.
#define AECOE_LOCKSELECTION           0x00000002  //Предотвращает изменение выделения. Используйте с флагом AECO_READONLY.
#define AECOE_OVERTYPE                0x00000004  //Включить режим замены вместо режима вставки.
#define AECOE_ALTDECINPUT             0x00000008  //Выполнять десятичный ввод Alt+NumPad при включенном NumLock (по умолчанию десятичный ввод после двух нажатий "Num 0").
#define AECOE_INVERTHORZWHEEL         0x00000010  //Инвертировать горизонтальное колесо мыши.
#define AECOE_INVERTVERTWHEEL         0x00000020  //Инвертировать вертикальное колесо мыши.
#define AECOE_NOCARETHORZINDENT       0x00000040  //Горизонтальный отступ курсора не восстанавливается после нажатия VK_UP, VK_DOWN, VK_PRIOR, VK_NEXT.
#define AECOE_NOPRINTCOLLAPSED        0x00001000  //Отключает печать свернутых строк. См. сообщение AEM_COLLAPSEFOLD.

#define AECOOP_SET              1  //Устанавливает параметры, указанные в lParam.
#define AECOOP_OR               2  //Объединяет указанные параметры с текущими.
#define AECOOP_AND              3  //Сохраняет только те текущие параметры, которые также указаны в lParam.
#define AECOOP_XOR              4  //Логически исключающее ИЛИ для текущих параметров с указанными в lParam.

//Флаги модификаторов
#define AEMOD_ALT               0x1  //Клавиша ALT
#define AEMOD_SHIFT             0x2  //Клавиша SHIFT
#define AEMOD_CONTROL           0x4  //Клавиша CTRL

//Флаги AEM_GETLINENUMBER
#define AEGL_LINECOUNT                 0  //Общее количество строк текста. Если элемент управления не содержит текста, возвращаемое значение равно 1.
#define AEGL_FIRSTSELLINE              1  //Первая строка выделения.
#define AEGL_LASTSELLINE               2  //Последняя строка выделения.
#define AEGL_CARETLINE                 3  //Строка с курсором.
#define AEGL_FIRSTVISIBLELINE          4  //Первая видимая строка.
#define AEGL_LASTVISIBLELINE           5  //Последняя видимая строка.
#define AEGL_FIRSTFULLVISIBLELINE      6  //Первая полностью видимая строка.
#define AEGL_LASTFULLVISIBLELINE       7  //Последняя полностью видимая строка.
#define AEGL_LINEUNWRAPCOUNT          11  //Общее количество неперенесенных строк текста. Если элемент управления не содержит текста, возвращаемое значение равно 1.
#define AEGL_UNWRAPSELMULTILINE       12  //Возвращает значение: TRUE - если выделение на нескольких строках. FALSE - если выделения нет или выделение на одной строке.
                                          //  Следующие флаги требуют смещение RichEdit в lParam.
#define AEGL_LINEFROMRICHOFFSET       20  //Строка указанного смещения RichEdit. lParam - смещение RichEdit (если -1, смещение курсора). Эквивалентно EM_EXLINEFROMCHAR.
#define AEGL_UNWRAPLINEFROMRICHOFFSET 21  //Неперенесенная строка указанного смещения RichEdit. lParam - смещение RichEdit (если -1, смещение курсора).

//Флаги AEM_GETINDEX и AEM_GETRICHOFFSET
#define AEGI_FIRSTCHAR                 1  //Первый символ.
#define AEGI_LASTCHAR                  2  //Последний символ.
#define AEGI_FIRSTSELCHAR              3  //Первый символ выделения.
#define AEGI_LASTSELCHAR               4  //Последний символ выделения.
#define AEGI_CARETCHAR                 5  //Символ под курсором.
#define AEGI_FIRSTVISIBLECHAR          6  //Первый видимый символ, свернутые строки пропускаются.
#define AEGI_LASTVISIBLECHAR           7  //Последний видимый символ, свернутые строки пропускаются.
#define AEGI_FIRSTFULLVISIBLECHAR      8  //Первый полностью видимый символ, свернутые строки пропускаются.
#define AEGI_LASTFULLVISIBLECHAR       9  //Последний полностью видимый символ, свернутые строки пропускаются.
#define AEGI_FIRSTVISIBLELINE         10  //Первый символ первой видимой строки, свернутые строки пропускаются.
#define AEGI_LASTVISIBLELINE          11  //Последний символ последней видимой строки, свернутые строки пропускаются.
#define AEGI_FIRSTFULLVISIBLELINE     12  //Первый символ первой полностью видимой строки, свернутые строки пропускаются.
#define AEGI_LASTFULLVISIBLELINE      13  //Последний символ последней полностью видимой строки, свернутые строки пропускаются.
                                          //  Следующие флаги требуют в lParam:
                                          //    AEM_GETINDEX - указатель на структуру AECHARINDEX.
                                          //    AEM_GETRICHOFFSET - смещение RichEdit.
#define AEGI_VALIDCHARINLINE          15  //Скорректировать символ, чтобы убедиться, что он находится в строке. AEM_GETRICHOFFSET - не поддерживается.
                                          //Для лучшей производительности используйте AEC_ValidCharInLine.
#define AEGI_LINEBEGIN                16  //Первый символ в строке.
                                          //
#define AEGI_LINEEND                  17  //Последний символ в строке.
                                          //
#define AEGI_WRAPLINEBEGIN            18  //Первый символ неперенесенной строки. Возвращает количество символов как результат AEM_GETINDEX.
                                          //Для лучшей производительности используйте AEC_WrapLineBeginEx.
#define AEGI_WRAPLINEEND              19  //Последний символ неперенесенной строки. Возвращает количество символов как результат AEM_GETINDEX.
                                          //Для лучшей производительности используйте AEC_WrapLineEndEx.
#define AEGI_NEXTCHARINLINE           20  //Следующий символ в строке.
                                          //Для лучшей производительности используйте AEC_NextCharInLineEx.
#define AEGI_PREVCHARINLINE           21  //Предыдущий символ в строке.
                                          //Для лучшей производительности используйте AEC_PrevCharInLineEx.
#define AEGI_NEXTCHAR                 22  //Следующий широкий символ.
                                          //Для лучшей производительности используйте AEC_NextCharEx.
#define AEGI_PREVCHAR                 23  //Предыдущий широкий символ.
                                          //Для лучшей производительности используйте AEC_PrevCharEx.
#define AEGI_NEXTLINE                 24  //Первый символ следующей строки.
                                          //Для лучшей производительности используйте AEC_NextLineEx.
#define AEGI_PREVLINE                 25  //Первый символ предыдущей строки.
                                          //Для лучшей производительности используйте AEC_PrevLineEx.
#define AEGI_NEXTUNCOLLAPSEDCHAR      26  //Следующий широкий символ, свернутые строки пропускаются.
#define AEGI_PREVUNCOLLAPSEDCHAR      27  //Предыдущий широкий символ, свернутые строки пропускаются.
#define AEGI_NEXTUNCOLLAPSEDLINE      28  //Первый символ следующей строки, свернутые строки пропускаются.
#define AEGI_PREVUNCOLLAPSEDLINE      29  //Первый символ предыдущей строки, свернутые строки пропускаются.
                                          //  Следующие флаги требуют в lParam:
                                          //    AEM_GETINDEX - не поддерживается.
                                          //    AEM_GETRICHOFFSET - номер строки.
#define AEGI_RICHOFFSETFROMLINE       40  //Первый символ (смещение RichEdit) указанной строки. lParam - номер строки (если -1, строка с курсором). Эквивалентно EM_LINEINDEX.
#define AEGI_RICHOFFSETFROMUNWRAPLINE 41  //Первый символ (смещение RichEdit) указанной неперенесенной строки. lParam - номер строки (если -1, строка с курсором).

//Параметр AEM_ISDELIMITER
#define AEDLM_PREVCHAR  0x00000001  //Проверить предыдущий символ.
#define AEDLM_WORD      0x00000010  //Разделитель слов.
#define AEDLM_WRAP      0x00000020  //Разделитель переноса.
#define AEDLM_URLLEFT   0x00000040  //Левый разделитель URL.
#define AEDLM_URLRIGHT  0x00000080  //Правый разделитель URL.

//Флаги AEM_COLUMNTOINDEX и AEM_INDEXTOCOLUMN
#define AECTI_WRAPLINEBEGIN 0x0001  //Если установлено, сканировать с первого символа неперенесенной строки. Если не установлено, сканировать с первого символа перенесенной строки.
#define AECTI_FIT           0x0002  //AEM_COLUMNTOINDEX: если установлено, позиция символа должна быть меньше или равна границе столбца. Если не установлено, позиция символа должна быть больше или равна границе столбца.

//Флаги AEM_SETSEL и AEM_UPDATESEL
#define AESELT_COLUMNON            0x00000001  //Включить колоночное выделение.
#define AESELT_COLUMNASIS          0x00000002  //Оставить колоночное выделение как есть.
#define AESELT_LOCKNOTIFY          0x00000004  //Отключить уведомления AEN_SELCHANGING и AEN_SELCHANGED.
#define AESELT_LOCKSCROLL          0x00000008  //Заблокировать прокрутку окна редактирования.
#define AESELT_LOCKUPDATE          0x00000010  //Заблокировать обновление окна редактирования.
#define AESELT_LOCKCARET           0x00000020  //Заблокировать перемещение курсора.
#define AESELT_LOCKUNDOGROUPING    0x00000040  //Не использовать. Только для внутреннего кода.
#define AESELT_NOCARETHORZINDENT   0x00000080  //Горизонтальный отступ курсора не изменяется.
#define AESELT_NOVERTSCROLLCORRECT 0x00000100  //При некоторых условиях прокрутка может быть увеличена на высоту одной строки.
#define AESELT_MOUSE               0x00000200  //Не использовать. Только для внутреннего кода.
#define AESELT_RESETSELECTION      0x00000400  //Не использовать. Только для внутреннего кода.
#define AESELT_INDEXUPDATE         0x00000800  //Обновить член lpLine структур сообщения AEM_SETSEL, чтобы избежать висячего указателя после изменения текста.

//Флаги AEM_REPLACESEL
#define AEREPT_COLUMNON            0x00000001  //Включить колоночное выделение.
#define AEREPT_COLUMNASIS          0x00000002  //Оставить колоночное выделение как есть.
#define AEREPT_LOCKSCROLL          0x00000004  //Заблокировать прокрутку окна редактирования. Однако окно редактирования может прокручиваться при изменении размера окна, если не установлена опция AECO_DISABLENOSCROLL.
#define AEREPT_UNDOGROUPING        0x00000100  //Продолжить группировку отмены.
#define AEREPT_SELECT              0x00000200  //Выделить вставленный текст.

//Возвращаемое значение AEM_CHARFROMPOS
#define AEPC_ERROR    0  //Ошибка.
#define AEPC_EQUAL    1  //Символ точно в указанной позиции.
#define AEPC_BEFORE   2  //Символ перед указанной позицией.
#define AEPC_AFTER    3  //Символ после указанной позиции.

//Значение новой строки
#define AELB_ASINPUT  1  //Использовать входную новую строку, см. AEM_SETNEWLINE с AENL_INPUT.
#define AELB_ASOUTPUT 2  //Использовать выходную новую строку, см. AEM_SETNEWLINE с AENL_OUTPUT.
#define AELB_ASIS     3  //Использовать новую строку источника.
#define AELB_EOF      4  //Конец файла, последняя строка в документе.
#define AELB_R        5  //Новая строка "\r".
#define AELB_N        6  //Новая строка "\n".
#define AELB_RN       7  //Новая строка "\r\n".
#define AELB_RRN      8  //Новая строка "\r\r\n".
#define AELB_WRAP     9  //Нет новой строки, эта строка перенесена.

//Флаги AEM_SETNEWLINE
#define AENL_INPUT           0x00000001  //Устанавливает новую строку по умолчанию для операций ввода, таких как вставка.
#define AENL_OUTPUT          0x00000002  //Устанавливает новую строку по умолчанию для операций вывода, таких как вырезание, копирование.

//Флаги AEM_CUT, AEM_COPY
#define AECFC_WORD           0x00000001  //Вырезать/Копировать слово под курсором, если нет выделения.
#define AECFC_LINE           0x00000002  //Вырезать/Копировать строку под курсором, если нет выделения.
#define AECFC_UNWRAPLINE     0x00000004  //Вырезать/Копировать неперенесенную строку под курсором, если нет выделения.
#define AECFC_NEWLINE        0x00000008  //Вырезать/Копировать также новую строку. Используется с AECFC_LINE или AECFC_UNWRAPLINE.

//Флаги AEM_PASTE
#define AEPFC_ANSI           0x00000001  //Вставить текст как ANSI. По умолчанию вставка как текст Unicode, если текст Unicode недоступен, будет использован текст ANSI.
#define AEPFC_COLUMN         0x00000002  //Вставить в колоночное выделение.
#define AEPFC_SELECT         0x00000004  //Выделить вставленный текст.

//Флаги AEM_LOCKUPDATE
#define AELU_SCROLLBAR  0x00000001
#define AELU_CARET      0x00000002

//Флаги AEM_SETDOCUMENT
#define AESWD_NOCHECKFOCUS        0x00000001  //Не обновлять состояние фокуса.
#define AESWD_NODRAGDROP          0x00000002  //Не регистрировать перетаскивание с новым IDropTarget.
#define AESWD_NOSHOWSCROLLBARS    0x00000004  //Не обновлять видимость полос прокрутки.
#define AESWD_NOUPDATESCROLLBARS  0x00000008  //Не обновлять положение полос прокрутки.
#define AESWD_NOUPDATECARET       0x00000010  //Не обновлять курсор.
#define AESWD_NOINVALIDATERECT    0x00000020  //Не перерисовывать окно редактирования.

#define AESWD_NOREDRAW  (AESWD_NOUPDATESCROLLBARS |\
                         AESWD_NOUPDATECARET      |\
                         AESWD_NOINVALIDATERECT)
#define AESWD_NOALL     (AESWD_NOCHECKFOCUS     |\
                         AESWD_NODRAGDROP       |\
                         AESWD_NOSHOWSCROLLBARS |\
                         AESWD_NOREDRAW)

//Флаги AEM_DRAGDROP
#define AEDD_GETDRAGWINDOW   1  //Вернуть дескриптор окна перетаскивания.
#define AEDD_STOPDRAG        2  //Установить флаг остановки операции перетаскивания.

//Операции AEM_URLVISIT
#define AEUV_STACK         1  //Получить стек посещений URL.
                              //lParam                    == не используется.
                              //(AESTACKURLVISIT *)Return == указатель на стек посещений URL.
#define AEUV_GETBYRANGE    2  //Получить элемент посещения URL по диапазону символов.
                              //(AECHARRANGE *)lParam     == диапазон URL.
                              //(AEURLVISIT *)Return      == указатель на элемент посещения URL.
#define AEUV_GETBYTEXT     3  //Получить элемент посещения URL по тексту.
                              //(const wchar_t *)lParam   == строка URL.
                              //(AEURLVISIT *)Return      == указатель на элемент посещения URL.
#define AEUV_ADD           4  //Добавить элемент посещения URL.
                              //(AECHARRANGE *)lParam     == диапазон URL. Может быть NULL.
                              //(AEURLVISIT *)Return      == указатель на элемент посещения URL.
#define AEUV_DEL           5  //Удалить элемент посещения URL.
                              //(AEURLVISIT *)lParam      == указатель на элемент посещения URL.
                              //Return                    == ноль.
#define AEUV_FREE          6  //Освободить стек посещений URL.
                              //lParam                    == не используется.
                              //Return                    == ноль.


//Операции AEM_PAINTCALLBACK
#define AEPCB_STACK         1 //Получить стек.
                              //lParam                         == не используется.
                              //(AESTACKPAINTCALLBACK *)Return == указатель на стек обратного вызова рисования.
#define AEPCB_ADD           2 //Добавить элемент обратного вызова рисования.
                              //(AEPAINTCALLBACKADD *)lParam   == указатель на структуру AEPAINTCALLBACKADD.
                              //(AEPAINTCALLBACK *)Return      == указатель на элемент AEPAINTCALLBACK.
#define AEPCB_DEL           3 //Удалить элемент обратного вызова.
                              //(AEPAINTCALLBACK *)lParam      == указатель на элемент AEPAINTCALLBACK.
                              //Return                         == ноль.
#define AEPCB_FREE          4 //Освободить стек.
                              //lParam                         == не используется.
                              //Return                         == ноль.

//Флаги AEM_SETCOLORS
#define AECLR_DEFAULT          0x00000001  //Использовать системные цвета по умолчанию для указанных флагов, все члены структуры AECOLORS игнорируются.
#define AECLR_CARET            0x00000002  //Устанавливает цвет курсора. Действителен член crCaret.
#define AECLR_BASICTEXT        0x00000004  //Устанавливает цвет основного текста. Действителен член crBasicText.
#define AECLR_BASICBK          0x00000008  //Устанавливает цвет основного фона. Действителен член crBasicBk.
#define AECLR_SELTEXT          0x00000010  //Устанавливает цвет текста в выделении. Действителен член crSelText.
#define AECLR_SELBK            0x00000020  //Устанавливает цвет фона в выделении. Действителен член crSelBk.
#define AECLR_ACTIVELINETEXT   0x00000040  //Устанавливает цвет текста активной строки. Действителен член crActiveLineText.
#define AECLR_ACTIVELINEBK     0x00000080  //Устанавливает цвет фона активной строки. Действителен член crActiveLineBk.
#define AECLR_URLTEXT          0x00000100  //Устанавливает цвет текста гиперссылки. Действителен член crUrlText.
#define AECLR_ACTIVECOLUMN     0x00000200  //Устанавливает цвет активного столбца. Действителен член crActiveColumn.
#define AECLR_COLUMNMARKER     0x00000400  //Устанавливает цвет маркера столбца. Действителен член crColumnMarker.
#define AECLR_URLCURSORTEXT    0x00000800  //Устанавливает цвет текста активной гиперссылки. Действителен член crUrlCursorText.
#define AECLR_URLVISITTEXT     0x00001000  //Устанавливает цвет текста посещенной гиперссылки. Действителен член crUrlVisitText.
#define AECLR_ACTIVELINEBORDER 0x00002000  //Устанавливает цвет границы активной строки. Действителен член crActiveLineBorder.
#define AECLR_ALTLINETEXT      0x00004000  //Устанавливает цвет текста чередующейся строки. Действителен член crAltLineText.
#define AECLR_ALTLINEBK        0x00008000  //Устанавливает цвет фона чередующейся строки. Действителен член crAltLineBk.
#define AECLR_ALTLINEBORDER    0x00010000  //Устанавливает цвет границы чередующейся строки. Действителен член crAltLineBorder.

#define AECLR_ALL  (AECLR_CARET            |\
                    AECLR_BASICTEXT        |\
                    AECLR_BASICBK          |\
                    AECLR_SELTEXT          |\
                    AECLR_SELBK            |\
                    AECLR_ACTIVELINETEXT   |\
                    AECLR_ACTIVELINEBK     |\
                    AECLR_URLTEXT          |\
                    AECLR_ACTIVECOLUMN     |\
                    AECLR_COLUMNMARKER     |\
                    AECLR_URLCURSORTEXT    |\
                    AECLR_URLVISITTEXT     |\
                    AECLR_ACTIVELINEBORDER |\
                    AECLR_ALTLINETEXT      |\
                    AECLR_ALTLINEBK        |\
                    AECLR_ALTLINEBORDER)

//Печать
#define AEPRN_TEST                      0x00001  //Вычислить данные без рисования.
#define AEPRN_INHUNDREDTHSOFMILLIMETERS 0x00002  //Указывает, что единицей измерения для полей являются сотые доли миллиметра.
#define AEPRN_INTHOUSANDTHSOFINCHES     0x00004  //Указывает, что единицей измерения для полей являются тысячные доли дюйма.
#define AEPRN_WRAPNONE                  0x00008  //Печатать без переноса.
#define AEPRN_WRAPWORD                  0x00010  //Печатать с переносом по словам (по умолчанию).
#define AEPRN_WRAPSYMBOL                0x00020  //Печатать с переносом по символам.
#define AEPRN_IGNOREFORMFEED            0x00040  //Игнорировать символ перевода страницы '\f'.
#define AEPRN_ANSI                      0x00080  //Вывод текста в ANSI. Может решить проблемы с рисованием на Win95/98/Me.
#define AEPRN_COLOREDTEXT               0x00100  //Печатать цветной текст.
#define AEPRN_COLOREDBACKGROUND         0x00200  //Печатать на цветном фоне.
#define AEPRN_COLOREDSELECTION          0x00400  //Печатать выделение текста.
#define AEPRN_CALLEMPTY                 0x10000  //Не использовать. Только для внутреннего кода.

//Тип AEM_HLFINDTHEME
#define AEHLFT_CURRENT 0  //Текущий дескриптор темы.
                          //lParam == не используется.
#define AEHLFT_BYNAMEA 1  //Найти по имени темы ANSI.
                          //(char *)lParam == имя темы ANSI для поиска. Если NULL, будет возвращен дескриптор активной темы.
#define AEHLFT_BYNAMEW 2  //Найти по имени темы Unicode.
                          //(wchar_t *)lParam == имя темы Unicode для поиска. Если NULL, будет возвращен дескриптор активной темы.
#define AEHLFT_BYFOLD  3  //Найти тему в указанном месте (AEFINDFOLD.dwFindIt). Если не найдено фолдов с собственной темой (AEFOLD.hRuleTheme), возвращается дескриптор текущей темы.
                          //(AEFINDFOLD *)lParam == указатель на структуру AEFINDFOLD.

//Опции подсветки
#define AEHLO_IGNOREFONTNORMAL       0x00000001  //Использовать стиль шрифта AEHLS_NONE, если изменяемый стиль шрифта - AEHLS_FONTNORMAL.
#define AEHLO_IGNOREFONTBOLD         0x00000002  //Использовать стиль шрифта AEHLS_FONTNORMAL, если изменяемый стиль шрифта - AEHLS_FONTBOLD.
                                                 //Использовать стиль шрифта AEHLS_FONTITALIC, если изменяемый стиль шрифта - AEHLS_FONTBOLDITALIC.
#define AEHLO_IGNOREFONTITALIC       0x00000004  //Использовать стиль шрифта AEHLS_FONTNORMAL, если изменяемый стиль шрифта - AEHLS_FONTITALIC.
                                                 //Использовать стиль шрифта AEHLS_FONTBOLD, если изменяемый стиль шрифта - AEHLS_FONTBOLDITALIC.

//Флаги подсветки
#define AEHLF_MATCHCASE              0x00000001  //Если установлено, операция подсветки чувствительна к регистру. Если не установлено, операция подсветки не чувствительна к регистру.
#define AEHLF_WHOLEWORD              0x00000002  //Только для AEMARKTEXTITEM.dwFlags. Если установлено, операция ищет только целые слова, совпадающие со строкой поиска. Если не установлено, операция также ищет фрагменты слов.
#define AEHLF_WORDCOMPOSITION        0x00000002  //Только для AEWORDITEM.dwFlags. Слово является композицией символов. Например, AEWORDITEM.pWord, равный "1234567890" с этим флагом, означает подсветку слов, содержащих только цифры.
#define AEHLF_QUOTEEND_REQUIRED      0x00000004  //Если конец кавычки не найден, текст после начала кавычки не будет подсвечен.
#define AEHLF_QUOTESTART_ISDELIMITER 0x00000008  //Последний встреченный разделитель используется как начало кавычки (член AEQUOTEITEM.pQuoteStart игнорируется).
#define AEHLF_QUOTEEND_ISDELIMITER   0x00000010  //Первый встреченный разделитель используется как конец кавычки (член AEQUOTEITEM.pQuoteEnd игнорируется).
#define AEHLF_QUOTESTART_NOHIGHLIGHT 0x00000020  //Не подсвечивать строку начала кавычки.
#define AEHLF_QUOTEEND_NOHIGHLIGHT   0x00000040  //Не подсвечивать строку конца кавычки.
#define AEHLF_QUOTESTART_NOCATCH     0x00000080  //Не ловить и не подсвечивать строку начала кавычки.
#define AEHLF_QUOTEEND_NOCATCH       0x00000100  //Не ловить и не подсвечивать строку конца кавычки.
#define AEHLF_ATLINESTART            0x00000200  //Начало кавычки, разделитель или слово находятся в начале строки.
#define AEHLF_ATLINEEND              0x00000400  //Конец кавычки, разделитель или слово находятся в конце строки.
#define AEHLF_QUOTESTART_ISWORD      0x00000800  //Начало кавычки окружено разделителями.
#define AEHLF_QUOTEEND_ISWORD        0x00001000  //Конец кавычки окружен разделителями.
#define AEHLF_QUOTEWITHOUTDELIMITERS 0x00002000  //Кавычка не содержит разделителей.
#define AEHLF_QUOTESTART_CATCHONLY   0x00004000  //Ловится только строка начала кавычки.
#define AEHLF_QUOTEEMPTY             0x00008000  //Кавычка не содержит ни одного символа.
#define AEHLF_QUOTEINCLUDE           0x00010000  //Строка включения кавычки действительна.
#define AEHLF_QUOTEEXCLUDE           0x00020000  //Строка исключения кавычки действительна.
                                                 //Регулярные выражения:
#define AEHLF_REGEXP                 0x10000000  //Может использоваться в AEQUOTEITEM.dwFlags.
                                                 //  AEQUOTEITEM.pQuoteStart - это шаблон регулярного выражения,
                                                 //  AEQUOTEITEM.pQuoteEnd - это карта соответствия обратных ссылок в формате:
                                                 //    "\BackRef1=(FontStyle,ColorText,ColorBk) \BackRef2=(FontStyle,ColorText,ColorBk) ..."
                                                 //  Примечания:
                                                 //    Цвет должен быть в формате RRGGBB или RGB с префиксом # или без.
                                                 //    Если цвет равен нулю, то цвет игнорируется.
                                                 //    Вместо цвета может использоваться обратная ссылка.
                                                 //  Пример (подсветка строки в кавычках):
                                                 //    AEQUOTEITEM.pQuoteStart  (")([^"\\]*(\\.[^"\\]*)*)(")
                                                 //    AEQUOTEITEM.pQuoteEnd    \1=(0,#FF0000,0) \2=(0,#00F,0) \4=(0,#FF0000,0)
                                                 //  Пример (подсветка слова #RRGGBB или #RGB его цветом):
                                                 //    AEQUOTEITEM.pQuoteStart  #([A-F\d]{6}|[A-F\d]{3})\b
                                                 //    AEQUOTEITEM.pQuoteEnd    \0=(0,\1,0)
                                                 //Может использоваться в AEMARKTEXTITEM.dwFlags.
                                                 //  AEMARKTEXTITEM.pMarkText - это шаблон регулярного выражения.
#define AEHLF_STYLED                 0x80000000  //Не использовать. Только для внутреннего кода.

//Стиль шрифта подсветки
#define AEHLS_NONE                   0  //Текущий стиль.
#define AEHLS_FONTNORMAL             1  //Обычный стиль.
#define AEHLS_FONTBOLD               2  //Жирный стиль.
#define AEHLS_FONTITALIC             3  //Курсивный стиль.
#define AEHLS_FONTBOLDITALIC         4  //Жирный курсивный стиль.

//Элементы подсветки
#define AEHLE_DELIMITER              1  //Разделитель. Новая строка, начало файла и конец файла являются разделителями по умолчанию.
#define AEHLE_WORD                   2  //Слово - строка, окруженная разделителями.
#define AEHLE_QUOTE                  3  //Кавычка - текст, начинающийся со строки начала кавычки и заканчивающийся строкой конца кавычки.
#define AEHLE_MARKTEXT               4  //Пометка текста - пометить указанный текст.
#define AEHLE_MARKRANGE              5  //Пометка диапазона - пометить указанный диапазон символов.

//Флаги подсветки AEM_HLGETHIGHLIGHT
#define AEGHF_NOSELECTION            0x00000001  //Игнорировать раскраску выделения текста.
#define AEGHF_NOACTIVELINE           0x00000002  //Игнорировать цвета активной строки.
#define AEGHF_NOALTLINE              0x00000004  //Игнорировать цвета чередующихся строк.
#define AEGHF_CALLENDLINE            0x00010000  //Вызвать функцию для конца непустой строки.
#define AEGHF_CALLENDRANGE           0x00020000  //Вызвать функцию для конца диапазона.

//Тип рисования подсветки
#define AEHPT_SELECTION              0x00000001
#define AEHPT_DELIM1                 0x00000002
#define AEHPT_WORD                   0x00000004
#define AEHPT_DELIM2                 0x00000008
#define AEHPT_QUOTE                  0x00000010
#define AEHPT_MARKTEXT               0x00000020
#define AEHPT_MARKRANGE              0x00000040
#define AEHPT_LINK                   0x00000080
#define AEHPT_FOLD                   0x00000100

//Флаги AEREGROUPCOLOR
#define AEREGCF_BACKREFCOLORTEXT  0x00000001  //AEREGROUPCOLOR.crText - это индекс обратной ссылки для цвета текста в формате #RRGGBB или RRGGBB.
#define AEREGCF_BACKREFCOLORBK    0x00000002  //AEREGROUPCOLOR.crBk - это индекс обратной ссылки для цвета фона в формате #RRGGBB или RRGGBB.

//Тип родителя
#define AEHAP_NONE   0
#define AEHAP_ROOT   1
#define AEHAP_QUOTE  2
#define AEHAP_FOLD   3

//Флаги фолда
#define AEFOLDF_COLLAPSED    0x00000001  //Фолд свернут.
#define AEFOLDF_STYLED       0x80000000  //Не использовать. Только для внутреннего кода.

//Флаги AEM_FINDFOLD
#define AEFF_FINDOFFSET      0x00000001  //AEFINDFOLD.dwFindIt - это смещение RichEdit.
#define AEFF_FINDINDEX       0x00000002  //AEFINDFOLD.dwFindIt - это указатель на структуру AECHARINDEX.
#define AEFF_FINDLINE        0x00000004  //AEFINDFOLD.dwFindIt - это номер строки, начиная с нуля.
#define AEFF_FOLDSTART       0x00000008  //Фолд также принимается, если AEFINDFOLD.dwFindIt указывает на начало фолда.
#define AEFF_FOLDEND         0x00000010  //Фолд также принимается, если AEFINDFOLD.dwFindIt указывает на конец фолда.
#define AEFF_RECURSE         0x00000020  //Рекурсивный поиск. Возвращенный фолд будет максимально глубоким.
#define AEFF_GETROOT         0x00000040  //Вернуть корневой фолд.
                                         //
                                         //Следующие группы флагов нельзя использовать вместе:
                                         //  AEFF_FINDOFFSET, AEFF_FINDINDEX и AEFF_FINDLINE.
                                         //  AEFF_RECURSE и AEFF_GETROOT.

//Флаги AEM_SCROLL, AEM_LINESCROLL
#define AESB_HORZ            0x00000001  //Горизонтальная прокрутка. Не может использоваться с AESB_VERT.
#define AESB_VERT            0x00000002  //Вертикальная прокрутка. Не может использоваться с AESB_HORZ.
#define AESB_RETURNUNITS     0x00000004  //Если указано AESB_HORZ, возвращается количество прокрученных символов. Если указано AESB_VERT, возвращается количество прокрученных строк.
#define AESB_ALIGNLEFT       0x00000008  //Выровнять первый видимый символ.
#define AESB_ALIGNRIGHT      0x00000010  //Выровнять последний видимый символ.
#define AESB_ALIGNTOP        0x00000020  //Выровнять первую видимую строку.
#define AESB_ALIGNBOTTOM     0x00000040  //Выровнять последнюю видимую строку.

//Флаги AEM_SCROLLTOPOINT
#define AESC_TEST            0x00000001  //Только проверка прокрутки. Возвращает результат, но фактически не прокручивает.
#define AESC_POINTCARET      0x00000010  //Используется позиция курсора, а AESCROLLTOPOINT.ptPos игнорируется.
#define AESC_POINTGLOBAL     0x00000020  //AESCROLLTOPOINT.ptPos - это позиция в координатах виртуального текстового пространства.
#define AESC_POINTCLIENT     0x00000040  //AESCROLLTOPOINT.ptPos - это позиция в координатах клиентской области (по умолчанию).
#define AESC_POINTOUT        0x00000080  //AESCROLLTOPOINT.ptPos будет содержать новую позицию прокрутки после возврата из AEM_SCROLLTOPOINT.
#define AESC_OFFSETPIXELX    0x00000100  //AESCROLLTOPOINT.nOffsetX указывает количество пикселей.
#define AESC_OFFSETPIXELY    0x00000200  //AESCROLLTOPOINT.nOffsetY указывает количество пикселей.
#define AESC_OFFSETCHARX     0x00000400  //AESCROLLTOPOINT.nOffsetX указывает количество символов.
#define AESC_OFFSETCHARY     0x00000800  //AESCROLLTOPOINT.nOffsetY указывает количество символов.
#define AESC_OFFSETRECTDIVX  0x00001000  //AESCROLLTOPOINT.nOffsetX указывает делитель ширины прямоугольника редактирования.
#define AESC_OFFSETRECTDIVY  0x00002000  //AESCROLLTOPOINT.nOffsetY указывает делитель ширины прямоугольника редактирования.
#define AESC_FORCELEFT       0x00010000  //Прокручивает влево, даже если AESCROLLTOPOINT.ptPos видим.
#define AESC_FORCETOP        0x00020000  //Прокручивает вверх, даже если AESCROLLTOPOINT.ptPos видим.
#define AESC_FORCERIGHT      0x00040000  //Прокручивает вправо, даже если AESCROLLTOPOINT.ptPos видим.
#define AESC_FORCEBOTTOM     0x00080000  //Прокручивает вниз, даже если AESCROLLTOPOINT.ptPos видим.

//Возвращаемые значения AEM_SCROLLTOPOINT
#define AECSE_SCROLLEDX      0x00000001  //Элемент редактирования был прокручен по горизонтали.
#define AECSE_SCROLLEDY      0x00000002  //Элемент редактирования был прокручен по вертикали.
#define AECSE_SCROLLEDLEFT   0x00000004  //Элемент редактирования был прокручен влево по горизонтали.
#define AECSE_SCROLLEDRIGHT  0x00000008  //Элемент редактирования был прокручен вправо по горизонтали.
#define AECSE_SCROLLEDUP     0x00000010  //Элемент редактирования был прокручен вверх по вертикали.
#define AECSE_SCROLLEDDOWN   0x00000020  //Элемент редактирования был прокручен вниз по вертикали.

//Тип AEM_GETFONT
#define AEGF_CURRENT         0  //Дескриптор текущего шрифта.
#define AEGF_NORMAL          1  //Дескриптор шрифта обычного стиля.
#define AEGF_BOLD            2  //Дескриптор шрифта жирного стиля.
#define AEGF_ITALIC          3  //Дескриптор шрифта курсивного стиля.
#define AEGF_BOLDITALIC      4  //Дескриптор шрифта жирного курсивного стиля.
#define AEGF_URL             5  //Дескриптор шрифта стиля URL.

//Флаги AEM_GETCHARSIZE
#define AECS_HEIGHT          0  //Высота символа текущего шрифта, включая межстрочный интервал. lParam не используется.
#define AECS_AVEWIDTH        1  //Средняя ширина латинского символа текущего шрифта. lParam не используется.
#define AECS_INDEXWIDTH      2  //lParam - это индекс символа, ширина которого запрашивается.
#define AECS_POINTSIZE       3  //Размер в пунктах текущего шрифта. lParam не используется.
#define AECS_SPACEWIDTH      4  //Ширина пробела текущего шрифта. lParam не используется.
#define AECS_TABWIDTH        5  //Ширина табуляции текущего шрифта. lParam не используется.
#define AECS_MAXWIDTH        6  //Максимальная ширина латинского символа текущего шрифта. lParam не используется.
#define AECS_FIXEDCHARWIDTH  7  //Фиксированная ширина символа, установленная с помощью AEM_FIXEDCHARWIDTH. lParam не используется.
#define AECS_FIXEDTABWIDTH   8  //Фиксированная ширина табуляции, установленная с помощью AEM_FIXEDCHARWIDTH. lParam не используется.

//Флаги AEM_CONVERTPOINT
#define AECPT_GLOBALTOCLIENT 0  //Преобразовать позицию в виртуальном текстовом пространстве документа в координаты клиентской области.
#define AECPT_CLIENTTOGLOBAL 1  //Преобразовать позицию в координатах клиентской области в виртуальное текстовое пространство документа.

//Тип координат
#define AECT_GLOBAL 0  //Позиция в координатах виртуального текстового пространства.
#define AECT_CLIENT 1  //Позиция в координатах клиентской области.

//Флаги прямоугольника
#define AERC_UPDATE    0x01  //Перерисовать окно редактирования. Только для AEM_SETRECT и AEM_SETERASERECT.
#define AERC_MARGINS   0x02  //Прямоугольник содержит поля области редактирования вместо координат области редактирования.
#define AERC_NOLEFT    0x04  //Не устанавливать/получать левую сторону.
#define AERC_NOTOP     0x08  //Не устанавливать/получать верхнюю сторону.
#define AERC_NORIGHT   0x10  //Не устанавливать/получать правую сторону.
#define AERC_NOBOTTOM  0x20  //Не устанавливать/получать нижнюю сторону.

//Стороны AEM_POINTONMARGIN
#define AESIDE_LEFT          0x00000001
#define AESIDE_TOP           0x00000002
#define AESIDE_RIGHT         0x00000004
#define AESIDE_BOTTOM        0x00000008

//Типы AEM_GETMOUSESTATE
#define AEMS_CAPTURE         1  //Состояние захвата.
#define AEMS_SELECTION       2  //Состояние выделения.

//Захват AEM_GETMOUSESTATE
#define AEMSC_MOUSEMOVE       0x1  //Выделение текста.
#define AEMSC_MOUSESCROLL     0x2  //Прокрутка средней кнопкой.
#define AEMSC_MOUSEDRAG       0x4  //Перетаскивание выделения.
#define AEMSC_MOUSEMARKER     0x8  //Перемещение маркера.

//Выделение AEM_GETMOUSESTATE
#define AEMSS_LBUTTONUP      0x1  //Получено WM_LBUTTONUP.
#define AEMSS_CHARS          0x2  //Выделение символов.
#define AEMSS_WORDS          0x4  //Выделение слов.
#define AEMSS_LINES          0x8  //Выделение строк.

//Флаги AEM_FINDTEXT, AEM_ISMATCH
#define AEFR_DOWN               0x00000001  //То же, что FR_DOWN. Если установлено, поиск выполняется от начала до конца диапазона поиска. Если не установлено, поиск выполняется от конца до начала диапазона поиска.
#define AEFR_WHOLEWORD          0x00000002  //То же, что FR_WHOLEWORD. Если установлено, операция ищет только целые слова, совпадающие со строкой поиска. Если не установлено, операция также ищет фрагменты слов.
#define AEFR_MATCHCASE          0x00000004  //То же, что FR_MATCHCASE. Если установлено, операция поиска чувствительна к регистру. Если не установлено, операция поиска не чувствительна к регистру.
#define AEFR_REGEXP             0x00080000  //Поиск с регулярным выражением.
#define AEFR_REGEXPNONEWLINEDOT 0x00100000  //Символ . обозначает любой символ, кроме новой строки.
#define AEFR_REGEXPMINMATCH     0x00200000  //Разрешить совпадение нулевой длины по краям строки. Например: "^" в начале строки или "$" в конце строки.

//Флаги AEM_SETWORDWRAP
#define AEWW_NONE            0x00000000  //Выключить перенос.
#define AEWW_WORD            0x00000001  //Перенос по словам.
#define AEWW_SYMBOL          0x00000002  //Перенос по символам.
#define AEWW_LIMITPIXEL      0x00000100  //Ограничение в пикселях (по умолчанию).
#define AEWW_LIMITSYMBOL     0x00000200  //Ограничение в символах.

//Типы AEM_SETMARKER
#define AEMT_PIXEL           0  //Целое число пикселей.
#define AEMT_SYMBOL          1  //Номер столбца.

//Флаги AEM_SETWORDBREAK
#define AEWB_LEFTWORDSTART   0x00000001  //Движение влево останавливается при обнаружении начала слова.
#define AEWB_LEFTWORDEND     0x00000002  //Движение влево останавливается при обнаружении конца слова.
#define AEWB_RIGHTWORDSTART  0x00000004  //Движение вправо останавливается при обнаружении начала слова.
#define AEWB_RIGHTWORDEND    0x00000008  //Движение вправо останавливается при обнаружении конца слова.
#define AEWB_STOPSPACESTART  0x00000010  //Движение останавливается при обнаружении начала пробела. Нельзя комбинировать с AEWB_SKIPSPACESTART.
#define AEWB_STOPSPACEEND    0x00000020  //Движение останавливается при обнаружении конца пробела. Нельзя комбинировать с AEWB_SKIPSPACEEND.
#define AEWB_SKIPSPACESTART  0x00000040  //Движение продолжается при обнаружении начала пробела. Нельзя комбинировать с AEWB_STOPSPACESTART.
#define AEWB_SKIPSPACEEND    0x00000080  //Движение продолжается при обнаружении конца пробела. Нельзя комбинировать с AEWB_STOPSPACEEND.
#define AEWB_STOPNEWLINE     0x00000100  //Движение останавливается при обнаружении новой строки.
#define AEWB_MINMOVE         0x00001000  //Минимальное движение или отсутствие движения, если флаги совпали.

//Флаги AEM_STREAMIN, AEM_STREAMOUT
#define AESF_SELECTION       0x00000001  //Потоковый ввод (чтение) или вывод (запись) текущего выделения. Если не указано, потоковый ввод (чтение) или вывод (запись) всего содержимого элемента управления.
#define AESF_FILLSPACES      0x00000002  //Потоковый вывод (запись) текущего колоночного выделения с заполнением пустых мест пробелами. Действительно, если член bColumnSel структуры AESTREAMOUT равен TRUE.

//Возвращаемое значение AEM_ISRANGEMODIFIED
#define AEIRM_UNMODIFIED      1
#define AEIRM_MODIFIEDUNSAVED 2
#define AEIRM_MODIFIEDSAVED   3

//Флаги AEM_GETUNDOPOS
#define AEGUP_CURRENT         0x00
#define AEGUP_NEXT            0x01
#define AEGUP_PREV            0x02
#define AEGUP_FIRST           0x04 //Всегда возвращает -1.
#define AEGUP_LAST            0x08 //Всегда возвращает -1.
#define AEGUP_NOUNDO          0x10 //Возвращает -1, если элемент отмены находится в стеке отмены.
#define AEGUP_NOREDO          0x20 //Возвращает -1, если элемент отмены находится в стеке повтора.
#define AEGUP_SAVED           0x40 //Всегда возвращает -1.

#ifndef FR_DOWN
  #define FR_DOWN 0x00000001
#endif
#ifndef FR_WHOLEWORD
  #define FR_WHOLEWORD 0x00000002
#endif
#ifndef FR_MATCHCASE
  #define FR_MATCHCASE 0x00000004
#endif
#ifndef EC_LEFTMARGIN
  #define EC_LEFTMARGIN 0x0001
#endif
#ifndef EC_RIGHTMARGIN
  #define EC_RIGHTMARGIN 0x0002
#endif
#ifndef GT_SELECTION
  #define GT_SELECTION 0x0002
#endif
#ifndef SPI_GETWHEELSCROLLLINES
  #define SPI_GETWHEELSCROLLLINES 0x0068
#endif
#ifndef WC_NO_BEST_FIT_CHARS
  #define WC_NO_BEST_FIT_CHARS 0x00000400
#endif
#ifndef WM_MOUSEWHEEL
  #define WM_MOUSEWHEEL 0x020A
#endif
#ifndef EN_DRAGDROPDONE
  #define EN_DRAGDROPDONE 0x070c
#endif
#ifndef EM_SHOWSCROLLBAR
  #define EM_SHOWSCROLLBAR (WM_USER + 96)
#endif
#ifndef EM_GETSCROLLPOS
  #define EM_GETSCROLLPOS (WM_USER + 221)
#endif
#ifndef EM_SETSCROLLPOS
  #define EM_SETSCROLLPOS (WM_USER + 222)
#endif
#ifndef EM_SETTEXTEX
  #define EM_SETTEXTEX (WM_USER + 97)

  #define ST_DEFAULT    0x0000
  #define ST_KEEPUNDO   0x0001
  #define ST_SELECTION  0x0002
  #define ST_NEWCHARS   0x0004

  typedef struct {
    DWORD flags;
    UINT codepage;
  } SETTEXTEX;
#endif

#ifndef MAKE_IDENTIFIER
  #define MAKE_IDENTIFIER(a, b, c, d)  ((DWORD)MAKELONG(MAKEWORD(a, b), MAKEWORD(c, d)))
#endif

#ifndef mod
  #define mod(a)  (((a) < 0) ? (0 - (a)) : (a))
#endif

DECLARE_HANDLE (AEHDOC);
DECLARE_HANDLE (AEHPRINT);
DECLARE_HANDLE (AEHTHEME);
DECLARE_HANDLE (AEHDELIMITER);
DECLARE_HANDLE (AEHWORD);
DECLARE_HANDLE (AEHQUOTE);
DECLARE_HANDLE (AEHMARKTEXT);
DECLARE_HANDLE (AEHMARKRANGE);

typedef LRESULT (CALLBACK *AEEditProc)(AEHDOC hDoc, UINT uMsg, WPARAM wParam, LPARAM lParam);
//hDoc        Дескриптор документа, возвращенный AEM_GETDOCUMENT или AEM_CREATEDOCUMENT.
//uMsg        Идентификатор сообщения, например EM_SETSEL.
//lParam      Дополнительный параметр.
//wParam      Дополнительный параметр.
//
//Возвращаемое значение
// Зависит от сообщения.


//// Структуры для поддержки x64 RichEdit

typedef struct {
  INT_PTR cpMin;
  INT_PTR cpMax;
} CHARRANGE64;

typedef struct {
  CHARRANGE64 chrg;
  LPSTR lpstrText;
} TEXTRANGE64A;

typedef struct {
  CHARRANGE64 chrg;
  LPWSTR lpstrText;
} TEXTRANGE64W;

typedef struct {
  CHARRANGE64 chrg;
  LPCSTR lpstrText;
  CHARRANGE64 chrgText;
} FINDTEXTEX64A;

typedef struct {
  CHARRANGE64 chrg;
  LPCWSTR lpstrText;
  CHARRANGE64 chrgText;
} FINDTEXTEX64W;

typedef struct {
  UINT_PTR cb;
  DWORD flags;
  UINT codepage;
  LPCSTR lpDefaultChar;
  LPBOOL lpUsedDefChar;
} GETTEXTEX64;

typedef struct {
  NMHDR nmhdr;
  CHARRANGE chrg;
  WORD seltyp;
  CHARRANGE64 chrg64;
} SELCHANGE64;

typedef struct {
  NMHDR nmhdr;
  HANDLE hDrop;
  LONG cp;
  BOOL fProtected;
  INT_PTR cp64;
} ENDROPFILES64;

typedef struct {
  NMHDR nmhdr;
  UINT msg;
  WPARAM wParam;
  LPARAM lParam;
  CHARRANGE chrg;
  CHARRANGE64 chrg64;
} ENLINK64;


//// Структуры для поддержки x64

typedef struct {
  INT_PTR x;
  INT_PTR y;
} POINT64;

typedef struct {
  INT_PTR cx;
  INT_PTR cy;
} SIZE64;


//// Структуры

#ifndef _HSTACK_STRUCT_
#define _HSTACK_STRUCT_
typedef struct {
  INT_PTR first;
  INT_PTR last;
} HSTACK;
#endif

#ifndef _STACK_STRUCT_
#define _STACK_STRUCT_
typedef struct _stack {
  struct _stack *next;
  struct _stack *prev;
} stack;
#endif

typedef struct _AELINEDATA {
  struct _AELINEDATA *next;   //Указатель на следующую структуру AELINEDATA.
  struct _AELINEDATA *prev;   //Указатель на предыдущую структуру AELINEDATA.
  wchar_t *wpLine;            //Текст строки, заканчивающийся NULL-символом.
  int nLineLen;               //Длина wpLine, не включая завершающий NULL-символ.
  BYTE nLineBreak;            //Новая строка: AELB_EOF, AELB_R, AELB_N, AELB_RN, AELB_RRN или AELB_WRAP.
  BYTE nLineFlags;            //Зарезервировано.
  WORD nReserved;             //Зарезервировано.
  int nLineWidth;             //Ширина строки в пикселях.
  int nSelStart;              //Начальная позиция символа выделения в строке.
  int nSelEnd;                //Конечная позиция символа выделения в строке.
} AELINEDATA;

typedef struct _AELINEINDEX {
  int nLine;                  //Номер строки в документе, начиная с нуля.
  AELINEDATA *lpLine;         //Указатель на структуру AELINEDATA.
} AELINEINDEX;

typedef struct _AECHARINDEX {
  int nLine;                  //Номер строки в документе, начиная с нуля.
  AELINEDATA *lpLine;         //Указатель на структуру AELINEDATA.
  int nCharInLine;            //Позиция символа в строке.
} AECHARINDEX;

typedef struct {
  AECHARINDEX ciMin;  //Индекс первого символа в диапазоне.
  AECHARINDEX ciMax;  //Индекс последнего символа в диапазоне.
} AECHARRANGE;

typedef struct {
  AECHARRANGE crSel;  //Диапазон символов.
  DWORD dwFlags;      //См. определения AESELT_*.
  DWORD dwType;       //См. определения AESCT_*.
} AESELECTION;

typedef struct _AEPOINT {
  struct _AEPOINT *next;   //Указатель на следующую структуру AEPOINT.
  struct _AEPOINT *prev;   //Указатель на предыдущую структуру AEPOINT.
  AECHARINDEX ciPoint;     //Индекс символа только для чтения.
  INT_PTR nPointOffset;    //Смещение символа RichEdit или одно из определений AEPTO_*.
  int nPointLen;           //Длина точки.
  DWORD dwFlags;           //См. определения AEPTF_*.
  UINT_PTR dwUserData;     //Пользовательские данные.
  INT_PTR nTmpPointOffset; //Не использовать. Только для внутреннего кода.
  int nTmpPointLen;        //Не использовать. Только для внутреннего кода.
} AEPOINT;

typedef struct _AEFOLD {
  struct _AEFOLD *next;       //Указатель на следующую структуру AEFOLD.
  struct _AEFOLD *prev;       //Указатель на предыдущую структуру AEFOLD.
  struct _AEFOLD *parent;     //Указатель на родительскую структуру AEFOLD.
  struct _AEFOLD *firstChild; //Указатель на первый дочерний элемент AEFOLD.
  struct _AEFOLD *lastChild;  //Указатель на последний дочерний элемент AEFOLD.
  AEPOINT *lpMinPoint;        //Минимальная точка строки.
  AEPOINT *lpMaxPoint;        //Максимальная точка строки.
  DWORD dwFlags;              //См. определения AEFOLDF_*.
  DWORD dwFontStyle;          //См. определения AEHLS_*.
  COLORREF crText;            //Цвет текста. Если -1, то не устанавливать.
  COLORREF crBk;              //Цвет фона. Если -1, то не устанавливать.
  int nParentID;              //Идентификатор родительского правила.
  int nRuleID;                //Идентификатор правила.
  AEHTHEME hRuleTheme;        //Тема подсветки правила.
  UINT_PTR dwUserData;        //Пользовательские данные.
} AEFOLD;

typedef struct {
  DWORD dwFlags;         //[in]  См. определения AEFF_*.
  UINT_PTR dwFindIt;     //[in]  Зависит от определения AEFF_FIND*.
  AEFOLD *lpParent;      //[out] Родительский фолд.
  AEFOLD *lpPrevSubling; //[out] Предыдущий смежный фолд.
} AEFINDFOLD;

typedef struct {
  const char *pText;     //[in] Текст для добавления.
  UINT_PTR dwTextLen;    //[in] Длина текста. Если это значение равно -1, строка считается нуль-терминированной, и длина вычисляется автоматически.
  int nNewLine;          //[in] См. определения AELB_*.
  int nCodePage;         //[in] Идентификатор кодовой страницы (любая доступная в системе). Вы также можете указать одно из следующих значений: CP_ACP - кодовая страница ANSI, CP_OEMCP - кодовая страница OEM, CP_UTF8 - кодовая страница UTF-8.
} AESETTEXTA;

typedef struct {
  const wchar_t *pText;  //[in] Текст для добавления.
  UINT_PTR dwTextLen;    //[in] Длина текста. Если это значение равно -1, строка считается нуль-терминированной, и длина вычисляется автоматически.
  int nNewLine;          //[in] См. определения AELB_*.
} AESETTEXTW;

typedef struct {
  const char *pText;     //[in] Текст для добавления.
  UINT_PTR dwTextLen;    //[in] Длина текста. Если это значение равно -1, строка считается нуль-терминированной, и длина вычисляется автоматически.
  int nNewLine;          //[in] См. определения AELB_*.
  int nCodePage;         //[in] Идентификатор кодовой страницы (любая доступная в системе). Вы также можете указать одно из следующих значений: CP_ACP - кодовая страница ANSI, CP_OEMCP - кодовая страница OEM, CP_UTF8 - кодовая страница UTF-8.
} AEAPPENDTEXTA;

typedef struct {
  const wchar_t *pText;  //[in] Текст для добавления.
  UINT_PTR dwTextLen;    //[in] Длина текста. Если это значение равно -1, строка считается нуль-терминированной, и длина вычисляется автоматически.
  int nNewLine;          //[in] См. определения AELB_*.
} AEAPPENDTEXTW;

typedef struct {
  const char *pText;           //[in]  Текст для замены.
  UINT_PTR dwTextLen;          //[in]  Длина текста. Если это значение равно -1, строка считается нуль-терминированной, и длина вычисляется автоматически.
  int nNewLine;                //[in]  См. определения AELB_*.
  DWORD dwFlags;               //[in]  См. определения AEREPT_*.
  AECHARINDEX *ciInsertStart;  //[out] Индекс символа "откуда" после замены.
  AECHARINDEX *ciInsertEnd;    //[out] Индекс символа "докуда" после замены.
  int nCodePage;               //[in]  Идентификатор кодовой страницы (любая доступная в системе). Вы также можете указать одно из следующих значений: CP_ACP - кодовая страница ANSI, CP_OEMCP - кодовая страница OEM, CP_UTF8 - кодовая страница UTF-8.
} AEREPLACESELA;

typedef struct {
  const wchar_t *pText;        //[in]  Текст для замены.
  UINT_PTR dwTextLen;          //[in]  Длина текста. Если это значение равно -1, строка считается нуль-терминированной, и длина вычисляется автоматически.
  int nNewLine;                //[in]  См. определения AELB_*.
  DWORD dwFlags;               //[in]  См. определения AEREPT_*.
  AECHARINDEX *ciInsertStart;  //[out] Индекс символа "откуда" после замены.
  AECHARINDEX *ciInsertEnd;    //[out] Индекс символа "докуда" после замены.
} AEREPLACESELW;

typedef struct {
  AECHARRANGE cr;             //[in]  Диапазон символов для получения.
  BOOL bColumnSel;            //[in]  Колоночное выделение. Если это значение равно -1, используется текущий тип выделения.
  char *pBuffer;              //[out] Указатель на буфер, который получает текст. Если это значение равно NULL, функция возвращает требуемый размер буфера в символах.
  UINT_PTR dwBufferMax;       //[in]  Указывает максимальное количество символов для копирования в буфер, включая NULL-символ.
  int nNewLine;               //[in]  См. определения AELB_*.
  int nCodePage;              //[in]  Идентификатор кодовой страницы (любая доступная в системе). Вы также можете указать одно из следующих значений: CP_ACP - кодовая страница ANSI, CP_OEMCP - кодовая страница OEM, CP_UTF8 - кодовая страница UTF-8.
  const char *lpDefaultChar;  //[in]  Указывает на символ, используемый, если широкий символ не может быть представлен в указанной кодовой странице. Если этот член равен NULL, используется системное значение по умолчанию.
  BOOL *lpUsedDefChar;        //[in]  Указывает на флаг, который показывает, использовался ли символ по умолчанию. Флаг устанавливается в TRUE, если один или несколько широких символов в исходной строке не могут быть представлены в указанной кодовой странице. В противном случае флаг устанавливается в FALSE. Этот член может быть NULL.
  BOOL bFillSpaces;           //[in]  Если bColumnSel равно TRUE, заполнять пустые места пробелами.
} AETEXTRANGEA;

typedef struct {
  AECHARRANGE cr;             //[in]  Диапазон символов для получения.
  BOOL bColumnSel;            //[in]  Колоночное выделение. Если это значение равно -1, используется текущий тип выделения. Если bColumnSel равно TRUE, то выделение должно существовать, в противном случае это не обязательно.
  wchar_t *pBuffer;           //[out] Указатель на буфер, который получает текст. Если это значение равно NULL, функция возвращает требуемый размер буфера в символах.
  UINT_PTR dwBufferMax;       //[in]  Указывает максимальное количество символов для копирования в буфер, включая NULL-символ.
  int nNewLine;               //[in]  См. определения AELB_*.
  int nCodePage;              //[in]  Игнорируется. Кодовая страница всегда 1200 (UTF-16 LE).
  const char *lpDefaultChar;  //[in]  Игнорируется.
  BOOL *lpUsedDefChar;        //[in]  Игнорируется.
  BOOL bFillSpaces;           //[in]  Если bColumnSel равно TRUE, заполнять пустые места пробелами.
} AETEXTRANGEW;

typedef DWORD (CALLBACK *AEStreamCallback)(UINT_PTR dwCookie, wchar_t *wszBuf, DWORD dwBufBytesSize, DWORD *dwBufBytesDone);
//dwCookie        Значение члена dwCookie структуры AESTREAMIN или AESTREAMOUT. Приложение указывает это значение при отправке сообщения AEM_STREAMIN или AEM_STREAMOUT.
//wszBuf          Указатель на буфер для чтения или записи. Для операции потокового ввода (чтения) функция обратного вызова заполняет этот буфер данными для передачи в элемент редактирования. Для операции потокового вывода (записи) буфер содержит данные из элемента управления, которые функция обратного вызова записывает в какое-либо хранилище.
//dwBufBytesSize  Количество байтов для чтения или записи.
//dwBufBytesDone  Указатель на переменную, которую функция обратного вызова устанавливает в количество фактически прочитанных или записанных байтов.
//
//Возвращаемое значение
// Функция обратного вызова возвращает ноль для обозначения успеха.
//
//Примечания
// Элемент управления продолжает вызывать функцию обратного вызова, пока не выполнится одно из следующих условий:
// * Функция обратного вызова возвращает ненулевое значение.
// * Функция обратного вызова возвращает ноль в параметре *dwBufBytesDone.

typedef struct {
  UINT_PTR dwCookie;            //[in]  Указывает определенное приложением значение, которое элемент редактирования передает функции AEStreamCallback, указанной членом lpCallback.
  DWORD dwError;                //[out] Указывает результаты операции потокового ввода (чтения).
  AEStreamCallback lpCallback;  //[in]  Указатель на функцию AEStreamCallback, которая является определенной приложением функцией, вызываемой элементом управления для передачи данных. Элемент управления вызывает функцию обратного вызова многократно, передавая часть данных при каждом вызове.
  int nNewLine;                 //[in]  См. определения AELB_*.
  UINT_PTR dwTextLen;           //[in]  Длина текста. Необходимо, если используется уведомление AEN_PROGRESS.
  int nFirstNewLine;            //[out] Указывает первую новую строку. См. определения AELB_*.
} AESTREAMIN;

typedef struct {
  UINT_PTR dwCookie;            //[in]  Указывает определенное приложением значение, которое элемент редактирования передает функции AEStreamCallback, указанной членом lpCallback.
  DWORD dwError;                //[out] Указывает результат операции потокового вывода (записи).
  AEStreamCallback lpCallback;  //[in]  Указатель на функцию AEStreamCallback, которая является определенной приложением функцией, вызываемой элементом управления для передачи данных. Элемент управления вызывает функцию обратного вызова многократно, передавая часть данных при каждом вызове.
  int nNewLine;                 //[in]  См. определения AELB_*.
  BOOL bColumnSel;              //[in]  Колоночное выделение. Если это значение равно -1, используется текущий тип выделения.
} AESTREAMOUT;

typedef struct {
  DWORD dwFlags;                //[in]  См. определения AEFR_*.
  const char *pText;            //[in]  Текст для поиска.
  UINT_PTR dwTextLen;           //[in]  Длина текста. Если это значение равно -1, строка считается нуль-терминированной, и длина вычисляется автоматически.
  int nNewLine;                 //[in]  См. определения AELB_*.
  AECHARRANGE crSearch;         //[in]  Диапазон символов для поиска.
  AECHARRANGE crFound;          //[out] Диапазон символов, в котором найден текст.
  INT_PTR nCompileErrorOffset;  //[out] Содержит смещение в шаблоне, если произошла ошибка во время компиляции шаблона. Возвращается, когда установлен AEFR_REGEXP.
} AEFINDTEXTA;

typedef struct {
  DWORD dwFlags;                //[in]  См. определения AEFR_*.
  const wchar_t *pText;         //[in]  Текст для поиска.
  UINT_PTR dwTextLen;           //[in]  Длина текста. Если это значение равно -1, строка считается нуль-терминированной, и длина вычисляется автоматически.
  int nNewLine;                 //[in]  См. определения AELB_*.
  AECHARRANGE crSearch;         //[in]  Диапазон символов для поиска.
  AECHARRANGE crFound;          //[out] Диапазон символов, в котором найден текст.
  INT_PTR nCompileErrorOffset;  //[out] Содержит смещение в шаблоне, если произошла ошибка во время компиляции шаблона. Возвращается, когда установлен AEFR_REGEXP.
} AEFINDTEXTW;

typedef struct {
  DWORD dwFlags;                  //[in] См. определения AECLR_*.
  COLORREF crCaret;               //[in] Цвет курсора.
  COLORREF crBasicText;           //[in] Цвет основного текста.
  COLORREF crBasicBk;             //[in] Цвет основного фона.
  COLORREF crSelText;             //[in] Цвет текста в выделении.
  COLORREF crSelBk;               //[in] Цвет фона в выделении.
  COLORREF crActiveLineText;      //[in] Цвет текста в активной строке.
  COLORREF crActiveLineBk;        //[in] Цвет фона в активной строке.
  COLORREF crUrlText;             //[in] Цвет текста гиперссылки.
  COLORREF crActiveColumn;        //[in] Цвет активного столбца.
  COLORREF crColumnMarker;        //[in] Цвет маркера столбца.
  COLORREF crUrlCursorText;       //[in] Цвет текста активной гиперссылки.
  COLORREF crUrlVisitText;        //[in] Цвет текста посещенной гиперссылки.
  COLORREF crActiveLineBorder;    //[in] Цвет границы в активной строке.
  COLORREF crAltLineText;         //[in] Цвет текста в чередующейся строке.
  COLORREF crAltLineBk;           //[in] Цвет фона в чередующейся строке.
  COLORREF crAltLineBorder;       //[in] Цвет границы в чередующейся строке.
} AECOLORS;

typedef struct {
  DWORD dwFlags;           //[in] См. определения AEGHF_*.
  DWORD dwFontStyle;       //[Out] См. определения AEHLS_*.
  COLORREF crText;         //[Out] Цвет текста в строке.
  COLORREF crBk;           //[Out] Цвет фона в строке.
  COLORREF crBorderTop;    //[Out] Цвет верхней границы строки.
  COLORREF crBorderBottom; //[Out] Цвет нижней границы строки.
} AECHARCOLORS;

typedef struct {
  AECHARINDEX *ciCharIn;   //[in]  Входной индекс символа.
  AECHARINDEX *ciCharOut;  //[out] Выходной индекс символа (результат).
  INT_PTR nOffset;         //[in]  Смещение может быть положительным или отрицательным. Например, +1 вернет следующий символ, -1 вернет предыдущий символ.
  int nNewLine;            //[in]  См. определения AELB_*.
} AEINDEXOFFSET;

typedef struct {
  AECHARINDEX *ciChar1;   //[in] Первый индекс символа. Если NULL, используется первый символ.
  AECHARINDEX *ciChar2;   //[in] Второй индекс символа. Если NULL, используется последний символ.
  BOOL bColumnSel;        //[in] Колоночное выделение. Если это значение равно -1, используется текущий тип выделения.
  int nNewLine;           //[in] См. определения AELB_*.
} AEINDEXSUBTRACT;

typedef struct {
  DWORD dwFlags;    //[in]     См. определения AESC_*.
  POINT64 ptPos;    //[in,out] Точка для прокрутки, игнорируется, если указан флаг AESC_POINTCARET.
                    //         Если указан флаг AESC_POINTOUT, то после возврата из AEM_SCROLLTOPOINT ptPos будет содержать новую позицию прокрутки, в противном случае не изменяется.
  int nOffsetX;     //[in]     Горизонтальное смещение прокрутки.
  int nOffsetY;     //[in]     Вертикальное смещение прокрутки.
} AESCROLLTOPOINT;

typedef struct {
  DWORD dwFlags;    //См. определения AESC_OFFSET*.
  DWORD dwSelFlags; //См. определения AESELT_*. Может быть нулем.
  DWORD dwSelType;  //См. определения AESCT_*.
  int nOffsetX;     //Минимальное количество символов до горизонтального края окна.
  int nOffsetY;     //Минимальное количество строк до вертикального края окна.
} AESCROLLCARETOPTIONS;

typedef struct {
  AEHDOC hDoc;     //Дескриптор документа. См. сообщение AEM_CREATEDOCUMENT.
  UINT uMsg;       //Сообщение окна.
  WPARAM wParam;   //Первый дополнительный параметр окна.
  LPARAM lParam;   //Второй дополнительный параметр окна.
  LRESULT lResult; //Результат после возврата из окна сообщения.
} AESENDMESSAGE;

typedef struct _AEURLVISIT {
  struct _AEURLVISIT *next;
  struct _AEURLVISIT *prev;
  wchar_t *pUrlText;    //Строка URL.
  INT_PTR nUrlTextLen;  //Длина строки URL.
  int nVisitCount;      //Количество посещений.
  BOOL bStatic;         //TRUE  Элемент управления не удаляет элемент с нулевым количеством посещений.
                        //FALSE Элемент управления может автоматически удалить этот элемент с нулевым количеством посещений.
} AEURLVISIT;

typedef struct {
  AEURLVISIT *first;
  AEURLVISIT *last;
} AESTACKURLVISIT;

typedef struct {
  DWORD dwFlags;          //[in]     См. определения AEPRN_*.
  HDC hPrinterDC;         //[in]     Контекст устройства принтера.
  HFONT hEditFont;        //[in]     Шрифт редактирования.
  HFONT hPrintFont;       //[out]    Шрифт для печати (отображенный шрифт редактирования).
  int nCharHeight;        //[out]    Высота символа для печати.
  int nAveCharWidth;      //[out]    Средняя ширина символа для печати.
  int nSpaceCharWidth;    //[out]    Ширина пробела для печати.
  int nTabWidth;          //[out]    Ширина табуляции для печати.
  RECT rcMargins;         //[in]     Указывает ширину левого, верхнего, правого и нижнего полей. Флаг AEPRN_INHUNDREDTHSOFMILLIMETERS или AEPRN_INTHOUSANDTHSOFINCHES указывает единицы измерения.
  RECT rcPageFull;        //[out]    Полный прямоугольник страницы. Заполняется сообщением AEM_STARTPRINTDOC.
  RECT rcPageIn;          //[in,out] Доступный прямоугольник страницы (за вычетом полей). Заполняется сообщением AEM_STARTPRINTDOC и может быть изменен пользователем перед вызовом AEM_PRINTPAGE.
  RECT rcPageOut;         //[out]    Заполненный прямоугольник страницы. Заполняется сообщением AEM_PRINTPAGE.
  AECHARRANGE crText;     //[in,out] Диапазон текста для печати. Заполняется пользователем и изменяется после сообщения AEM_PRINTPAGE.
} AEPRINT;

typedef struct _AEDELIMITEMA {
  struct _AEDELIMITEMA *next;
  struct _AEDELIMITEMA *prev;
  int nIndex;                //Позиция элемента: если положительное, вставляется в начало стека; если отрицательное, в конец.
  const char *pDelimiter;    //Строка-разделитель.
  int nDelimiterLen;         //Длина строки-разделителя.
  DWORD dwFlags;             //См. определения AEHLF_*.
  DWORD dwFontStyle;         //См. определения AEHLS_*.
  COLORREF crText;           //Цвет текста разделителя. Если -1, то не устанавливать.
  COLORREF crBk;             //Цвет фона разделителя. Если -1, то не устанавливать.
  int nParentID;             //Идентификатор родительского правила.
} AEDELIMITEMA;

typedef struct _AEDELIMITEMW {
  struct _AEDELIMITEMW *next;
  struct _AEDELIMITEMW *prev;
  int nIndex;                //Позиция элемента: если положительное, вставляется в начало стека; если отрицательное, в конец.
  const wchar_t *pDelimiter; //Строка-разделитель.
  int nDelimiterLen;         //Длина строки-разделителя.
  DWORD dwFlags;             //См. определения AEHLF_*.
  DWORD dwFontStyle;         //См. определения AEHLS_*.
  COLORREF crText;           //Цвет текста разделителя. Если -1, то не устанавливать.
  COLORREF crBk;             //Цвет фона разделителя. Если -1, то не устанавливать.
  int nParentID;             //Идентификатор родительского правила.
} AEDELIMITEMW;

typedef struct _AEWORDITEMA {
  struct _AEWORDITEMA *next;
  struct _AEWORDITEMA *prev;
  int nIndex;                //Зарезервировано. Элементы слов автоматически сортируются.
  const char *pWord;         //Строка слова.
  int nWordLen;              //Длина строки слова.
  DWORD dwFlags;             //См. определения AEHLF_*.
  DWORD dwFontStyle;         //См. определения AEHLS_*.
  COLORREF crText;           //Цвет текста слова. Если -1, то не устанавливать.
  COLORREF crBk;             //Цвет фона слова. Если -1, то не устанавливать.
  int nParentID;             //Идентификатор родительского правила.
} AEWORDITEMA;

typedef struct _AEWORDITEMW {
  struct _AEWORDITEMW *next;
  struct _AEWORDITEMW *prev;
  int nIndex;                //Зарезервировано. Элементы слов автоматически сортируются.
  const wchar_t *pWord;      //Строка слова.
  int nWordLen;              //Длина строки слова.
  DWORD dwFlags;             //См. определения AEHLF_*.
  DWORD dwFontStyle;         //См. определения AEHLS_*.
  COLORREF crText;           //Цвет текста слова. Если -1, то не устанавливать.
  COLORREF crBk;             //Цвет фона слова. Если -1, то не устанавливать.
  int nParentID;             //Идентификатор родительского правила.
} AEWORDITEMW;

typedef struct _AEQUOTEITEMA {
  struct _AEQUOTEITEMA *next;
  struct _AEQUOTEITEMA *prev;
  int nIndex;                    //Зарезервировано. Элементы начала кавычек автоматически группируются в отдельный стек, если следующие члены равны: pQuoteStart, chEscape и dwFlags с AEHLF_QUOTESTART_ISDELIMITER, AEHLF_ATLINESTART, AEHLF_QUOTESTART_ISWORD.
  const char *pQuoteStart;       //Строка начала кавычки.
  int nQuoteStartLen;            //Длина строки начала кавычки.
  const char *pQuoteEnd;         //Строка конца кавычки. Если NULL, конец строки используется как конец кавычки.
  int nQuoteEndLen;              //Длина строки конца кавычки.
  char chEscape;                 //Экранирующий символ. Если он предшествует строке кавычки, кавычка игнорируется.
  const char *pQuoteInclude;     //Строка включения кавычки.
  int nQuoteIncludeLen;          //Длина строки включения кавычки.
  const char *pQuoteExclude;     //Строка исключения кавычки.
  int nQuoteExcludeLen;          //Длина строки исключения кавычки.
  DWORD dwFlags;                 //См. определения AEHLF_*.
  DWORD dwFontStyle;             //См. определения AEHLS_*.
  COLORREF crText;               //Цвет текста кавычки. Если -1, то не устанавливать.
  COLORREF crBk;                 //Цвет фона кавычки. Если -1, то не устанавливать.
  void *lpQuoteStart;            //Не использовать. Только для внутреннего кода.
  int nParentID;                 //Идентификатор родительского правила.
  int nRuleID;                   //Идентификатор правила.
  INT_PTR nCompileErrorOffset;   //Содержит смещение в pQuoteStart, если произошла ошибка во время компиляции шаблона регулярного выражения.
} AEQUOTEITEMA;

typedef struct _AEQUOTEITEMW {
  struct _AEQUOTEITEMW *next;
  struct _AEQUOTEITEMW *prev;
  int nIndex;                    //Зарезервировано. Элементы начала кавычек автоматически группируются в отдельный стек, если следующие члены равны: pQuoteStart, chEscape и dwFlags с AEHLF_QUOTESTART_ISDELIMITER, AEHLF_ATLINESTART, AEHLF_QUOTESTART_ISWORD.
  const wchar_t *pQuoteStart;    //Строка начала кавычки.
  int nQuoteStartLen;            //Длина строки начала кавычки.
  const wchar_t *pQuoteEnd;      //Строка конца кавычки. Если NULL, конец строки используется как конец кавычки.
  int nQuoteEndLen;              //Длина строки конца кавычки.
  wchar_t chEscape;              //Экранирующий символ. Если он предшествует строке кавычки, кавычка игнорируется.
  const wchar_t *pQuoteInclude;  //Строка включения кавычки.
  int nQuoteIncludeLen;          //Длина строки включения кавычки.
  const wchar_t *pQuoteExclude;  //Строка исключения кавычки.
  int nQuoteExcludeLen;          //Длина строки исключения кавычки.
  DWORD dwFlags;                 //См. определения AEHLF_*.
  DWORD dwFontStyle;             //См. определения AEHLS_*.
  COLORREF crText;               //Цвет текста кавычки. Если -1, то не устанавливать.
  COLORREF crBk;                 //Цвет фона кавычки. Если -1, то не устанавливать.
  int nParentID;                 //Идентификатор родительского правила.
  int nRuleID;                   //Идентификатор правила.
  void *lpQuoteStart;            //Не использовать. Только для внутреннего кода.
  union {
    void *lpREGroupStack;        //Не использовать. Только для внутреннего кода.
    INT_PTR nCompileErrorOffset; //Содержит смещение в pQuoteStart, если произошла ошибка во время компиляции шаблона регулярного выражения.
  };
} AEQUOTEITEMW;

typedef struct {
  DWORD dwFlags;                //См. определения AEREGCF_*.
  DWORD dwFontStyle;            //См. определения AEHLS_*.
  COLORREF crText;              //Цвет текста кавычки. Если -1, то не устанавливать.
  COLORREF crBk;                //Цвет фона кавычки. Если -1, то не устанавливать.
} AEREGROUPCOLOR;

typedef struct _AEMARKTEXTITEMA {
  struct _AEMARKTEXTITEMA *next;
  struct _AEMARKTEXTITEMA *prev;
  int nIndex;                  //Позиция элемента: если положительное, вставляется в начало стека; если отрицательное, в конец.
  const char *pMarkText;       //Текст пометки.
  int nMarkTextLen;            //Длина текста пометки.
  DWORD dwFlags;               //См. определения AEHLF_*.
  DWORD dwFontStyle;           //См. определения AEHLS_*.
  COLORREF crText;             //Цвет текста пометки. Если -1, то не устанавливать.
  COLORREF crBk;               //Цвет фона пометки. Если -1, то не устанавливать.
  INT_PTR nCompileErrorOffset; //Содержит смещение в pMarkText, если произошла ошибка во время компиляции шаблона регулярного выражения.
} AEMARKTEXTITEMA;

typedef struct _AEMARKTEXTITEMW {
  struct _AEMARKTEXTITEMW *next;
  struct _AEMARKTEXTITEMW *prev;
  int nIndex;                    //Позиция элемента: если положительное, вставляется в начало стека; если отрицательное, в конец.
  const wchar_t *pMarkText;      //Текст пометки.
  int nMarkTextLen;              //Длина текста пометки.
  DWORD dwFlags;                 //См. определения AEHLF_*.
  DWORD dwFontStyle;             //См. определения AEHLS_*.
  COLORREF crText;               //Цвет текста пометки. Если -1, то не устанавливать.
  COLORREF crBk;                 //Цвет фона пометки. Если -1, то не устанавливать.
  union {
    void *lpREGroupStack;        //Не использовать. Только для внутреннего кода.
    INT_PTR nCompileErrorOffset; //Содержит смещение в pMarkText, если произошла ошибка во время компиляции шаблона регулярного выражения.
  };
} AEMARKTEXTITEMW;

typedef struct _AEMARKRANGEITEM {
  struct _AEMARKRANGEITEM *next;
  struct _AEMARKRANGEITEM *prev;
  int nIndex;              //Позиция элемента: если положительное, вставляется в начало стека; если отрицательное, в конец.
  CHARRANGE64 crMarkRange; //Член cpMin - первый символ в диапазоне (смещение RichEdit), член cpMax - последний символ в диапазоне (смещение RichEdit).
  DWORD dwFlags;           //Зарезервировано.
  DWORD dwFontStyle;       //См. определения AEHLS_*.
  COLORREF crText;         //Цвет текста пометки. Если -1, то не устанавливать.
  COLORREF crBk;           //Цвет фона пометки. Если -1, то не устанавливать.
} AEMARKRANGEITEM;

typedef struct {
  AEMARKTEXTITEMW *lpMarkText;
  AECHARRANGE crMarkText;
} AEMARKTEXTMATCH;

typedef struct {
  AEMARKRANGEITEM *lpMarkRange;
  CHARRANGE64 crMarkRange;
} AEMARKRANGEMATCH;

typedef struct _AEQUOTEMATCHITEM {
  struct _AEQUOTEMATCHITEM *next;
  struct _AEQUOTEMATCHITEM *prev;
  AEQUOTEITEMW *lpQuote;
  AECHARRANGE crQuoteStart;
  AECHARRANGE crQuoteEnd;
  INT_PTR nQuoteLen;
  DWORD dwFontStyle;   //См. определения AEHLS_*.
  DWORD dwActiveText;  //Цвет текста. Если -1, то не устанавливать.
  DWORD dwActiveBk;    //Цвет фона. Если -1, то не устанавливать.
} AEQUOTEMATCHITEM;

typedef struct {
  AEQUOTEMATCHITEM *first;
  AEQUOTEMATCHITEM *last;
} AESTACKQUOTEMATCH;

typedef struct {
  AEQUOTEITEMW *lpQuote;
  AECHARRANGE crQuoteStart;
  AECHARRANGE crQuoteEnd;
  INT_PTR nQuoteLen;
  AECHARINDEX ciFindFirst;
  AECHARINDEX ciChildScan;
  AESTACKQUOTEMATCH hParentStack;
  int nParentType;     //См. определения AEHAP_*.
  DWORD dwFontStyle;   //См. определения AEHLS_*.
  DWORD dwActiveText;  //Цвет текста. Если -1, то не устанавливать.
  DWORD dwActiveBk;    //Цвет фона. Если -1, то не устанавливать.
} AEQUOTEMATCH;

typedef struct {
  AEDELIMITEMW *lpDelim1;
  AECHARRANGE crDelim1;
  AEWORDITEMW *lpWord;
  AECHARRANGE crWord;
  AEDELIMITEMW *lpDelim2;
  AECHARRANGE crDelim2;
} AEWORDMATCH;

typedef struct _AEACTIVETHEMEITEM {
  struct _AEACTIVETHEMEITEM *next;
  struct _AEACTIVETHEMEITEM *prev;
  AEHTHEME hActiveTheme;
} AEACTIVETHEMEITEM;

typedef struct {
  AEACTIVETHEMEITEM *first;
  AEACTIVETHEMEITEM *last;
} AESTACKACTIVETHEME;

typedef struct {
  AEFOLD *lpFold;
  CHARRANGE64 crFoldStart;
  CHARRANGE64 crFoldEnd;
  INT_PTR nFoldStartMax;
  AECHARINDEX ciFoldStartMax;
  AEHDOC hDoc;
  AEHTHEME hActiveThemeBegin;
  AESTACKACTIVETHEME hParentStack;
} AEFOLDMATCH;

typedef struct {
  DWORD cb;              //Размер структуры.
  DWORD dwDefaultText;   //Цвет текста без подсветки.
  DWORD dwDefaultBk;     //Цвет фона без подсветки.
  DWORD dwActiveText;    //Цвет текста с подсветкой.
  DWORD dwActiveBk;      //Цвет фона с подсветкой.
  DWORD dwFontStyle;     //См. определения AEHLS_*.
  DWORD dwPaintType;     //См. определения AEHPT_*.
  DWORD dwFindFirst;     //Не использовать. Только для внутреннего кода.

  AEWORDMATCH wm;        //Найдены элементы слова и/или разделители, если AEWORDITEMW.lpDelim1 или AEWORDITEMW.lpWord или AEWORDITEMW.lpDelim2 не равны NULL.
  AEQUOTEMATCH qm;       //Найден элемент кавычки, если AEQUOTEMATCH.lpQuote не равен NULL.
  AEMARKRANGEMATCH mrm;  //Найден элемент диапазона пометки, если AEMARKRANGEMATCH.lpMarkRange не равен NULL.
  AEMARKTEXTMATCH mtm;   //Найден элемент текста пометки, если AEMARKTEXTMATCH.lpMarkText не равен NULL.
  AEFOLDMATCH fm;        //Найден элемент фолда, если AEFOLDMATCH.lpFold не равен NULL.
  AECHARRANGE crLink;    //Найден элемент URL, если AECHARRANGE.ciMin.lpLine и AECHARRANGE.ciMax.lpLine не равны NULL.
} AEHLPAINT;

typedef DWORD (CALLBACK *AEGetHighLightCallback)(UINT_PTR dwCookie, AECHARRANGE *crAkelRange, CHARRANGE64 *crRichRange, AEHLPAINT *hlp);
//dwCookie        Значение члена dwCookie структуры AEGETHIGHLIGHT. Приложение указывает это значение при отправке сообщения AEM_HLGETHIGHLIGHT.
//crAkelRange     Диапазон подсвеченных символов.
//crRichRange     Диапазон подсвеченных символов (смещение RichEdit).
//hlp             Информация о подсветке.
//
//Возвращаемое значение
// Чтобы продолжить обработку, функция обратного вызова должна вернуть ноль; чтобы остановить обработку, она должна вернуть ненулевое значение.

typedef struct {
  UINT_PTR dwCookie;                 //[in]  Указывает определенное приложением значение, которое элемент редактирования передает функции AEGetHighLightCallback, указанной членом lpCallback.
  DWORD dwError;                     //[out] Указывает результат функции обратного вызова.
  AEGetHighLightCallback lpCallback; //[in]  Указатель на функцию AEGetHighLightCallback, которая является определенной приложением функцией, которую элемент управления вызывает для передачи информации о подсветке.
  AECHARRANGE crText;                //[in]  Диапазон символов для обработки.
  DWORD dwFlags;                     //[in]  См. определения AEGHF_*.
} AEGETHIGHLIGHT;

typedef struct {
  //Стандартный NMHDR
  HWND hwndFrom;
  UINT_PTR idFrom;
  UINT code;

  //Члены AkelEdit
  AEHDOC docFrom;      //Дескриптор документа. См. сообщение AEM_CREATEDOCUMENT.
} AENMHDR;

typedef struct {
  AENMHDR hdr;
  SIZE_T dwBytes;      //Количество байтов, которые не могут быть выделены.
} AENERRSPACE;

typedef struct {
  AENMHDR hdr;
  HWND hWndChange;     //AEN_SETFOCUS - дескриптор окна, которое потеряло фокус клавиатуры.
                       //AEN_KILLFOCUS - дескриптор окна, которое получает фокус клавиатуры.
} AENFOCUS;

typedef struct {
  AENMHDR hdr;
  INT_PTR nPosNew;     //Текущая позиция прокрутки.
  INT_PTR nPosOld;     //Предыдущая позиция прокрутки.
  INT_PTR nPosMax;     //Максимальная позиция прокрутки.
} AENSCROLL;

typedef struct {
  AENMHDR hdr;
  RECT rcDraw;         //Прямоугольник рисования.
  RECT rcEdit;         //Прямоугольник клиентской области редактирования.
} AENSETRECT;

typedef struct {
  AENMHDR hdr;
  DWORD dwType;           //См. определения AEPNT_*.
  HDC hDC;                //Контекст устройства.
  AECHARINDEX ciMinDraw;  //Первый индекс в строке для рисования.
  AECHARINDEX ciMaxDraw;  //Последний индекс в строке для рисования.
  INT_PTR nMinDrawOffset; //Первый символ в строке для рисования (смещение RichEdit).
  INT_PTR nMaxDrawOffset; //Последний символ в строке для рисования (смещение RichEdit).
  POINT ptMinDraw;        //Левый верхний угол в клиентских координатах первого символа в строке для рисования.
  POINT ptMaxDraw;        //Левый верхний угол в клиентских координатах последнего символа в строке для рисования.
} AENPAINT;

typedef DWORD (CALLBACK *AEPaintCallback)(UINT_PTR dwCookie, const AENPAINT *pnt);
//dwCookie     Значение члена dwCookie структуры AEPAINTCALLBACKADD. Приложение указывает это значение при отправке сообщения AEM_PAINTCALLBACK с AEPCB_ADD.
//pnt          Информация о рисовании.
//
//Возвращаемое значение
// Чтобы продолжить обработку, функция обратного вызова должна вернуть ноль; чтобы остановить обработку (до следующего AEPNT_BEGIN), она должна вернуть ненулевое значение.

typedef struct {
  AEPaintCallback lpCallback;
  UINT_PTR dwCookie;
} AEPAINTCALLBACKADD;

typedef struct _AEPAINTCALLBACK {
  struct _AEPAINTCALLBACK *next;
  struct _AEPAINTCALLBACK *prev;
  AEHDOC hDoc;                //Дескриптор документа. См. сообщение AEM_CREATEDOCUMENT.
  HWND hWnd;                  //Дескриптор окна.
  AEPaintCallback lpCallback; //Функция обратного вызова.
  UINT_PTR dwCookie;          //Пользовательский параметр для функции обратного вызова.
  DWORD dwError;              //Указывает результат функции обратного вызова.
} AEPAINTCALLBACK;

typedef struct {
  AEPAINTCALLBACK *first;
  AEPAINTCALLBACK *last;
} AESTACKPAINTCALLBACK;

typedef struct {
  AENMHDR hdr;
  UINT_PTR dwTextLimit;   //Текущий лимит текста.
} AENMAXTEXT;

typedef struct {
  AENMHDR hdr;
  DWORD dwType;        //См. определения AEPGS_*.
  DWORD dwTimeElapsed; //Прошедшее время с момента запуска действия.
  INT_PTR nCurrent;    //Обработано символов. Равно нулю, если это первое сообщение.
  INT_PTR nMaximum;    //Общее количество символов. Равно члену nCurrent, если это последнее сообщение.
} AENPROGRESS;

typedef struct {
  AENMHDR hdr;
  BOOL bModified;      //TRUE состояние документа установлено как измененное, FALSE состояние документа установлено как неизмененное.
} AENMODIFY;

typedef struct {
  AENMHDR hdr;
  AECHARRANGE crSel;     //Текущее выделение.
  AECHARINDEX ciCaret;   //Позиция индекса символа курсора.
  DWORD dwType;          //См. определения AESCT_*.
  BOOL bColumnSel;       //Колоночное выделение.
  CHARRANGE64 crRichSel; //Текущее выделение (смещение RichEdit).
} AENSELCHANGE;

typedef struct {
  AENMHDR hdr;
  AECHARRANGE crSel;     //Текущее выделение.
  AECHARINDEX ciCaret;   //Позиция индекса символа курсора.
  DWORD dwType;          //См. определения AETCT_*.
  BOOL bColumnSel;       //Колоночное выделение.
  CHARRANGE64 crRichSel; //Текущее выделение (смещение RichEdit).
} AENTEXTCHANGE;

typedef struct {
  AENMHDR hdr;
  AECHARRANGE crSel;       //Зарезервировано.
  AECHARINDEX ciCaret;     //Зарезервировано.
  DWORD dwType;            //См. определения AETCT_*.
  const wchar_t *wpText;   //Текст для вставки.
  UINT_PTR dwTextLen;      //Длина текста.
  int nNewLine;            //См. определения AELB_*.
  BOOL bColumnSel;         //Колоночное выделение.
  DWORD dwInsertFlags;     //См. определения AEINST_*.
  AECHARRANGE crAkelRange; //AEN_TEXTINSERTBEGIN - позиция вставки текста или AEN_TEXTINSERTEND - диапазон текста после вставки.
  CHARRANGE64 crRichRange; //AEN_TEXTINSERTBEGIN - позиция вставки текста или AEN_TEXTINSERTEND - диапазон текста после вставки (смещение RichEdit).
} AENTEXTINSERT;

typedef struct {
  AENMHDR hdr;
  AECHARRANGE crSel;       //Зарезервировано.
  AECHARINDEX ciCaret;     //Зарезервировано.
  DWORD dwType;            //См. определения AETCT_*.
  BOOL bColumnSel;         //Колоночное выделение.
  DWORD dwDeleteFlags;     //См. определения AEDELT_*.
  AECHARRANGE crAkelRange; //AEN_TEXTDELETEBEGIN - диапазон удаляемого текста или AEN_TEXTDELETEEND - диапазон текста после удаления.
  CHARRANGE64 crRichRange; //AEN_TEXTDELETEBEGIN - диапазон удаляемого текста или AEN_TEXTDELETEEND - диапазон текста после удаления (смещение RichEdit).
} AENTEXTDELETE;

typedef struct {
  AENMHDR hdr;
  DWORD dwType;        //См. определения AEPTT_*.
  AEPOINT *lpPoint;    //Указатель на структуру AEPOINT. NULL, если тип AEPTT_SETTEXT или AEPTT_STREAMIN.
} AENPOINT;

typedef struct {
  AENMHDR hdr;
  HDROP hDrop;         //Дескриптор списка сброшенных файлов (так же, как с WM_DROPFILES).
  AECHARINDEX ciChar;  //Индекс символа, в который будут вставлены сброшенные файлы.
} AENDROPFILES;

typedef struct {
  AENMHDR hdr;
  int nAction;         //См. определения AEDS_*.
  DWORD dwEffect;      //Эффект курсора: DROPEFFECT_COPY, DROPEFFECT_MOVE или DROPEFFECT_NONE.
  DWORD dwDropResult;  //Результат сброса. Действителен, если nAction равно AEDS_SOURCEEND или AEDS_SOURCEDONE.
} AENDROPSOURCE;

typedef struct {
  AENMHDR hdr;
  int nAction;         //См. определения AEDT_*.
  POINT pt;            //Позиция курсора в экранных координатах.
  DWORD dwEffect;      //Эффект курсора: DROPEFFECT_COPY, DROPEFFECT_MOVE или DROPEFFECT_NONE.
} AENDROPTARGET;

typedef struct {
  AENMHDR hdr;
  UINT uMsg;           //Сообщение мыши: WM_LBUTTONDBLCLK, WM_LBUTTONDOWN, WM_LBUTTONUP, WM_MOUSEMOVE, WM_RBUTTONDBLCLK, WM_RBUTTONDOWN, WM_RBUTTONUP, WM_SETCURSOR.
  WPARAM wParam;       //Первый параметр сообщения.
  LPARAM lParam;       //Второй параметр сообщения.
  AECHARRANGE crLink;  //Диапазон символов, содержащий текст URL.
  int nVisitCount;     //Количество посещений URL. Переменная должна быть увеличена, если URL открыт.
} AENLINK;

typedef struct {
  AENMHDR hdr;
  DWORD dwType; //Тип маркера столбца.
  DWORD dwPos;  //Позиция маркера столбца.
  BOOL bMouse;  //Позиция маркера столбца изменена с помощью мыши.
} AENMARKER;


//// Сообщения AkelEdit

//Уведомления об ошибках
#define AEN_ERRSPACE              (WM_USER + 1001)  //0x7E9

//Уведомления окна
#define AEN_SETFOCUS              (WM_USER + 1026)  //0x802
#define AEN_KILLFOCUS             (WM_USER + 1027)  //0x803
#define AEN_HSCROLL               (WM_USER + 1028)  //0x804
#define AEN_VSCROLL               (WM_USER + 1029)  //0x805
#define AEN_SETRECT               (WM_USER + 1030)  //0x806
#define AEN_PAINT                 (WM_USER + 1031)  //0x807

//Уведомления о тексте
#define AEN_MAXTEXT               (WM_USER + 1050)  //0x81A
#define AEN_PROGRESS              (WM_USER + 1051)  //0x81B
#define AEN_MODIFY                (WM_USER + 1052)  //0x81C
#define AEN_SELCHANGING           (WM_USER + 1053)  //0x81D
#define AEN_SELCHANGED            (WM_USER + 1054)  //0x81E
#define AEN_TEXTCHANGING          (WM_USER + 1055)  //0x81F
#define AEN_TEXTINSERTBEGIN       (WM_USER + 1056)  //0x820
#define AEN_TEXTINSERTEND         (WM_USER + 1057)  //0x821
#define AEN_TEXTDELETEBEGIN       (WM_USER + 1058)  //0x822
#define AEN_TEXTDELETEEND         (WM_USER + 1059)  //0x823
#define AEN_TEXTCHANGED           (WM_USER + 1060)  //0x824
#define AEN_POINT                 (WM_USER + 1061)  //0x825

//Уведомления мыши
#define AEN_DROPFILES             (WM_USER + 1076)  //0x834
#define AEN_DROPSOURCE            (WM_USER + 1077)  //0x835
#define AEN_DROPTARGET            (WM_USER + 1078)  //0x836
#define AEN_LINK                  (WM_USER + 1079)  //0x837
#define AEN_MARKER                (WM_USER + 1080)  //0x838

//Расширение RichEdit для Unicode
#define EM_REPLACESELA            (WM_USER + 1901)
#define EM_REPLACESELW            (WM_USER + 1902)
#define EM_GETSELTEXTA            (WM_USER + 1905)
#define EM_GETSELTEXTW            (WM_USER + 1906)
#define EM_GETLINEA               (WM_USER + 1907)
#define EM_GETLINEW               (WM_USER + 1908)

//Расширение RichEdit для x64
#define EM_GETSEL64               (WM_USER + 1951)
#define EM_EXGETSEL64             (WM_USER + 1952)
#define EM_EXSETSEL64             (WM_USER + 1953)
#define EM_FINDTEXTEX64           (WM_USER + 1954)
#define EM_FINDTEXTEX64A          (WM_USER + 1955)
#define EM_FINDTEXTEX64W          (WM_USER + 1956)
#define EM_GETTEXTRANGE64         (WM_USER + 1961)
#define EM_GETTEXTRANGE64A        (WM_USER + 1962)
#define EM_GETTEXTRANGE64W        (WM_USER + 1963)
#define EM_GETTEXTEX64            (WM_USER + 1964)

//Получение и изменение текста
#define AEM_EXSETTEXTA            (WM_USER + 1999)
#define AEM_EXSETTEXTW            (WM_USER + 2000)
#define AEM_SETTEXTA              (WM_USER + 2001)
#define AEM_SETTEXTW              (WM_USER + 2002)
#define AEM_APPENDTEXTA           (WM_USER + 2003)
#define AEM_APPENDTEXTW           (WM_USER + 2004)
#define AEM_REPLACESELA           (WM_USER + 2005)
#define AEM_REPLACESELW           (WM_USER + 2006)
#define AEM_GETTEXTRANGEA         (WM_USER + 2007)
#define AEM_GETTEXTRANGEW         (WM_USER + 2008)
#define AEM_STREAMIN              (WM_USER + 2009)
#define AEM_STREAMOUT             (WM_USER + 2010)
#define AEM_CANPASTE              (WM_USER + 2011)
#define AEM_PASTE                 (WM_USER + 2012)
#define AEM_CUT                   (WM_USER + 2013)
#define AEM_COPY                  (WM_USER + 2014)
#define AEM_CHECKCODEPAGE         (WM_USER + 2015)
#define AEM_FINDTEXTA             (WM_USER + 2016)
#define AEM_FINDTEXTW             (WM_USER + 2017)
#define AEM_ISMATCHA              (WM_USER + 2018)
#define AEM_ISMATCHW              (WM_USER + 2019)
#define AEM_KEYDOWN               (WM_USER + 2020)
#define AEM_INSERTCHAR            (WM_USER + 2021)
#define AEM_CHARAT                (WM_USER + 2022)
#define AEM_INPUTLANGUAGE         (WM_USER + 2023)
#define AEM_DRAGDROP              (WM_USER + 2024)

//Отмена и Повтор
#define AEM_CANUNDO               (WM_USER + 2051)
#define AEM_CANREDO               (WM_USER + 2052)
#define AEM_UNDO                  (WM_USER + 2053)
#define AEM_REDO                  (WM_USER + 2054)
#define AEM_EMPTYUNDOBUFFER       (WM_USER + 2055)
#define AEM_STOPGROUPTYPING       (WM_USER + 2056)
#define AEM_BEGINUNDOACTION       (WM_USER + 2057)
#define AEM_ENDUNDOACTION         (WM_USER + 2058)
#define AEM_LOCKCOLLECTUNDO       (WM_USER + 2059)
#define AEM_GETUNDOLIMIT          (WM_USER + 2060)
#define AEM_SETUNDOLIMIT          (WM_USER + 2061)
#define AEM_GETMODIFY             (WM_USER + 2062)
#define AEM_SETMODIFY             (WM_USER + 2063)
#define AEM_UNDOBUFFERSIZE        (WM_USER + 2064)
#define AEM_ISRANGEMODIFIED       (WM_USER + 2065)
#define AEM_DETACHUNDO            (WM_USER + 2066)
#define AEM_ATTACHUNDO            (WM_USER + 2067)
#define AEM_GETUNDOPOS            (WM_USER + 2068)

//Текстовые координаты
#define AEM_EXGETSEL              (WM_USER + 2099)
#define AEM_EXSETSEL              (WM_USER + 2100)
#define AEM_GETSEL                (WM_USER + 2101)
#define AEM_SETSEL                (WM_USER + 2102)
#define AEM_GETCOLUMNSEL          (WM_USER + 2103)
#define AEM_UPDATESEL             (WM_USER + 2104)
#define AEM_GETLINENUMBER         (WM_USER + 2105)
#define AEM_GETINDEX              (WM_USER + 2106)
#define AEM_GETLINEINDEX          (WM_USER + 2107)
#define AEM_INDEXUPDATE           (WM_USER + 2108)
#define AEM_INDEXCOMPARE          (WM_USER + 2109)
#define AEM_INDEXSUBTRACT         (WM_USER + 2110)
#define AEM_INDEXOFFSET           (WM_USER + 2111)
#define AEM_INDEXTORICHOFFSET     (WM_USER + 2112)
#define AEM_RICHOFFSETTOINDEX     (WM_USER + 2113)
#define AEM_GETRICHOFFSET         (WM_USER + 2114)
#define AEM_GETWRAPLINE           (WM_USER + 2118)
#define AEM_GETUNWRAPLINE         (WM_USER + 2119)
#define AEM_GETNEXTBREAK          (WM_USER + 2120)
#define AEM_GETPREVBREAK          (WM_USER + 2121)
#define AEM_ISDELIMITER           (WM_USER + 2122)
#define AEM_INDEXTOCOLUMN         (WM_USER + 2123)
#define AEM_COLUMNTOINDEX         (WM_USER + 2124)
#define AEM_INDEXINURL            (WM_USER + 2125)
#define AEM_URLVISIT              (WM_USER + 2126)
#define AEM_ADDPOINT              (WM_USER + 2141)
#define AEM_DELPOINT              (WM_USER + 2142)
#define AEM_GETPOINTSTACK         (WM_USER + 2143)

//Экранные координаты
#define AEM_CHARFROMGLOBALPOS     (WM_USER + 2149)
#define AEM_GLOBALPOSFROMCHAR     (WM_USER + 2150)
#define AEM_CHARFROMPOS           (WM_USER + 2151)
#define AEM_POSFROMCHAR           (WM_USER + 2152)
#define AEM_GETRECT               (WM_USER + 2153)
#define AEM_SETRECT               (WM_USER + 2154)
#define AEM_GETSCROLLPOS          (WM_USER + 2155)
#define AEM_SETSCROLLPOS          (WM_USER + 2156)
#define AEM_SCROLL                (WM_USER + 2157)
#define AEM_LINESCROLL            (WM_USER + 2158)
#define AEM_SCROLLTOPOINT         (WM_USER + 2159)
#define AEM_LOCKSCROLL            (WM_USER + 2161)
#define AEM_GETCHARSIZE           (WM_USER + 2164)
#define AEM_GETSTRWIDTH           (WM_USER + 2165)
#define AEM_GETCARETPOS           (WM_USER + 2166)
#define AEM_GETCARETHORZINDENT    (WM_USER + 2167)
#define AEM_SETCARETHORZINDENT    (WM_USER + 2168)
#define AEM_CONVERTPOINT          (WM_USER + 2169)
#define AEM_POINTONMARGIN         (WM_USER + 2170)
#define AEM_POINTONSELECTION      (WM_USER + 2171)
#define AEM_POINTONURL            (WM_USER + 2172)
#define AEM_LINEFROMVPOS          (WM_USER + 2173)
#define AEM_VPOSFROMLINE          (WM_USER + 2174)
#define AEM_GETMOUSESTATE         (WM_USER + 2175)

//Опции
#define AEM_CONTROLCLASS          (WM_USER + 2199)
#define AEM_CONTROLVERSION        (WM_USER + 2200)
#define AEM_GETEVENTMASK          (WM_USER + 2201)
#define AEM_SETEVENTMASK          (WM_USER + 2202)
#define AEM_GETOPTIONS            (WM_USER + 2203)
#define AEM_SETOPTIONS            (WM_USER + 2204)
#define AEM_GETNEWLINE            (WM_USER + 2205)
#define AEM_SETNEWLINE            (WM_USER + 2206)
#define AEM_GETCOLORS             (WM_USER + 2207)
#define AEM_SETCOLORS             (WM_USER + 2208)
#define AEM_EXGETOPTIONS          (WM_USER + 2209)
#define AEM_EXSETOPTIONS          (WM_USER + 2210)
#define AEM_GETCARETWIDTH         (WM_USER + 2213)
#define AEM_SETCARETWIDTH         (WM_USER + 2214)
#define AEM_GETTABSTOP            (WM_USER + 2215)
#define AEM_SETTABSTOP            (WM_USER + 2216)
#define AEM_GETWORDWRAP           (WM_USER + 2217)
#define AEM_SETWORDWRAP           (WM_USER + 2218)
#define AEM_GETWORDDELIMITERS     (WM_USER + 2219)
#define AEM_SETWORDDELIMITERS     (WM_USER + 2220)
#define AEM_GETWRAPDELIMITERS     (WM_USER + 2221)
#define AEM_SETWRAPDELIMITERS     (WM_USER + 2222)
#define AEM_GETURLLEFTDELIMITERS  (WM_USER + 2223)
#define AEM_SETURLLEFTDELIMITERS  (WM_USER + 2224)
#define AEM_GETURLRIGHTDELIMITERS (WM_USER + 2225)
#define AEM_SETURLRIGHTDELIMITERS (WM_USER + 2226)
#define AEM_GETURLPREFIXES        (WM_USER + 2227)
#define AEM_SETURLPREFIXES        (WM_USER + 2228)
#define AEM_GETURLMAXLENGTH       (WM_USER + 2229)
#define AEM_SETURLMAXLENGTH       (WM_USER + 2230)
#define AEM_GETWORDBREAK          (WM_USER + 2231)
#define AEM_SETWORDBREAK          (WM_USER + 2232)
#define AEM_GETMARKER             (WM_USER + 2233)
#define AEM_SETMARKER             (WM_USER + 2234)
#define AEM_GETLINEGAP            (WM_USER + 2235)
#define AEM_SETLINEGAP            (WM_USER + 2236)
#define AEM_GETTEXTLIMIT          (WM_USER + 2237)
#define AEM_SETTEXTLIMIT          (WM_USER + 2238)
#define AEM_GETFONT               (WM_USER + 2239)
#define AEM_GETALTLINE            (WM_USER + 2240)
#define AEM_SETALTLINE            (WM_USER + 2241)
#define AEM_GETCHARCOLORS         (WM_USER + 2242)
#define AEM_SCROLLCARETOPTIONS    (WM_USER + 2243)
#define AEM_FIXEDCHARWIDTH        (WM_USER + 2244)
#define AEM_GETSCROLLSPEED        (WM_USER + 2245)
#define AEM_SETSCROLLSPEED        (WM_USER + 2246)

//Рисование
#define AEM_SHOWSCROLLBAR         (WM_USER + 2351)
#define AEM_UPDATESCROLLBAR       (WM_USER + 2352)
#define AEM_UPDATECARET           (WM_USER + 2353)
#define AEM_UPDATESIZE            (WM_USER + 2354)
#define AEM_LOCKUPDATE            (WM_USER + 2355)
#define AEM_LOCKERASERECT         (WM_USER + 2356)
#define AEM_GETERASERECT          (WM_USER + 2357)
#define AEM_SETERASERECT          (WM_USER + 2358)
#define AEM_HIDESELECTION         (WM_USER + 2361)
#define AEM_REDRAWLINERANGE       (WM_USER + 2362)
#define AEM_GETBACKGROUNDIMAGE    (WM_USER + 2366)
#define AEM_SETBACKGROUNDIMAGE    (WM_USER + 2367)
#define AEM_PAINTCALLBACK         (WM_USER + 2368)

//Сворачивание (Фолды)
#define AEM_GETFOLDSTACK          (WM_USER + 2381)
#define AEM_GETFOLDCOUNT          (WM_USER + 2382)
#define AEM_ADDFOLD               (WM_USER + 2383)
#define AEM_DELETEFOLD            (WM_USER + 2384)
#define AEM_ISFOLDVALID           (WM_USER + 2385)
#define AEM_FINDFOLD              (WM_USER + 2386)
#define AEM_NEXTFOLD              (WM_USER + 2387)
#define AEM_PREVFOLD              (WM_USER + 2388)
#define AEM_ISLINECOLLAPSED       (WM_USER + 2389)
#define AEM_COLLAPSELINE          (WM_USER + 2390)
#define AEM_COLLAPSEFOLD          (WM_USER + 2391)
#define AEM_UPDATEFOLD            (WM_USER + 2392)
#define AEM_GETFOLDHIDEOFFSET     (WM_USER + 2393)
#define AEM_SETFOLDHIDEOFFSET     (WM_USER + 2394)

//Документ
#define AEM_CREATEDOCUMENT        (WM_USER + 2401)
#define AEM_DELETEDOCUMENT        (WM_USER + 2402)
#define AEM_GETDOCUMENT           (WM_USER + 2403)
#define AEM_SETDOCUMENT           (WM_USER + 2404)
#define AEM_GETDOCUMENTPROC       (WM_USER + 2405)
#define AEM_GETDOCUMENTWINDOW     (WM_USER + 2406)
#define AEM_SENDMESSAGE           (WM_USER + 2407)

//Клоны
#define AEM_ADDCLONE              (WM_USER + 2421)
#define AEM_DELCLONE              (WM_USER + 2422)
#define AEM_GETMASTER             (WM_USER + 2423)
#define AEM_GETCLONE              (WM_USER + 2424)

//Печать
#define AEM_STARTPRINTDOC         (WM_USER + 2451)
#define AEM_PRINTPAGE             (WM_USER + 2452)
#define AEM_ENDPRINTDOC           (WM_USER + 2453)

//Подсветка
#define AEM_HLCREATETHEMEA        (WM_USER + 2501)
#define AEM_HLCREATETHEMEW        (WM_USER + 2502)
#define AEM_HLFINDTHEME           (WM_USER + 2504)
#define AEM_HLGETTHEMENAMEA       (WM_USER + 2505)
#define AEM_HLGETTHEMENAMEW       (WM_USER + 2506)
#define AEM_HLGETTHEMESTACK       (WM_USER + 2507)
#define AEM_HLTHEMEEXISTS         (WM_USER + 2508)
#define AEM_HLSETTHEME            (WM_USER + 2509)
#define AEM_HLDELETETHEME         (WM_USER + 2510)
#define AEM_HLDELETETHEMEALL      (WM_USER + 2511)
#define AEM_HLADDDELIMITERA       (WM_USER + 2521)
#define AEM_HLADDDELIMITERW       (WM_USER + 2522)
#define AEM_HLDELETEDELIMITER     (WM_USER + 2523)
#define AEM_HLADDWORDA            (WM_USER + 2531)
#define AEM_HLADDWORDW            (WM_USER + 2532)
#define AEM_HLDELETEWORD          (WM_USER + 2533)
#define AEM_HLADDQUOTEA           (WM_USER + 2541)
#define AEM_HLADDQUOTEW           (WM_USER + 2542)
#define AEM_HLDELETEQUOTE         (WM_USER + 2543)
#define AEM_HLADDMARKTEXTA        (WM_USER + 2551)
#define AEM_HLADDMARKTEXTW        (WM_USER + 2552)
#define AEM_HLDELETEMARKTEXT      (WM_USER + 2553)
#define AEM_HLADDMARKRANGE        (WM_USER + 2561)
#define AEM_HLDELETEMARKRANGE     (WM_USER + 2562)
#define AEM_HLGETHIGHLIGHT        (WM_USER + 2571)
#define AEM_HLGETOPTIONS          (WM_USER + 2581)
#define AEM_HLSETOPTIONS          (WM_USER + 2582)


//// Сообщения RichEdit

/*
AkelEdit может эмулировать RichEdit 3.0 и поддерживает следующие сообщения:

EN_CHANGE
EN_DRAGDROPDONE
EN_DROPFILES
EN_ERRSPACE
EN_HSCROLL
EN_KILLFOCUS
EN_LINK
EN_MAXTEXT
EN_MSGFILTER
EN_SELCHANGE
EN_SETFOCUS
EN_VSCROLL

EM_AUTOURLDETECT
EM_CANPASTE
EM_CANREDO
EM_CANUNDO
EM_CHARFROMPOS
EM_EMPTYUNDOBUFFER
EM_EXGETSEL
EM_EXLIMITTEXT
EM_EXLINEFROMCHAR
EM_EXSETSEL
EM_FINDTEXT
EM_FINDTEXTEX
EM_FINDTEXTEXW
EM_FINDTEXTW
EM_FINDWORDBREAK
EM_GETAUTOURLDETECT
EM_GETEVENTMASK
EM_GETFIRSTVISIBLELINE
EM_GETLIMITTEXT
EM_GETLINE
EM_GETLINECOUNT
EM_GETMARGINS
EM_GETMODIFY
EM_GETOPTIONS
EM_GETRECT
EM_GETSCROLLPOS
EM_GETSEL
EM_GETSELTEXT
EM_GETTEXTEX
EM_GETTEXTLENGTHEX
EM_GETTEXTRANGE
EM_GETTHUMB
EM_HIDESELECTION
EM_LIMITTEXT
EM_LINEFROMCHAR
EM_LINEINDEX
EM_LINELENGTH
EM_LINESCROLL
EM_POSFROMCHAR
EM_REDO
EM_REPLACESEL
EM_SCROLL
EM_SCROLLCARET
EM_SELECTIONTYPE
EM_SETBKGNDCOLOR
EM_SETEVENTMASK
EM_SETLIMITTEXT
EM_SETMARGINS
EM_SETMODIFY
EM_SETOPTIONS
EM_SETREADONLY
EM_SETRECT
EM_SETRECTNP
EM_SETSCROLLPOS
EM_SETSEL
EM_SETTEXTEX
EM_SETUNDOLIMIT
EM_SHOWSCROLLBAR
EM_STOPGROUPTYPING
EM_STREAMIN
EM_STREAMOUT
EM_UNDO

Дополнительные сообщения для поддержки Unicode:
EM_REPLACESELA
EM_REPLACESELW
EM_GETTEXTRANGEA
EM_GETTEXTRANGEW
EM_GETSELTEXTA
EM_GETSELTEXTW
EM_GETLINEA
EM_GETLINEW

Дополнительные сообщения для поддержки x64:
EM_GETSEL64
EM_EXGETSEL64
EM_EXSETSEL64
EM_FINDTEXTEX64
EM_FINDTEXTEX64A
EM_FINDTEXTEX64W
EM_GETTEXTRANGE64
EM_GETTEXTRANGE64A
EM_GETTEXTRANGE64W
EM_GETTEXTEX64
*/


//// Описание сообщений AkelEdit

/*
AEN_ERRSPACE
____________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна, когда элемент редактирования не может выделить достаточно памяти.

(int)wParam           == указывает идентификатор элемента управления.
(AENERRSPACE *)lParam == указатель на структуру AENERRSPACE.

Возвращаемое значение
 Ноль.


AEN_SETFOCUS
____________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна, когда элемент редактирования получает фокус клавиатуры.

(int)wParam     == указывает идентификатор элемента управления.
(NMHDR *)lParam == указатель на структуру NMHDR.

Возвращаемое значение
 Ноль.


AEN_KILLFOCUS
_____________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна, когда элемент редактирования теряет фокус клавиатуры.

(int)wParam     == указывает идентификатор элемента управления.
(NMHDR *)lParam == указатель на структуру NMHDR.

Возвращаемое значение
 Ноль.


AEN_HSCROLL
___________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна перед горизонтальной прокруткой окна элемента редактирования.

(int)wParam         == указывает идентификатор элемента управления.
(AENSCROLL *)lParam == указатель на структуру AENSCROLL.

Возвращаемое значение
 Если ноль, элемент управления разрешает операцию прокрутки.
 Если ненулевое значение, элемент управления подавляет операцию прокрутки.

Примечания
 Чтобы получать уведомления AEN_HSCROLL, укажите AENM_SCROLL в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEN_VSCROLL
___________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна перед вертикальной прокруткой окна элемента редактирования.

(int)wParam         == указывает идентификатор элемента управления.
(AENSCROLL *)lParam == указатель на структуру AENSCROLL.

Возвращаемое значение
 Если ноль, элемент управления разрешает операцию прокрутки.
 Если ненулевое значение, элемент управления подавляет операцию прокрутки.

Примечания
 Чтобы получать уведомления AEN_VSCROLL, укажите AENM_SCROLL в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEN_SETRECT
___________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна после изменения форматирующего прямоугольника элемента редактирования.

(int)wParam          == указывает идентификатор элемента управления.
(AENSETRECT *)lParam == указатель на структуру AENSETRECT.

Возвращаемое значение
 Ноль.

Примечания
 Уведомление AEN_SETRECT не отправляется во время обработки сообщения WM_SIZE.


AEN_PAINT
_________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна перед рисованием строки.

(int)wParam        == указывает идентификатор элемента управления.
(AENPAINT *)lParam == указатель на структуру AENPAINT.

Возвращаемое значение
 Ноль.

Примечания
 Чтобы получать уведомления AEN_PAINT, укажите AENM_PAINT в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEN_MAXTEXT
___________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна, когда достигнут лимит текста элемента редактирования.

(int)wParam     == указывает идентификатор элемента управления.
(NMHDR *)lParam == указатель на структуру NMHDR.

Возвращаемое значение
 Ноль.


AEN_PROGRESS
____________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна, когда обработано необходимое количество строк.

(int)wParam           == указывает идентификатор элемента управления.
(AENPROGRESS *)lParam == указатель на структуру AENPROGRESS.

Возвращаемое значение
 Если ноль, элемент управления продолжает операцию.
 Если ненулевое значение, элемент управления останавливает операцию.

Примечания
 Во время операции, вызывающей AEN_PROGRESS, содержимое элемента редактирования нестабильно.
 Чтобы получать уведомления AEN_PROGRESS, укажите AENM_PROGRESS в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEN_MODIFY
__________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна после изменения состояния модификации документа.

(int)wParam         == указывает идентификатор элемента управления.
(AENMODIFY *)lParam == указатель на структуру AENMODIFY.

Возвращаемое значение
 Ноль.

Примечания
 Чтобы получать уведомления AEN_MODIFY, укажите AENM_MODIFY в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEN_SELCHANGING
_______________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна перед изменением текущего выделения.

(int)wParam            == указывает идентификатор элемента управления.
(AENSELCHANGE *)lParam == указатель на структуру AENSELCHANGE.

Возвращаемое значение
 Ноль.

Примечания
 Чтобы получать уведомления AEN_SELCHANGING, укажите AENM_SELCHANGE в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEN_SELCHANGED
______________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна после изменения текущего выделения.

(int)wParam            == указывает идентификатор элемента управления.
(AENSELCHANGE *)lParam == указатель на структуру AENSELCHANGE.

Возвращаемое значение
 Ноль.

Примечания
 Чтобы получать уведомления AEN_SELCHANGED, укажите AENM_SELCHANGE в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEN_TEXTCHANGING
________________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна перед изменением текста документа.

(int)wParam             == указывает идентификатор элемента управления.
(AENTEXTCHANGE *)lParam == указатель на структуру AENTEXTCHANGE.

Возвращаемое значение
 Ноль.

Примечания
 Чтобы получать уведомления AEN_TEXTCHANGING, укажите AENM_TEXTCHANGE в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEN_TEXTINSERTBEGIN
___________________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна перед вставкой текста в документ.

(int)wParam             == указывает идентификатор элемента управления.
(AENTEXTINSERT *)lParam == указатель на структуру AENTEXTINSERT.

Возвращаемое значение
 Ноль.

Примечания
 Чтобы получать уведомления AEN_TEXTINSERTBEGIN, укажите AENM_TEXTCHANGE в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEN_TEXTINSERTEND
_________________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна после вставки текста в документ.

(int)wParam             == указывает идентификатор элемента управления.
(AENTEXTINSERT *)lParam == указатель на структуру AENTEXTINSERT.

Возвращаемое значение
 Ноль.

Примечания
 Чтобы получать уведомления AEN_TEXTINSERTEND, укажите AENM_TEXTCHANGE в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEN_TEXTDELETEBEGIN
___________________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна перед удалением текста из документа.

(int)wParam             == указывает идентификатор элемента управления.
(AENTEXTDELETE *)lParam == указатель на структуру AENTEXTDELETE.

Возвращаемое значение
 Ноль.

Примечания
 Чтобы получать уведомления AEN_TEXTDELETEBEGIN, укажите AENM_TEXTCHANGE в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEN_TEXTDELETEEND
_________________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна после удаления текста из документа.

(int)wParam             == указывает идентификатор элемента управления.
(AENTEXTDELETE *)lParam == указатель на структуру AENTEXTDELETE.

Возвращаемое значение
 Ноль.

Примечания
 Чтобы получать уведомления AEN_TEXTDELETEEND, укажите AENM_TEXTCHANGE в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEN_TEXTCHANGED
_______________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна после изменения текста документа.

(int)wParam             == указывает идентификатор элемента управления.
(AENTEXTCHANGE *)lParam == указатель на структуру AENTEXTCHANGE.

Возвращаемое значение
 Ноль.

Примечания
 Чтобы получать уведомления AEN_TEXTCHANGED, укажите AENM_TEXTCHANGE в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEN_POINT
_________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна после изменения текстовой точки.

(int)wParam        == указывает идентификатор элемента управления.
(AENPOINT *)lParam == указатель на структуру AENPOINT.

Возвращаемое значение
 Ноль.

Примечания
 Чтобы получать уведомления AEN_POINT, укажите AENM_POINT в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEN_DROPFILES
_____________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна, когда пользователь пытается сбросить файлы в элемент управления (когда он получает сообщение WM_DROPFILES).

(int)wParam            == указывает идентификатор элемента управления.
(AENDROPFILES *)lParam == указатель на структуру AENDROPFILES.

Возвращаемое значение
 Если ноль, элемент управления игнорирует операцию сброса.
 Если ненулевое значение, элемент управления разрешает операцию сброса.

Примечания
 Чтобы получать уведомления AEN_DROPFILES, укажите AENM_DROPFILES в маске, отправленной с сообщением AEM_SETEVENTMASK.
 Чтобы получать сообщения WM_DROPFILES, родительское окно должно зарегистрировать элемент управления как цель сброса с помощью функции DragAcceptFiles. Элемент управления не регистрирует себя сам.


AEN_DROPSOURCE
______________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна, когда пользователь перетаскивает выделение.

(int)wParam             == указывает идентификатор элемента управления.
(AENDROPSOURCE *)lParam == указатель на структуру AENDROPSOURCE.

Возвращаемое значение
 Если ноль, элемент управления игнорирует операцию сброса.
 Если ненулевое значение, элемент управления разрешает операцию сброса.

Примечания
 Чтобы получать уведомления AEN_DROPSOURCE, укажите AEN_DRAGDROP в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEN_DROPTARGET
______________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна, когда пользователь пытается сбросить данные в элемент управления.

(int)wParam             == указывает идентификатор элемента управления.
(AENDROPTARGET *)lParam == указатель на структуру AENDROPTARGET.

Возвращаемое значение
 Если ноль, элемент управления игнорирует операцию сброса.
 Если ненулевое значение, элемент управления разрешает операцию сброса.

Примечания
 Чтобы получать уведомления AEN_DROPTARGET, укажите AEN_DRAGDROP в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEN_LINK
________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна, когда элемент редактирования получает сообщения мыши, в то время как указатель мыши находится над URL.

(int)wParam       == указывает идентификатор элемента управления.
(AENLINK *)lParam == указатель на структуру AENLINK.

Возвращаемое значение
 Если ноль, элемент управления продолжает свою обычную обработку сообщения мыши.
 Если ненулевое значение, элемент управления не обрабатывает сообщение мыши.

Примечания
 Чтобы получать уведомления AEN_LINK, укажите AENM_LINK в маске, отправленной с сообщением AEM_SETEVENTMASK, и включите обнаружение URL с помощью флага AECOE_DETECTURL.


AEN_MARKER
__________

Уведомление отправляется в виде сообщения WM_NOTIFY.
Отправляется в процедуру родительского окна после изменения позиции или типа маркера столбца.

(int)wParam         == указывает идентификатор элемента управления.
(AENMARKER *)lParam == указатель на структуру AENMARKER.

Возвращаемое значение
 Ноль.

Примечания
 Чтобы получать уведомления AEN_MARKER, укажите AENM_MARKER в маске, отправленной с сообщением AEM_SETEVENTMASK.


AEM_EXSETTEXTA
______________

Устанавливает текст элемента редактирования в кодировке ANSI.

wParam               == не используется.
(AESETTEXTA *)lParam == указатель на структуру AESETTEXTA.

Возвращаемое значение
 Длина текста.

Примечания
 Сообщение игнорирует флаг AECO_READONLY.

Пример:
 AESETTEXTA st;

 st.pText="SomeText";
 st.dwTextLen=(UINT_PTR)-1;
 st.nNewLine=AELB_ASINPUT;
 st.nCodePage=CP_ACP;
 SendMessage(hWndEdit, AEM_EXSETTEXTA, 0, (LPARAM)&st);


AEM_EXSETTEXTW
______________

Устанавливает текст элемента редактирования в кодировке Unicode.

wParam               == не используется.
(AESETTEXTW *)lParam == указатель на структуру AESETTEXTW.

Возвращаемое значение
 Длина текста.

Примечания
 Сообщение игнорирует флаг AECO_READONLY.

Пример:
 AESETTEXTW st;

 st.pText=L"SomeText";
 st.dwTextLen=(UINT_PTR)-1;
 st.nNewLine=AELB_ASINPUT;
 SendMessage(hWndEdit, AEM_EXSETTEXTW, 0, (LPARAM)&st);


AEM_SETTEXTA
____________

Устанавливает текст элемента редактирования в кодировке ANSI.

(UINT_PTR)wParam == длина текста. Если это значение равно -1, строка считается нуль-терминированной, и длина вычисляется автоматически.
(char *)lParam   == указатель на текст.

Возвращаемое значение
 Длина текста.

Примечания
 Сообщение игнорирует флаг AECO_READONLY.

Пример:
 SendMessage(hWndEdit, AEM_SETTEXTA, (WPARAM)-1, (LPARAM)"SomeText");


AEM_SETTEXTW
____________

Устанавливает текст элемента редактирования в кодировке Unicode.

(UINT_PTR)wParam  == длина текста. Если это значение равно -1, строка считается нуль-терминированной, и длина вычисляется автоматически.
(wchar_t *)lParam == указатель на текст.

Возвращаемое значение
 Длина текста.

Примечания
 Сообщение игнорирует флаг AECO_READONLY.

Пример:
 SendMessage(hWndEdit, AEM_SETTEXTW, (WPARAM)-1, (LPARAM)L"SomeText");


AEM_APPENDTEXTA
_______________

Добавляет текст в кодировке ANSI в конец элемента редактирования.

wParam                  == не используется.
(AEAPPENDTEXTA *)lParam == указатель на структуру AEAPPENDTEXTA.

Возвращаемое значение
 Ноль.

Примечания
 Сообщение игнорирует флаг AECO_READONLY.

Пример:
 AEAPPENDTEXTA at;

 at.pText="SomeText";
 at.dwTextLen=(UINT_PTR)-1;
 at.nNewLine=AELB_ASINPUT;
 at.nCodePage=CP_ACP;
 SendMessage(hWndEdit, AEM_APPENDTEXTA, 0, (LPARAM)&at);


AEM_APPENDTEXTW
_______________

Добавляет текст в кодировке Unicode в конец элемента редактирования.

wParam                  == не используется.
(AEAPPENDTEXTW *)lParam == указатель на структуру AEAPPENDTEXTW.

Возвращаемое значение
 Ноль.

Примечания
 Сообщение игнорирует флаг AECO_READONLY.

Пример:
 AEAPPENDTEXTW at;

 at.pText=L"SomeText";
 at.dwTextLen=(UINT_PTR)-1;
 at.nNewLine=AELB_ASINPUT;
 SendMessage(hWndEdit, AEM_APPENDTEXTW, 0, (LPARAM)&at);


AEM_REPLACESELA
_______________

Заменяет выделение текстом в кодировке ANSI.

wParam                  == не используется.
(AEREPLACESELA *)lParam == указатель на структуру AEREPLACESELA.

Возвращаемое значение
 Ноль.

Примечания
 Сообщение игнорирует флаг AECO_READONLY.

Пример:
 AEREPLACESELA rs;

 rs.pText="SomeText";
 rs.dwTextLen=(UINT_PTR)-1;
 rs.nNewLine=AELB_ASINPUT;
 rs.dwFlags=AEREPT_COLUMNASIS;
 rs.ciInsertStart=NULL;
 rs.ciInsertEnd=NULL;
 rs.nCodePage=CP_ACP;
 SendMessage(hWndEdit, AEM_REPLACESELA, 0, (LPARAM)&rs);


AEM_REPLACESELW
_______________

Заменяет выделение текстом в кодировке Unicode.

wParam                  == не используется.
(AEREPLACESELW *)lParam == указатель на структуру AEREPLACESELW.

Возвращаемое значение
 Ноль.

Примечания
 Сообщение игнорирует флаг AECO_READONLY.

Пример:
 AEREPLACESELW rs;

 rs.pText=L"SomeText";
 rs.dwTextLen=(UINT_PTR)-1;
 rs.nNewLine=AELB_ASINPUT;
 rs.dwFlags=AEREPT_COLUMNASIS;
 rs.ciInsertStart=NULL;
 rs.ciInsertEnd=NULL;
 SendMessage(hWndEdit, AEM_REPLACESELW, 0, (LPARAM)&rs);


AEM_GETTEXTRANGEA
_________________

Получает указанный диапазон символов из элемента редактирования в кодировке ANSI.

wParam                 == не используется.
(AETEXTRANGEA *)lParam == указатель на структуру AETEXTRANGEA.

Возвращаемое значение
 Количество скопированных символов, не включая завершающий NULL-символ.

Пример:
 AETEXTRANGEA tr;

 SendMessage(hWndEdit, AEM_GETSEL, (WPARAM)NULL, (LPARAM)&tr);
 tr.pBuffer=NULL;
 tr.nNewLine=AELB_ASOUTPUT;
 tr.nCodePage=CP_ACP;
 tr.lpDefaultChar=NULL;
 tr.lpUsedDefChar=NULL;
 tr.bFillSpaces=FALSE;

 if (tr.dwBufferMax=SendMessage(hWndEdit, AEM_GETTEXTRANGEA, 0, (LPARAM)&tr))
 {
   if (tr.pBuffer=(char *)GlobalAlloc(GPTR, tr.dwBufferMax))
   {
     SendMessage(hWndEdit, AEM_GETTEXTRANGEA, 0, (LPARAM)&tr);
     MessageBoxA(NULL, tr.pBuffer, NULL, 0);

     GlobalFree((HGLOBAL)tr.pBuffer);
   }
 }


AEM_GETTEXTRANGEW
_________________

Получает указанный диапазон символов из элемента редактирования в кодировке Unicode.

wParam                 == не используется.
(AETEXTRANGEW *)lParam == указатель на структуру AETEXTRANGEW.

Возвращаемое значение
 Количество скопированных символов, не включая завершающий NULL-символ.

Пример:
 AETEXTRANGEW tr;

 SendMessage(hWndEdit, AEM_GETSEL, (WPARAM)NULL, (LPARAM)&tr);
 tr.pBuffer=NULL;
 tr.nNewLine=AELB_ASOUTPUT;
 tr.bFillSpaces=FALSE;

 if (tr.dwBufferMax=SendMessage(hWndEdit, AEM_GETTEXTRANGEW, 0, (LPARAM)&tr))
 {
   if (tr.pBuffer=(wchar_t *)GlobalAlloc(GPTR, tr.dwBufferMax * sizeof(wchar_t)))
   {
     SendMessage(hWndEdit, AEM_GETTEXTRANGEW, 0, (LPARAM)&tr);
     MessageBoxW(NULL, tr.pBuffer, NULL, 0);

     GlobalFree((HGLOBAL)tr.pBuffer);
   }
 }


AEM_STREAMIN
____________

Заменяет содержимое элемента редактирования потоком данных, предоставленных определенной приложением функцией обратного вызова.

(DWORD)wParam        == см. определения AESF_*.
(AESTREAMIN *)lParam == указатель на структуру AESTREAMIN.

Возвращаемое значение
 Количество прочитанных байтов.

Примечания
 Сообщение игнорирует флаги AECO_READONLY и !AECO_MULTILINE.

Пример:
 typedef struct {
   wchar_t *wpData;
   UINT_PTR dwDataLen;
   UINT_PTR dwCount;
 } STREAMINDATA;

 AESTREAMIN aesi;
 STREAMINDATA sid;

 sid.wpData=L"SomeText";
 sid.dwDataLen=lstrlenW(sid.wpData);
 sid.dwCount=0;

 aesi.dwCookie=(UINT_PTR)&sid;
 aesi.lpCallback=InputStreamCallback;
 aesi.nNewLine=AELB_ASINPUT;
 aesi.dwTextLen=sid.dwDataLen;
 SendMessage(hWndEdit, AEM_STREAMIN, AESF_SELECTION, (LPARAM)&aesi);

 DWORD CALLBACK InputStreamCallback(UINT_PTR dwCookie, wchar_t *wszBuf, DWORD dwBufBytesSize, DWORD *dwBufBytesDone)
 {
   STREAMINDATA *lpData=(STREAMINDATA *)dwCookie;
   wchar_t *wpSrc=lpData->wpData;
   wchar_t *wpDest=wszBuf;
   DWORD dwDestLen=dwBufBytesSize / sizeof(wchar_t);
   DWORD i;

   for (i=0; i < dwDestLen; ++i)
   {
     if (lpData->dwCount >= lpData->dwDataLen)
       break;
     wpDest[i]=wpSrc[lpData->dwCount++];
   }
   *dwBufBytesDone=i * sizeof(wchar_t);

   return 0;
 }


AEM_STREAMOUT
_____________

Заставляет элемент редактирования передавать свое содержимое определенной приложением функции обратного вызова.
Затем функция обратного вызова может записать поток данных в файл или любое другое место по своему выбору.

(DWORD)wParam         == см. определения AESF_*.
(AESTREAMOUT *)lParam == указатель на структуру AESTREAMOUT.

Возвращаемое значение
 Количество байтов, записанных в поток данных.

Пример:
 typedef struct {
   HANDLE hFile;
 } STREAMOUTDATA;

 AESTREAMOUT aeso;
 STREAMOUTDATA sod;

 sod.hFile=CreateFileA("C:\\Test.tmp", GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

 if (sod.hFile != INVALID_HANDLE_VALUE)
 {
   aeso.dwCookie=(UINT_PTR)&sod;
   aeso.lpCallback=OutputStreamCallback;
   aeso.nNewLine=AELB_ASOUTPUT;
   aeso.bColumnSel=FALSE;
   SendMessage(hWndEdit, AEM_STREAMOUT, 0, (LPARAM)&aeso);

   CloseHandle(sod.hFile);
 }

 DWORD CALLBACK OutputStreamCallback(UINT_PTR dwCookie, wchar_t *wszBuf, DWORD dwBufBytesSize, DWORD *dwBufBytesDone)
 {
   STREAMOUTDATA *lpData=(STREAMOUTDATA *)dwCookie;
   unsigned char *pDataToWrite=(unsigned char *)wszBuf;
   DWORD dwBytesToWrite=dwBufBytesSize;

   return !WriteFile(lpData->hFile, pDataToWrite, dwBytesToWrite, dwBufBytesDone, NULL);
 }


AEM_CANPASTE
____________

Определяет, может ли элемент редактирования вставить текст из буфера обмена.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 TRUE   успех.
 FALSE  неудача.

Пример:
 SendMessage(hWndEdit, AEM_CANPASTE, 0, 0);


AEM_PASTE
_________

Вставляет текст из буфера обмена.

(int)wParam   == см. определения AELB_*.
(DWORD)lParam == см. определения AEPFC_*.

Возвращаемое значение
 Количество вставленных символов, -1 в случае ошибки.

Пример:
 SendMessage(hWndEdit, AEM_PASTE, 0, 0);


AEM_CUT
_______

Удаляет текущее выделение, если оно есть, и копирует удаленный текст в буфер обмена.

(int)wParam   == см. определения AELB_*.
(DWORD)lParam == см. определения AECFC_*.

Возвращаемое значение
 TRUE   буфер обмена изменен.
 FALSE  буфер обмена не изменен.

Пример:
 SendMessage(hWndEdit, AEM_CUT, 0, 0);


AEM_COPY
________

Копирует текущее выделение в буфер обмена.

(int)wParam   == см. определения AELB_*.
(DWORD)lParam == см. определения AECFC_*.

Возвращаемое значение
 TRUE   буфер обмена изменен.
 FALSE  буфер обмена не изменен.

Пример:
 SendMessage(hWndEdit, AEM_COPY, 0, 0);


AEM_CHECKCODEPAGE
_________________

Проверяет, может ли содержимое элемента редактирования быть преобразовано в указанную кодовую страницу.

(int)wParam   == кодовая страница для проверки.
(int *)lParam == возвращает номер строки и позицию непреобразованного символа (первый символ == 1). Может быть NULL.

Возвращаемое значение
 Ноль в случае успеха, иначе возвращает номер первой встреченной строки, содержащей непреобразованный символ (первая строка == 1).

Примечания
 Windows 95 не поддерживается.

Пример:
 SendMessage(hWndEdit, AEM_CHECKCODEPAGE, 1251, (LPARAM)NULL);


AEM_FINDTEXTA
_____________

Находит текст в кодировке ANSI в элементе редактирования.

wParam                == не используется.
(AEFINDTEXTA *)lParam == указатель на структуру AEFINDTEXTA.

Возвращаемое значение
 TRUE   найдено.
 FALSE  не найдено.

Пример:
 AEFINDTEXTA ft;
 AESELECTION aes;

 ft.dwFlags=AEFR_DOWN;
 ft.pText="SomeText";
 ft.dwTextLen=(UINT_PTR)-1;
 ft.nNewLine=AELB_ASIS;
 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_FIRSTCHAR, (LPARAM)&ft.crSearch.ciMin);
 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_LASTCHAR, (LPARAM)&ft.crSearch.ciMax);

 if (SendMessage(hWndEdit, AEM_FINDTEXTA, 0, (LPARAM)&ft))
 {
   aes.crSel=ft.crFound;
   aes.dwFlags=0;
   aes.dwType=0;
   SendMessage(hWndEdit, AEM_SETSEL, (WPARAM)NULL, (LPARAM)&aes);
 }


AEM_FINDTEXTW
_____________

Находит текст в кодировке Unicode в элементе редактирования.

wParam                == не используется.
(AEFINDTEXTW *)lParam == указатель на структуру AEFINDTEXTW.

Возвращаемое значение
 TRUE   найдено.
 FALSE  не найдено.

Пример:
 AEFINDTEXTW ft;
 AESELECTION aes;

 ft.dwFlags=AEFR_DOWN;
 ft.pText=L"SomeText";
 ft.dwTextLen=(UINT_PTR)-1;
 ft.nNewLine=AELB_ASIS;
 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_FIRSTCHAR, (LPARAM)&ft.crSearch.ciMin);
 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_LASTCHAR, (LPARAM)&ft.crSearch.ciMax);

 if (SendMessage(hWndEdit, AEM_FINDTEXTW, 0, (LPARAM)&ft))
 {
   aes.crSel=ft.crFound;
   aes.dwFlags=0;
   aes.dwType=0;
   SendMessage(hWndEdit, AEM_SETSEL, (WPARAM)NULL, (LPARAM)&aes);
 }


AEM_ISMATCHA
____________

Совпадает ли текст в кодировке ANSI с текстом в указанной позиции.

(AECHARINDEX *)wParam == позиция для проверки.
(AEFINDTEXTA *)lParam == указатель на структуру AEFINDTEXTA. Член AEFINDTEXTA.crSearch игнорируется.

Возвращаемое значение
 Длина совпавшего текста или ноль, если не найдено.

Пример:
 AEFINDTEXTA ft;
 AECHARINDEX ciChar;
 AESELECTION aes;

 ft.dwFlags=AEFR_MATCHCASE;
 ft.pText="SomeText";
 ft.dwTextLen=(UINT_PTR)-1;
 ft.nNewLine=AELB_ASIS;
 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_FIRSTSELCHAR, (LPARAM)&ciChar);

 if (SendMessage(hWndEdit, AEM_ISMATCHA, (WPARAM)&ciChar, (LPARAM)&ft))
 {
   aes.crSel=ft.crFound;
   aes.dwFlags=0;
   aes.dwType=0;
   SendMessage(hWndEdit, AEM_SETSEL, (WPARAM)NULL, (LPARAM)&aes);
 }


AEM_ISMATCHW
____________

Совпадает ли текст в кодировке Unicode с текстом в указанной позиции.

(AECHARINDEX *)wParam == позиция для проверки.
(AEFINDTEXTW *)lParam == указатель на структуру AEFINDTEXTW. Член AEFINDTEXTW.crSearch игнорируется.

Возвращаемое значение
 Длина совпавшего текста или ноль, если не найдено.

Пример:
 AEFINDTEXTW ft;
 AECHARINDEX ciChar;
 AESELECTION aes;

 ft.dwFlags=AEFR_MATCHCASE;
 ft.pText=L"SomeText";
 ft.dwTextLen=(UINT_PTR)-1;
 ft.nNewLine=AELB_ASIS;
 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_FIRSTSELCHAR, (LPARAM)&ciChar);

 if (SendMessage(hWndEdit, AEM_ISMATCHW, (WPARAM)&ciChar, (LPARAM)&ft))
 {
   aes.crSel=ft.crFound;
   aes.dwFlags=0;
   aes.dwType=0;
   SendMessage(hWndEdit, AEM_SETSEL, (WPARAM)NULL, (LPARAM)&aes);
 }


AEM_KEYDOWN
___________

Эмулирует нажатие специальной клавиши. Например: VK_HOME, VK_DOWN, VK_INSERT, VK_BACK и т.д.

(int)wParam   == код виртуальной клавиши.
(DWORD)lParam == см. определения AEMOD_*.

Возвращаемое значение
 TRUE  виртуальная клавиша обработана.
 FALSE виртуальная клавиша не обработана.

Примечания
 Для эмуляции клавиши VK_RETURN используйте сообщение WM_CHAR.
 Для эмуляции клавиши VK_TAB используйте ее с модификатором AEMOD_CONTROL.

Пример:
 SendMessage(hWndEdit, AEM_KEYDOWN, VK_RIGHT, AEMOD_SHIFT|AEMOD_CONTROL);


AEM_INSERTCHAR
______________

Вставляет символ с учетом режима замены и группировки отмены.

(wchar_t)wParam == символ Unicode.
lParam          == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_INSERTCHAR, (WPARAM)L' ', 0);


AEM_CHARAT
__________

Получает символ по индексу.

(AECHARINDEX *)wParam == индекс символа.
lParam                == не используется.

Возвращаемое значение
 Символ Unicode или отрицательные значения:
  -AELB_EOF  конец файла.
  -AELB_R    "\r" новая строка.
  -AELB_N    "\n" новая строка.
  -AELB_RN   "\r\n" новая строка.
  -AELB_RRN  "\r\r\n" новая строка.

Примечания
 Для лучшей производительности используйте AEC_CharAtIndex.

Пример:
 AECHARINDEX ciCaret;
 int nChar;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_CARETCHAR, (LPARAM)&ciCaret);
 nChar=SendMessage(hWndEdit, AEM_CHARAT, (WPARAM)&ciCaret, 0);


AEM_INPUTLANGUAGE
_________________

Получает идентификатор активной локали ввода.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Идентификатор локали ввода.

Пример:
 HKL dwInputLocale=(HKL)SendMessage(hWndEdit, AEM_INPUTLANGUAGE, 0, 0);


AEM_DRAGDROP
____________

Операции с текущим перетаскиванием.

(DWORD)wParam == см. определения AEDD_*.
lParam        == не используется.

Возвращаемое значение
 Значение зависит от определения AEDD_*.

Пример:
 HWND hWndDragSource;

 hWndDragSource=(HWND)SendMessage(hWndEdit, AEM_DRAGDROP, AEDD_GETDRAGWINDOW, 0);


AEM_CANUNDO
___________

Определяет, есть ли какие-либо действия в очереди отмены элемента редактирования.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 TRUE   успех.
 FALSE  неудача.

Пример:
 SendMessage(hWndEdit, AEM_CANUNDO, 0, 0);


AEM_CANREDO
___________

Определяет, есть ли какие-либо действия в очереди повтора элемента редактирования.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 TRUE   успех.
 FALSE  неудача.

Пример:
 SendMessage(hWndEdit, AEM_CANREDO, 0, 0);


AEM_UNDO
________

Отменяет последнюю операцию элемента редактирования в очереди отмены.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 TRUE   успех.
 FALSE  неудача.

Пример:
 SendMessage(hWndEdit, AEM_UNDO, 0, 0);


AEM_REDO
________

Повторяет следующую операцию элемента редактирования в очереди повтора.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 TRUE   успех.
 FALSE  неудача.

Пример:
 SendMessage(hWndEdit, AEM_REDO, 0, 0);


AEM_EMPTYUNDOBUFFER
___________________

Очищает историю отмены и повтора.

(BOOL)wParam   == TRUE   очистить только историю повтора.
                  FALSE  очистить историю отмены и повтора.
(HANDLE)lParam == стек отмены, возвращенный AEM_DETACHUNDO. Если не ноль, то wParam игнорируется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_EMPTYUNDOBUFFER, FALSE, 0);


AEM_STOPGROUPTYPING
___________________

Останавливает сбор дополнительных действий ввода в текущее действие отмены.
Элемент управления сохраняет следующее действие ввода, если оно есть, как новое действие в очереди отмены.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_STOPGROUPTYPING, 0, 0);


AEM_BEGINUNDOACTION
___________________

Начало набора операций, которые будут отменены все как одна операция.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_STOPGROUPTYPING, 0, 0);
 SendMessage(hWndEdit, AEM_BEGINUNDOACTION, 0, 0);
 SendMessage(hWndEdit, EM_REPLACESEL, TRUE, (LPARAM)"123");
 SendMessage(hWndEdit, EM_REPLACESEL, TRUE, (LPARAM)"456");
 SendMessage(hWndEdit, AEM_ENDUNDOACTION, 0, 0);
 SendMessage(hWndEdit, AEM_STOPGROUPTYPING, 0, 0);


AEM_ENDUNDOACTION
_________________

Конец набора операций, которые будут отменены все как одна операция.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Ноль.

Пример:
 См. пример AEM_BEGINUNDOACTION.


AEM_LOCKCOLLECTUNDO
___________________

Остановить сбор истории отмены/повтора.

(BOOL)wParam == TRUE   остановить сбор.
                FALSE  начать сбор.
lParam       == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_EMPTYUNDOBUFFER, FALSE, 0);
 SendMessage(hWndEdit, AEM_LOCKCOLLECTUNDO, TRUE, 0);
 SendMessage(hWndEdit, EM_REPLACESEL, TRUE, (LPARAM)"123");
 SendMessage(hWndEdit, EM_REPLACESEL, TRUE, (LPARAM)"456");
 SendMessage(hWndEdit, AEM_LOCKCOLLECTUNDO, FALSE, 0);


AEM_GETUNDOLIMIT
________________

Получает максимальное количество действий, которое может храниться в очереди отмены.

wParam          == не используется.
(DWORD *)lParam == указатель на переменную, которая получает текущее количество действий, хранящихся в очереди отмены. Может быть NULL.

Возвращаемое значение
 Максимальное количество действий, которое может храниться в очереди отмены.

Пример:
 SendMessage(hWndEdit, AEM_GETUNDOLIMIT, 0, (LPARAM)NULL);


AEM_SETUNDOLIMIT
________________

Устанавливает максимальное количество действий, которое может храниться в очереди отмены.

(DWORD)wParam == максимальное количество действий, которое может храниться в очереди отмены. По умолчанию максимальное количество действий в очереди отмены не ограничено.
lParam        == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_SETUNDOLIMIT, 100, 0);


AEM_GETMODIFY
_____________

Получает состояние флага модификации элемента редактирования.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 TRUE   текст был изменен.
 FALSE  текст не был изменен.

Пример:
 SendMessage(hWndEdit, AEM_GETMODIFY, 0, 0);


AEM_SETMODIFY
_____________

Устанавливает состояние флага модификации элемента редактирования.

(BOOL)wParam == TRUE   текст был изменен.
                FALSE  текст не был изменен.
lParam       == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_SETMODIFY, FALSE, 0);


AEM_UNDOBUFFERSIZE
__________________

Получает количество байтов, хранящихся в очереди отмены.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Количество байтов.

Пример:
 SendMessage(hWndEdit, AEM_UNDOBUFFERSIZE, 0, 0);


AEM_ISRANGEMODIFIED
___________________

Получает флаг модификации указанного диапазона символов.

wParam                == не используется.
(CHARRANGE64 *)lParam == диапазон символов для проверки (смещение RichEdit).

Возвращаемое значение
 См. определения AEIRM_*.

Пример (проверка, была ли изменена строка):
 AECHARINDEX ciCaretLine;
 CHARRANGE64 crLineRange;
 int nLineModified;

 //Получить первый символ строки с курсором
 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_CARETCHAR, (LPARAM)&ciCaretLine);
 ciCaretLine.nCharInLine=0;

 //Получить координаты строки с курсором в смещениях RichEdit
 crLineRange.cpMin=SendMessage(hWndEdit, AEM_INDEXTORICHOFFSET, 0, (LPARAM)&ciCaretLine);
 crLineRange.cpMax=crLineRange.cpMin + ciCaretLine.lpLine->nLineLen;
 if (ciCaretLine.lpLine->nLineBreak != AELB_WRAP)
   ++crLineRange.cpMax;

 nLineModified=(int)SendMessage(hWndEdit, AEM_ISRANGEMODIFIED, 0, (LPARAM)&crLineRange);


AEM_DETACHUNDO
______________

Отсоединяет стек отмены.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Стек отмены.

Примечания
 AEM_DETACHUNDO требует стиль ES_GLOBALUNDO.
 Если стек отмены не присоединен с помощью AEM_ATTACHUNDO, то он должен быть освобожден с помощью AEM_EMPTYUNDOBUFFER.

Пример:
 HANDLE hUndoStack;

 hUndoStack=(HANDLE)SendMessage(hWndEdit1, AEM_DETACHUNDO, 0, 0);
 SendMessage(hWndEdit2, AEM_ATTACHUNDO, 0, (LPARAM)hUndoStack);


AEM_ATTACHUNDO
______________

Присоединяет стек отмены.

wParam         == не используется.
(HANDLE)lParam == стек отмены, возвращенный AEM_DETACHUNDO. Текущий стек отмены будет заменен этим.

Возвращаемое значение
 TRUE   успех.
 FALSE  неудача.

Примечания
 AEM_ATTACHUNDO требует стиль ES_GLOBALUNDO.

Пример:
 См. пример AEM_DETACHUNDO.


AEM_GETUNDOPOS
______________

Получает смещение RichEdit элемента отмены.

(DWORD)wParam    == см. определения AEGUP_*.
(HANDLE *)lParam == указатель на дескриптор элемента отмены.

Возвращаемое значение
 Смещение RichEdit элемента отмены. -1 в случае ошибки.

Пример (перейти к предыдущей позиции отмены):
 HANDLE hUndoItem=NULL;
 INT_PTR nOffset=SendMessage(hWndEdit, AEM_GETUNDOPOS, AEGUP_PREV, (LPARAM)&hUndoItem);

 if (nOffset != -1)
   SendMessage(hWndEdit, EM_SETSEL, nOffset, nOffset);


AEM_EXGETSEL
____________

Получает информацию о текущем выделении элемента редактирования. Упрощенная форма AEM_GETSEL.

(AECHARINDEX *)wParam == начальный индекс выделения. Может быть NULL.
(AECHARINDEX *)lParam == конечный индекс выделения. Может быть NULL.

Возвращаемое значение
 TRUE   выделение не пусто.
 FALSE  выделение пусто.

Пример:
 AECHARRANGE aecr;

 SendMessage(hWndEdit, AEM_EXGETSEL, (WPARAM)&aecr.ciMin, (LPARAM)&aecr.ciMax);


AEM_EXSETSEL
____________

Устанавливает текущее выделение элемента редактирования. Упрощенная форма AEM_SETSEL.

(AECHARINDEX *)wParam == начальный индекс выделения.
(AECHARINDEX *)lParam == конечный индекс выделения.

Возвращаемое значение
 Ноль.

Пример:
 AECHARRANGE aecr;
 BOOL bCaretAtEnd=TRUE;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_FIRSTCHAR, (LPARAM)&aecr.ciMin);
 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_LASTCHAR, (LPARAM)&aecr.ciMax);

 if (bCaretAtEnd)
   SendMessage(hWndEdit, AEM_EXSETSEL, (WPARAM)&aecr.ciMin, (LPARAM)&aecr.ciMax);
 else
   SendMessage(hWndEdit, AEM_EXSETSEL, (WPARAM)&aecr.ciMax, (LPARAM)&aecr.ciMin);


AEM_GETSEL
__________

Получает информацию о текущем выделении элемента редактирования.

(AECHARINDEX *)wParam == индекс курсора, NULL если не нужен.
(AESELECTION *)lParam == указатель на структуру AESELECTION, NULL если не нужна.

Возвращаемое значение
 TRUE   выделение не пусто.
 FALSE  выделение пусто.

Пример:
 AESELECTION aes;
 AECHARINDEX ciCaret;

 SendMessage(hWndEdit, AEM_GETSEL, (WPARAM)&ciCaret, (LPARAM)&aes);


AEM_SETSEL
__________

Устанавливает текущее выделение элемента редактирования.

(AECHARINDEX *)wParam == индекс курсора, может быть NULL.
(AESELECTION *)lParam == указатель на структуру AESELECTION.

Возвращаемое значение
 Ноль.

Пример:
 AESELECTION aes;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_FIRSTCHAR, (LPARAM)&aes.crSel.ciMin);
 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_LASTCHAR, (LPARAM)&aes.crSel.ciMax);
 aes.dwFlags=0;
 aes.dwType=0;
 SendMessage(hWndEdit, AEM_SETSEL, (WPARAM)&aes.crSel.ciMax, (LPARAM)&aes);


AEM_GETCOLUMNSEL
________________

Получает режим колонки текущего выделения.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 TRUE   выделение в колоночном режиме.
 FALSE  выделение в неколоночном режиме.

Пример:
 SendMessage(hWndEdit, AEM_GETCOLUMNSEL, 0, 0);


AEM_UPDATESEL
_____________

Обновляет текущее выделение.

(DWORD)wParam == см. определения AESELT_*.
lParam        == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_UPDATESEL, AESELT_LOCKSCROLL, 0);


AEM_GETLINENUMBER
_________________

Получает указанный номер строки.

(int)wParam     == см. определения AEGL_*.
(INT_PTR)lParam == входное смещение символа RichEdit, если требуется.

Возвращаемое значение
 Номер строки, начиная с нуля. -1 в случае ошибки.

Пример:
 SendMessage(hWndEdit, AEM_GETLINENUMBER, AEGL_LINECOUNT, 0);


AEM_GETINDEX
____________

Получает указанный индекс символа.

(int)wParam           == см. определения AEGI_*.
(AECHARINDEX *)lParam == индекс символа.

Возвращаемое значение
 Ноль в случае неудачи, ненулевое значение в случае успеха.

Пример:
 AECHARINDEX ciChar;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_FIRSTCHAR, (LPARAM)&ciChar);


AEM_GETLINEINDEX
________________

Получает первый индекс символа в указанной строке.

(int)wParam           == номер строки, начиная с нуля.
(AECHARINDEX *)lParam == индекс символа.

Возвращаемое значение
 TRUE   успех.
 FALSE  неудача.

Пример:
 AECHARINDEX ciChar;

 SendMessage(hWndEdit, AEM_GETLINEINDEX, 10, (LPARAM)&ciChar);


AEM_INDEXUPDATE
_______________

Обновляет член lpLine структуры AECHARINDEX, чтобы избежать висячего указателя после изменения текста.

wParam                == не используется.
(AECHARINDEX *)lParam == индекс символа.

Возвращаемое значение
 TRUE   успех.
 FALSE  неудача.

Пример:
 AESELECTION aes;

 SendMessage(hWndEdit, AEM_GETSEL, (WPARAM)NULL, (LPARAM)&aes);
 SendMessage(hWndEdit, EM_REPLACESEL, TRUE, (LPARAM)"123");
 SendMessage(hWndEdit, AEM_INDEXUPDATE, 0, (LPARAM)&aes.crSel.ciMin);
 SendMessage(hWndEdit, AEM_INDEXUPDATE, 0, (LPARAM)&aes.crSel.ciMax);


AEM_INDEXCOMPARE
________________

Сравнивает два индекса символов.

(AECHARINDEX *)wParam == первый индекс символа.
(AECHARINDEX *)lParam == второй индекс символа.

Возвращаемое значение
 -1  первый индекс меньше второго индекса
  0  первый индекс равен второму индексу
  1  первый индекс больше второго индекса

Пример:
 AESELECTION aes;

 SendMessage(hWndEdit, AEM_GETSEL, (WPARAM)NULL, (LPARAM)&aes);
 SendMessage(hWndEdit, AEM_INDEXCOMPARE, (WPARAM)&aes.crSel.ciMin, (LPARAM)&aes.crSel.ciMax);

Для лучшей производительности вместо сообщения AEM_INDEXCOMPARE добавьте:
 #define AEC_FUNCTIONS
 #include "AkelEdit.h"
И используйте вызов AEC_IndexCompare:
 AEC_IndexCompare(&aes.crSel.ciMin, &aes.crSel.ciMax);


AEM_INDEXSUBTRACT
_________________

Получает, сколько символов находится между двумя индексами символов.

wParam                    == не используется.
(AEINDEXSUBTRACT *)lParam == указатель на структуру AEINDEXSUBTRACT.

Возвращаемое значение
 Количество символов. Отрицательное, если AEINDEXSUBTRACT.ciChar1 < AEINDEXSUBTRACT.ciChar2.

Пример:
 AEINDEXSUBTRACT is;
 AECHARINDEX ciChar1;
 AECHARINDEX ciChar2;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_FIRSTCHAR, (LPARAM)&ciChar1);
 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_LASTCHAR, (LPARAM)&ciChar2);
 is.ciChar1=&ciChar1;
 is.ciChar2=&ciChar2;
 is.bColumnSel=FALSE;
 is.nNewLine=AELB_ASIS;
 SendMessage(hWndEdit, AEM_INDEXSUBTRACT, 0, (LPARAM)&is);


AEM_INDEXOFFSET
_______________

Получает целевой индекс символа по указанному смещению от исходного индекса символа.

wParam                  == не используется.
(AEINDEXOFFSET *)lParam == указатель на структуру AEINDEXOFFSET.

Возвращаемое значение
 Обработанное количество символов.

Пример:
 AEINDEXOFFSET io;
 AECHARINDEX ciCharIn;
 AECHARINDEX ciCharOut;

 //Получить индекс 10-го символа элемента редактирования
 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_FIRSTCHAR, (LPARAM)&ciCharIn);
 io.ciCharIn=&ciCharIn;
 io.ciCharOut=&ciCharOut;
 io.nOffset=10;
 io.nNewLine=AELB_R;
 SendMessage(hWndEdit, AEM_INDEXOFFSET, 0, (LPARAM)&io);


AEM_INDEXTORICHOFFSET
_____________________

Преобразует индекс символа AkelEdit в смещение RichEdit.

wParam                == не используется.
(AECHARINDEX *)lParam == индекс символа AkelEdit.

Возвращаемое значение
 Смещение RichEdit. В случае ошибки возвращается -1.

Пример:
 AECHARRANGE aecr;
 CHARRANGE recr;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_FIRSTVISIBLELINE, (LPARAM)&aecr.ciMin);
 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_LASTVISIBLELINE, (LPARAM)&aecr.ciMax);
 recr.cpMin=SendMessage(hWndEdit, AEM_INDEXTORICHOFFSET, 0, (LPARAM)&aecr.ciMin);
 recr.cpMax=SendMessage(hWndEdit, AEM_INDEXTORICHOFFSET, 0, (LPARAM)&aecr.ciMax);
 SendMessage(hWndEdit, EM_EXSETSEL, 0, (LPARAM)&recr);


AEM_RICHOFFSETTOINDEX
_____________________

Преобразует смещение RichEdit в индекс символа AkelEdit.

(UINT_PTR)wParam      == смещение RichEdit.
(AECHARINDEX *)lParam == индекс символа AkelEdit.

Возвращаемое значение
 Ноль.

Пример:
 AECHARRANGE aecr;
 CHARRANGE recr;

 SendMessage(hWndEdit, EM_EXGETSEL, 0, (LPARAM)&recr);
 SendMessage(hWndEdit, AEM_RICHOFFSETTOINDEX, (WPARAM)recr.cpMin, (LPARAM)&aecr.ciMin);
 SendMessage(hWndEdit, AEM_RICHOFFSETTOINDEX, (WPARAM)recr.cpMax, (LPARAM)&aecr.ciMax);


AEM_GETRICHOFFSET
_________________

Получает указанное смещение RichEdit.

(int)wParam     == см. определения AEGI_*.
(INT_PTR)lParam == входное смещение символа RichEdit, если требуется.

Возвращаемое значение
 Смещение RichEdit.

Пример:
 INT_PTR nOffset;

 nOffset=SendMessage(hWndEdit, AEM_GETRICHOFFSET, AEGI_LASTCHAR, 0);


AEM_GETWRAPLINE
_______________

Преобразует номер неперенесенной строки в номер перенесенной строки.

(int)wParam           == номер неперенесенной строки, начиная с нуля.
(AECHARINDEX *)lParam == возвращаемый первый символ в перенесенной строке. Может быть NULL.

Возвращаемое значение
 Номер перенесенной строки.

Пример:
 AECHARINDEX ciChar;

 SendMessage(hWndEdit, AEM_GETWRAPLINE, (WPARAM)10, (LPARAM)&ciChar);


AEM_GETUNWRAPLINE
_________________

Преобразует номер перенесенной строки в номер неперенесенной строки.

(int)wParam == номер перенесенной строки, начиная с нуля.
lParam      == не используется.

Возвращаемое значение
 Номер неперенесенной строки.

Пример:
 AECHARINDEX ciCaret;
 int nUnwrappedLine;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_CARETCHAR, (LPARAM)&ciCaret);

 if (SendMessage(hWndEdit, AEM_GETWORDWRAP, 0, (LPARAM)NULL))
   nUnwrappedLine=SendMessage(hWndEdit, AEM_GETUNWRAPLINE, (WPARAM)ciCaret.nLine, 0);
 else
   nUnwrappedLine=ciCaret.nLine;


AEM_GETNEXTBREAK
________________

Получает индекс следующего разрыва слова.

(DWORD)wParam         == см. определения AEWB_*. Если ноль, используются текущие настройки разрыва слова, см. сообщение AEM_SETWORDBREAK.
(AECHARINDEX *)lParam == индекс символа (входной/выходной).

Возвращаемое значение
 Количество символов до разрыва.

Пример:
 AECHARINDEX ciCaret;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_CARETCHAR, (LPARAM)&ciCaret);
 SendMessage(hWndEdit, AEM_GETNEXTBREAK, AEWB_RIGHTWORDSTART|AEWB_RIGHTWORDEND, (LPARAM)&ciCaret);


AEM_GETPREVBREAK
________________

Получает индекс предыдущего разрыва слова.

(DWORD)wParam         == см. определения AEWB_*. Если ноль, используются текущие настройки разрыва слова, см. сообщение AEM_SETWORDBREAK.
(AECHARINDEX *)lParam == индекс символа (входной/выходной).

Возвращаемое значение
 Количество символов до разрыва.

Пример:
 AECHARINDEX ciCaret;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_CARETCHAR, (LPARAM)&ciCaret);
 SendMessage(hWndEdit, AEM_GETPREVBREAK, AEWB_LEFTWORDSTART|AEWB_LEFTWORDEND, (LPARAM)&ciCaret);


AEM_ISDELIMITER
_______________

Определяет, является ли индекс символа разделителем.

(DWORD)wParam         == см. определения AEDLM_*.
(AECHARINDEX *)lParam == индекс символа.

Возвращаемое значение
 TRUE   индекс символа является разделителем.
 FALSE  индекс символа не является разделителем.

Пример:
 AECHARINDEX ciChar;

 SendMessage(hWndEdit, AEM_ISDELIMITER, AEDLM_WORD, (LPARAM)&ciChar);


AEM_INDEXTOCOLUMN
_________________

Получает столбец в строке для индекса символа с учетом размера табуляции.

(DWORD)wParam         == младшее слово:
                          размер табуляции в символах. Используйте текущее значение, если ноль.
                         старшее слово:
                          см. определения AECTI_*.
(AECHARINDEX *)lParam == индекс символа AkelEdit.

Возвращаемое значение
 Номер столбца в строке, начиная с нуля, для индекса символа.

Пример:
 AECHARINDEX ciCaret;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_CARETCHAR, (LPARAM)&ciCaret);
 SendMessage(hWndEdit, AEM_INDEXTOCOLUMN, MAKELONG(0, AECTI_WRAPLINEBEGIN), (LPARAM)&ciCaret);


AEM_COLUMNTOINDEX
_________________

Получает индекс символа для столбца в строке с учетом размера табуляции.

(DWORD)wParam         == младшее слово:
                          размер табуляции в символах. Используйте текущее значение, если ноль.
                         старшее слово:
                          см. определения AECTI_*.
(AECHARINDEX *)lParam == Входные данные: члены AECHARINDEX.lpLine и AECHARINDEX.nLine указывают строку для сканирования.
                                 AECHARINDEX.nCharInLine указывает номер столбца в строке, начиная с нуля.
                         Выходные данные: структура AECHARINDEX заполняется результирующим индексом символа.

Возвращаемое значение
 TRUE   успех.
 FALSE  неудача.

Пример:
 AECHARINDEX ciCaret;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_CARETCHAR, (LPARAM)&ciCaret);
 ciCaret.nCharInLine=10;
 SendMessage(hWndEdit, AEM_COLUMNTOINDEX, MAKELONG(0, AECTI_WRAPLINEBEGIN), (LPARAM)&ciCaret);


AEM_INDEXINURL
______________

Проверяет, находится ли индекс в URL.

(AECHARINDEX *)wParam == индекс символа.
(AECHARRANGE *)lParam == указатель на структуру AECHARRANGE, которая получает диапазон URL, если символ в URL.

Возвращаемое значение
 Длина URL, если индекс в URL, или ноль, если не в URL.

Примечания
 Используйте AEM_POINTONURL для обнаружения URL под точкой.

Пример:
 AECHARINDEX ciCaret;
 AECHARRANGE crUrl;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_CARETCHAR, (LPARAM)&ciCaret);
 SendMessage(hWndEdit, AEM_INDEXINURL, (WPARAM)&ciCaret, (LPARAM)&crUrl);


AEM_URLVISIT
____________

Операции с посещениями URL.

(int)wParam  == см. определения AEUV_*.
(void)lParam == зависит от определения AEUV_*.

Возвращаемое значение
 Зависит от определения AEUV_*.

Пример:
 AECHARINDEX ciCaret;
 AECHARRANGE crUrl;
 AEURLVISIT *lpUrlVisit;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_CARETCHAR, (LPARAM)&ciCaret);
 if (SendMessage(hWndEdit, AEM_INDEXINURL, (WPARAM)&ciCaret, (LPARAM)&crUrl))
 {
   if (lpUrlVisit=(AEURLVISIT *)SendMessage(hWndEdit, AEM_URLVISIT, AEUV_GET, (LPARAM)&crUrl))
   {
     //Сбросить счетчик посещений. Элемент управления может автоматически удалить элемент с нулевым количеством посещений.
     lpUrlVisit->nVisitCount=0;
     InvalidateRect(hWndEdit, NULL, FALSE);
   }
 }


AEM_ADDPOINT
____________

Добавляет индекс символа в стек точек. Индекс символа будет обновляться после каждого изменения текста.

wParam            == не используется.
(AEPOINT *)lParam == указатель на заполненную структуру AEPOINT. Требуются члены AEPOINT.ciPoint и AEPOINT.nPointOffset.

Возвращаемое значение
 Указатель на созданную структуру AEPOINT.

Пример:
 AEPOINT *lpPoint;
 AEPOINT point;
 AECHARINDEX ciChar;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_FIRSTSELCHAR, (LPARAM)&point.ciPoint);
 point.nPointOffset=AEPTO_CALC;
 point.nPointLen=0;
 point.dwFlags=0;
 point.dwUserData=0;

 if (lpPoint=(AEPOINT *)SendMessage(hWndEdit, AEM_ADDPOINT, 0, (LPARAM)&point))
 {
   SendMessage(hWndEdit, EM_REPLACESEL, TRUE, (LPARAM)"123");
   ciChar=lpPoint->ciPoint;  //Прочитать новую позицию
   SendMessage(hWndEdit, AEM_DELPOINT, (WPARAM)lpPoint, 0);
 }


AEM_DELPOINT
____________

Удаляет индекс символа из стека точек.

(AEPOINT *)wParam == указатель на структуру AEPOINT, возвращенную AEM_ADDPOINT.
lParam            == не используется.

Возвращаемое значение
 Ноль.

Пример:
 См. пример AEM_ADDPOINT.


AEM_GETPOINTSTACK
_________________

Получает дескриптор стека точек.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Указатель на структуру HSTACK.

Пример:
void RemoveChangedPoints(HWND hWnd)
{
  HSTACK *hPointStack;
  AEPOINT *lpPointItem;
  AEPOINT *lpPointNextItem;

  if (hPointStack=(HSTACK *)SendMessage(hWndEdit, AEM_GETPOINTSTACK, 0, 0))
  {
    lpPointItem=(AEPOINT *)hPointStack->first;

    while (lpPointItem)
    {
      lpPointNextItem=lpPointItem->next;

      if ((lpPointItem->dwFlags & AEPTF_INSERT) ||
          (lpPointItem->dwFlags & AEPTF_DELETE))
      {
        SendMessage(hWndEdit, AEM_DELPOINT, (WPARAM)lpPointItem, 0);
      }
      lpPointItem=lpPointNextItem;
    }
  }
}


AEM_CHARFROMGLOBALPOS
_____________________

Получает ближайший широкий символ к указанной точке в виртуальном текстовом пространстве элемента редактирования.

(POINT64 *)wParam     == Входные данные: координаты точки в виртуальном текстовом пространстве элемента управления.
                         Выходные данные: точные координаты в виртуальном текстовом пространстве возвращенного символа.
(AECHARINDEX *)lParam == индекс символа.

Возвращаемое значение
 См. определения AEPC_*.

Пример:
 AECHARINDEX ciCaret;
 POINT64 ptGlobal;

 SendMessage(hWndEdit, AEM_GETCARETPOS, (WPARAM)NULL, (LPARAM)&ptGlobal);
 SendMessage(hWndEdit, AEM_CHARFROMGLOBALPOS, (WPARAM)&ptGlobal, (LPARAM)&ciCaret);


AEM_GLOBALPOSFROMCHAR
_____________________

Получает координаты в виртуальном текстовом пространстве для указанного символа в элементе редактирования.

(POINT64 *)wParam     == координаты точки в виртуальном текстовом пространстве элемента управления.
(AECHARINDEX *)lParam == индекс символа.

Возвращаемое значение
 TRUE   успех.
 FALSE  неудача.

Пример:
 AECHARINDEX ciChar;
 POINT64 ptGlobal;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_FIRSTVISIBLECHAR, (LPARAM)&ciChar);
 SendMessage(hWndEdit, AEM_GLOBALPOSFROMCHAR, (WPARAM)&ptGlobal, (LPARAM)&ciChar);


AEM_CHARFROMPOS
_______________

Получает ближайший широкий символ к указанной точке в клиентской области элемента редактирования.

(POINT *)wParam       == Входные данные: координаты точки в клиентской области элемента управления.
                         Выходные данные: точные клиентские координаты возвращенного символа.
(AECHARINDEX *)lParam == индекс символа.

Возвращаемое значение
 См. определения AEPC_*.

Пример:
 AECHARINDEX ciFirstVisible;
 POINT ptClient;

 ptClient.x=10;
 ptClient.y=10;
 SendMessage(hWndEdit, AEM_CHARFROMPOS, (WPARAM)&ptClient, (LPARAM)&ciFirstVisible);


AEM_POSFROMCHAR
_______________

Получает координаты клиентской области для указанного символа в элементе редактирования.

(POINT *)wParam       == координаты точки в клиентской области элемента управления.
(AECHARINDEX *)lParam == индекс символа.

Возвращаемое значение
 TRUE   успех.
 FALSE  неудача.

Пример:
 AECHARINDEX ciChar;
 POINT ptClient;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_FIRSTVISIBLELINE, (LPARAM)&ciChar);
 SendMessage(hWndEdit, AEM_POSFROMCHAR, (WPARAM)&ptClient, (LPARAM)&ciChar);


AEM_GETRECT
___________

Получает форматирующий прямоугольник элемента редактирования. Форматирующий прямоугольник - это ограничивающий прямоугольник, в котором элемент управления рисует текст.

(DWORD)wParam  == см. определения AERC_*.
(RECT *)lParam == указатель на структуру RECT, которая получает форматирующий прямоугольник.

Возвращаемое значение
 Ноль.

Пример:
 RECT rc;

 SendMessage(hWndEdit, AEM_GETRECT, 0, (LPARAM)&rc);


AEM_SETRECT
___________

Устанавливает форматирующий прямоугольник элемента редактирования. Форматирующий прямоугольник - это ограничивающий прямоугольник, в котором элемент управления рисует текст.

(DWORD)wParam  == см. определения AERC_*.
(RECT *)lParam == указатель на структуру RECT, которая определяет новые размеры прямоугольника. Если этот параметр равен NULL, форматирующий прямоугольник устанавливается в значения по умолчанию.

Возвращаемое значение
 Ноль.

Пример:
 RECT rc;

 rc.left=10;
 rc.top=10;
 rc.right=200;
 rc.bottom=200;
 SendMessage(hWndEdit, AEM_SETRECT, AERC_UPDATE, (LPARAM)&rc);


AEM_GETSCROLLPOS
________________

Получает текущую и/или максимальную позицию прокрутки элемента редактирования.

(POINT64 *)wParam == указатель на структуру POINT64, которая получает максимальную позицию прокрутки в виртуальном текстовом пространстве документа, выраженную в пикселях. Может быть NULL.
(POINT64 *)lParam == указатель на структуру POINT64, которая получает позицию левого верхнего угла в виртуальном текстовом пространстве документа, выраженную в пикселях. Может быть NULL.

Возвращаемое значение
 Ноль.

Пример:
 POINT64 ptGlobalMax;
 POINT64 ptGlobalPos;

 SendMessage(hWndEdit, AEM_GETSCROLLPOS, (WPARAM)&ptGlobalMax, (LPARAM)&ptGlobalPos);


AEM_SETSCROLLPOS
________________

Прокручивает элемент редактирования до определенной точки.

wParam            == не используется.
(POINT64 *)lParam == указатель на структуру POINT64, которая определяет точку в виртуальном текстовом пространстве документа, выраженную в пикселях.
                     Если POINT64.x равно -1, то горизонтальная прокрутка не изменяется.
                     Если POINT64.y равно -1, то вертикальная прокрутка не изменяется.

Возвращаемое значение
 Ноль.

Пример:
 POINT64 ptGlobal;

 ptGlobal.x=20;
 ptGlobal.y=10;
 SendMessage(hWndEdit, AEM_SETSCROLLPOS, 0, (LPARAM)&ptGlobal);


AEM_SCROLL
__________

Прокручивает текст по горизонтали или вертикали в элементе редактирования. Это сообщение эквивалентно WM_HSCROLL и WM_VSCROLL.

(DWORD)wParam == см. определения AESB_*.
(int)lParam   == действие, которое может быть указано с AESB_HORZ:
                  SB_LINELEFT  прокручивает влево на один символ.
                  SB_LINERIGHT прокручивает вправо на один символ.
                  SB_PAGELEFT  прокручивает влево на ширину окна.
                  SB_PAGERIGHT прокручивает вправо на ширину окна.
                  SB_LEFT      прокручивает в самый левый край.
                  SB_RIGHT     прокручивает в самый правый край.
                 действие, которое может быть указано с AESB_VERT:
                  SB_LINEUP    прокручивает на одну строку вверх.
                  SB_LINEDOWN  прокручивает на одну строку вниз.
                  SB_PAGEUP    прокручивает на одну страницу вверх.
                  SB_PAGEDOWN  прокручивает на одну страницу вниз.
                  SB_TOP       прокручивает в самый верх.
                  SB_BOTTOM    прокручивает в самый низ.

Возвращаемое значение
 Количество прокрученных пикселей.

Пример:
 SendMessage(hWndEdit, AEM_SCROLL, AESB_VERT, SB_LINEDOWN);


AEM_LINESCROLL
______________

Прокручивает текст по горизонтали или вертикали на указанное количество символов или строк.

(DWORD)wParam == см. определения AESB_*.
(int)lParam   == Если указано AESB_HORZ, количество символов для горизонтальной прокрутки.
                 Если указано AESB_VERT, количество строк для вертикальной прокрутки.

Возвращаемое значение
 Количество прокрученных пикселей.

Пример:
 SendMessage(hWndEdit, AEM_LINESCROLL, AESB_VERT, -10);


AEM_SCROLLTOPOINT
_________________

Прокручивает указанную точку в поле зрения элемента редактирования.

wParam                    == не используется.
(AESCROLLTOPOINT *)lParam == указатель на структуру AESCROLLTOPOINT. Если lParam равен NULL, то выполняется интеллектуальная прокрутка к позиции курсора.

Возвращаемое значение
 См. определения AECSE_*.

Пример:
 AESCROLLTOPOINT stp={0};

 stp.dwFlags=AESC_POINTCARET|AESC_OFFSETCHARX|AESC_OFFSETCHARY;
 stp.nOffsetX=1;
 stp.nOffsetY=1;
 SendMessage(hWndEdit, AEM_SCROLLTOPOINT, 0, (LPARAM)&stp);


AEM_LOCKSCROLL
______________

Блокирует прокрутку элемента редактирования.

(int)wParam  == SB_BOTH  заблокировать горизонтальную и вертикальную прокрутку.
                SB_HORZ  заблокировать горизонтальную прокрутку.
                SB_VERT  заблокировать вертикальную прокрутку.
                -1       только получить текущую блокировку SB_*, lParam игнорируется.
(BOOL)lParam == TRUE   заблокировать прокрутку.
                FALSE  разблокировать прокрутку.

Возвращаемое значение
 Предыдущая блокировка SB_* или -1, если информация о блокировке не определена.

Примечания
 Блокировка является кумулятивной. Если ваше приложение блокирует прокрутку пять раз подряд, оно также должно разблокировать прокрутку пять раз, прежде чем прокрутка разблокируется.

Пример:
 SendMessage(hWndEdit, AEM_LOCKSCROLL, SB_BOTH, TRUE);
 SendMessage(hWndEdit, EM_SETSEL, (WPARAM)-1, (LPARAM)-1);
 SendMessage(hWndEdit, AEM_LOCKSCROLL, SB_BOTH, FALSE);


AEM_GETCHARSIZE
_______________

Получает высоту/ширину символа текущего шрифта или среднюю ширину.

(DWORD)wParam         == см. определения AECS_*.
(AECHARINDEX *)lParam == индекс символа.

Возвращаемое значение
 Целое число, зависящее от значения AECS_*.

Пример:
 SendMessage(hWndEdit, AEM_GETCHARSIZE, AECS_HEIGHT, (LPARAM)NULL);


AEM_GETSTRWIDTH
_______________

Получает ширину строки. Использует текущий выбранный шрифт.

(wchar_t *)wParam == строка Unicode.
(int)lParam       == длина строки.

Возвращаемое значение
 Ширина строки.

Пример:
 SendMessage(hWndEdit, AEM_GETSTRWIDTH, (WPARAM)L"ABC", 3);


AEM_GETCARETPOS
_______________

Получает текущую позицию курсора.

(POINT *)wParam   == указатель на структуру POINT, которая получает позицию курсора в координатах клиентской области, выраженную в пикселях. Может быть NULL.
(POINT64 *)lParam == указатель на структуру POINT64, которая получает позицию курсора в виртуальном текстовом пространстве документа, выраженную в пикселях. Может быть NULL.

Возвращаемое значение
 TRUE   курсор видим.
 FALSE  курсор не видим.

Пример:
 POINT ptClient;
 POINT64 ptGlobal;

 SendMessage(hWndEdit, AEM_GETCARETPOS, (WPARAM)&ptClient, (LPARAM)&ptGlobal);


AEM_GETCARETHORZINDENT
______________________

Получает горизонтальный отступ курсора. Он не изменяется после нажатия клавиш VK_UP, VK_DOWN, VK_PRIOR, VK_NEXT.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Горизонтальный отступ курсора в виртуальном текстовом пространстве документа.

Пример:
 SendMessage(hWndEdit, AEM_GETCARETHORZINDENT, 0, 0);


AEM_SETCARETHORZINDENT
______________________

Устанавливает горизонтальный отступ курсора. Он не изменяется после нажатия клавиш VK_UP, VK_DOWN, VK_PRIOR, VK_NEXT.

(DWORD)wParam == горизонтальный отступ курсора в виртуальном текстовом пространстве документа.
lParam        == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_SETCARETHORZINDENT, 10, 0);


AEM_CONVERTPOINT
________________

Преобразует координаты позиции.

(DWORD)wParam     == см. определения AECPT_*.
(POINT64 *)lParam == указатель на структуру POINT64.

Возвращаемое значение
 Ноль.

Пример:
 POINT64 pt;

 pt.x=SendMessage(hWndEdit, AEM_GETCARETHORZINDENT, 0, 0);
 pt.y=0;
 SendMessage(hWndEdit, AEM_CONVERTPOINT, AECPT_GLOBALTOCLIENT, (LPARAM)&pt);


AEM_POINTONMARGIN
_________________

Проверяет, находится ли точка на поле.

(POINT *)wParam == координаты точки в клиентской области элемента управления.
lParam          == не используется.

Возвращаемое значение
 См. определения AESIDE_*.

Пример:
 POINT ptClient;

 ptClient.x=10;
 ptClient.y=10;
 SendMessage(hWndEdit, AEM_POINTONMARGIN, (WPARAM)&ptClient, 0);


AEM_POINTONSELECTION
____________________

Проверяет, находится ли точка на выделении.

(POINT *)wParam == координаты точки в клиентской области элемента управления.
lParam          == не используется.

Возвращаемое значение
 TRUE  на выделении.
 FALSE не на выделении.

Пример:
 POINT ptClient;

 ptClient.x=10;
 ptClient.y=10;
 SendMessage(hWndEdit, AEM_POINTONSELECTION, (WPARAM)&ptClient, 0);


AEM_POINTONURL
______________

Проверяет, находится ли точка на URL.

(POINT *)wParam       == координаты точки в клиентской области элемента управления.
(AECHARRANGE *)lParam == указатель на структуру AECHARRANGE, которая получает диапазон URL, если найден. Может быть NULL.

Возвращаемое значение
 Длина обнаруженного URL или ноль, если не найден.

Пример:
 AECHARRANGE cr;
 POINT ptClient;

 ptClient.x=10;
 ptClient.y=10;
 SendMessage(hWndEdit, AEM_POINTONURL, (WPARAM)&ptClient, (LPARAM)&cr);


AEM_LINEFROMVPOS
________________

Получает строку по вертикальной позиции.

(int)wParam     == см. определения AECT_*.
(INT_PTR)lParam == вертикальная позиция.

Возвращаемое значение
 Номер строки, начиная с нуля.

Пример:
 POINT ptClient;

 SendMessage(hWndEdit, AEM_GETCARETPOS, (LPARAM)&ptClient, (LPARAM)NULL);
 SendMessage(hWndEdit, AEM_LINEFROMVPOS, AECT_CLIENT, ptClient.y);


AEM_VPOSFROMLINE
________________

Получает вертикальную позицию по номеру строки.

(int)wParam == см. определения AECT_*.
(int)lParam == номер строки, начиная с нуля.

Возвращаемое значение
 Вертикальная позиция.

Пример:
 AECHARINDEX ciCaret;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_CARETCHAR, (LPARAM)&ciCaret);
 SendMessage(hWndEdit, AEM_VPOSFROMLINE, AECT_CLIENT, ciCaret.nLine);


AEM_GETMOUSESTATE
_________________

Получает состояния мыши.

(int)wParam == Тип состояния. См. определения AEMS_*.
lParam      == не используется.

Возвращаемое значение
 Если указано AEMS_CAPTURE, см. определения AEMSC_*.
 Если указано AEMS_SELECTION, см. определения AEMSS_*.

Пример:
 SendMessage(hWndEdit, AEM_GETMOUSESTATE, AEMS_CAPTURE, 0);


AEM_CONTROLCLASS
________________

Получает класс элемента управления: AkelEdit или RichEdit.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 См. определения AECLASS_*.

Пример:
 SendMessage(hWndEdit, AEM_CONTROLCLASS, 0, 0);


AEM_CONTROLVERSION
__________________

Получает версию элемента управления.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Номер версии. Создается как: MAKE_IDENTIFIER(dwMajor, dwMinor, dwRelease, dwBuild).

Пример:
 DWORD dwVersion;
 DWORD dwMajor;
 DWORD dwMinor;
 DWORD dwRelease;
 DWORD dwBuild;

 dwVersion=SendMessage(hWndEdit, AEM_CONTROLVERSION, 0, 0);
 dwMajor=LOBYTE(LOWORD(dwVersion));
 dwMinor=HIBYTE(LOWORD(dwVersion));
 dwRelease=LOBYTE(HIWORD(dwVersion));
 dwBuild=HIBYTE(HIWORD(dwVersion));


AEM_GETEVENTMASK
________________

Получает маску событий для элемента редактирования. Маска событий определяет, какие уведомления элемент управления отправляет своему родительскому окну.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 См. определения AENM_*.

Пример:
 SendMessage(hWndEdit, AEM_GETEVENTMASK, 0, 0);


AEM_SETEVENTMASK
________________

Устанавливает маску событий для элемента редактирования. Маска событий определяет, какие уведомления элемент управления отправляет своему родительскому окну.

wParam        == не используется.
(DWORD)lParam == см. определения AENM_*.

Возвращаемое значение
 Предыдущая маска событий.

Пример:
 SendMessage(hWndEdit, AEM_SETEVENTMASK, 0, AENM_SELCHANGE|AENM_TEXTCHANGE|AENM_MODIFY);


AEM_GETOPTIONS
______________

Получает опции элемента редактирования.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Комбинация значений текущих флагов опций. См. определения AECO_*.

Пример:
 SendMessage(hWndEdit, AEM_GETOPTIONS, 0, 0);


AEM_SETOPTIONS
______________

Устанавливает опции для элемента редактирования.

(DWORD)wParam == см. определения AECOOP_*.
(DWORD)lParam == см. определения AECO_*.

Возвращаемое значение
 Текущие опции элемента редактирования.

Пример 1:
 SendMessage(hWndEdit, AEM_SETOPTIONS, AECOOP_OR, AECO_DISABLEDRAG|AECO_DISABLEDROP);

Пример 2:
 if (bDisableNoScroll)
 {
   SendMessage(hWndEdit, AEM_SETOPTIONS, AECOOP_OR, AECO_DISABLENOSCROLL);
   ShowScrollBar(hWndEdit, SB_BOTH, TRUE);
   SetScrollRange(hWndEdit, SB_HORZ, 0, 100, TRUE);
   SetScrollRange(hWndEdit, SB_VERT, 0, 100, TRUE);
   SendMessage(hWndEdit, AEM_UPDATESCROLLBAR, SB_BOTH, 0);
 }
 else
 {
   SendMessage(hWndEdit, AEM_SETOPTIONS, AECOOP_XOR, AECO_DISABLENOSCROLL);
   ShowScrollBar(hWndEdit, SB_BOTH, TRUE);
   SendMessage(hWndEdit, AEM_UPDATESCROLLBAR, SB_BOTH, 0);
 }


AEM_GETNEWLINE
______________

Получает опции новой строки по умолчанию для элемента редактирования.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Младшее слово содержит новую строку ввода по умолчанию.
 Старшее слово содержит новую строку вывода по умолчанию.

Примечания
 Возможные новые строки: AELB_ASIS, AELB_R, AELB_N, AELB_RN, AELB_RRN.

Пример:
 SendMessage(hWndEdit, AEM_GETNEWLINE, 0, 0);


AEM_SETNEWLINE
______________

Устанавливает опции новой строки по умолчанию для элемента редактирования.

(DWORD)wParam == см. определения AENL_*.
(DWORD)lParam == младшее слово содержит новую строку ввода по умолчанию. Действительно, если указано AENL_INPUT.
                 старшее слово содержит новую строку вывода по умолчанию. Действительно, если указано AENL_OUTPUT.

Возвращаемое значение
 Ноль.

Примечания
 Возможные новые строки: AELB_ASIS, AELB_R, AELB_N, AELB_RN, AELB_RRN.

Пример:
 SendMessage(hWndEdit, AEM_SETNEWLINE, AENL_INPUT|AENL_OUTPUT, MAKELONG(AELB_R, AELB_RN));


AEM_GETCOLORS
_____________

Получает цвета элемента редактирования.

wParam             == не используется.
(AECOLORS *)lParam == указатель на структуру AECOLORS.

Возвращаемое значение
 Ноль.

Пример:
 AECOLORS aec;

 aec.dwFlags=AECLR_ALL;
 SendMessage(hWndEdit, AEM_GETCOLORS, 0, (LPARAM)&aec);


AEM_SETCOLORS
_____________

Устанавливает цвета элемента редактирования.

wParam             == не используется.
(AECOLORS *)lParam == указатель на структуру AECOLORS.

Возвращаемое значение
 Ноль.

Пример:
 AECOLORS aec;

 aec.dwFlags=AECLR_BASICTEXT|AECLR_BASICBK;
 aec.crBasicText=GetSysColor(COLOR_WINDOWTEXT);
 aec.crBasicBk=GetSysColor(COLOR_WINDOW);
 SendMessage(hWndEdit, AEM_SETCOLORS, 0, (LPARAM)&aec);


AEM_EXGETOPTIONS
________________

Получает расширенные опции элемента редактирования.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Комбинация значений текущих флагов расширенных опций. См. определения AECOE_*.

Пример:
 SendMessage(hWndEdit, AEM_EXGETOPTIONS, 0, 0);


AEM_EXSETOPTIONS
________________

Устанавливает расширенные опции для элемента редактирования.

(DWORD)wParam == см. определения AECOOP_*.
(DWORD)lParam == см. определения AECOE_*.

Возвращаемое значение
 Текущие расширенные опции элемента редактирования.

Пример:
 SendMessage(hWndEdit, AEM_EXSETOPTIONS, AECOOP_OR, AECOE_DETECTURL|AECOE_OVERTYPE);


AEM_GETCARETWIDTH
_________________

Получает ширину курсора.

wParam          == не используется.
(POINT *)lParam == указатель на структуру POINT, которая получает ширину курсора в режиме вставки в члене x и высоту курсора в режиме замены в члене y.

Возвращаемое значение
 Ноль.

Пример:
 POINT pt;

 SendMessage(hWndEdit, AEM_GETCARETWIDTH, 0, (LPARAM)&pt);


AEM_SETCARETWIDTH
_________________

Устанавливает ширину курсора.

wParam          == не используется.
(POINT *)lParam == указатель на структуру POINT, которая определяет ширину курсора в режиме вставки в члене x и высоту курсора в режиме замены в члене y.

Возвращаемое значение
 Ноль.

Пример:
 POINT pt;

 pt.x=2;
 pt.y=3;
 SendMessage(hWndEdit, AEM_SETCARETWIDTH, 0, (LPARAM)&pt);


AEM_GETTABSTOP
______________

Получает размер табуляции.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Размер табуляции в символах.

Пример:
 SendMessage(hWndEdit, AEM_GETTABSTOP, 0, 0);


AEM_SETTABSTOP
______________

Устанавливает размер табуляции.

(int)wParam == новый размер табуляции в символах. Значение по умолчанию используется, если ноль.
lParam      == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_SETTABSTOP, 4, 0);


AEM_GETWORDWRAP
_______________

Получает режим переноса слов.

wParam          == не используется.
(DWORD *)lParam == указатель на переменную, которая получает число лимита переноса. Может быть NULL.

Возвращаемое значение
 См. определения AEWW_*.

Пример:
 DWORD dwWrapLimit;

 SendMessage(hWndEdit, AEM_GETWORDWRAP, 0, (LPARAM)&dwWrapLimit);


AEM_SETWORDWRAP
_______________

Устанавливает режим переноса слов.

(DWORD)wParam == см. определения AEWW_*.
(int)lParam   == лимит переноса, если ноль, используется правый край окна.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_SETWORDWRAP, AEWW_WORD, 0);


AEM_GETWORDDELIMITERS
_____________________

Получает разделители слов.

(int)wParam       == размер буфера в TCHAR.
(wchar_t *)lParam == указатель на буфер, который получает символы-разделители.

Возвращаемое значение
 Количество скопированных символов, включая завершающие два NULL-символа.

Пример:
 wchar_t wszDelimiters[128];

 SendMessage(hWndEdit, AEM_GETWORDDELIMITERS, 128, (LPARAM)wszDelimiters);


AEM_SETWORDDELIMITERS
_____________________

Устанавливает разделители слов.

wParam            == не используется.
(wchar_t *)lParam == строка, завершающаяся двумя нулями, определяющая символы-разделители. Если NULL, будут использованы разделители по умолчанию.

Возвращаемое значение
 Ноль.

Пример:
 wchar_t wszDelimiters[128]=L" \t\n[](){}<>\0\0";

 SendMessage(hWndEdit, AEM_SETWORDDELIMITERS, 0, (LPARAM)wszDelimiters);


AEM_GETWRAPDELIMITERS
_____________________

Получает разделители для переноса слов.

(int)wParam       == размер буфера в TCHAR.
(wchar_t *)lParam == указатель на буфер, который получает символы-разделители.

Возвращаемое значение
 Количество скопированных символов, включая завершающие два NULL-символа.

Пример:
 wchar_t wszDelimiters[128];

 SendMessage(hWndEdit, AEM_GETWRAPDELIMITERS, 128, (LPARAM)wszDelimiters);


AEM_SETWRAPDELIMITERS
_____________________

Устанавливает разделители для переноса слов.

wParam            == не используется.
(wchar_t *)lParam == строка, завершающаяся двумя нулями, определяющая символы-разделители. Если NULL, будут использованы разделители по умолчанию.

Возвращаемое значение
 Ноль.

Пример:
 wchar_t wszDelimiters[128]=L" \t\n[](){}<>\0\0";

 SendMessage(hWndEdit, AEM_SETWRAPDELIMITERS, 0, (LPARAM)wszDelimiters);


AEM_GETURLLEFTDELIMITERS
________________________

Получает левые разделители для обнаружения URL.

(int)wParam       == размер буфера в TCHAR.
(wchar_t *)lParam == указатель на буфер, который получает символы-разделители.

Возвращаемое значение
 Количество скопированных символов, включая завершающие два NULL-символа.

Пример:
 wchar_t wszDelimiters[128];

 SendMessage(hWndEdit, AEM_GETURLLEFTDELIMITERS, 128, (LPARAM)wszDelimiters);


AEM_SETURLLEFTDELIMITERS
________________________

Устанавливает левые разделители для обнаружения URL.

wParam            == не используется.
(wchar_t *)lParam == строка, завершающаяся двумя нулями, определяющая символы-разделители. Если NULL, будут использованы разделители по умолчанию.

Возвращаемое значение
 Ноль.

Пример:
 wchar_t wszDelimiters[128]=L" \t\n'`\"(<{[=\0\0";

 SendMessage(hWndEdit, AEM_SETURLLEFTDELIMITERS, 0, (LPARAM)wszDelimiters);


AEM_GETURLRIGHTDELIMITERS
________________________

Получает правые разделители для обнаружения URL.

(int)wParam       == размер буфера в TCHAR.
(wchar_t *)lParam == указатель на буфер, который получает символы-разделители.

Возвращаемое значение
 Количество скопированных символов, включая завершающие два NULL-символа.

Пример:
 wchar_t wszDelimiters[128];

 SendMessage(hWndEdit, AEM_GETURLRIGHTDELIMITERS, 128, (LPARAM)wszDelimiters);


AEM_SETURLRIGHTDELIMITERS
________________________

Устанавливает правые разделители для обнаружения URL.

wParam            == не используется.
(wchar_t *)lParam == строка, завершающаяся двумя нулями, определяющая символы-разделители. Если NULL, будут использованы разделители по умолчанию.

Возвращаемое значение
 Ноль.

Пример:
 wchar_t wszDelimiters[128]=L" \t\n'`\")>}]\0\0";

 SendMessage(hWndEdit, AEM_SETURLRIGHTDELIMITERS, 0, (LPARAM)wszDelimiters);


AEM_GETURLPREFIXES
__________________

Получает префиксы URL.

(int)wParam       == размер буфера в TCHAR.
(wchar_t *)lParam == указатель на буфер, который получает пары строк префиксов, завершающихся нулем. Последняя строка заканчивается двумя NULL-символами.

Возвращаемое значение
 Количество скопированных символов, включая завершающие два NULL-символа.

Пример:
 wchar_t wszPrefixes[128];

 SendMessage(hWndEdit, AEM_GETURLPREFIXES, 128, (LPARAM)wszPrefixes);


AEM_SETURLPREFIXES
__________________

Устанавливает префиксы для обнаружения URL.

wParam            == не используется.
(wchar_t *)lParam == буфер, содержащий пары строк префиксов, завершающихся нулем. Последняя строка в буфере должна заканчиваться двумя NULL-символами. Если NULL, будут использованы префиксы по умолчанию.

Возвращаемое значение
 Количество строк префиксов.

Пример:
 wchar_t wszPrefixes[128]=L"http:\0https:\0www.\0ftp:\0file:\0mailto:\0\0"

 SendMessage(hWndEdit, AEM_SETURLPREFIXES, 0, (LPARAM)wszPrefixes);


AEM_GETURLMAXLENGTH
___________________

Получает максимальную длину URL.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Максимальная длина URL.

Пример:
 SendMessage(hWndEdit, AEM_GETURLMAXLENGTH, 0, 0);


AEM_SETURLMAXLENGTH
___________________

Устанавливает максимальную длину URL.

(DWORD)wParam == максимальная длина URL (по умолчанию 512).
lParam        == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_SETURLMAXLENGTH, 1024, 0);


AEM_GETWORDBREAK
________________

Получает движение разрыва слова.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 См. определения AEWB_*.

Пример:
 SendMessage(hWndEdit, AEM_GETWORDBREAK, 0, 0);


AEM_SETWORDBREAK
________________

Устанавливает движение разрыва слова.

(DWORD)wParam == см. определения AEWB_*.
lParam        == не используется.

Возвращаемое значение
 Предыдущее движение разрыва слова. См. определения AEWB_*.

Пример:
 SendMessage(hWndEdit, AEM_SETWORDBREAK, AEWB_LEFTWORDSTART|AEWB_RIGHTWORDSTART, 0);


AEM_GETMARKER
_____________

Получает столбец маркера.

(int *)wParam == указатель на переменную, которая получает тип маркера, см. определения AEMT_*. Может быть NULL.
lParam        == не используется.

Возвращаемое значение
 Номер столбца, ноль, если маркер не установлен.

Пример:
 SendMessage(hWndEdit, AEM_GETMARKER, (WPARAM)NULL, 0);


AEM_SETMARKER
_____________

Устанавливает маркер в указанную позицию.

(int)wParam == см. определения AEMT_*.
(int)lParam == целое число, ноль для сброса маркера.

Возвращаемое значение
 TRUE  тип или позиция маркера изменены.
 FALSE изменения не внесены.

Пример:
 SendMessage(hWndEdit, AEM_SETMARKER, AEMT_SYMBOL, 80);


AEM_GETLINEGAP
______________

Получает внешний межстрочный интервал.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Межстрочный интервал (внешний полуапрош).

Пример:
 SendMessage(hWndEdit, AEM_GETLINEGAP, 0, 0);


AEM_SETLINEGAP
______________

Устанавливает внешний межстрочный интервал.

(int)wParam == межстрочный интервал (внешний полуапрош), по умолчанию ноль.
lParam      == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_SETLINEGAP, 3, 0);


AEM_GETTEXTLIMIT
________________

Получает текущий лимит текста для элемента редактирования.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Лимит текста.

Пример:
 SendMessage(hWndEdit, AEM_GETTEXTLIMIT, 0, 0);


AEM_SETTEXTLIMIT
________________

Устанавливает лимит текста для элемента редактирования. Лимит текста - это максимальное количество текста в TCHAR, которое пользователь может ввести в элемент редактирования.

(UINT_PTR)wParam == максимальное количество TCHAR, которое пользователь может ввести. По умолчанию не ограничено.
lParam           == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_SETTEXTLIMIT, MAX_PATH, 0);


AEM_GETFONT
___________

Получает дескриптор шрифта.

(int)wParam == см. определения AEGF_*.
lParam      == не используется.

Возвращаемое значение
 Дескриптор шрифта.

Пример:
 HFONT hFontItalic=(HFONT)SendMessage(hWndEdit, AEM_GETFONT, AEGF_ITALIC, 0);


AEM_GETALTLINE
______________

Получает интервалы чередующихся строк.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Младшее слово содержит интервал пропуска в строках.
 Старшее слово содержит интервал заполнения в строках.

Пример:
 SendMessage(hWndEdit, AEM_GETALTLINE, 0, 0);


AEM_SETALTLINE
______________

Устанавливает интервалы чередующихся строк.

(DWORD)wParam == младшее слово содержит интервал пропуска в строках.
                 старшее слово содержит интервал заполнения в строках.
lParam        == не используется.

Возвращаемое значение
 Ноль.

Примечания
 Если wParam равен нулю, рисование четных строк выключено.

Пример:
 SendMessage(hWndEdit, AEM_SETALTLINE, MAKELONG(1, 1), 0);


AEM_GETCHARCOLORS
_________________

Получает цвета символа.

(AECHARINDEX *)wParam  == индекс символа.
(AECHARCOLORS *)lParam == указатель на структуру AECHARCOLORS.

Возвращаемое значение
 TRUE  символ в выделении.
 FALSE символ не в выделении.

Пример:
 AECHARINDEX ciCaret;
 AECHARCOLORS aelc;

 aelc.dwFlags=0;
 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_CARETCHAR, (LPARAM)&ciCaret);
 SendMessage(hWndEdit, AEM_GETCHARCOLORS, (WPARAM)&ciCaret, (LPARAM)&aelc);


AEM_SCROLLCARETOPTIONS
______________________

Получает или устанавливает опции прокрутки к курсору.

(BOOL)wParam                   == TRUE   установить операцию курсора.
                                  FALSE  получить операцию курсора.
(AESCROLLCARETOPTIONS *)lParam == указатель на структуру AESCROLLCARETOPTIONS. Если этот параметр равен NULL, а wParam равен TRUE, опции прокрутки курсора устанавливаются в значения по умолчанию.

Возвращаемое значение
 ноль

Пример:
 AESCROLLCARETOPTIONS sco;

 sco.dwFlags=AESC_OFFSETCHARX|AESC_OFFSETCHARY;
 sco.dwSelFlags=0;
 sco.dwSelType=AESCT_KEYBOARD;
 sco.nOffsetX=10;
 sco.nOffsetY=5;
 SendMessage(hWndEdit, AEM_SCROLLCARETOPTIONS, TRUE, (LPARAM)&sco);


AEM_FIXEDCHARWIDTH
__________________

Устанавливает фиксированную ширину символа. Все символы, включая пропорциональные шрифты, будут рисоваться с этой шириной.

(int)wParam  == ширина символа или одно из следующих значений:
                -AECS_AVEWIDTH   средняя ширина латинского символа шрифта.
                -AECS_SPACEWIDTH ширина пробела шрифта.
                -AECS_MAXWIDTH   максимальная ширина латинского символа шрифта.
                0                отключить фиксированную ширину.
lParam       == не используется.

Возвращаемое значение
 Предыдущая фиксированная ширина.

Примечания
 Чтобы получить текущую фиксированную ширину, используйте AEM_GETCHARSIZE.

Пример:
 SendMessage(hWndEdit, AEM_FIXEDCHARWIDTH, (WPARAM)-AECS_MAXWIDTH, 0);


AEM_GETSCROLLSPEED
___________________

Получает скорость прокрутки средней кнопкой мыши в процентах.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Скорость прокрутки средней кнопкой мыши.

Пример:
 SendMessage(hWndEdit, AEM_GETSCROLLSPEED, 0, 0);


AEM_SETSCROLLSPEED
___________________

Устанавливает скорость прокрутки средней кнопкой мыши.

(DWORD)wParam == скорость прокрутки средней кнопкой мыши в процентах (по умолчанию 10).
lParam        == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_SETSCROLLSPEED, 50, 0);


AEM_SHOWSCROLLBAR
_________________

Показывает или скрывает полосы прокрутки в элементе редактирования.

(int)wParam  == SB_BOTH  горизонтальная и вертикальная полосы прокрутки.
                SB_HORZ  горизонтальная полоса прокрутки.
                SB_VERT  вертикальная полоса прокрутки.
                -1       только получить текущую видимость SB_*, lParam игнорируется.
(BOOL)lParam == TRUE   показать.
                FALSE  скрыть.

Возвращаемое значение
 Предыдущая видимость SB_* или -1, если нет видимых полос прокрутки.

Пример:
 SendMessage(hWndEdit, AEM_SHOWSCROLLBAR, SB_BOTH, FALSE);


AEM_UPDATESCROLLBAR
___________________

Обновляет полосы прокрутки в элементе редактирования.

(int)wParam  == SB_BOTH  горизонтальная и вертикальная полосы прокрутки.
                SB_HORZ  горизонтальная полоса прокрутки.
                SB_VERT  вертикальная полоса прокрутки.
lParam       == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_UPDATESCROLLBAR, SB_BOTH, 0);


AEM_UPDATECARET
_______________

Обновляет курсор в элементе редактирования.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 TRUE   окно имеет фокус.
 FALSE  окно не имеет фокуса.

Пример:
 SendMessage(hWndEdit, AEM_UPDATECARET, 0, 0);


AEM_UPDATESIZE
______________

Обновляет элемент редактирования после изменения размера окна. Полезно для виртуального дескриптора документа.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_UPDATESIZE, 0, 0);


AEM_LOCKUPDATE
______________

Блокирует обновление указанных объектов.

(DWORD)wParam == см. определения AELU_*.
(BOOL)lParam  == TRUE  заблокировать обновление.
                 FALSE разблокировать обновление.

Возвращаемое значение
 Новое состояние обновления, см. определения AELU_*.

Пример:
 RECT rc={10, 10, 200, 200};

 SendMessage(hWndEdit, AEM_LOCKUPDATE, AELU_SCROLLBAR|AELU_CARET, TRUE);
 SendMessage(hWndEdit, AEM_SETRECT, FALSE, (LPARAM)&rc);
 SendMessage(hWndEdit, AEM_LOCKUPDATE, AELU_SCROLLBAR|AELU_CARET, FALSE);


AEM_LOCKERASERECT
_________________

Блокирует стираемый прямоугольник элемента редактирования. Имеет смысл при ответе на WM_ERASEBKGND.

wParam               == не используется.
(const RECT *)lParam == указатель на структуру RECT, которая определяет стираемый прямоугольник.

Возвращаемое значение
 TRUE   прямоугольник был заблокирован.
 FALSE  прямоугольник не в области стирания.

Пример:
 if (uMsg == WM_ERASEBKGND)
 {
   RECT rcKeep={10, 0, 100, 100}; //Не стирать этот прямоугольник, чтобы избежать мерцания.

   SendMessage(hWndEdit, AEM_LOCKERASERECT, 0, (LPARAM)&rcKeep);
 }


AEM_GETERASERECT
________________

Получает стираемый прямоугольник элемента редактирования. По умолчанию стирается вся область редактирования.

(DWORD)wParam  == см. определения AERC_*.
(RECT *)lParam == указатель на структуру RECT, которая получает стираемый прямоугольник.

Возвращаемое значение
 Ноль.

Пример:
 RECT rc;

 SendMessage(hWndEdit, AEM_GETERASERECT, 0, (LPARAM)&rc);


AEM_SETERASERECT
________________

Устанавливает стираемый прямоугольник элемента редактирования. Стираемый прямоугольник - это ограничивающий прямоугольник, в котором элемент управления стирает фон.

(DWORD)wParam  == см. определения AERC_*.
(RECT *)lParam == указатель на структуру RECT, которая определяет новые размеры прямоугольника. Если этот параметр равен NULL, стираемый прямоугольник устанавливается в значения по умолчанию.

Возвращаемое значение
 Ноль.

Пример (исключить 10 левых пикселей из стирания):
 RECT rc;

 rc.left=10;
 SendMessage(hWndEdit, AEM_SETERASERECT, AERC_NOTOP|AERC_NORIGHT|AERC_NOBOTTOM, (LPARAM)&rc);


AEM_HIDESELECTION
_________________

Скрывает или показывает выделение в элементе редактирования.

(BOOL)wParam == TRUE   скрыть выделение.
                FALSE  показать выделение.
lParam       == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_HIDESELECTION, TRUE, 0);


AEM_REDRAWLINERANGE
___________________

Перерисовывает диапазон строк.

(int)wParam == первая строка для перерисовки. Если -1, перерисовать с верха элемента редактирования.
(int)lParam == последняя строка для перерисовки. Если -1, перерисовать до низа элемента редактирования.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_REDRAWLINERANGE, 10, (LPARAM)-1);


AEM_GETBACKGROUNDIMAGE
______________________

Получает фоновое изображение.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Дескриптор изображения или NULL, если не установлено.

Пример:
 HBITMAP hBitmap=(HBITMAP)SendMessage(hWndEdit, AEM_GETBACKGROUNDIMAGE, 0, 0);


AEM_SETBACKGROUNDIMAGE
______________________

Устанавливает фоновое изображение.

(HBITMAP)wParam == дескриптор изображения. Если NULL, изображение удаляется с фона.
(int)lParam     == значение альфа-прозрачности от 0 до 255 (по умолчанию 128).

Возвращаемое значение
 TRUE   успех.
 FALSE  неудача.

Пример:
HBITMAP hBkImage;

if (hBkImage=(HBITMAP)LoadImageA(NULL, "c:\\MyBackground.bmp", IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE|LR_LOADFROMFILE))
{
  SendMessage(hWndEdit, AEM_SETBACKGROUNDIMAGE, (WPARAM)hBkImage, 128);
}


AEM_PAINTCALLBACK
_________________

Получение операций рисования, включая рисование строки.

(int)wParam  == см. определения AEPCB_*.
(void)lParam == зависит от определения AEPCB_*.

Возвращаемое значение
 Зависит от определения AEPCB_*.

Пример:
 DWORD CALLBACK PaintCallback(UINT_PTR dwCookie, const AENPAINT *pnt)
 {
   if (pnt->dwType == AEPNT_BEGIN)
   {
   }
   else if (pnt->dwType == AEPNT_DRAWLINE)
   {
   }
   else if (pnt->dwType == AEPNT_END)
   {
   }
   return 0
 }

 //Инициализация
 AEPAINTCALLBACKADD pcba;

 pcba.lpCallback=PaintCallback;
 pcba.dwCookie=0;
 lpPaintCallback=(AEPAINTCALLBACK *)SendMessage(hWndEdit, AEM_PAINTCALLBACK, AEPCB_ADD, (LPARAM)&pcba);

 //Деинициализация
 SendMessage(hWndEdit, AEM_PAINTCALLBACK, AEPCB_DEL, (LPARAM)lpPaintCallback);



AEM_GETFOLDSTACK
________________

Получает дескриптор стека фолдов.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Указатель на структуру HSTACK.

Пример:
AEFOLD* GetFold(HWND hWnd, int nLine)
{
  HSTACK *hFoldsStack;
  AEFOLD *lpFold;
  AEFOLD *lpResult=NULL;

  hFoldsStack=(HSTACK *)SendMessage(hWndEdit, AEM_GETFOLDSTACK, 0, 0);

  for (lpFold=(AEFOLD *)hFoldsStack->first; lpFold; lpFold=AEC_NextFold(lpFold, TRUE))
  {
    if (lpFold->lpMinPoint->ciPoint.nLine > nLine)
      break;
    if (lpFold->lpMaxPoint->ciPoint.nLine >= nLine)
      lpResult=lpFold;
  }
  return lpResult;
}


AEM_GETFOLDCOUNT
________________

Получает количество фолдов.

(int)wParam == см. определения AEFC_*.
lParam      == не используется.

Возвращаемое значение
 Количество фолдов.

Пример:
  SendMessage(hWndEdit, AEM_GETFOLDCOUNT, AEFC_ALL, 0);


AEM_ADDFOLD
___________

Добавляет фолд.

wParam           == не используется.
(AEFOLD *)lParam == указатель на заполненную структуру AEFOLD. Члены AEFOLD.next, AEFOLD.prev, AEFOLD.parent, AEFOLD.firstChild, AEFOLD.lastChild игнорируются.

Возвращаемое значение
 Дескриптор фолда (указатель на структуру AEFOLD).

Пример:
 AEPOINT pointMin={0};
 AEPOINT pointMax={0};
 AEFOLD fold;

 pointMin.nPointOffset=AEPTO_CALC;
 pointMax.nPointOffset=AEPTO_CALC;
 SendMessage(hWndEdit, AEM_EXGETSEL, (WPARAM)&pointMin.ciPoint, (LPARAM)&pointMax.ciPoint);
 fold.lpMinPoint=&pointMin;
 fold.lpMaxPoint=&pointMax;
 fold.dwFlags=0;
 fold.dwFontStyle=AEHLS_NONE;
 fold.crText=RGB(0xFF, 0x00, 0x00);
 fold.crBk=(DWORD)-1;
 fold.dwUserData=0;
 SendMessage(hWndEdit, AEM_ADDFOLD, 0, (LPARAM)&fold);


AEM_DELETEFOLD
______________

Удаляет указанный или все фолды.

(AEFOLD *)wParam == дескриптор фолда (указатель на структуру AEFOLD). Если NULL, удалить все фолды.
(BOOL)lParam     == TRUE  обновить прокрутку и выделение.
                    FALSE не обновлять прокрутку и выделение.

Возвращаемое значение
 Количество удаленных фолдов, которые были свернуты.

Пример:
 SendMessage(hWndEdit, AEM_DELETEFOLD, (WPARAM)lpFold, TRUE);


AEM_ISFOLDVALID
_______________

Проверяет, действителен ли дескриптор фолда.

(AEFOLD *)wParam == дескриптор фолда (указатель на структуру AEFOLD), возвращенный AEM_ADDFOLD.
lParam           == не используется.

Возвращаемое значение
 TRUE   дескриптор фолда действителен.
 FALSE  дескриптор фолда недействителен.

Пример:
 SendMessage(hWndEdit, AEM_ISFOLDVALID, (WPARAM)lpFold, 0);


AEM_FINDFOLD
____________

Находит дескриптор фолда.

(AEFINDFOLD *)wParam == указатель на структуру AEFINDFOLD.
lParam               == не используется.

Возвращаемое значение
 Ноль.

Пример:
 AEFINDFOLD ff;
 AECHARINDEX ciCaret;

 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_CARETCHAR, (LPARAM)&ciCaret);
 ff.dwFlags=AEFF_FINDINDEX|AEFF_FOLDSTART|AEFF_GETROOT;
 ff.dwFindIt=(UINT_PTR)&ciCaret;
 SendMessage(hWndEdit, AEM_FINDFOLD, (WPARAM)&ff, 0);


AEM_NEXTFOLD
____________

Получает следующий дескриптор фолда.

(AEFOLD *)wParam == дескриптор фолда (указатель на структуру AEFOLD).
(BOOL)lParam     == TRUE   войти в дочерние фолды, если возможно (рекурсивно).
                    FALSE  не входить в дочерние фолды.

Возвращаемое значение
 Дескриптор фолда (указатель на структуру AEFOLD).

Примечания
 Для лучшей производительности используйте AEC_NextFold.

Пример:
 AEFOLD *lpNextFold;

 lpNextFold=(AEFOLD *)SendMessage(hWndEdit, AEM_NEXTFOLD, (WPARAM)lpFold, TRUE);


AEM_PREVFOLD
____________

Получает предыдущий дескриптор фолда.

(AEFOLD *)wParam == дескриптор фолда (указатель на структуру AEFOLD).
(BOOL)lParam     == TRUE   войти в дочерние фолды, если возможно (рекурсивно).
                    FALSE  не входить в дочерние фолды.

Возвращаемое значение
 Дескриптор фолда (указатель на структуру AEFOLD).

Примечания
 Для лучшей производительности используйте AEC_PrevFold.

Пример:
 AEFOLD *lpPrevFold;

 lpPrevFold=(AEFOLD *)SendMessage(hWndEdit, AEM_PREVFOLD, (WPARAM)lpFold, TRUE);


AEM_ISLINECOLLAPSED
___________________

Проверяет, свернута ли строка.

(int)wParam == номер строки.
lParam      == не используется.

Возвращаемое значение
 Дескриптор фолда (указатель на структуру AEFOLD), который скрывает строку, или NULL, если строка не свернута.

Пример:
 AEFOLD *lpFold;

 lpFold=(AEFOLD *)SendMessage(hWndEdit, AEM_ISLINECOLLAPSED, 5, 0);


AEM_COLLAPSELINE
________________

Сворачивает или разворачивает все фолды, содержащие строку.

(int)wParam   == номер строки, начиная с нуля.
(DWORD)lParam == см. определения AECF_*.

Возвращаемое значение
 Количество измененных фолдов.

Пример:
 SendMessage(hWndEdit, AEM_COLLAPSELINE, 5, AECF_EXPAND);


AEM_COLLAPSEFOLD
________________

Устанавливает состояние свернутости фолда.

(AEFOLD *)wParam == дескриптор фолда (указатель на структуру AEFOLD), возвращенный AEM_ADDFOLD. Если NULL, обработать все фолды.
(DWORD)lParam    == см. определения AECF_*.

Возвращаемое значение
 Количество измененных фолдов.

Пример:
 SendMessage(hWndEdit, AEM_COLLAPSEFOLD, (WPARAM)lpFold, AECF_COLLAPSE);


AEM_UPDATEFOLD
______________

Обновляет прокрутку и выделение. Обычно может использоваться после удаления/сворачивания фолда.

wParam      == не используется.
(int)lParam == первая видимая строка, которая была до удаления/сворачивания фолда. Если -1, игнорируется.

Возвращаемое значение
 Количество прокрученных пикселей.

Пример:
 nFirstVisibleLine=SendMessage(hWndEdit, AEM_GETLINENUMBER, AEGL_FIRSTVISIBLELINE, 0);
 SendMessage(hWndEdit, AEM_DELETEFOLD, (WPARAM)lpFold1, FALSE);
 SendMessage(hWndEdit, AEM_COLLAPSEFOLD, (WPARAM)lpFold2, AECF_EXPAND|AECF_NOUPDATE);
 SendMessage(hWndEdit, AEM_UPDATEFOLD, 0, nFirstVisibleLine);


AEM_GETFOLDHIDEOFFSET
_____________________

Получает смещения строк, скрываемых при сворачивании.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Младшее слово содержит смещение начала фолда для скрытия.
 Старшее слово содержит смещение конца фолда для скрытия.

Пример:
 DWORD dwHideLineOffsets=SendMessage(hWndEdit, AEM_GETFOLDHIDEOFFSET, 0, 0);
 int nHideMinLineOffset=(short)LOWORD(dwHideLineOffsets);
 int nHideMaxLineOffset=(short)HIWORD(dwHideLineOffsets);


AEM_SETFOLDHIDEOFFSET
_____________________

Устанавливает смещения строк, скрываемых при сворачивании.

(DWORD)wParam == младшее слово содержит смещение начала фолда для скрытия. Должно быть >= 1. По умолчанию 1.
                 старшее слово содержит смещение конца фолда для скрытия. Должно быть <= 0. По умолчанию -1.
lParam        == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_SETFOLDHIDEOFFSET, MAKELONG(1, 0), 0);


AEM_CREATEDOCUMENT
__________________

Создает новый виртуальный документ, который позже может быть связан с любым окном редактирования. Обратите внимание, что новое окно редактирования после создания уже имеет назначенный дескриптор документа.

wParam                 == не используется.
(CREATESTRUCT *)lParam == указатель на структуру CREATESTRUCT.

Возвращаемое значение
 Дескриптор созданного документа.

Пример:
 CREATESTRUCTA cs;
 AEHDOC hDocNew;
 AEHDOC hDocOld;

 cs.lpCreateParams=NULL;
 cs.hInstance=GetModuleHandle(NULL);
 cs.hMenu=(HMENU)100;
 cs.hwndParent=GetParent(hWndEdit);
 cs.cy=CW_USEDEFAULT;
 cs.cx=CW_USEDEFAULT;
 cs.y=CW_USEDEFAULT;
 cs.x=CW_USEDEFAULT;
 cs.style=WS_CHILD|WS_VISIBLE|WS_HSCROLL|WS_VSCROLL|ES_DISABLENOSCROLL;
 cs.lpszName=NULL;
 cs.lpszClass=AES_AKELEDITA;
 cs.dwExStyle=WS_EX_CLIENTEDGE;

 hDocNew=(AEHDOC)SendMessage(hWndEdit, AEM_CREATEDOCUMENT, 0, (LPARAM)&cs);
 hDocOld=(AEHDOC)SendMessage(hWndEdit, AEM_SETDOCUMENT, (WPARAM)hDocNew, 0);


AEM_DELETEDOCUMENT
__________________

Уничтожает дескриптор документа. Дескриптор документа не должен быть связан ни с одним окном редактирования.

(AEHDOC)wParam == дескриптор документа.
lParam         == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_DELETEDOCUMENT, (WPARAM)hDoc, 0);


AEM_GETDOCUMENT
_______________

Получает дескриптор документа.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Дескриптор документа.

Пример:
 AEHDOC hDoc=(AEHDOC)SendMessage(hWndEdit, AEM_GETDOCUMENT, 0, 0);


AEM_SETDOCUMENT
_______________

Связывает или отсоединяет дескриптор документа с элементом редактирования, которому отправляется сообщение.

(AEHDOC)wParam == дескриптор документа.
(DWORD)lParam  == см. определения AESWD_*.

Возвращаемое значение
 Старый дескриптор документа.

Пример:
 См. пример AEM_CREATEDOCUMENT.


AEM_GETDOCUMENTPROC
___________________

Получает процедуру документа.

(AEHDOC)wParam == дескриптор документа. Если NULL, возвращается текущая процедура.
lParam         == не используется.

Возвращаемое значение
 Указатель на процедуру AEEditProc.

Пример (Вызов процедуры окна напрямую):
 AEHDOC hDoc=(AEHDOC)SendMessage(hWndEdit, AEM_GETDOCUMENT, 0, 0);
 AEEditProc lpEditProc=(AEEditProc)SendMessage(hWndEdit, AEM_GETDOCUMENTPROC, (WPARAM)hDoc, 0);
 LRESULT lResult;

 lResult=lpEditProc(hDoc, EM_SETSEL, (WPARAM)0, (LPARAM)-1);


AEM_GETDOCUMENTWINDOW
_____________________

Получает элемент редактирования документа.

(AEHDOC)wParam == дескриптор документа. Если NULL, возвращается текущий элемент редактирования.
lParam         == не используется.

Возвращаемое значение
 Дескриптор элемента редактирования.

Пример:
 AEHDOC hDoc=(AEHDOC)SendMessage(hWndEditFirst, AEM_GETDOCUMENT, 0, 0);
 HWND hWnd=(HWND)SendMessage(hWndEditSecond, AEM_GETDOCUMENTWINDOW, (WPARAM)hDoc, 0);
 //hWnd == hWndEditFirst


AEM_SENDMESSAGE
_______________

Отправляет сообщение связанному или отсоединенному дескриптору документа.

lParam                  == не используется.
(AESENDMESSAGE *)lParam == указатель на структуру AESENDMESSAGE.

Возвращаемое значение
 TRUE   успех.
 FALSE  неудача.

Пример:
 AESENDMESSAGE sm;

 sm.hDoc=hDoc;
 sm.uMsg=EM_SETSEL;
 sm.wParam=0;
 sm.lParam=(LPARAM)-1;
 if (SendMessage(hWndAnyEdit, AEM_SENDMESSAGE, 0, (LPARAM)&sm))
   return sm.lResult;


AEM_ADDCLONE
____________

Добавляет клон к главному окну. Сообщение отправляется главному окну, которое будет клонировано.

(HWND)wParam == дескриптор элемента редактирования, который станет клоном. Текст главного окна и окна-клона будет одинаковым.
lParam       == не используется.

Возвращаемое значение
 TRUE   успех.
 FALSE  неудача.

Пример:
 SendMessage(hWndEdit, AEM_ADDCLONE, (WPARAM)hWndEdit2, 0);


AEM_DELCLONE
____________

Удаляет клон из главного окна. Сообщение отправляется главному окну.

(HWND)wParam == дескриптор элемента редактирования, который потеряет статус клона. Текст окна-клона будет восстановлен.
lParam       == не используется.

Возвращаемое значение
 TRUE   успех.
 FALSE  неудача.

Пример:
 SendMessage(hWndEdit, AEM_DELCLONE, (WPARAM)hWndEdit2, 0);


AEM_GETMASTER
_____________

Получает главное окно/дескриптор документа. Сообщение отправляется главному или подчиненному окну.

(BOOL)wParam == TRUE   получить главный документ.
                FALSE  получить главное окно.
lParam       == не используется.

Возвращаемое значение
 Дескриптор главного окна/документа.

Пример:
 HWND hWndMaster;

 if (hWndMaster=(HWND)SendMessage(hWndEdit, AEM_GETMASTER, FALSE, 0))
 {
   if (hWndMaster == hWndEdit)
     MessageBoxA(NULL, "hWndEdit является главным", NULL, 0);
   else
     MessageBoxA(NULL, "hWndEdit является подчиненным", NULL, 0);
 }
 else MessageBoxA(NULL, "hWndEdit не является ни главным, ни подчиненным", NULL, 0);


AEM_GETCLONE
____________

Получает дескриптор окна-клона. Сообщение отправляется главному окну.

(DWORD)wParam == индекс клона, начиная с нуля.
lParam        == не используется.

Возвращаемое значение
 Дескриптор окна-клона.

Пример:
 SendMessage(hWndEdit, AEM_GETCLONE, 2, 0);


AEM_STARTPRINTDOC
_________________

Подготавливает печать документа.

wParam            == не используется.
(AEPRINT *)lParam == указатель на структуру AEPRINT.

Возвращаемое значение
 Дескриптор документа.

Пример:
 PRINTDLGA pdlg={0};
 DOCINFOA di={0};
 AEPRINT prn;
 AEHPRINT hPrintDoc;
 BOOL bPrintStop=FALSE;

 //Выбрать принтер
 pdlg.lStructSize=sizeof(PRINTDLGA);
 pdlg.hwndOwner=hWndEdit;
 pdlg.Flags=PD_ALLPAGES|PD_NOPAGENUMS|PD_RETURNDC|PD_USEDEVMODECOPIESANDCOLLATE;
 pdlg.nCopies=1;
 if (!PrintDlgA(&pdlg)) return;

 //Установить настройки печати
 prn.dwFlags=AEPRN_INHUNDREDTHSOFMILLIMETERS|AEPRN_WRAPWORD;
 prn.hPrinterDC=pdlg.hDC;
 prn.hEditFont=(HFONT)SendMessage(hWndEdit, WM_GETFONT, 0, 0);
 prn.rcMargins.left=1000;
 prn.rcMargins.top=1000;
 prn.rcMargins.right=1000;
 prn.rcMargins.bottom=1000;
 if (pdlg.Flags & PD_SELECTION)
 {
   SendMessage(hWndEdit, AEM_GETINDEX, AEGI_FIRSTSELCHAR, (LPARAM)&prn.crText.ciMin);
   SendMessage(hWndEdit, AEM_GETINDEX, AEGI_LASTSELCHAR, (LPARAM)&prn.crText.ciMax);
 }
 else
 {
   SendMessage(hWndEdit, AEM_GETINDEX, AEGI_FIRSTCHAR, (LPARAM)&prn.crText.ciMin);
   SendMessage(hWndEdit, AEM_GETINDEX, AEGI_LASTCHAR, (LPARAM)&prn.crText.ciMax);
 }

 //Свойства документа
 di.cbSize=sizeof(DOCINFOA);
 di.lpszDocName="AkelEdit document";
 if (pdlg.Flags & PD_PRINTTOFILE)
   di.lpszOutput="FILE:";

 //Начать документ
 if (StartDocA(pdlg.hDC, &di) > 0)
 {
   if (hPrintDoc=(AEHPRINT)SendMessage(hWndEdit, AEM_STARTPRINTDOC, 0, (LPARAM)&prn))
   {
     while (!bPrintStop)
     {
       if (StartPage(prn.hPrinterDC) > 0)
       {
         //Напечатать страницу
         if (!SendMessage(hWndEdit, AEM_PRINTPAGE, (WPARAM)hPrintDoc, (LPARAM)&prn))
           bPrintStop=TRUE;

         if (EndPage(prn.hPrinterDC) <= 0)
           bPrintStop=TRUE;
       }
       else bPrintStop=TRUE;
     }
     SendMessage(hWndEdit, AEM_ENDPRINTDOC, (WPARAM)hPrintDoc, (LPARAM)&prn);
   }
   EndDoc(pdlg.hDC);
 }
 DeleteDC(pdlg.hDC);
 pdlg.hDC=NULL;


AEM_PRINTPAGE
_____________

Печатает страницу.

(AEHPRINT)wParam  == дескриптор документа, возвращенный AEM_STARTPRINTDOC.
(AEPRINT *)lParam == указатель на структуру AEPRINT.

Возвращаемое значение
 TRUE   страница напечатана, и есть еще текст для печати.
 FALSE  страница напечатана, и больше нет текста для печати.

Пример:
 См. пример AEM_STARTPRINTDOC.


AEM_ENDPRINTDOC
_______________

Закрывает дескриптор документа печати.

(AEHPRINT)wParam  == дескриптор документа, возвращенный AEM_STARTPRINTDOC.
(AEPRINT *)lParam == указатель на структуру AEPRINT.

Возвращаемое значение
 Ноль.

Пример:
 См. пример AEM_STARTPRINTDOC.


AEM_HLCREATETHEMEA
__________________

Создает пустую тему подсветки.

wParam         == не используется.
(char *)lParam == имя темы в кодировке ANSI.

Возвращаемое значение
 Дескриптор темы.

Пример:
 AEHTHEME hTheme;
 AEDELIMITEMA di;
 AEWORDITEMA wi;
 AEQUOTEITEMA qi;
 AEMARKRANGEITEM mri;
 AEMARKTEXTITEMA mti;

 if (hTheme=(AEHTHEME)SendMessage(hWndEdit, AEM_HLCREATETHEMEA, 0, (LPARAM)"MyTheme"))
 {
   di.nIndex=-1;
   di.pDelimiter=" ";
   di.nDelimiterLen=lstrlenA(di.pDelimiter);
   di.dwFlags=AEHLF_MATCHCASE;
   di.dwFontStyle=AEHLS_NONE;
   di.crText=(DWORD)-1;
   di.crBk=(DWORD)-1;
   SendMessage(hWndEdit, AEM_HLADDDELIMITERA, (WPARAM)hTheme, (LPARAM)&di);

   wi.pWord="for";
   wi.nWordLen=lstrlenA(wi.pWord);
   wi.dwFlags=AEHLF_MATCHCASE;
   wi.dwFontStyle=AEHLS_NONE;
   wi.crText=RGB(0x00, 0xFF, 0x00);
   wi.crBk=(DWORD)-1;
   SendMessage(hWndEdit, AEM_HLADDWORDA, (WPARAM)hTheme, (LPARAM)&wi);

   qi.nIndex=-1;
   qi.pQuoteStart="\"";
   qi.nQuoteStartLen=lstrlenA(qi.pQuoteStart);
   qi.pQuoteEnd="\"";
   qi.nQuoteEndLen=lstrlenA(qi.pQuoteEnd);
   qi.chEscape='\\';
   qi.pQuoteInclude=NULL;
   qi.nQuoteIncludeLen=0
   qi.pQuoteExclude=NULL;
   qi.nQuoteExcludeLen=0;
   qi.dwFlags=AEHLF_MATCHCASE;
   qi.dwFontStyle=AEHLS_NONE;
   qi.crText=RGB(0x00, 0x00, 0xFF);
   qi.crBk=(DWORD)-1;
   SendMessage(hWndEdit, AEM_HLADDQUOTEA, (WPARAM)hTheme, (LPARAM)&qi);

   mri.nIndex=-1;
   mri.crMarkRange.cpMin=10;
   mri.crMarkRange.cpMax=20;
   mri.dwFlags=0;
   mri.dwFontStyle=AEHLS_NONE;
   mri.crText=RGB(0xFF, 0x00, 0x00);
   mri.crBk=(DWORD)-1;
   SendMessage(hWndEdit, AEM_HLADDMARKRANGE, (WPARAM)hTheme, (LPARAM)&mri);

   mti.nIndex=-1;
   mti.pMarkText="or";
   mti.nMarkTextLen=lstrlenA(mti.pMarkText);
   mti.dwFlags=AEHLF_MATCHCASE;
   mti.dwFontStyle=AEHLS_NONE;
   mti.crText=(DWORD)-1;
   mti.crBk=RGB(0xFF, 0x00, 0x00);
   SendMessage(hWndEdit, AEM_HLADDMARKTEXTA, (WPARAM)hTheme, (LPARAM)&mti);

   SendMessage(hWndEdit, AEM_HLSETTHEME, (WPARAM)hTheme, TRUE);
 }


AEM_HLCREATETHEMEW
__________________

Создает пустую тему подсветки.

wParam            == не используется.
(wchar_t *)lParam == имя темы в кодировке Unicode.

Возвращаемое значение
 Дескриптор темы.

Пример:
 AEHTHEME hTheme;
 AEDELIMITEMW di;
 AEWORDITEMW wi;
 AEQUOTEITEMW qi;
 AEMARKRANGEITEM mri;
 AEMARKTEXTITEMW mti;

 if (hTheme=(AEHTHEME)SendMessage(hWndEdit, AEM_HLCREATETHEMEW, 0, (LPARAM)L"MyTheme"))
 {
   di.nIndex=-1;
   di.pDelimiter=L" ";
   di.nDelimiterLen=lstrlenW(di.pDelimiter);
   di.dwFlags=AEHLF_MATCHCASE;
   di.dwFontStyle=AEHLS_NONE;
   di.crText=(DWORD)-1;
   di.crBk=(DWORD)-1;
   SendMessage(hWndEdit, AEM_HLADDDELIMITERW, (WPARAM)hTheme, (LPARAM)&di);

   wi.pWord=L"for";
   wi.nWordLen=lstrlenW(wi.pWord);
   wi.dwFlags=AEHLF_MATCHCASE;
   wi.dwFontStyle=AEHLS_NONE;
   wi.crText=RGB(0x00, 0xFF, 0x00);
   wi.crBk=(DWORD)-1;
   SendMessage(hWndEdit, AEM_HLADDWORDW, (WPARAM)hTheme, (LPARAM)&wi);

   qi.nIndex=-1;
   qi.pQuoteStart=L"\"";
   qi.nQuoteStartLen=lstrlenW(qi.pQuoteStart);
   qi.pQuoteEnd=L"\"";
   qi.nQuoteEndLen=lstrlenW(qi.pQuoteEnd);
   qi.chEscape=L'\\';
   qi.pQuoteInclude=NULL;
   qi.nQuoteIncludeLen=0
   qi.pQuoteExclude=NULL;
   qi.nQuoteExcludeLen=0;
   qi.dwFlags=AEHLF_MATCHCASE;
   qi.dwFontStyle=AEHLS_NONE;
   qi.crText=RGB(0x00, 0x00, 0xFF);
   qi.crBk=(DWORD)-1;
   SendMessage(hWndEdit, AEM_HLADDQUOTEW, (WPARAM)hTheme, (LPARAM)&qi);

   mri.nIndex=-1;
   mri.crMarkRange.cpMin=10;
   mri.crMarkRange.cpMax=20;
   mri.dwFlags=0;
   mri.dwFontStyle=AEHLS_NONE;
   mri.crText=RGB(0xFF, 0x00, 0x00);
   mri.crBk=(DWORD)-1;
   SendMessage(hWndEdit, AEM_HLADDMARKRANGE, (WPARAM)hTheme, (LPARAM)&mri);

   mti.nIndex=-1;
   mti.pMarkText=L"or";
   mti.nMarkTextLen=lstrlenW(mti.pMarkText);
   mti.dwFlags=AEHLF_MATCHCASE;
   mti.dwFontStyle=AEHLS_NONE;
   mti.crText=(DWORD)-1;
   mti.crBk=RGB(0xFF, 0x00, 0x00);
   SendMessage(hWndEdit, AEM_HLADDMARKTEXTW, (WPARAM)hTheme, (LPARAM)&mti);

   SendMessage(hWndEdit, AEM_HLSETTHEME, (WPARAM)hTheme, TRUE);
 }


AEM_HLFINDTHEME
_______________

Находит дескриптор темы подсветки.

(int)wParam  == см. определения AEHLFT_*.
(void)lParam == зависит от определения AEHLFT_*.

Возвращаемое значение
 Дескриптор темы.

Пример:
 AEHTHEME hTheme=(AEHTHEME)SendMessage(hWndEdit, AEM_HLFINDTHEME, AEHLFT_BYNAMEW, (LPARAM)L"MyTheme");


AEM_HLGETTHEMENAMEA
___________________

Получает имя темы подсветки в кодировке ANSI.

(AEHTHEME)wParam == дескриптор темы.
(char *)lParam   == указатель на буфер, который получает имя темы подсветки в кодировке ANSI. Если NULL, возвращаемое значение - требуемый размер буфера.

Возвращаемое значение
 Длина строки, скопированной в буфер, в TCHAR, не включая завершающий нулевой символ.

Пример:
 char szThemeName[MAX_PATH];

 SendMessage(hWndEdit, AEM_HLGETTHEMENAMEA, (WPARAM)hTheme, (LPARAM)szThemeName);


AEM_HLGETTHEMENAMEW
___________________

Получает имя темы подсветки в кодировке Unicode.

(AEHTHEME)wParam  == дескриптор темы.
(wchar_t *)lParam == указатель на буфер, который получает имя темы подсветки в кодировке Unicode. Если NULL, возвращаемое значение - требуемый размер буфера.

Возвращаемое значение
 Длина строки, скопированной в буфер, в TCHAR, не включая завершающий нулевой символ.

Пример:
 wchar_t wszThemeName[MAX_PATH];

 SendMessage(hWndEdit, AEM_HLGETTHEMENAMEW, (WPARAM)hTheme, (LPARAM)wszThemeName);


AEM_HLGETTHEMESTACK
___________________

Получает один из стеков темы.

(AEHTHEME)wParam == дескриптор темы или NULL для темы окна по умолчанию.
(int)lParam      == см. определения AEHLE_*.

Возвращаемое значение
 Указатель на структуру HSTACK.

Пример:
BOOL IsCharDelimiter(HWND hWnd, const AECHARINDEX *ciChar, BOOL bPrevious)
{
  AECHARINDEX ciTmp=*ciChar;
  AEHTHEME hTheme;
  HSTACK *hDelimStack;
  AEDELIMITEMW *lpDelimItem; //Исходный элемент стека всегда в Unicode.
  int nChar;

  if (bPrevious)
  {
    if (!SendMessage(hWndEdit, AEM_GETINDEX, AEGI_PREVCHAR, (LPARAM)&ciTmp))
      return TRUE;
  }
  nChar=SendMessage(hWndEdit, AEM_CHARAT, (WPARAM)&ciTmp, 0);
  if (nChar < 0) return TRUE;

  if (hTheme=(AEHTHEME)SendMessage(hWndEdit, AEM_HLGETTHEMEW, 0, (LPARAM)NULL))
  {
    hDelimStack=(HSTACK *)SendMessage(hWndEdit, AEM_HLGETTHEMESTACK, (WPARAM)hTheme, AEHLE_DELIMITER);

    for (lpDelimItem=(AEDELIMITEMW *)hDelimStack->first; lpDelimItem; lpDelimItem=lpDelimItem->next)
    {
      if (lpDelimItem->nDelimiterLen == 1)
      {
        if (lpDelimItem->pDelimiter[0] == nChar)
          return TRUE;
      }
    }
  }
  return FALSE;
}


AEM_HLTHEMEEXISTS
_________________

Проверяет существование темы подсветки.

(AEHTHEME)wParam == дескриптор темы.
lParam           == не используется.

Возвращаемое значение
 TRUE   тема существует.
 FALSE  тема не существует.

Пример:
 SendMessage(hWndEdit, AEM_HLTHEMEEXISTS, (WPARAM)hTheme, 0);


AEM_HLSETTHEME
______________

Активирует тему подсветки.

(AEHTHEME)wParam == дескриптор темы. Если NULL, активная тема будет деактивирована.
(BOOL)lParam     == TRUE   перерисовать окно редактирования.
                    FALSE  не перерисовывать окно редактирования.

Возвращаемое значение
 Ноль.

Пример:
 См. пример AEM_HLCREATETHEMEA или AEM_HLCREATETHEMEW.


AEM_HLDELETETHEME
_________________

Удаляет тему подсветки.

(AEHTHEME)wParam == дескриптор темы или NULL для удаления всех элементов в теме окна по умолчанию.
lParam           == не используется.

Возвращаемое значение
 Ноль.

Пример:
 AEHTHEME hTheme;

 hTheme=(AEHTHEME)SendMessage(hWndEdit, AEM_HLCREATETHEMEW, 0, (LPARAM)L"MyTheme");
 SendMessage(hWndEdit, AEM_HLDELETETHEME, (WPARAM)hTheme, 0);


AEM_HLDELETETHEMEALL
____________________

Удаляет все темы подсветки, созданные с помощью AEM_HLCREATETHEME.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_HLDELETETHEMEALL, 0, 0);


AEM_HLADDDELIMITERA
___________________

Добавляет разделитель в кодировке ANSI в тему подсветки.

(AEHTHEME)wParam       == дескриптор темы или NULL для темы окна по умолчанию.
(AEDELIMITEMA *)lParam == указатель на структуру AEDELIMITEMA.

Возвращаемое значение
 Дескриптор разделителя - AEHDELIMITER (указатель на структуру AEDELIMITEMW).

Пример:
 См. пример AEM_HLCREATETHEMEA.


AEM_HLADDDELIMITERW
___________________

Добавляет разделитель в кодировке Unicode в тему подсветки.

(AEHTHEME)wParam       == дескриптор темы или NULL для темы окна по умолчанию.
(AEDELIMITEMW *)lParam == указатель на структуру AEDELIMITEMW.

Возвращаемое значение
 Дескриптор разделителя - AEHDELIMITER (указатель на структуру AEDELIMITEMW).

Пример:
 См. пример AEM_HLCREATETHEMEW.


AEM_HLDELETEDELIMITER
_____________________

Удаляет разделитель из темы подсветки.

(AEHTHEME)wParam     == дескриптор темы или NULL для темы окна по умолчанию.
(AEHDELIMITER)lParam == дескриптор разделителя. Если NULL, удалить все разделители.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_HLDELETEDELIMITER, (WPARAM)hTheme, (LPARAM)hDelimiter);


AEM_HLADDWORDA
______________

Добавляет слово в кодировке ANSI в тему подсветки.

(AEHTHEME)wParam      == дескриптор темы или NULL для темы окна по умолчанию.
(AEWORDITEMA *)lParam == указатель на структуру AEWORDITEMA.

Возвращаемое значение
 Дескриптор слова - AEHWORD (указатель на структуру AEWORDITEMW).

Пример:
 См. пример AEM_HLCREATETHEMEA.


AEM_HLADDWORDW
______________

Добавляет слово в кодировке Unicode в тему подсветки.

(AEHTHEME)wParam      == дескриптор темы или NULL для темы окна по умолчанию.
(AEWORDITEMW *)lParam == указатель на структуру AEWORDITEMW.

Возвращаемое значение
 Дескриптор слова - AEHWORD (указатель на структуру AEWORDITEMW).

Пример:
 См. пример AEM_HLCREATETHEMEW.


AEM_HLDELETEWORD
________________

Удаляет слово из темы подсветки.

(AEHTHEME)wParam == дескриптор темы или NULL для темы окна по умолчанию.
(AEHWORD)lParam  == дескриптор слова. Если NULL, удалить все слова.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_HLDELETEWORD, (WPARAM)hTheme, (LPARAM)hWord);


AEM_HLADDQUOTEA
_______________

Добавляет кавычку в кодировке ANSI в тему подсветки.

(AEHTHEME)wParam       == дескриптор темы или NULL для темы окна по умолчанию.
(AEQUOTEITEMA *)lParam == указатель на структуру AEQUOTEITEMA.

Возвращаемое значение
 Дескриптор кавычки - AEHQUOTE (указатель на структуру AEQUOTEITEMW).

Пример:
 См. пример AEM_HLCREATETHEMEA.


AEM_HLADDQUOTEW
_______________

Добавляет кавычку в кодировке Unicode в тему подсветки.

(AEHTHEME)wParam       == дескриптор темы или NULL для темы окна по умолчанию.
(AEQUOTEITEMW *)lParam == указатель на структуру AEQUOTEITEMW.

Возвращаемое значение
 Дескриптор кавычки - AEHQUOTE (указатель на структуру AEQUOTEITEMW).

Пример:
 См. пример AEM_HLCREATETHEMEW.


AEM_HLDELETEQUOTE
_________________

Удаляет кавычку из темы подсветки.

(AEHTHEME)wParam == дескриптор темы или NULL для темы окна по умолчанию.
(AEHQUOTE)lParam == дескриптор кавычки. Если NULL, удалить все кавычки.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_HLDELETEQUOTE, (WPARAM)hTheme, (LPARAM)hQuote);


AEM_HLADDMARKTEXTA
__________________

Добавляет пометку текста в кодировке ANSI в тему подсветки.

(AEHTHEME)wParam          == дескриптор темы или NULL для темы окна по умолчанию.
(AEMARKTEXTITEMA *)lParam == указатель на структуру AEMARKTEXTITEMA.

Возвращаемое значение
 Дескриптор пометки текста - AEHMARKTEXT (указатель на структуру AEMARKTEXTITEMW).

Пример:
 См. пример AEM_HLCREATETHEMEA.


AEM_HLADDMARKTEXTW
__________________

Добавляет пометку текста в кодировке Unicode в тему подсветки.

(AEHTHEME)wParam          == дескриптор темы или NULL для темы окна по умолчанию.
(AEMARKTEXTITEMW *)lParam == указатель на структуру AEMARKTEXTITEMW.

Возвращаемое значение
 Дескриптор пометки текста - AEHMARKTEXT (указатель на структуру AEMARKTEXTITEMW).

Пример:
 См. пример AEM_HLCREATETHEMEW.


AEM_HLDELETEMARKTEXT
____________________

Удаляет пометку текста из темы подсветки.

(AEHTHEME)wParam    == дескриптор темы или NULL для темы окна по умолчанию.
(AEHMARKTEXT)lParam == дескриптор пометки текста. Если NULL, удалить все пометки.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_HLDELETEMARKTEXT, (WPARAM)hTheme, (LPARAM)hMark);


AEM_HLADDMARKRANGE
__________________

Добавляет пометку диапазона в кодировке Unicode в тему подсветки.

(AEHTHEME)wParam          == дескриптор темы или NULL для темы окна по умолчанию.
(AEMARKRANGEITEM *)lParam == указатель на структуру AEMARKRANGEITEM.

Возвращаемое значение
 Дескриптор пометки диапазона - AEHMARKRANGE (указатель на структуру AEMARKRANGEITEM).

Пример:
 См. пример AEM_HLCREATETHEMEW.


AEM_HLDELETEMARKRANGE
_____________________

Удаляет пометку диапазона из темы подсветки.

(AEHTHEME)wParam     == дескриптор темы или NULL для темы окна по умолчанию.
(AEHMARKRANGE)lParam == дескриптор пометки диапазона. Если NULL, удалить все пометки.

Возвращаемое значение
 Ноль.

Пример:
 SendMessage(hWndEdit, AEM_HLDELETEMARKRANGE, (WPARAM)hTheme, (LPARAM)hMark);


AEM_HLGETHIGHLIGHT
__________________

Получает информацию о подсветке, предоставленную определенной приложением функцией обратного вызова.

wParam                   == не используется.
(AEGETHIGHLIGHT *)lParam == указатель на структуру AEGETHIGHLIGHT.

Возвращаемое значение
 Ноль.

Пример:
 AEGETHIGHLIGHT aegh;

 aegh.dwCookie=0;
 aegh.lpCallback=GetHighLightCallback;
 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_FIRSTCHAR, (LPARAM)&aegh.crText.ciMin);
 SendMessage(hWndEdit, AEM_GETINDEX, AEGI_LASTCHAR, (LPARAM)&aegh.crText.ciMax);
 aegh.dwFlags=0;
 SendMessage(hWndEdit, AEM_HLGETHIGHLIGHT, 0, (LPARAM)&aegh);

 DWORD CALLBACK GetHighLightCallback(UINT_PTR dwCookie, AECHARRANGE *crAkelRange, CHARRANGE64 *crRichRange, AEHLPAINT *hlp)
 {
   wchar_t wszRange[MAX_PATH];
   wchar_t wszMessage[MAX_PATH];

   lstrcpynW(wszRange, crAkelRange->ciMin.lpLine->wpLine + crAkelRange->ciMin.nCharInLine, crRichRange->cpMax - crRichRange->cpMin + 1);
   wsprintfW(wszMessage, L"[%s]\nFontStyle=%d\nActiveText=0x%06x\nActiveBk=0x%06x", wszRange, hlp->dwFontStyle, hlp->dwActiveText, hlp->dwActiveBk);
   MessageBoxW(NULL, wszMessage, NULL, 0);

   return 0;
 }


AEM_HLGETOPTIONS
________________

Получает опции подсветки.

wParam == не используется.
lParam == не используется.

Возвращаемое значение
 Комбинация значений текущих флагов опций. См. определения AEHLO_*.

Пример:
 SendMessage(hWndEdit, AEM_HLGETOPTIONS, 0, 0);


AEM_HLSETOPTIONS
________________

Устанавливает опции подсветки.

(DWORD)wParam == см. определения AECOOP_*.
(DWORD)lParam == см. определения AEHLO_*.

Возвращаемое значение
 Текущие опции подсветки.

Пример:
 SendMessage(hWndEdit, AEM_HLSETOPTIONS, AECOOP_OR, AEHLO_IGNOREFONTITALIC);

*/


//// Определение UNICODE

#ifndef UNICODE
  #define AES_AKELEDIT AES_AKELEDITA
  #define AES_RICHEDIT20 AES_RICHEDIT20A

  #define TEXTRANGE64 TEXTRANGE64A
  #define FINDTEXTEX64 FINDTEXTEX64A

  #define AEAPPENDTEXT AEAPPENDTEXTA
  #define AEREPLACESEL AEREPLACESELA
  #define AETEXTRANGE AETEXTRANGEA
  #define AEFINDTEXT AEFINDTEXTA
  #define AEDELIMITEM AEDELIMITEMA
  #define AEWORDITEM AEWORDITEMA
  #define AEQUOTEITEM AEQUOTEITEMA
  #define AEMARKTEXTITEM AEMARKTEXTITEMA

  #define AEM_SETTEXT AEM_SETTEXTA
  #define AEM_APPENDTEXT AEM_APPENDTEXTA
  #define AEM_REPLACESEL AEM_REPLACESELA
  #define AEM_GETTEXTRANGE AEM_GETTEXTRANGEA
  #define AEM_FINDTEXT AEM_FINDTEXTA
  #define AEM_ISMATCH AEM_ISMATCHA
  #define AEM_HLCREATETHEME AEM_HLCREATETHEMEA
  #define AEM_HLGETTHEME AEM_HLGETTHEMEA
  #define AEM_HLGETTHEMENAME AEM_HLGETTHEMENAMEA
  #define AEM_HLADDDELIMITER AEM_HLADDDELIMITERA
  #define AEM_HLADDWORD AEM_HLADDWORDA
  #define AEM_HLADDQUOTE AEM_HLADDQUOTEA
  #define AEM_HLADDMARKTEXT AEM_HLADDMARKTEXTA
#else
  #define AES_AKELEDIT AES_AKELEDITW
  #define AES_RICHEDIT20 AES_RICHEDIT20W

  #define TEXTRANGE64 TEXTRANGE64W
  #define FINDTEXTEX64 FINDTEXTEX64W

  #define AEAPPENDTEXT AEAPPENDTEXTW
  #define AEREPLACESEL AEREPLACESELW
  #define AETEXTRANGE AETEXTRANGEW
  #define AEFINDTEXT AEFINDTEXTW
  #define AEDELIMITEM AEDELIMITEMW
  #define AEWORDITEM AEWORDITEMW
  #define AEQUOTEITEM AEQUOTEITEMW
  #define AEMARKTEXTITEM AEMARKTEXTITEMW

  #define AEM_SETTEXT AEM_SETTEXTW
  #define AEM_APPENDTEXT AEM_APPENDTEXTW
  #define AEM_REPLACESEL AEM_REPLACESELW
  #define AEM_GETTEXTRANGE AEM_GETTEXTRANGEW
  #define AEM_FINDTEXT AEM_FINDTEXTW
  #define AEM_ISMATCH AEM_ISMATCHW
  #define AEM_HLCREATETHEME AEM_HLCREATETHEMEW
  #define AEM_HLGETTHEME AEM_HLGETTHEMEW
  #define AEM_HLGETTHEMENAME AEM_HLGETTHEMENAMEW
  #define AEM_HLADDDELIMITER AEM_HLADDDELIMITERW
  #define AEM_HLADDWORD AEM_HLADDWORDW
  #define AEM_HLADDQUOTE AEM_HLADDQUOTEW
  #define AEM_HLADDMARKTEXT AEM_HLADDMARKTEXTW
#endif

#endif //__AKELEDIT_H__


//// Функции AkelEdit

#ifndef AEC_IsSurrogate
  #define AEC_IsSurrogate(c)  ((wchar_t)(c) >= 0xD800 && (wchar_t)(c) <= 0xDFFF)
#endif
#ifndef AEC_IsHighSurrogate
  #define AEC_IsHighSurrogate(c)  ((wchar_t)(c) >= 0xD800 && (wchar_t)(c) <= 0xDBFF)
#endif
#ifndef AEC_IsLowSurrogate
  #define AEC_IsLowSurrogate(c)  ((wchar_t)(c) >= 0xDC00 && (wchar_t)(c) <= 0xDFFF)
#endif
#ifndef AEC_ScalarFromSurrogate
  #define AEC_ScalarFromSurrogate(high, low)  ((((high) - 0xD800) * 0x400) + ((low) - 0xDC00) + 0x10000)
#endif
#ifndef AEC_HighSurrogateFromScalar
  #define AEC_HighSurrogateFromScalar(s)  ((wchar_t)((((s) - 0x10000) / 0x400) + 0xD800))
#endif
#ifndef AEC_LowSurrogateFromScalar
  #define AEC_LowSurrogateFromScalar(s)  ((wchar_t)((((s) - 0x10000) % 0x400) + 0xDC00))
#endif

#ifdef AEC_FUNCTIONS
#define AEC_FUNCTIONS_INCLUDED
  int AEC_CopyChar(wchar_t *wszTarget, DWORD dwTargetSize, const wchar_t *wpSource)
  {
    if (AEC_IsSurrogate(*wpSource))
    {
      if (dwTargetSize >= 2)
      {
        if (AEC_IsHighSurrogate(*wpSource) && AEC_IsLowSurrogate(*(wpSource + 1)))
        {
          if (wszTarget)
          {
            *wszTarget=*wpSource;
            *(wszTarget + 1)=*(wpSource + 1);
          }
          return 2;
        }
      }
    }
    else
    {
      if (wszTarget) *wszTarget=*wpSource;
      return 1;
    }
    return 0;
  }

  int AEC_IndexInc(AECHARINDEX *ciChar)
  {
    if (ciChar->nCharInLine >= 0 &&
        ciChar->nCharInLine + 1 < ciChar->lpLine->nLineLen)
    {
      if (AEC_IsHighSurrogate(ciChar->lpLine->wpLine[ciChar->nCharInLine]) &&
          AEC_IsLowSurrogate(ciChar->lpLine->wpLine[ciChar->nCharInLine + 1]))
      {
        ciChar->nCharInLine+=2;
        return 2;
      }
    }
    ++ciChar->nCharInLine;
    return 1;
  }

  int AEC_IndexDec(AECHARINDEX *ciChar)
  {
    if (ciChar->nCharInLine - 2 >= 0 &&
        ciChar->nCharInLine - 1 < ciChar->lpLine->nLineLen)
    {
      if (AEC_IsLowSurrogate(ciChar->lpLine->wpLine[ciChar->nCharInLine - 1]) &&
          AEC_IsHighSurrogate(ciChar->lpLine->wpLine[ciChar->nCharInLine - 2]))
      {
        ciChar->nCharInLine-=2;
        return 2;
      }
    }
    --ciChar->nCharInLine;
    return 1;
  }

  int AEC_IndexLen(AECHARINDEX *ciChar)
  {
    if (ciChar->nCharInLine >= 0 &&
        ciChar->nCharInLine + 1 < ciChar->lpLine->nLineLen)
    {
      if (AEC_IsHighSurrogate(ciChar->lpLine->wpLine[ciChar->nCharInLine]) &&
          AEC_IsLowSurrogate(ciChar->lpLine->wpLine[ciChar->nCharInLine + 1]))
      {
        return 2;
      }
    }
    return 1;
  }

  int AEC_IndexCompare(const AECHARINDEX *ciChar1, const AECHARINDEX *ciChar2)
  {
    if (ciChar1->nLine == ciChar2->nLine &&
        ciChar1->nCharInLine == ciChar2->nCharInLine)
    {
      return 0;
    }
    if ((ciChar1->nLine < ciChar2->nLine) ||
        (ciChar1->nLine == ciChar2->nLine &&
         ciChar1->nCharInLine < ciChar2->nCharInLine))
    {
      return -1;
    }
    return 1;
  }

  int AEC_IndexCompareEx(const AECHARINDEX *ciChar1, const AECHARINDEX *ciChar2)
  {
    if ((ciChar1->nLine == ciChar2->nLine &&
         ciChar1->nCharInLine == ciChar2->nCharInLine) ||
        (ciChar1->lpLine && ciChar2->lpLine &&
          ((ciChar1->lpLine->next == ciChar2->lpLine &&
            ciChar1->lpLine->nLineBreak == AELB_WRAP &&
            ciChar1->nCharInLine == ciChar1->lpLine->nLineLen &&
            ciChar2->nCharInLine == 0) ||
           (ciChar2->lpLine->next == ciChar1->lpLine &&
            ciChar2->lpLine->nLineBreak == AELB_WRAP &&
            ciChar2->nCharInLine == ciChar2->lpLine->nLineLen &&
            ciChar1->nCharInLine == 0))))
    {
      return 0;
    }
    if ((ciChar1->nLine < ciChar2->nLine) ||
        (ciChar1->nLine == ciChar2->nLine &&
         ciChar1->nCharInLine < ciChar2->nCharInLine))
    {
      return -1;
    }
    return 1;
  }

  AELINEDATA* AEC_NextLine(AECHARINDEX *ciChar)
  {
    if (ciChar->lpLine)
    {
      ciChar->nLine+=1;
      ciChar->lpLine=ciChar->lpLine->next;
      ciChar->nCharInLine=0;
    }
    return ciChar->lpLine;
  }

  AELINEDATA* AEC_PrevLine(AECHARINDEX *ciChar)
  {
    if (ciChar->lpLine)
    {
      ciChar->nLine-=1;
      ciChar->lpLine=ciChar->lpLine->prev;
      if (ciChar->lpLine)
        ciChar->nCharInLine=ciChar->lpLine->nLineLen;
      else
        ciChar->nCharInLine=0;
    }
    return ciChar->lpLine;
  }

  AELINEDATA* AEC_NextLineEx(const AECHARINDEX *ciIn, AECHARINDEX *ciOut)
  {
    AECHARINDEX ciTmp=*ciIn;

    if (AEC_NextLine(&ciTmp))
    {
      *ciOut=ciTmp;
      return ciOut->lpLine;
    }
    else
    {
      *ciOut=*ciIn;
      return NULL;
    }
  }

  AELINEDATA* AEC_PrevLineEx(const AECHARINDEX *ciIn, AECHARINDEX *ciOut)
  {
    AECHARINDEX ciTmp=*ciIn;

    if (AEC_PrevLine(&ciTmp))
    {
      *ciOut=ciTmp;
      return ciOut->lpLine;
    }
    else
    {
      *ciOut=*ciIn;
      return NULL;
    }
  }

  AELINEDATA* AEC_NextChar(AECHARINDEX *ciChar)
  {
    AEC_IndexInc(ciChar);

    if (ciChar->nCharInLine >= ciChar->lpLine->nLineLen)
    {
      if (ciChar->nCharInLine > ciChar->lpLine->nLineLen ||
          ciChar->lpLine->nLineBreak == AELB_WRAP)
      {
        AEC_NextLine(ciChar);
      }
    }
    return ciChar->lpLine;
  }

  AELINEDATA* AEC_PrevChar(AECHARINDEX *ciChar)
  {
    AEC_IndexDec(ciChar);

    if (ciChar->nCharInLine < 0)
    {
      if (AEC_PrevLine(ciChar))
      {
        if (ciChar->lpLine->nLineBreak == AELB_WRAP)
          AEC_IndexDec(ciChar);
      }
    }
    return ciChar->lpLine;
  }

  AELINEDATA* AEC_NextCharEx(const AECHARINDEX *ciIn, AECHARINDEX *ciOut)
  {
    AECHARINDEX ciTmp=*ciIn;

    if (AEC_NextChar(&ciTmp))
    {
      *ciOut=ciTmp;
      return ciOut->lpLine;
    }
    else
    {
      *ciOut=*ciIn;
      return NULL;
    }
  }

  AELINEDATA* AEC_PrevCharEx(const AECHARINDEX *ciIn, AECHARINDEX *ciOut)
  {
    AECHARINDEX ciTmp=*ciIn;

    if (AEC_PrevChar(&ciTmp))
    {
      *ciOut=ciTmp;
      return ciOut->lpLine;
    }
    else
    {
      *ciOut=*ciIn;
      return NULL;
    }
  }

  AELINEDATA* AEC_NextCharInLine(AECHARINDEX *ciChar)
  {
    AEC_IndexInc(ciChar);

    if (ciChar->nCharInLine >= ciChar->lpLine->nLineLen)
    {
      if (ciChar->lpLine->nLineBreak == AELB_WRAP)
        AEC_NextLine(ciChar);
      else
        return NULL;
    }
    return ciChar->lpLine;
  }

  AELINEDATA* AEC_PrevCharInLine(AECHARINDEX *ciChar)
  {
    if (ciChar->nCharInLine == 0)
    {
      if (!ciChar->lpLine->prev || ciChar->lpLine->prev->nLineBreak != AELB_WRAP)
        return NULL;
    }
    AEC_PrevChar(ciChar);
    return ciChar->lpLine;
  }

  AELINEDATA* AEC_NextCharInLineEx(const AECHARINDEX *ciIn, AECHARINDEX *ciOut)
  {
    AECHARINDEX ciTmp=*ciIn;

    if (AEC_NextCharInLine(&ciTmp))
    {
      *ciOut=ciTmp;
      return ciOut->lpLine;
    }
    else
    {
      *ciOut=*ciIn;
      return NULL;
    }
  }

  AELINEDATA* AEC_PrevCharInLineEx(const AECHARINDEX *ciIn, AECHARINDEX *ciOut)
  {
    AECHARINDEX ciTmp=*ciIn;

    if (AEC_PrevCharInLine(&ciTmp))
    {
      *ciOut=ciTmp;
      return ciOut->lpLine;
    }
    else
    {
      *ciOut=*ciIn;
      return NULL;
    }
  }

  AELINEDATA* AEC_ValidCharInLine(AECHARINDEX *ciChar)
  {
    if (ciChar->nCharInLine >= ciChar->lpLine->nLineLen)
    {
      if (ciChar->lpLine->nLineBreak == AELB_WRAP)
        AEC_NextLine(ciChar);
      else
        ciChar->nCharInLine=ciChar->lpLine->nLineLen;
    }
    else if (ciChar->nCharInLine < 0)
    {
      ciChar->nCharInLine=0;
    }
    return ciChar->lpLine;
  }

  int AEC_WrapLineBegin(AECHARINDEX *ciChar)
  {
    int nCount=ciChar->nCharInLine;

    if (ciChar->lpLine)
    {
      while (ciChar->lpLine->prev)
      {
        if (ciChar->lpLine->prev->nLineBreak != AELB_WRAP)
          break;

        --ciChar->nLine;
        ciChar->lpLine=ciChar->lpLine->prev;
        nCount+=ciChar->lpLine->nLineLen;
      }
    }
    ciChar->nCharInLine=0;
    return nCount;
  }

  int AEC_WrapLineEnd(AECHARINDEX *ciChar)
  {
    int nCount=ciChar->lpLine->nLineLen - ciChar->nCharInLine;

    while (ciChar->lpLine)
    {
      if (ciChar->lpLine->nLineBreak != AELB_WRAP)
        break;

      ++ciChar->nLine;
      ciChar->lpLine=ciChar->lpLine->next;
      nCount+=ciChar->lpLine->nLineLen;
    }
    ciChar->nCharInLine=ciChar->lpLine->nLineLen;
    return nCount;
  }

  int AEC_WrapLineBeginEx(const AECHARINDEX *ciIn, AECHARINDEX *ciOut)
  {
    *ciOut=*ciIn;
    return AEC_WrapLineBegin(ciOut);
  }

  int AEC_WrapLineEndEx(const AECHARINDEX *ciIn, AECHARINDEX *ciOut)
  {
    *ciOut=*ciIn;
    return AEC_WrapLineEnd(ciOut);
  }

  int AEC_CharAtIndex(const AECHARINDEX *ciChar)
  {
    int nChar;

    if (ciChar->nCharInLine >= ciChar->lpLine->nLineLen)
    {
      if (ciChar->lpLine->nLineBreak == AELB_WRAP)
      {
        nChar=ciChar->lpLine->next->wpLine[0];
        if (AEC_IsHighSurrogate(nChar))
          nChar=AEC_ScalarFromSurrogate(nChar, ciChar->lpLine->next->wpLine[1]);
        return nChar;
      }
      return -ciChar->lpLine->nLineBreak;
    }
    nChar=ciChar->lpLine->wpLine[ciChar->nCharInLine];
    if (AEC_IsHighSurrogate(nChar))
      nChar=AEC_ScalarFromSurrogate(nChar, ciChar->lpLine->wpLine[ciChar->nCharInLine + 1]);
    return nChar;
  }

  BOOL AEC_IsCharInSelection(const AECHARINDEX *ciChar)
  {
    if (ciChar->lpLine->nSelStart <= ciChar->nCharInLine && ciChar->nCharInLine < ciChar->lpLine->nSelEnd)
      return TRUE;
    return FALSE;
  }

  BOOL AEC_IsFirstCharInLine(const AECHARINDEX *ciChar)
  {
    if (ciChar->nCharInLine == 0 && (!ciChar->lpLine->prev || ciChar->lpLine->prev->nLineBreak != AELB_WRAP))
      return TRUE;
    return FALSE;
  }

  BOOL AEC_IsLastCharInLine(const AECHARINDEX *ciChar)
  {
    if (ciChar->nCharInLine == ciChar->lpLine->nLineLen && ciChar->lpLine->nLineBreak != AELB_WRAP)
      return TRUE;
    return FALSE;
  }

  BOOL AEC_IsFirstCharInFile(const AECHARINDEX *ciChar)
  {
    if (ciChar->nCharInLine == 0 && !ciChar->lpLine->prev)
      return TRUE;
    return FALSE;
  }

  BOOL AEC_IsLastCharInFile(const AECHARINDEX *ciChar)
  {
    if (ciChar->nCharInLine == ciChar->lpLine->nLineLen && !ciChar->lpLine->next)
      return TRUE;
    return FALSE;
  }

  AEFOLD* AEC_NextFold(AEFOLD *lpFold, BOOL bRecursive)
  {
    if (lpFold)
    {
      if (bRecursive)
      {
        if (lpFold->firstChild)
          return lpFold->firstChild;
      }

      do
      {
        if (lpFold->next)
          return lpFold->next;
      }
      while (lpFold=lpFold->parent);
    }
    return lpFold;
  }

  AEFOLD* AEC_PrevFold(AEFOLD *lpFold, BOOL bRecursive)
  {
    if (lpFold)
    {
      if (bRecursive)
      {
        if (lpFold->lastChild)
          return lpFold->lastChild;
      }

      do
      {
        if (lpFold->prev)
          return lpFold->prev;
      }
      while (lpFold=lpFold->parent);
    }
    return lpFold;
  }
#else
  int AEC_CopyChar(wchar_t *wszTarget, DWORD dwTargetSize, const wchar_t *wpSource);
  int AEC_IndexInc(AECHARINDEX *ciChar);
  int AEC_IndexDec(AECHARINDEX *ciChar);
  int AEC_IndexLen(AECHARINDEX *ciChar);
  int AEC_IndexCompare(const AECHARINDEX *ciChar1, const AECHARINDEX *ciChar2);
  int AEC_IndexCompareEx(const AECHARINDEX *ciChar1, const AECHARINDEX *ciChar2);
  AELINEDATA* AEC_NextLine(AECHARINDEX *ciChar);
  AELINEDATA* AEC_PrevLine(AECHARINDEX *ciChar);
  AELINEDATA* AEC_NextLineEx(const AECHARINDEX *ciIn, AECHARINDEX *ciOut);
  AELINEDATA* AEC_PrevLineEx(const AECHARINDEX *ciIn, AECHARINDEX *ciOut);
  AELINEDATA* AEC_NextChar(AECHARINDEX *ciChar);
  AELINEDATA* AEC_PrevChar(AECHARINDEX *ciChar);
  AELINEDATA* AEC_NextCharEx(const AECHARINDEX *ciIn, AECHARINDEX *ciOut);
  AELINEDATA* AEC_PrevCharEx(const AECHARINDEX *ciIn, AECHARINDEX *ciOut);
  AELINEDATA* AEC_NextCharInLine(AECHARINDEX *ciChar);
  AELINEDATA* AEC_PrevCharInLine(AECHARINDEX *ciChar);
  AELINEDATA* AEC_NextCharInLineEx(const AECHARINDEX *ciIn, AECHARINDEX *ciOut);
  AELINEDATA* AEC_PrevCharInLineEx(const AECHARINDEX *ciIn, AECHARINDEX *ciOut);
  AELINEDATA* AEC_ValidCharInLine(AECHARINDEX *ciChar);
  int AEC_WrapLineBegin(AECHARINDEX *ciChar);
  int AEC_WrapLineEnd(AECHARINDEX *ciChar);
  int AEC_WrapLineBeginEx(const AECHARINDEX *ciIn, AECHARINDEX *ciOut);
  int AEC_WrapLineEndEx(const AECHARINDEX *ciIn, AECHARINDEX *ciOut);
  int AEC_CharAtIndex(const AECHARINDEX *ciChar);
  BOOL AEC_IsCharInSelection(const AECHARINDEX *ciChar);
  BOOL AEC_IsFirstCharInLine(const AECHARINDEX *ciChar);
  BOOL AEC_IsLastCharInLine(const AECHARINDEX *ciChar);
  BOOL AEC_IsFirstCharInFile(const AECHARINDEX *ciChar);
  BOOL AEC_IsLastCharInFile(const AECHARINDEX *ciChar);
  AEFOLD* AEC_NextFold(AEFOLD *lpFold, BOOL bRecursive);
  AEFOLD* AEC_PrevFold(AEFOLD *lpFold, BOOL bRecursive);
#endif //AEC_FUNCTIONS
